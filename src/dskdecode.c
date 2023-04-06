#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <getopt.h>

#include "dskdecode.h"


void syntax() {
    fprintf(stderr, "Usage: dskdecode infile outfile\n");
}

int main(int argc, char **argv) {
    char *infilename=NULL, *outfilename=NULL;
    FILE *dskf,*raw;
    int c;
    int i,num_bytes;
    char header[40];
    long dsk_offset;
    dskf_header *hdrptr;
    int sectors_in_file=0;
    int sectors_in_disk=0;
    int sector_size=0;
    int disk_size, infile_size;
    char *dataBuffer;

    while((c=getopt(argc,argv,"i:o:")) != -1) {
        switch(c) {
            case 'i':
                infilename = optarg;
                break;
            case 'o':
                outfilename = optarg;
                break;
            case '?':
            default:
                syntax();
                exit(32);
        }
    }

    if (infilename == NULL || outfilename == NULL || optind != argc) {
        syntax();
        exit(32);
    }

    printf("Input DSKF image : %s\n", infilename);
    printf("Output raw image : %s\n", outfilename);

    dskf = fopen(infilename, "r");
    if (dskf == NULL) {
        perror("Error opening input image");
        exit(16);
    }

    num_bytes = fread(header, 1, 40, dskf);
    if (num_bytes != 40) {
        fprintf(stderr, "The file doesn't contain a DSKF file: it's too short!\n");
        fclose(dskf);
        fclose(raw);
        exit(8);
    }  
    hdrptr = (void * ) header;

    switch (hdrptr->magic) {
        case MAGIC_NOCOMPRESSED:
            printf("Non compressed image\n");
            break;
        case MAGIC_OLD:
            printf("Old non compressed image\n");
            break;
        case MAGIC_COMPRESSED:
            fprintf(stderr, "Error: The DSKF image is compressed. Compressed images are not supported.\n");
            fclose(dskf);
            exit(8);
        default:
            fprintf(stderr, "Error: Unknown image type, or not an image at all.\n");
            fclose(dskf);
            exit(8);
    }

    sectors_in_file = hdrptr->sectors_in_image;
    sectors_in_disk = hdrptr->heads * hdrptr->cylinders * hdrptr->sectors_track;

    printf("CHS: %d/%d/%d\n", hdrptr->cylinders, hdrptr->heads, hdrptr->sectors_track);
    printf("Total sectors in disk: %d\n", sectors_in_disk);
    printf("Total sectors in file: %d\n", sectors_in_file);

    disk_size = sectors_in_disk * hdrptr->sector_size;
    printf("Total disk size (bytes): %d\n", disk_size);
    dataBuffer = malloc(disk_size);
    if (dataBuffer == NULL) {
        fprintf(stderr, "Error: not enough memory to allocate the buffer.\n");
        fclose(dskf);
        exit(8);
    }
    memset(dataBuffer, 0, disk_size);

    dsk_offset = hdrptr->magic == MAGIC_OLD ? 0x200 : hdrptr->first_sector_offset;
    if (0 != fseek(dskf, dsk_offset, SEEK_SET)) {
        perror("Error:");
        fclose(dskf);
        free(dataBuffer);
        exit(8);
    }

    if ((num_bytes=fread(dataBuffer, hdrptr->sector_size, sectors_in_file, dskf)) != sectors_in_file) {
        perror("Error reading the image file:");
        fclose(dskf);
        free(dataBuffer);
        exit(8);
    }

    raw = fopen(outfilename, "w");
    if (dskf == NULL) {
        perror("Error opening output image");
        fclose(dskf);
        exit(16);
    }

    if (fwrite(dataBuffer, hdrptr->sector_size, sectors_in_disk, raw) != sectors_in_disk) {
        perror("Error reading the raw image file:");
        fclose(dskf);
        fclose(raw);
        free(dataBuffer);
        exit(8);
    }

    fclose(dskf);
    fclose(raw);
    free(dataBuffer);
    printf("Extraction completed.\n");
    exit(0);
}
