apt-get -y update
apt-get -y upgrade

# libjasper-devを入れるためにリポジトリを追加
add-apt-repository "deb http://security.ubuntu.com/ubuntu bionic-security main"

# 依存パッケージをインストールする
apt-get -y install build-essential checkinstall cmake unzip pkg-config yasm
apt-get -y install git gfortran python3-dev
apt-get -y install libjpeg8-dev libjasper-dev libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine2-dev libv4l-dev
apt-get -y install libjpeg-dev libpng-dev libtiff-dev libtbb-dev
apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libatlas-base-dev libxvidcore-dev libx264-dev libgtk-3-dev

# opencvとopencv_contribのソースをgithubからダウンロードする（zipに圧縮しているものでも可）
#  masterにチェックアウトしているものも見かけるけど、それだと開発中のバージョンになるので、タグから最新のバージョンを指定する
cd /usr/local/src
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout -b 3.4.3 refs/tags/3.4.3
cd ../opencv/
git checkout -b 3.4.3 refs/tags/3.4.3

# ビルドしてインストールする
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

# きちんとインストールされていることを確認する
#   opencvっていうコマンドはないので注意
opencv_version
