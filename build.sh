#!/bin/sh

g++ main.cpp capture.cpp `pkg-config --cflags --libs opencv` -o vidux
