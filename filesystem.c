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

static int read_callback(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) 
{
	(void) fi;
	int index = path_index(path);
	FILE *file_in = fopen(STORE_FILE, "rb");
	int start = index == 0 ? 0 : file_offset_end[index-1];
	fseek(file_in, start + offset, SEEK_SET);
	fread(buf, size, 1, file_in);
	printf("%d\n",file_offset_end[index]-start);
	printf("%s\n", buf);
	fclose(file_in);
	return size;
}

static int fst_utimens (const char *v, const struct timespec tv[2])
{
	return 0;
}

static int fst_getxattr (const char *x, const char *y, char *z, size_t f)
{
	return 0;
}

static int fst_setxattr (const char *x, const char *y, const char *z, size_t l, int f)
{
	return 0;
}

static int fst_listxattr (const char *x, char *y, size_t z)
{
	return 0;
}

