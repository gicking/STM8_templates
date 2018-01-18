#!/bin/bash 

# change to current working directory
cd `dirname $0`

# recursively make all python scripts executable
find . -name "*.py" -exec chmod u+x {} \;

