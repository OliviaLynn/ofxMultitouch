#pragma once

#include "ofMain.h"
#ifdef TARGET_LINUX
#include <libinput.h>
#include <thread>

#define MAXTOUCH 10

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
    ofPoint lastTouch_[MAXTOUCH];

    static int open_restricted(const char *path, int flags, void *user_data);
    static void close_restricted(int fd, void *user_data);

    void eventHandler();
};

#endif // TARGET_LINUX