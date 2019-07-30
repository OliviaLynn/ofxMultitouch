# ofxMultitouch
[openFrameworks](http://openframeworks.cc/) is an open source toolkit for creative coding.

## Introduction
ofxMultitouch is an openFrameworks addon for making the most of multitouch screens running Windows 7 and up, based on Trent Brooks' [ofxWintouchHook](https://github.com/trentbrooks/ofxWinTouchHook).

## Installation
ofMultitouch is made from a fork of ofxWinTouchHook, so there are no dependencies to be installed! Just drop this folder into your `openFrameworks/addons/`.

*(Made and tested on Windows 10, openFrameworks 10.1, and Visual Studio 2017.)*

## Examples

### touchDraw
Touch and drag the screen to produce a randomly colored line displaying the path of your fingertip. Can support at least 10 touches at once (though this number may change based on hardware). Press `SPACE` to clear.