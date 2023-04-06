# CFLAGS = -g -O0
CFLAGS = -O

all: subdir ./bin/dskdecode

.PHONY: clean subdir

clean: 
	rm -rf ./bin

subdir:
	-mkdir ./bin


./bin/dskdecode: src/dskdecode.c src/dskdecode.h
	clang $< -o $@ $(CFLAGS)
