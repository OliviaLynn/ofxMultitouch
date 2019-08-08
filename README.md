# ofxMultitouch
[openFrameworks](http://openframeworks.cc/) is an open source toolkit for creative coding.

## Introduction
ofxMultitouch is an openFrameworks addon for making the most of multitouch screens that run Windows 7, 8, and 10, by intercepting and responding to Windows messages for touch and mouse events.

## Installation
ofMultitouch is made from a fork of Trent Brooks' [ofxWinTouchHook](https://github.com/trentbrooks/ofxWinTouchHook), so there are no dependencies to be installed!

**Installing ofxMultitouch:**
- Download from GitHub
- Unzip the folder and rename it from `ofxMultitouch-master` to `ofxMultitouch`
- Place it in your `openFrameworks/addons` folder.

**Running examples:**
- Import the example into the project generator
- Create a new project
- Open the project file in your IDE

*(Made and tested on Windows 10, openFrameworks 9.8 and 10.1, and Visual Studio 2017 - feel free to reach out if you run into problems in other environments)*

## Examples

### touchCircles
![gif](https://i.imgur.com/csCVV4N.gif)
- Displays circles under each active touch.
- Top left of screen displays current framerate.
- A simple example to make sure current install & hardware are working properly.

### touchDraw
![gif](https://i.imgur.com/ji1KP8n.gif)
- Touch and drag the screen to produce a randomly colored line displaying the path of your fingertip. Can support at least 10 touches at once (though this number may change based on hardware). 
- Use the mouse to pan.
- Press `0` to reset panning.
- Press `SPACE` to clear canvas.
- Top left of screen displays current framerate.

### imageGestures
![gif](https://i.imgur.com/hsXeJLF.gif)
- Use two fingers to pan and zoom an image.
- Image is confined to screen space and cannot be translated past the edges.
- Press `SPACE` to reset transformations.


## How does it work?
ofxMultitouch runs by watching Windows Messages, which can be read about at the [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues).

### Hooks
"A [hook](https://docs.microsoft.com/en-us/windows/win32/winmsg/about-hooks) is a mechanism by which an application can intercept events, such as messages, mouse actions, and keystrokes. A function that intercepts a particular type of event is known as a hook procedure. A hook procedure can act on each event it receives, and then modify or discard the event."

The specific messages we look at include:
- mouse messages `WM_LBUTTONDOWN` and `WM_LBUTTONUP`
- touch messages `WM_POINTERDOWN`, `WM_POINTERUPDATE`, and `WM_POINTERUP`

These touch messages control most of our touch functionality⁠—as you might expect, they correspond to touchDown-, touchMoved-, and touchUp-style functions, respectively. 

### A Single Touch
However, Windows typically treats a single touch event as a mouse event. This allows a touch screen user to interact with programs as expected: dragging windows, clicking buttons, etc. Unfortunately, this means a single touch creates both touch *and* mouse messages. This can get confusing for us!

For example, we use the mouse to pan in `example-touchDraw`. A single touch would end up calling the touch messages we use to draw, but it would *also* call the mouse messages we use to pan. This ends up with some pretty uncomfortable functionality; so, we use a hook to intercept our `WM_LBUTTONDOWN`/`WM_LBUTTONUP` messages, check a flag to see if they originated from a touch, and pass on an event to help us differentiate a moving touch from a mouse drag.
