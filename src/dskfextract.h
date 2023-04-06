#pragma once

#include <stdint.h>

#define MAGIC_COMPRESSED 0x5AAA
#define MAGIC_NOCOMPRESSED 0x59AA
#define MAGIC_OLD 0x58AA

#pragma pack(1)
struct dskf_header_s {
    uint16_t magic;
    uint16_t media_type;
    uint16_t sector_size;
    uint8_t cluster_mask;
    uint8_t cluster_shift;
    uint16_t reserved_sectors;
    uint8_t fat_copies;
    uint16_t root_entries;
    uint16_t first_cluster_sector;
    uint16_t clusters_in_image;
    uint8_t sectors_fat;
    uint16_t root_directory_sector;
    uint32_t checksum;
    uint16_t cylinders;
    uint16_t heads;
    uint16_t sectors_track;
    uint8_t filler[4];
    uint16_t sectors_in_image;
    uint16_t comment_offset;
    uint16_t first_sector_offset;     
};
#pragma options align=reset
typedef struct dskf_header_s dskf_header;

