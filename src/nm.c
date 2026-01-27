#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include "nm.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

char	define_symbol_type(Elf64_Sym *symtab, t_elf *e)
{
	int	bind = ELF64_ST_BIND(symtab->st_info);
	int	type = ELF64_ST_TYPE(symtab->st_info);
	char c = 0;

	if (symtab->st_shndx == SHN_UNDEF)
	{
		if (bind == STB_WEAK)
			return ('w');
		return ('U');
	}

	if (symtab->st_shndx == SHN_ABS)
		return ('A');

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
		{
			if (symtab->st_shndx == SHN_UNDEF)
				return ('v');
			else
				return ('V');
		}
		if (symtab->st_shndx == SHN_UNDEF)
			return ('w');
		else
			return ('W');
	}

	Elf64_Shdr *shdr = &e->sectionsHeader[symtab->st_shndx];

	if (shdr->sh_flags & SHF_EXECINSTR)
		return ('T');

	if ((shdr->sh_flags & SHF_ALLOC) &&
			!(shdr->sh_flags & SHF_WRITE) &&
			!(shdr->sh_flags & SHF_EXECINSTR))
		return ('R');

	if ((shdr->sh_flags & SHF_ALLOC) && (shdr->sh_flags & SHF_WRITE))
	{
		if (shdr->sh_type == SHT_NOBITS)
			return ('B');
		else
			return ('D');
	}
	return ('?');
}

void print_symbol_line(Elf64_Sym *symtab, char *name,  t_elf *e)
{
	if (symtab->st_value)
		printf("%016lx", symtab->st_value);
	else
		printf("                ");

	char c = define_symbol_type(symtab, e);
	if (c != 'U' && c != 'W' && c != 'V' && ELF64_ST_BIND(symtab->st_info) == STB_LOCAL)
		c = ft_tolower(c);

	printf(" %c ", c);
	
	printf("%s\n", name);
}

void	print_all_symbols(t_symbol_container *s, t_elf *e)
{
	for (int i = 0; i < s->size; i++)
	{
		print_symbol_line(s->tab[i].symbol, s->tab[i].name, e);
	}
}

int	size_of_file(int fd)
{
	struct stat stat;

	if (fstat(fd, &stat))
	{
		ft_putstr_fd("Error: fsat\n", 2);
		return (-1);
	}
	if (stat.st_size < EI_NIDENT)
	{
		ft_putstr_fd("File too small\n", 2);
		return (-1);
	}
	return (stat.st_size);
}

int	safe_exit(t_elf	*e)
{
	if (e->fd != -1)
		close (e->fd);	
	if (e->file_map)
		munmap(e->file_map, e->file_size);
	// if (e->sectionsHeader)
	// 	free(e->sectionsHeader);
	// if (e->shstrtab)
	// 	free(e->shstrtab);
	return (1);
}

int	nm(t_elf *e)
{
	Elf64_Shdr	*symtabHeader = get_section_header_by_name(e, "symtab");

	Elf64_Sym	*symtab = (Elf64_Sym *)get_section_by_header(e, symtabHeader);

	Elf64_Shdr	*dynsymHeader = get_section_header_by_name(e, "dynsym");

	Elf64_Sym	*dynsym = (Elf64_Sym *)get_section_by_header(e, dynsymHeader);

	char	*strtab = get_section_by_name(e, "strtab");

	char	*dynstr = get_section_by_name(e, "dynstr");

	print_symbols(symtabHeader, symtab, strtab, dynsymHeader, dynsym, dynstr, e);

	return (0);
}

// int init_elf(t_elf *e, char *filename)
// {
// 	e->elfHeader = NULL;
// 	e->sectionsHeader = NULL;
// 	e->shstrtab = NULL;

// 	e->fd = open(filename, O_RDONLY);
// 	if (e->fd == -1)
// 	{
// 		perror(filename);
// 		return (1);
// 	}

// 	if (size_of_file(e->fd) == -1)
// 		return (1);

// 	e->page_size = getpagesize();

// 	e->elfHeader = get_elf_header(e->fd, e->page_size);
// 	if (!e->elfHeader)
// 		return (1);

// 	e->sectionsHeader = get_sections_header(e->fd, e->elfHeader, e->page_size);
// 	if (!e->sectionsHeader)
// 		return (1);

// 	e->shstrtab = get_section_by_header(e, &e->sectionsHeader[e->elfHeader->e_shstrndx]);
// 	if (!e->shstrtab)
// 		return (1);

// 	return (0);
// }

int	new_init_elf(t_elf *e, char *filename)
{
	e->elf_header = NULL;
	e->sectionsHeader = NULL;
	e->shstrtab = NULL;
	e->file_map = NULL;

	e->fd = open(filename, O_RDONLY);
	if (e->fd == -1)
	{
		perror(filename);
		return (1);
	}

	e->file_size = size_of_file(e->fd);
	if (e->file_size == -1)
		return (1);

	e->page_size = getpagesize();

	e->file_map = get_file_in_a_map(e->fd, e->file_size);
	if (!e->file_map)
		return (1);

	e->elf_header = get_elf_header(e);
	if (!e->elf_header)	
		return (1);

	e->sectionsHeader = get_sections_header(e);
	if (!e->sectionsHeader)
		return (1);

	e->shstrtab = get_section_by_header(e, &e->sectionsHeader[e->elf_header->e_shstrndx]);
	if (!e->shstrtab)
		return (1);

	return (0);
}


int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	t_elf	e;

	// if (init_elf(&e, argv[argc - 1]))
	// 	return (safe_exit(&e));

	if (new_init_elf(&e, argv[argc - 1]))
		return (safe_exit(&e));

	nm(&e);

	// Elf64_Shdr	*symtabHeader = get_section_header_by_name("symtab", e.sectionsHeader, e.shstrtab, e.elfHeader->e_shnum);

	// Elf64_Sym	*symtab = (Elf64_Sym *)get_section_by_header(e.fd, symtabHeader, e.elfHeader->e_shnum);

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
	safe_exit(&e);

	return (0);
}
