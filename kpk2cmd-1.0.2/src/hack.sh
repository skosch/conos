#!/bin/bash

if [ $1 == -embed ]; then
    echo "== hack.sh substituted for uic so image collection works =="
    uic $*
    cat hack.cpp >> qmake_image_collection.cpp
else
    uic $*
fi
