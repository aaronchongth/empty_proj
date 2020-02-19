#!/bin/bash

sudo apt-get update
sudo apt-get upgrade

sudo apt-get install \
  gcc cmake make wget \
  build-essentials \
  vim git unzip \
  snapd openvpn \
  openssh-client openssh-server \
  python3-vcstool \
  libeigen3-dev \
  -y

# vscodium
wget -qO - https://gitlab.com/paulcarroty/vscodium-deb-rpm-repo/raw/master/pub.gpg | sudo apt-key add - 

echo 'deb https://gitlab.com/paulcarroty/vscodium-deb-rpm-repo/raw/repos/debs/ vscodium main' | sudo tee --append /etc/apt/sources.list.d/vscodium.list

sudo apt update && sudo apt install codium -y

# gimp 2.10
sudo add-apt-repository ppa:otto-kesselgulasch/gimp
sudo apt update && sudo apt install gimp -y

# typora
wget -qO - https://typora.io/linux/public-key.asc | sudo apt-key add -
sudo add-apt-repository 'deb https://typora.io/linux ./'
sudo apt update && sudo apt install typora -y

