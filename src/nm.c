#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include "nm.h"
#include <string.h>
#include <errno.h>

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

int init_elf(t_elf *e, char *filename)
{
	e->elfHeader = NULL;
	e->sectionsHeader = NULL;
	e->shstrtab = NULL;

	e->fd = open(filename, O_RDONLY);
	if (e->fd == -1)
	{
		perror(filename);
		return (1);
	}

	e->page_size = getpagesize();

	e->elfHeader = get_elf_header(e->fd, e->page_size);
	if (!e->elfHeader)
		return (1);

	e->sectionsHeader = get_sections_header(e->fd, e->elfHeader, e->page_size);
	if (!e->sectionsHeader)
		return (1);

	e->shstrtab = get_section_by_header(e->fd, &e->sectionsHeader[e->elfHeader->e_shstrndx], e->page_size);
	if (!e->shstrtab)
		return (1);

	return (0);
}

int	safe_exit(t_elf	*e)
{
	if (e->fd != -1)
		close (e->fd);	
	if (e->elfHeader)
		free(e->elfHeader);
	if (e->sectionsHeader)
		free(e->sectionsHeader);
	if (e->shstrtab)
		free(e->shstrtab);
	return (1);
}

int	nm(t_elf *e)
{
	
}


int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	t_elf	e;

	if (init_elf(&e, argv[1]))
		return (safe_exit(&e));

	nm(&e);

	Elf64_Shdr	*symtabHeader = get_section_header_by_name("symtab", e.sectionsHeader, e.shstrtab, e.elfHeader->e_shnum);

	Elf64_Sym	*symtab = (Elf64_Sym *)get_section_by_header(e.fd, symtabHeader, e.elfHeader->e_shnum);

	// Elf64_Shdr	*dynsymHeader = get_section_header_by_name("dynsym", sectionsHeader, shstrtab, elfHeader->e_shnum);

	// Elf64_Sym	*dynsym = (Elf64_Sym *)get_section_by_header(fd, dynsymHeader, page_size);

	// char	*strtab = get_section_by_name(fd, "strtab", sectionsHeader, shstrtab, page_size, elfHeader->e_shnum);

	// char	*dynstr = get_section_by_name(fd, "dynstr", sectionsHeader, shstrtab, page_size, elfHeader->e_shnum);

	// print_symbols(symtabHeader, symtab, strtab, dynsymHeader, dynsym, dynstr);

	// free(elfHeader);
	// free(sectionsHeader);
	// free(shstrtab);
	// free(symtab);
	// free(dynsym);
	// free(strtab);
	// free(dynstr);

	return (0);
}
