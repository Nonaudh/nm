#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include "nm.h"

char *mapped(int fd, off_t offset, int map_size, int page_size) // have to save base ptr to free
{
	int aligned = offset - (offset % page_size);
	int delta = offset - aligned;

	// printf("mmaped; offset; %ld   map_size; %d\n", offset, map_size);

	void *map = mmap(NULL, map_size + delta, PROT_READ, MAP_PRIVATE, fd, aligned);
	if (map == MAP_FAILED)
	{
		perror("mapped; ");
		exit (3);
	}
	return (map + delta);
}

// mapelta mappedelta(int fd, off_t offset, int map_size, int page_size)
// {
// 	mapelta mapelta;
// 	int aligned = offset - (offset % page_size);

// 	mapelta.delta = offset - aligned;
// 	// printf("mmaped; offset; %ld   map_size; %d\n", offset, map_size);

// 	mapelta.map = mmap(NULL, map_size + mapelta.delta, PROT_READ, MAP_PRIVATE, fd, aligned);
// 	if (mapelta.map == MAP_FAILED)
// 	{
// 		perror("mapped; ");
// 		exit (3);
// 	}
// 	return (mapelta);
// }

int main(void)
{
	int fd = open("a.out", O_RDONLY);
	if (fd == -1)
		exit (1);

	int size = getpagesize();

	void *map = mapped(fd, 0, size, size);

	// mapelta Ehdr = mappedelta(fd, 0, size, size);

	Elf64_Ehdr *elfstruct = (Elf64_Ehdr *)map;

	printf("elf->e_type = %u\n", elfstruct->e_type);
	printf("elf->e_machine = %u\n", elfstruct->e_machine);
	printf("elf->e_version = %u\n", elfstruct->e_version);
	printf("elf->e_entry = %lu\n", elfstruct->e_entry);
	printf("elf->e_phoff = %lu\n", elfstruct->e_phoff);
	printf("elf->e_shoff = %lu\n", elfstruct->e_shoff);
	printf("elf->e_flags = %u\n", elfstruct->e_flags);
	printf("elf->e_ehsize = %u\n", elfstruct->e_ehsize);
	printf("elf->e_phentsize = %u\n", elfstruct->e_phentsize);
	printf("elf->e_phnum = %u\n", elfstruct->e_phnum);
	printf("elf->e_shentsize = %u\n", elfstruct->e_shentsize);
	printf("elf->e_shnum = %u\n", elfstruct->e_shnum);
	printf("elf->e_shstrndx = %u\n", elfstruct->e_shstrndx);

	__uint8_t *shmap = mapped(fd, elfstruct->e_shoff, elfstruct->e_shentsize * elfstruct->e_shnum, size);
    
    Elf64_Shdr *elfsh = (Elf64_Shdr *)(shmap);

	void *shstrtabmap = mapped(fd, elfsh[elfstruct->e_shstrndx].sh_offset, elfsh[elfstruct->e_shstrndx].sh_size, size);

	// const char *shstrtab = (const char *)shstrtabmap;

	for (int i = 0; i <= elfstruct->e_shnum; i++)
	{
		printf("%s\n", (const char *)shstrtabmap + elfsh[i].sh_name);
	}

	munmap(map, size);


	return (0);
}