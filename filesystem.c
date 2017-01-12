#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#define NAME_LENGTH 255
static int *file_offset_end;
static char **file_name;
static int *file_size;
static int file_count = 0;
#define STORE_FILE "/home/alex/Desktop/PMVS4/filesave"
#define BUF_FILE "/home/alex/Desktop/PMVS4/buffile"
#define _FILE_OFFSET_BITS 64

struct file_info 
{
	char file_name[NAME_LENGTH];
	int file_size;
	int file_offset;
};

static int path_index(const char* path)
{
	int i  = 0;
	for (i = 0; i < file_count; i++) {
		if (strcmp(file_name[i], path)==0) {
			return i;
		}
	}
	return -1;
}


