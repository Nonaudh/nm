#include <sys/mman.h>
#include <fcntl.h>
#include "nm32.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

int	size_of_file_32(int fd, char *filename)
{
	struct stat stat;

	if (fstat(fd, &stat))
		return (-1);
	if (stat.st_size < sizeof(Elf32_Ehdr))
	{
		ft_dprintf(2, "ft_nm: %s: file format not recognized\n", filename);
		return (-1);
	}
	return (stat.st_size);
}

int	safe_exit_32(t_elf32 *e)
{	
	if (e->file_map)
		munmap(e->file_map, e->file_size);
	return (1);
}

int	print_dynsym_32(t_elf32 *e)
{
	Elf32_Shdr	*symtabHeader = get_section_header_by_name_32(e, "dynsym");
	if (!symtabHeader)
		return (1);
	int size = symtabHeader->sh_size / symtabHeader->sh_entsize;

	Elf32_Sym * symbol = (Elf32_Sym *)get_section_by_header_32(e, symtabHeader);
	if (!symbol)
		return (1);

	char *strtab = get_section_by_name_32(e, "dynstr");
	if (!strtab)
		return (1);

	ft_printf("===============\n");
	for (int i = 0; i < size; i++)
	{
		ft_printf("%s\n", symbol[i].st_name + strtab);
	}
	ft_printf("===============\n");
	return (1);
}

int	fill_symbol_struct_32(t_symbol_part32 *symtab, t_elf32 *e)
{
	Elf32_Shdr	*symtabHeader = get_section_header_by_name_32(e, "symtab");
	if (!symtabHeader)
		return (1);
	symtab->size = symtabHeader->sh_size / symtabHeader->sh_entsize;

	symtab->symbol = (Elf32_Sym *)get_section_by_header_32(e, symtabHeader);
	if (!symtab->symbol)
		return (1);

	symtab->strtab = get_section_by_name_32(e, "strtab");
	if (!symtab->strtab)
		return (1);

	// ft_printf("===============\n");
	// for (int i = 0; i < symtab->size; i++)
	// {
	// 	ft_printf("%s\n", symtab->symbol[i].st_name + symtab->strtab);
	// }
	// ft_printf("===============\n");	

	// print_dynsym_32(e);
	return (0);
}

int	list_symbols_32(t_elf32 *e, int multiple_file)
{
	t_symbol_part32	symtab;

	if (fill_symbol_struct_32(&symtab, e))
		return (1);

	print_symbols_32(&symtab, e, multiple_file);

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
	e->filename = filename;

	e->file_size = size_of_file_32(fd, filename);
	if (e->file_size == -1)
	{
		close (fd);
		return (1);
	}

	// e->page_size = getpagesize();

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


int nm32(char *filename, t_bonus *bonus, int multiple_file)
{
	t_elf32	e;

	if (init_elf_32(&e, filename))
		return (safe_exit_32(&e));
	e.bonus = bonus;

	if (list_symbols_32(&e, multiple_file))
		ft_dprintf(2, "nm: %s: no symbols\n", filename);

	safe_exit_32(&e);

	return (0);
}
