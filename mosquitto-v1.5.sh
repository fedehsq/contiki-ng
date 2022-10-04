#!/bin/bash

# remove mosquitto
sudo apt-get purge *mosquitto*
# hold mosquitto packages
sudo apt-mark hold mosquitto libmosquitto1 mosquitto-clients
# required build dependency
sudo apt-get install uuid-dev
# needed for mosquitto_passwd
sudo apt-get install libssl-dev
# needed for manpages
sudo apt-get install docbook-xsl xsltproc
# needed for systemd
sudo apt-get install libsystemd-dev
# needed for websockets
sudo apt-get install libwebsockets-dev

wget https://github.com/eclipse/mosquitto/archive/v1.5.tar.gz
tar xf v1.5.tar.gz
cd mosquitto-1.5
nano config.mk
# set WITH_SYSTEMD -> yes
# set WITH_WEBSOCKETS -> yes
# set WITH_STATIC_LIBRARIES -> yes
# at bottom, set prefix=/usr

# build once, then uninstall to purge existing install
make
sudo make uninstall
sudo ldconfig

# rebuild
make reallyclean
make
sudo make install
sudo ldconfig

# test
mosquitto --help
mosquitto_sub --help
mosquitto_pub --help

# create mosquitto user
sudo useradd -r -M -s /usr/sbin/nologin mosquitto

# create a log dir
sudo mkdir /var/log/mosquitto
sudo chown -R mosquitto:mosquitto /var/log/mosquitto

# (optional) create a persist dir
sudo mkdir /var/lib/mosquitto
sudo chown -R mosquitto:mosquitto /var/lib/mosquitto

# create + edit config
sudo cp /etc/mosquitto/mosquitto.conf.example /etc/mosquitto/mosquitto.conf
sudo nano /etc/mosquitto/mosquitto.conf
# uncomment mosquitto user
# find logging section and add:
# log_dest file /var/log/mosquitto/broker.log

# install service
sudo cp service/systemd/mosquitto.service.notify /lib/systemd/system/mosquitto.service
sudo systemctl daemon-reload
sudo systemctl enable mosquitto.service
sudo systemctl reload-or-restart mosquitto.service
