1. ```
    docker pull contiker/contiki-ng
    ```

2. ```
    git clone https://github.com/contiki-ng/contiki-ng.git
    cd contiki-ng
    git submodule update --init --recursive 
    ```
3. ```
    cp ../script.sh .
    cp ../gradle-7.4.2-bin.zip .
    ```
4. ```
    cd
    nano .zshrc
    ```
    copy and paste
    ```
    export CNG_PATH=<absolute-path-to-your-contiki-ng>
    alias contiker="docker run --privileged \
    --mount type=bind,source=$CNG_PATH,destination=/home/user/contiki-ng \
    --sysctl net.ipv6.conf.all.disable_ipv6=0 \
    -e DISPLAY=host.docker.internal:0 \
    -ti contiker/contiki-ng"
    ```
5. ```
    brew cask install xquartz
    ```
6. reboot system
7. open xquartz
8. From the XQuartz preferences, in the security tab, make sure Allow connections from network clients is enabled. Restart XQuartz.
9. restart xquartz
10. After restarting XQuartz, you can run netstat -an | grep -F 6000 to find that XQuartz has opened port 6000. This is actually how your docker container will be communicating with XQuartz on the host.
11. In a terminal on the host, run 
```
    xhost +localhost
```
12. run
```
    contiker
    bash script.sh
    . /etc/profile.d/gradle.sh
    cd tools/cooja
    gradle run
```