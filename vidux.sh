#/bin/bash


sudo modprobe -r --first-time -v v4l2loopback
sudo modprobe --first-time -v v4l2loopback

./vidux
