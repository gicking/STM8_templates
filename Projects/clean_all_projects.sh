#!/bin/bash  

# change to current working directory
cd `dirname $0`

# find all folders 'output' and delete them
find . -name "output" -type d -exec rm -r "{}" \;

# find all Cosmic output folders and delete them
find . -name "Debug" -type d -exec rm -r "{}" \;
find . -name "Release" -type d -exec rm -r "{}" \;

