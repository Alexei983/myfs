# 🔧 MyFUSE — A Simple Custom File System in Userspace (FUSE)

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

**MyFUSE** is a minimalist, in-memory file system implemented in C using the [FUSE (Filesystem in Userspace)](https://github.com/libfuse/libfuse) framework. It serves as a didactic example of how fundamental file system mechanisms—such as file creation, reading, writing, and directory listing—can be realized entirely in user space.

This project is particularly well-suited for educational purposes and for those seeking to understand the internal architecture of file systems. It illustrates how FUSE enables user-level processes to emulate kernel-level file system behavior through a well-defined API, making it possible to prototype or experiment with custom file system logic without modifying kernel code.

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

## Install dependencies

### Debian/Ubuntu
```bash
sudo apt update
sudo apt install libfuse-dev build-essential
```
### Arch Linux
```bash
sudo pacman -S fuse2
```
## 🛠 Build & Run
### Clone the repo:
git clone https://github.com/yourusername/myfuse.git
cd myfuse
### Build the project:
./build.sh
### Create a mount point and run:
mkdir /tmp/myfs
./myfs /tmp/myfs
### Unmount:
fusermount -u /tmp/myfs
### Example Usage
cd /tmp/myfs

# 📂 Code Structure
- **`fuse_main_v2.c`** – Main implementation file containing all FUSE callbacks.  
- **`Makefile`** – Used to compile the project.  
- **`README.md`** – This file.

## ✅ Implemented FUSE Functions

| Function        | Description                         |
|----------------|-------------------------------------|
| `myfs_getattr` | Returns metadata (permissions, type, etc.) |
| `myfs_readdir` | Lists files and directories         |
| `myfs_open`    | Handles file open request           |
| `myfs_read`    | Reads file content from memory      |
| `myfs_write`   | Writes new content into memory      |
| `myfs_create`  | Creates new files dynamically       |

## 🌐 SEO Keywords
FUSE file system, Linux custom filesystem, FUSE tutorial, write your own file system,  
C filesystem project, educational file system, Linux filesystem in C, in-memory filesystem,  
filesystem from scratch, libfuse example, filesystem programming, FUSE create file,  
FUSE C example, FUSE beginners guide, FUSE memory file system.

## 🧾 License
MIT License. See LICENSE for more details.

## 🤝 Contributing
Pull requests and issues are welcome! If you're learning FUSE, feel free to fork this repository and experiment.

## ⭐ Support
If you find this project useful, please ⭐ star the repository to support continued development and visibility.
