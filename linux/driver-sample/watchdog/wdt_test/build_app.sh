#!/bin/bash
arm-linux-androideabi-gcc -pie -fPIE -o wdt_test wdt_test.c
chmod 777 ./wdt_test


