#!/bin/bash
g++ main.cpp camera.cpp cylinder.cpp light.cpp plane.cpp sphere.cpp vec3.cpp world.cpp -I include -O2 -L/usr/X11R6/lib -lm -lpthread -lX11