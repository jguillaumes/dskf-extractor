# CFLAGS = -g -O0
CFLAGS = -O


all: subdir ./bin/dskfextract

.PHONY: clean subdir

clean: 
	-rm -rf ./bin 2> /dev/null
	-find . -name "*.dSYM" -type d -exec rm -rf {} \;

subdir:
	-@mkdir -p ./bin 2> /dev/null


./bin/dskfextract: src/dskfextract.c src/dskfextract.h
	$(CC) $< -o $@ $(CFLAGS)
