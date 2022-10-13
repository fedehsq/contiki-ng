1. ```
    docker pull contiker/contiki-ng
    ```

2. ```
    git submodule update --init --recursive 
    ```
3. ```
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
4. ```
    brew cask install xquartz
    ```
5. reboot system
6. open xquartz
7. From the XQuartz preferences, in the security tab, make sure Allow 
connections from network clients is enabled. Restart XQuartz.
8. restart xquartz
9. After restarting XQuartz, you can run netstat -an | grep -F 6000 to 
find that XQuartz has opened port 6000. This is actually how your docker container will be communicating with XQuartz on the host.
10. In a terminal on the host, run 
```
    xhost +localhost
```
11. run
```
    contiker
    sudo -s
    bash script.sh
    . /etc/profile.d/gradle.sh
    bash mosquitto-v1.5.sh
    cd tools/cooja
    gradle run
```
12. 
```
    mosquitto -v
    cd tools/cooja
    gradle run (ant run)
    load simulation file MQTT.csc
    add node 1 as socket server
    start simulation
```
12. 
```
    docker exec -it <container-id> /bin/bash
    cd examples/mqtt-project/coap-server
    make TARGET=cooja connect-router-cooja
```
