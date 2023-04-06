# DSKF floppy disk image extractor

The DSKF format was created by IBM to distribute floppy images in CD-ROMs. The user was expected to use the MS-DOS LOADDSKF.EXE program to read those image files and write them into physical diskettes. Nowadays the emulator user must boot up a VM and create an empty image to obtain VM-usable floppy images from DSKF files.

This is a small utility which allows to do the conversion from any Unix-like operating system, like Linux or MacOS. 

## Using the utility

Just issue the command:

```
dskfextract -i input_dskf_image -o output-raw_image
```

## Building the utility

This program doesn't have any dependences out of a working C compiler and a POSIX-ish environment. Just change to the main directory and issue:

```
make
```

You should get the executable built in the ```./bin``` subdirectory.

## Acknowledgements

The information about the DSKF header structure was obtained from [this web page](http://justsolve.archiveteam.org/wiki/LoadDskF/SaveDskF). Many thanks for providing this information.

Also, the teams building and maintaining emulators, like [DosBox](dosbox), [DosBox-X](https://dosbox-x.com), [86Box](https://86box.net) and [PCem](https://pcem-emulator.co.uk) are much more are **real heroes**. Keep up the good work!
