#!/bin/sh

g++ -O2 \
    vidux-capture-main.cpp \
    capture/capture.cpp \
    vidux-capture-gui/capture_gui.cpp \
    `pkg-config --cflags --libs opencv`  \
    `pkg-config --cflags --libs gtk+-3.0`  \
    -o vidux_capture


g++ -O2 \
    vidux-selector-main.cpp \
    capture/capture.cpp \
    `pkg-config --cflags --libs opencv`  \
    `pkg-config --cflags --libs gtk+-3.0`  \
    -o vidux_selector
