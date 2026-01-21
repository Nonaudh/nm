#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include "nm.h"

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

	// print_symbol_type(symtab);
	
	printf("%s\n", name);
}

void	print_all_symbols(t_symbol_container *s)
{
	for (int i = 0; i < s->size; i++)
	{
		print_symbol_line(s->list[i].symbol, s->list[i].name);
	}
}

// int	print_symbols(Elf64_Shdr *symtabHeader, Elf64_Sym *symtab, char *strtab, Elf64_Shdr *dynsymHeader, Elf64_Sym *dynsym, char *dynstr)
// {
// 	for (int i = 0; i < symtabHeader->sh_size / symtabHeader->sh_entsize; i++)
// 	{
// 		print_symbol_line(&symtab[i], strtab + symtab[i].st_name);
// 	}

// 	printf("\n");

// 	// for (int i = 0; i < dynsymHeader->sh_size / dynsymHeader->sh_entsize; i++)
// 	// {
// 	// 	printf("%lu  %s\n", dynsym[i].st_value, dynstr + dynsym[i].st_name);
// 	// }
// 	return (0);
// }

int main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);

	int page_size = getpagesize();

	Elf64_Ehdr	*elfHeader = get_elf_header(fd, page_size);
	if (!elfHeader)
		return (1);

	Elf64_Shdr	*sectionHeader = get_sections_header(fd, elfHeader, page_size);
	if (!sectionHeader)
		return (1);

	char	*shstrtab = get_section_by_header(fd, 
		&sectionHeader[swap16(elfHeader->e_shstrndx)], page_size);

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
