#!/bin/sh

LED=`cat /sys/class/leds/blue5g9\:red\:phone/brightness`

if [ $LED -eq 0 ]; then
    mount /dev/sda1 /mnt
    mpc -q update
    mpc -q clear
    echo 255 > /sys/class/leds/blue5g9\:red\:phone/brightness
    while [ -n "$(mpc | grep Updating)" ] ; do sleep 1 ; done
    mpc -q add /
    mpc -q play 0
    mpc -q play 1
else
    mpc -q clear
    mpc -q load radiostations > /dev/null
    mpc -q play
    umount /mnt
    echo 0 > /sys/class/leds/blue5g9\:red\:phone/brightness
fi

