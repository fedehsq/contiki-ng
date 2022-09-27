#!/bin/bash
sudo touch /etc/profile.d/gradle.sh
sudo unzip -d /opt/gradle ./gradle-7.4.2-bin.zip
echo 'export GRADLE_HOME=/opt/gradle/gradle-7.4.2
export PATH=${GRADLE_HOME}/bin:${PATH}' | sudo tee -a /etc/profile.d/gradle.sh
echo ". /etc/profile.d/gradle.sh"
gradle