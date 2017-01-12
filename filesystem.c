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

static int getattr_callback(const char *path, struct stat *stbuf) 
{
	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
		return 0;
	} else {
		int index = path_index(path);
		if(index == -1) {
			return -ENOENT;
		}
		stbuf->st_mode = S_IFREG | 0777;
		stbuf->st_nlink = 1;
		int start = index == 0 ? 0 : file_offset_end[index-1];
		int size = file_offset_end[index]-start;
		printf("%d\n", size);
		stbuf->st_size = file_size[index];
		return 0;
	}
	return -ENOENT;
}

static int open_callback(const char *path, struct fuse_file_info *fi) 
{
  	int index = path_index(path);
	if (index == -1)
		return -ENOENT;
	return 0;
}
