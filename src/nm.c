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
	Elf64_Ehdr	*map = (Elf64_Ehdr *)mmap(NULL, page_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		return (NULL);

	Elf64_Ehdr	*ptr = malloc(map->e_ehsize);
	if (!ptr)
		return (NULL);

	memcpy(ptr, map, map->e_ehsize);

	if (munmap(map, page_size))
		return (NULL);
	return (ptr);
}

Elf64_Shdr	*get_sections_header(int fd, Elf64_Ehdr *elfHeader, int page_size)
{
	int	aligned = elfHeader->e_shoff - (elfHeader->e_shoff % page_size);

	int delta = elfHeader->e_shoff - aligned;

	void	*map = mmap(NULL, (elfHeader->e_shentsize * elfHeader->e_shnum) + delta,
			PROT_READ, MAP_PRIVATE, fd, aligned);
	if (map == MAP_FAILED)
		return (NULL);

	Elf64_Shdr	*ptr = malloc(elfHeader->e_shentsize * elfHeader->e_shnum);
	if (!ptr)
		return (NULL);

	memcpy(ptr, map + delta, elfHeader->e_shentsize * elfHeader->e_shnum);

	if (munmap(map, (elfHeader->e_shentsize * elfHeader->e_shnum) + delta))
		return (NULL);
	return (ptr);
}

char	*get_section_by_header(int fd, Elf64_Shdr *sectionNameHeader, int page_size)
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

	while (i < shnum)
	{
		if (!ft_strncmp(str, shstrtab + sectionHeader[i].sh_name + 1, ft_strlen(str)) 
			&& ft_strlen(str) == ft_strlen(shstrtab + sectionHeader[i].sh_name + 1))
			break ;
		i++;
	}
	if (i == shnum)
	{
		printf("Section not found : %s\n", str);
		return (NULL);
	}
	ptr = get_section_by_header(fd, &sectionHeader[i], page_size);
	return (ptr);
}

Elf64_Shdr	*get_section_header_by_name(const char *str, Elf64_Shdr	*sectionHeader, char *shstrtab, int shnum)
{
	int i = 1;

	while (i < shnum)
	{
		if (!ft_strncmp(str, shstrtab + sectionHeader[i].sh_name + 1, ft_strlen(str)) 
			&& ft_strlen(str) == ft_strlen(shstrtab + sectionHeader[i].sh_name + 1))
			break ;
		i++;
	}
	if (i == shnum)
	{
		printf("Section Header not found : %s\n", str);
		return (NULL);
	}
	return (&sectionHeader[i]);
}

void	print_symbol_type(Elf64_Sym *symtab)
{
	int	bind = ELF64_ST_BIND(symtab->st_info);
	int	type = ELF64_ST_TYPE(symtab->st_info);
	printf("bind ; %d  type; %d  sndx; %d  ", bind, type, symtab->st_shndx);
}

void print_symbol_line(Elf64_Sym *symtab, char *name)
{
	if (symtab->st_value)
		printf("%016lx ", symtab->st_value);
	else
		printf("                 ");

	print_symbol_type(symtab);
	
	printf("%s\n", name);
}

int	print_symbols(Elf64_Shdr *symtabHeader, Elf64_Sym *symtab, char *strtab, Elf64_Shdr *dynsymHeader, Elf64_Sym *dynsym, char *dynstr)
{
	for (int i = 0; i < symtabHeader->sh_size / symtabHeader->sh_entsize; i++)
	{
		print_symbol_line(&symtab[i], strtab + symtab[i].st_name);
	}

	printf("\n");

	// for (int i = 0; i < dynsymHeader->sh_size / dynsymHeader->sh_entsize; i++)
	// {
	// 	printf("%lu  %s\n", dynsym[i].st_value, dynstr + dynsym[i].st_name);
	// }
	return (0);
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

	Elf64_Shdr	*sectionHeader = get_sections_header(fd, elfHeader, page_size);
	if (!sectionHeader)
		return (1);

	char	*shstrtab = get_section_by_header(fd, &sectionHeader[elfHeader->e_shstrndx], page_size);

	Elf64_Shdr	*symtabHeader = get_section_header_by_name("symtab", sectionHeader, shstrtab, elfHeader->e_shnum);

	Elf64_Sym	*symtab = (Elf64_Sym *)get_section_by_header(fd, symtabHeader, page_size);

	Elf64_Shdr	*dynsymHeader = get_section_header_by_name("dynsym", sectionHeader, shstrtab, elfHeader->e_shnum);

	Elf64_Sym	*dynsym = (Elf64_Sym *)get_section_by_header(fd, dynsymHeader, page_size);

	char	*strtab = get_section_by_name(fd, "strtab", sectionHeader, shstrtab, page_size, elfHeader->e_shnum);

	char	*dynstr = get_section_by_name(fd, "dynstr", sectionHeader, shstrtab, page_size, elfHeader->e_shnum);

	print_symbols(symtabHeader, symtab, strtab, dynsymHeader, dynsym, dynstr);

	free(elfHeader);
	free(sectionHeader);
	free(shstrtab);
	free(symtab);
	free(dynsym);
	free(strtab);
	free(dynstr);

	return (0);
}
