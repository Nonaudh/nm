#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include "nm.h"


Elf64_Ehdr	*get_elf_hearder(int fd, int page_size)
{
	Elf64_Ehdr	*map = (Elf64_Ehdr	*)mmap(NULL, page_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		return (NULL);

	Elf64_Ehdr	*ptr = malloc((map->e_ehsize) * sizeof(Elf64_Ehdr));
	if (!ptr)
		return (NULL);

	memcpy(ptr, map, map->e_ehsize);

	if (munmap(map, page_size))
		return (NULL);
	return (ptr);
}

Elf64_Shdr	*get_section_header(int fd, Elf64_Ehdr *elfHeader, int page_size)
{
	int	aligned = elfHeader->e_shoff - (elfHeader->e_shoff % page_size);

	int delta = elfHeader->e_shoff - aligned;

	void	*map = mmap(NULL, (elfHeader->e_shentsize * elfHeader->e_shnum) + delta,
			PROT_READ, MAP_PRIVATE, fd, aligned);
	if (map == MAP_FAILED)
		return (NULL);

	Elf64_Shdr	*ptr = malloc((elfHeader->e_shentsize * elfHeader->e_shnum) * sizeof(Elf64_Shdr));
	if (!ptr)
		return (NULL);

	memcpy(ptr, map + delta, elfHeader->e_shentsize * elfHeader->e_shnum);

	if (munmap(map, (elfHeader->e_shentsize * elfHeader->e_shnum) + delta))
		return (NULL);
	return (ptr);
}

char	*get_mapped_and_copied(int fd, Elf64_Shdr *sectionNameHeader, int page_size)
{
	int	aligned = sectionNameHeader->sh_offset - (sectionNameHeader->sh_offset % page_size);

	int delta = sectionNameHeader->sh_offset - aligned;

	void	*map = mmap(NULL, sectionNameHeader->sh_size + delta,
			PROT_READ, MAP_PRIVATE, fd, aligned);
	if (map == MAP_FAILED)
		return (NULL);

	char *ptr = malloc(sectionNameHeader->sh_size * sizeof(char));
	if (!ptr)
		return (NULL);

	memcpy(ptr, map + delta, sectionNameHeader->sh_size);

	if (munmap(map, sectionNameHeader->sh_size + delta))
		return (NULL);
	return (ptr);
}

char	*get_section_by_name(int fd, const char *str, Elf64_Shdr *sectionHeader, char *shstrtab, int page_size, int shnum)
{
	int i = 1;
	char *ptr;

	while (shstrtab + sectionHeader[i].sh_name  && i < shnum)
	{
		if (!ft_strncmp(str, shstrtab + sectionHeader[i].sh_name + 1, ft_strlen(str)) && ft_strlen(str) == ft_strlen(shstrtab + sectionHeader[i].sh_name + 1))
			break ;
		i++;
	}
	if (i == shnum)
	{
		printf(("Section not found\n"));
		return (NULL);
	}
	ptr = get_mapped_and_copied(fd, &sectionHeader[i], page_size);
	return (ptr);
}


int main(void)
{
	int fd = open("a.out", O_RDONLY);
	if (fd == -1)
		return (1);

	int page_size = getpagesize();

	Elf64_Ehdr	*elfHeader = get_elf_hearder(fd, page_size);
	if (!elfHeader)
		return (1);

	Elf64_Shdr	*sectionHeader = get_section_header(fd, elfHeader, page_size);
	if (!sectionHeader)
		return (1);

	char	*shstrtab = get_mapped_and_copied(fd, &sectionHeader[elfHeader->e_shstrndx], page_size);

	char	*symtab = get_section_by_name(fd, "symtab", sectionHeader, shstrtab, page_size, elfHeader->e_shnum);


	free(elfHeader);
	free(sectionHeader);
	free(shstrtab);
	free(symtab);

	return (0);
}
