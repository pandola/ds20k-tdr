#!/bin/sh

if [ $# -lt 3 ]; then
  echo "usage $0 pattern1 pattern2 folder [file_extension]"
  exit 1
fi

ext=${4:-tex}

for i in `find $3 -name \*.$ext`; do
    echo $i
    echo sed -i.bck s,\\\\$1,\\\\$2,g $i
    sed -i.bck s,\\\\$1,\\\\$2,g $i
done