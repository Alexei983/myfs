# 🔧 MyFUSE — A Simple Custom File System in Userspace (FUSE)

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

**MyFUSE** is a minimalist in-memory file system built with [FUSE (Filesystem in Userspace)](https://github.com/libfuse/libfuse) and written in C. It demonstrates how to implement a working file system from scratch using FUSE, supporting essential operations such as file creation, reading, writing, and listing directories.

This project is ideal for learning how file systems operate under the hood and how FUSE provides an interface to implement one entirely in user space.

---

## 🚀 Features

- ✅ Dynamic file and directory creation
- ✅ `getattr` for file metadata
- ✅ `readdir` for directory listing
- ✅ `open` to handle file access
- ✅ `read` to retrieve content from memory
- ✅ `write` to update content dynamically
- ✅ Fully in-memory data storage using C structures

---

## 🧠 How It Works

Each file or directory is represented as a structure in an in-memory array:

```c
typedef struct {
    char *path;
    int is_dir;
    int size;
    char *data;
} myfs_entry_t;
