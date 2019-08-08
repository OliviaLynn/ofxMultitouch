# ofxMultitouch
[openFrameworks](http://openframeworks.cc/) is an open source toolkit for creative coding.

## Introduction
ofxMultitouch is an openFrameworks addon for making the most of multitouch screens running Windows 7, 8, and 10, based on Trent Brooks' [ofxWintouchHook](https://github.com/trentbrooks/ofxWinTouchHook).

## Installation
ofMultitouch is made from a fork of ofxWinTouchHook, so there are no dependencies to be installed! 

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
- Displays circles under each active touch.
- A simple example to make sure your install and hardware works properly.

### touchDraw
![gif](https://i.imgur.com/ji1KP8n.gif)
- Touch and drag the screen to produce a randomly colored line displaying the path of your fingertip. Can support at least 10 touches at once (though this number may change based on hardware). 
- Use the mouse to pan.
- Press `0` to reset panning.
- Press `SPACE` to clear canvas.
- Top left of screen displays current framerate.


### imageGestures
- Pan and zoom
- *TODO*

### selectionContour
- *TODO*

## How does it work?
ofxMultitouch runs by watching Windows Messages, which you can read about at the [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues).
*To be continued*

*To discuss:*
- *How hooks work*
- *How we're intercepting mouse messages and filtering based on actual mouse vs single touch commands*
