#! /usr/bin/env bash

USER_ERR=2

check() {
	prog=$1
	if ! command -v $prog >/dev/null; then
		echo -e "\e[31mFatal:\e[0m Install $prog to run this script!"
		exit $USER_ERR
	fi
}

check magick

src=bg-red.png

if (( $# > 0 )); then
	src=bg-$1.png
fi

magick $src bg.ppm
