#!/bin/sh

g++ main.cpp `pkg-config --cflags --libs opencv` -o vidux

