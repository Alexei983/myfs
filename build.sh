#!/bin/sh
CC=gcc
if [ -x $CC ] 
then
	CC=gcc
fi
$CC fuse_main_v2.c -o myfs `pkg-config fuse3 --cflags --libs`
