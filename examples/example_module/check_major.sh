#!/bin/bash


while [ 1 ]; do
    sudo rmmod chirisco
    sudo insmod chirisco.ko
    journalctl -n 100 | grep mknod
done
