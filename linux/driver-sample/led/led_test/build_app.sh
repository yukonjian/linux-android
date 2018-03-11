#!/bin/bash
arm-linux-androideabi-gcc -pie -fPIE -o led_test led_test.c
chmod 777 ./led_test


