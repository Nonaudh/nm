#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include "nm32.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int	size_of_file_32(int fd)
{
	struct stat stat;

	if (fstat(fd, &stat))
	{
		ft_putstr_fd("Error: fsat\n", 2);
		return (-1);
	}
	if (stat.st_size < sizeof(Elf32_Ehdr))
	{
		ft_putstr_fd("File too small\n", 2);
		return (-1);
	}
	return (stat.st_size);
}

int	safe_exit_32(t_elf32	*e)
{	
	if (e->file_map)
		munmap(e->file_map, e->file_size);
	return (1);
}

int	fill_symbol_struct_32(t_symbol_part32 *symtab, t_symbol_part32 *dynsym, t_elf32 *e)
{
	Elf32_Shdr	*symtabHeader = get_section_header_by_name_32(e, "symtab");
	Elf32_Shdr	*dynsymHeader = get_section_header_by_name_32(e, "dynsym");
	if (!dynsymHeader && !symtabHeader)
		return (1);
	if (symtabHeader)
	{
		symtab->size = symtabHeader->sh_size / symtabHeader->sh_entsize;

		symtab->symbol = (Elf32_Sym *)get_section_by_header_32(e, symtabHeader);
		if (!symtab->symbol)
			return (1);
	
		symtab->strtab = get_section_by_name_32(e, "strtab");
		if (!symtab->strtab)
			return (1);
	}
	else
	{
		symtab->size = 0;
	}
	if (dynsymHeader)
	{
		dynsym->size = dynsymHeader->sh_size / dynsymHeader->sh_entsize;

		dynsym->symbol = (Elf32_Sym *)get_section_by_header_32(e, dynsymHeader);
		if (!dynsym->symbol)
			return (1);
		
		dynsym->strtab = get_section_by_name_32(e, "dynstr");
		if (!dynsym->strtab)
			return (1);
	}
	else
		dynsym->size = 0;
	
	return (0);
}

int	list_symbols_32(t_elf32 *e)
{
	t_symbol_part32	symtab;
	t_symbol_part32	dynsym;

	if (fill_symbol_struct_32(&symtab, &dynsym, e))
		return (1);

	print_symbols_32(&symtab, &dynsym, e);

	return (0);
}

int	init_elf_32(t_elf32 *e, char *filename)
{
	e->file_map = NULL;

	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}

	e->file_size = size_of_file_32(fd);
	if (e->file_size == -1)
	{
		close (fd);
		return (1);
	}

	e->page_size = getpagesize();

	e->file_map = get_file_in_a_map_32(fd, e->file_size);
	if (!e->file_map)
	{
		close (fd);
		return (1);
	}
	close (fd);
	e->elf_header = get_elf_header_32(e);
	if (!e->elf_header)	
		return (1);

	e->sectionsHeader = get_sections_header_32(e);
	if (!e->sectionsHeader)
		return (1);

	e->shstrtab = get_section_by_header_32(e, &e->sectionsHeader[e->elf_header->e_shstrndx]);
	if (!e->shstrtab)
		return (1);

	return (0);
}


int nm32(char *filename, t_bonus *bonus)
{
	t_elf32	e;

	if (init_elf_32(&e, filename))
		return (safe_exit_32(&e));
	e.bonus = bonus;

	if (list_symbols_32(&e))
		ft_printf("nm: %s: no symbols\n", filename);

	safe_exit_32(&e);

	return (0);
}
