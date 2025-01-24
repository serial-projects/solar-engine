#!/bin/sh
do_everything() {
	# Set to ninja so we can have good stuff:

	# NOTE: some times you want to use ASAN and some times you want to use valgrind.

	cmake . -G Ninja					\
		-DCMAKE_BUILD_TYPE=Debug		\
		-DPROJECT_USE_ASAN=yes

	# Do cleanup & do not use cache:
	ninja -v clean
	ninja -v -j$(nproc)
}
do_everything
