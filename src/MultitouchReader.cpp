#include <libinput.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <thread> 

#include "MultitouchReader.h"
#ifdef TARGET_LINUX
/*
running as root:
sudo ./multitouch_reader

This also may work but is untested: On many Linux systems, including Ubuntu, there is an input group that provides access to input devices. You can add your user to this group to grant them permission to access input devices via: sudo usermod -aG input your_username
*/
MultitouchReader::MultitouchReader() : li_(nullptr), udev_(nullptr) {

    // for (int i = 0; i < MAXTOUCH; i++) {
    //     lastTouch_[i] = ofPoint(-1000,-1000);
    // }
}

MultitouchReader::~MultitouchReader() {
    stopMultitouch();

    if (udev_) {
        udev_unref(udev_);
    }
}

static int open_restricted(const char *path, int flags, void *user_data)
{
        int fd = open(path, flags);
        return fd < 0 ? -errno : fd;
}
 
static void close_restricted(int fd, void *user_data)
{
        close(fd);
}
 
 const static struct libinput_interface interface = {
        .open_restricted = open_restricted,
        .close_restricted = close_restricted,
};

 int MultitouchReader::startMultitouch()
 {
     if (!running_)
     {
         // Open the libinput context
         udev_ = udev_new();
         if (!udev_)
         {
             perror("Failed to create udev context");
             return 1;
         }

         li_ = libinput_udev_create_context(&interface, NULL, udev_);
         if (!li_)
         {
             perror("Failed to create libinput context");
             udev_unref(udev_);
             return 1;
         }

         libinput_udev_assign_seat(li_, "seat0");
         if (!li_)
         {
             perror("Failed to create libinput context");
             udev_unref(udev_);
             return 1;
         }

         // Create a separate thread for event handling
         event_thread_ = std::thread(&MultitouchReader::eventHandler, this); // Pass the current instance

         running_ = true;
         return 0;
     }
     else
     {
         // already running
         return 1;
     }
 }

void MultitouchReader::stopMultitouch() {
    exit_ = true;

    if (running_)
    {
        if (event_thread_.joinable())
        {
            // Clean up and close the libinput context in the event handler thread
            event_thread_.join();
        }

        if (li_)
        {
            // cout << "MultitouchReader::stopMultitouch: li_ = " << ofToString(li_) << endl;
            libinput_unref(li_);
        }

        if (udev_)
        {
            udev_unref(udev_);
        }

        running_ = false;
    }
}

// Function to handle libinput events in a separate thread
void MultitouchReader::eventHandler()
{
    while (!exit_)
    {
        struct libinput_event *ev;
        libinput_dispatch(li_);

        while ((ev = libinput_get_event(li_)) && !exit_)
        {
            libinput_event_type evType = libinput_event_get_type(ev);

            if (evType == LIBINPUT_EVENT_TOUCH_DOWN)
            {
                // Touch down event
                struct libinput_event_touch *tev = libinput_event_get_touch_event(ev);
                if (tev)
                {
                    int touch_id = libinput_event_touch_get_slot(tev);
                    double x = libinput_event_touch_get_x_transformed(tev, 1.0);
                    double y = libinput_event_touch_get_y_transformed(tev, 1.0);
                    // printf("Touch Down - ID: %d, X: %f, Y: %f\n", touch_id, x, y);

                    ofPoint p = normalizedScreenToWindowCoords(ofPoint(x, y));
                    lastTouch_[touch_id] = p;
                    ofEvents().notifyTouchDown(p.x, p.y, touch_id);
                }
            }
            else if (evType == LIBINPUT_EVENT_TOUCH_UP)
            {
                // Touch up event
                struct libinput_event_touch *tev = libinput_event_get_touch_event(ev);
                if (tev)
                {
                    int touch_id = libinput_event_touch_get_slot(tev);
                    // printf("Touch Up - ID: %d\n", touch_id);

                    ofEvents().notifyTouchUp(lastTouch_[touch_id].x, lastTouch_[touch_id].y, touch_id);
                }
            }
            else if (evType == LIBINPUT_EVENT_TOUCH_MOTION)
            {
                // Touch motion event
                struct libinput_event_touch *tev = libinput_event_get_touch_event(ev);
                if (tev)
                {
                    int touch_id = libinput_event_touch_get_slot(tev);
                    double x = libinput_event_touch_get_x_transformed(tev, 1.0);
                    double y = libinput_event_touch_get_y_transformed(tev, 1.0);
                    // printf("Touch Motion - ID: %d, X: %f, Y: %f\n", touch_id, x, y);

                    ofPoint p = normalizedScreenToWindowCoords(ofPoint(x, y));
                    lastTouch_[touch_id] = p;
                    ofEvents().notifyTouchMoved(p.x, p.y, touch_id);
                }
            }
            else if (evType == LIBINPUT_EVENT_TOUCH_CANCEL)
            {
                // Touch cancel event
                struct libinput_event_touch *tev = libinput_event_get_touch_event(ev);
                if (tev)
                {
                    int touch_id = libinput_event_touch_get_slot(tev);
                    // printf("Touch Cancel - ID: %d\n", touch_id);
                }
            }

            libinput_event_destroy(ev);
        }
        // Introduce a small delay to avoid high CPU usage
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}

ofPoint 
MultitouchReader::normalizedScreenToWindowCoords(ofPoint sc) {

    sc.x *= ofGetScreenWidth();
    sc.y *= ofGetScreenHeight();
    
    // Calculate the window's origin (top-left corner of the window) in screen coordinates
    int windowOriginXScreen = ofGetWindowPositionX();
    int windowOriginYScreen = ofGetWindowPositionY();

    // Calculate the window coordinates
    int windowX = static_cast<int>(sc.x - windowOriginXScreen);
    int windowY = static_cast<int>(sc.y - windowOriginYScreen);

    // cout << "MultitouchReader::normalizedScreenToWindowCoords: norm screen point [" << ofToString(sc.x) << "," << ofToString(sc.y) << "] = window [" << ofToString(windowX) << "," << ofToString(windowY) << endl; 
    return ofPoint(windowX, windowY);
}
#endif