#!/bin/sh

if [ $# -lt 2 ]; then
    echo "usage $0 pattern1 pattern2"
    exit 1
fi

./sed.sh $1 $2 /Users/cris/Dropbox/Bibliography def
./sed.sh $1 $2 /Users/cris/Dropbox/Papers/PEReports/CryogenicFrontEnd tex
./sed.sh $1 $2 /Users/cris/Dropbox/Papers/PEReports/RGB-HD tex
./sed.sh $1 $2 /Users/cris/Dropbox/Papers/PEReports/NUV-HD tex
./sed.sh $1 $2 /Users/cris/Dropbox/DS-20k-YB/YB-source-dev tex
