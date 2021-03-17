#!/bin/bash

sudo apt update && sudo apt upgrade -y

sudo apt-get install \
  gcc \
  cmake \
  make \
  wget \
  build-essentials \
  vim \
  git \
  unzip \
  snapd \
  openvpn \
  openssh-client \
  openssh-server \
  python3-vcstool \
  libeigen3-dev \
  htop \
  ffmpeg \
  -y

# Setup ccache
sudo apt install ccache -y
sudo /usr/sbin/update-ccache-symlinks
echo 'export PATH="/usr/lib/ccache:$PATH"' | tee -a ~/.bashrc
source ~/.bashrc

# gimp 2.10
sudo add-apt-repository ppa:otto-kesselgulasch/gimp
sudo apt update && sudo apt install gimp -y

# typora
wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
sudo add-apt-repository 'deb https://typora.io/linux ./'
sudo apt update && sudo apt install typora -y

