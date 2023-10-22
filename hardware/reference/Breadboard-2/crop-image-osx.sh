#!/bin/bash

# sips - scriptable image processing system
# -Z 1600 resizes the entire image to a max of 1600 on a side.
# --cropOffset is the upper left corner of the crop on the resized image.
# -c is the height and width of the cropped area on the resized image.

sips -Z 1600 --cropOffset 200 480 -c 910 640 Breadboard-2.jpg
