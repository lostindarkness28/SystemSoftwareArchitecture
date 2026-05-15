#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <elf-file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct stat st;
    fstat(fd, &st);

    void *file = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)file;

    printf("ELF Entry point: 0x%lx\n", ehdr->e_entry);

    Elf64_Phdr *phdr = (Elf64_Phdr *)((char *)file + ehdr->e_phoff);

    for (int i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type != PT_LOAD)
            continue;

        void *seg = mmap(
            (void *)phdr[i].p_vaddr,
            phdr[i].p_memsz,
            PROT_READ | PROT_WRITE | PROT_EXEC,
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
            -1,
            0
        );

        if (seg == MAP_FAILED) {
            perror("segment mmap");
            return 1;
        }

        memcpy(seg, (char *)file + phdr[i].p_offset, phdr[i].p_filesz);
    }

    void (*entry)() = (void (*)())ehdr->e_entry;

    printf("Transferring control...\n");

    entry();

    return 0;
}
