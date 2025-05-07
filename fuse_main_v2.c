#define FUSE_USE_VERSION 30
#define MAX_FILES 100

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fuse3/fuse.h>

typedef struct {
    char *path;
    int is_dir;
    int size;
    char *data;
} myfs_entry_t;

myfs_entry_t *myfs_files = NULL;
int file_count = 0;

void init_filesystem() {
    file_count = 3;
    myfs_files = malloc(sizeof(myfs_entry_t) * file_count);

    myfs_files[0].path = strdup("/");
    myfs_files[0].is_dir = 1;
    myfs_files[0].size = 0;
    myfs_files[0].data = NULL;

    myfs_files[1].path = strdup("/file.txt");
    myfs_files[1].is_dir = 0;
    myfs_files[1].size = 1024;
    myfs_files[1].data = calloc(1024, 1);
    strcpy(myfs_files[1].data, "Hello, world!!");

    myfs_files[2].path = strdup("/dir");
    myfs_files[2].is_dir = 1;
    myfs_files[2].size = 0;
    myfs_files[2].data = NULL;

    // for (int i = 0; i < file_count; i++) {
    //     if (!myfs_files[i].is_dir && myfs_files[i].data == NULL) {
    //         myfs_files[i].data = malloc(myfs_files[i].size);
    //         memset(myfs_files[i].data, 0, myfs_files[i].size);
    //         strncpy(myfs_files[i].data, "Hello, world!!", strlen("Hello World!!") + 1);
    //     }
    // }
}

static int myfs_getattr(const char *path, struct stat *stbuf, struct fuse_file_info *fi) {
    int res = 0;
    memset(stbuf, 0, sizeof(struct stat));

    for (int i = 0; myfs_files[i].path != NULL; i++) {
        if (strcmp(path, myfs_files[i].path) == 0) {
            if (myfs_files[i].is_dir) {
                stbuf->st_mode = S_IFDIR | 0755;
                stbuf->st_nlink = 2;
            } else {
                stbuf->st_mode = S_IFREG | 0444;
                stbuf->st_nlink = 1;
                stbuf->st_size = myfs_files[i].size;
            }
            return res;
        }
    }

    return -ENOENT;
}

static int myfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags) {
    if (strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0, 0);
    filler(buf, "..", NULL, 0, 0);

    for (int i = 0; myfs_files[i].path != NULL; i++) {
        if (myfs_files[i].is_dir && strcmp(path, "/") == 0) {
            filler(buf, myfs_files[i].path + 1, NULL, 0, 0);
        }
    }

    return 0;
}

static int myfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    for (int i = 0; myfs_files[i].path != NULL; i++) {
        if (strcmp(path, myfs_files[i].path) == 0 && !myfs_files[i].is_dir) {
            if (offset >= myfs_files[i].size)
                return 0;

            size_t len = (size < myfs_files[i].size - offset) ? size : myfs_files[i].size - offset;
            memcpy(buf, myfs_files[i].data + offset, len);
            return len;
        }
    }
    return -ENOENT;
}

static int myfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    for (int i = 0; myfs_files[i].path != NULL; i++) {
        if (strcmp(path, myfs_files[i].path) == 0 && !myfs_files[i].is_dir) {
            if (offset + size > myfs_files[i].size) {
                myfs_files[i].data = realloc(myfs_files[i].data, offset + size);
                myfs_files[i].size = offset + size;
            }
            memcpy(myfs_files[i].data + offset, buf, size);
            return size;
        }
    }
    return -ENOENT;
}

static int myfs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(myfs_files[i].path, path) == 0) {
            return -EEXIST;
        }
    }

    myfs_entry_t *new_files = realloc(myfs_files, sizeof(myfs_entry_t) * (file_count + 1));
    if (!new_files)
        return -ENOMEM;

    myfs_files = new_files;

    myfs_files[file_count].path = strdup(path);
    myfs_files[file_count].is_dir = 0;
    myfs_files[file_count].size = 0;
    myfs_files[file_count].data = NULL;

    file_count++;

    return 0;
}


static struct fuse_operations myfs_oper = {
    .getattr = myfs_getattr,
    .readdir = myfs_readdir,
    .read = myfs_read,
    .write = myfs_write,
};

int main(int argc, char *argv[]) {
    init_filesystem();
    return fuse_main(argc, argv, &myfs_oper, NULL);
}

