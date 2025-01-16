#!/bin/sh
do_everything() {
	# Set to ninja so we can have good stuff:
	cmake . -G Ninja -DCMAKE_BUILD_TYPE=Debug

	# Do cleanup & do not use cache:
	ninja -v clean
	ninja -v -j$(nproc)
}
do_everything
