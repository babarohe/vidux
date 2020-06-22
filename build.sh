#!/bin/sh

g++ -O2 \
    main.cpp \
    capture.cpp \
    gui_main.cpp \
    `pkg-config --cflags --libs opencv`  \
    `pkg-config --cflags --libs gtk+-3.0`  \
    -o vidux


    # lib/v4l2loopback_cpp/v4l2sink.cpp \
