#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include "nm64.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int	size_of_file(int fd)
{
	struct stat stat;

	if (fstat(fd, &stat))
	{
		ft_putstr_fd("Error: fsat\n", 2);
		return (-1);
	}
	if (stat.st_size < sizeof(Elf64_Ehdr))
	{
		ft_putstr_fd("File too small\n", 2);
		return (-1);
	}
	return (stat.st_size);
}

int	safe_exit(t_elf64	*e)
{	
	if (e->file_map)
		munmap(e->file_map, e->file_size);
	return (1);
}

int	fill_symbol_struct(t_symbol_part64	*symtab, t_symbol_part64 *dynsym, t_elf64 *e)
{
	Elf64_Shdr	*symtabHeader = get_section_header_by_name(e, "symtab");
	if (!symtabHeader)
		return (1);
	symtab->size = symtabHeader->sh_size / symtabHeader->sh_entsize;

	symtab->symbol = (Elf64_Sym *)get_section_by_header(e, symtabHeader);
	if (!symtab->symbol)
		return (1);
	
	symtab->strtab = get_section_by_name(e, "strtab");
	if (!symtab->strtab)
		return (1);

	Elf64_Shdr	*dynsymHeader = get_section_header_by_name(e, "dynsym");
	if (!dynsymHeader)
		return (1);
	dynsym->size = dynsymHeader->sh_size / dynsymHeader->sh_entsize;

	dynsym->symbol = (Elf64_Sym *)get_section_by_header(e, dynsymHeader);
	if (!dynsym->symbol)
		return (1);
	
	dynsym->strtab = get_section_by_name(e, "dynstr");
	if (!dynsym->strtab)
		return (1);
	return (0);
}

int	list_symbols(t_elf64 *e)
{
	t_symbol_part64	symtab;
	t_symbol_part64	dynsym;

	if (fill_symbol_struct(&symtab, &dynsym, e))
		return (1);

	print_symbols(&symtab, &dynsym, e);

	return (0);
}

int	init_elf(t_elf64 *e, char *filename)
{
	e->file_map = NULL;

	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}

	e->file_size = size_of_file(fd);
	if (e->file_size == -1)
	{
		close (fd);
		return (1);
	}

	e->page_size = getpagesize();

	e->file_map = get_file_in_a_map(fd, e->file_size);
	if (!e->file_map)
	{
		close (fd);
		return (1);
	}
	close (fd);
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


int nm64(char *filename, t_bonus *bonus)
{
	t_elf64	e;

	if (init_elf(&e, filename))
		return (safe_exit(&e));
	e.bonus = bonus;

	if (list_symbols(&e))
		ft_printf("nm: %s: no symbols\n", filename);

	safe_exit(&e);

	return (0);
}
