#pragma once

#include "ofMain.h"
#ifdef TARGET_LINUX
#include <libinput.h>
#include <thread>

class MultitouchReader {
public:
    MultitouchReader();
    ~MultitouchReader();

    int startMultitouch();
    void stopMultitouch();

    ofPoint normalizedScreenToWindowCoords(ofPoint sc);

private:
    struct libinput *li_;
    struct udev *udev_;
    std::thread event_thread_;
    bool exit_ = false, running_ = false;
    std::map<int, ofPoint> lastTouch_;

    static int open_restricted(const char *path, int flags, void *user_data);
    static void close_restricted(int fd, void *user_data);

    void eventHandler();
};

#endif // TARGET_LINUX