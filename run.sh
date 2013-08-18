#!/bin/bash

if [ ! -f "build/NaoFinder" ] ; then
    echo
    echo "###################################################################"
    echo "Be sure to have yo have Qt >= 4.7 dev packages and qmake installed!"
    echo "###################################################################"
    echo
    mkdir build
    cd build
    qmake-qt4 -makefile -o Makefile ../NaoFinder.pro
    make
    cd ..
fi

cd build
make
exec ./NaoFinder
