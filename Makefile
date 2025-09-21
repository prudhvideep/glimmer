CC := clang++
CSRC := $(wildcard *.cpp)
CFLAGS := -Wall -Wextra -pedantic -g
.PHONY = run run-profile debug build build-profile glimmer clean

run: clean build
	./glimmer

run-profile: clean build-profile
	time ./glimmer

debug: build-debug
	./glimmer

build:
	$(CC) $(CSRC) -o glimmer

build-profile:
	$(CC) $(CSRC) -O3 -Wno-narrowing -o glimmer

build-debug:
	$(CC) $(CFLAGS) $(CSRC) -o glimmer	

clean:
	rm -rf glimmer *.tga