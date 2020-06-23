# video-mux


## Required

- OpenCV 3.4
- Gtk+3.x
- v4l2loopback-dkms


## Supported environment

Ubuntu: Ubuntu 18.04
macOS: macOS Catalina

## Install OpenCV for Ubuntu

```bash
apt-get -y update
apt-get -y upgrade

add-apt-repository "deb http://security.ubuntu.com/ubuntu bionic-security main"

apt-get -y install build-essential checkinstall cmake unzip pkg-config yasm
apt-get -y install git gfortran python3-dev
apt-get -y install libjpeg8-dev libjasper-dev libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine2-dev libv4l-dev
apt-get -y install libjpeg-dev libpng-dev libtiff-dev libtbb-dev
apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libatlas-base-dev libxvidcore-dev libx264-dev libgtk-3-dev

cd /usr/local/src
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout -b 3.4.3 refs/tags/3.4.3
cd ../opencv/
git checkout -b 3.4.3 refs/tags/3.4.3

mkdir build
cd build
# cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
cmake -D CMAKE_BUILD_TYPE=Release \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D WITH_TBB=ON \
-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
make -j7
make install
echo /usr/local/lib > /etc/ld.so.conf.d/opencv.conf
ldconfig -v
```

## Install Qt5 for Ubuntu

```bash
sudo apt-get -y install libfontconfig1
sudo apt-get -y install mesa-common-dev
sudo apt-get -y install libglu1-mesa-dev

wget http://download.qt.io/official_releases/qt/5.14/5.14.2/qt-opensource-linux-x64-5.14.2.run
chmod +x qt-opensource-linux-x64-5.14.2.run
./qt-opensource-linux-x64-5.14.2.run

# http://download.qt.io/official_releases/qt/5.14/5.14.2/qt-opensource-mac-x64-5.14.2.dmg

```

https://wiki.qt.io/Install_Qt_5_on_Ubuntu


## Install gtkmm-3.0

```bash
# Ubuntu
sudo apt install -y glade
sudo apt install -y libgtk-3-dev
sudo get install -y libgtkmm-3.0-dev

# Mac
brew install gtkmm3

```


## Install v4l2 loopback

```bash
sudo apt install -y v4l2loopback-dkms
```

## Install OpenCV for macOS

```bash
brew install -v cmake
brew install pkg-config
brew tap homebrew/science
brew install opencv
```
