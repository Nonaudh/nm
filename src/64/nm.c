#include <sys/mman.h>
#include <fcntl.h>
#include "nm64.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

int	size_of_file_64(int fd, char *filename)
{
	struct stat stat;

	if (fstat(fd, &stat))
		return (-1);
	if (stat.st_size < sizeof(Elf64_Ehdr))
	{
		ft_dprintf(2, "ft_nm: %s: file format not recognized\n", filename);
		return (-1);
	}
	return (stat.st_size);
}

int	safe_exit_64(t_elf64 *e)
{	
	if (e->file_map)
		munmap(e->file_map, e->file_size);
	return (1);
}

int	print_dynsym_64(t_elf64 *e)
{
	Elf64_Shdr	*symtabHeader = get_section_header_by_name_64(e, "dynsym");
	if (!symtabHeader)
		return (1);
	int size = symtabHeader->sh_size / symtabHeader->sh_entsize;

	Elf64_Sym * symbol = (Elf64_Sym *)get_section_by_header_64(e, symtabHeader);
	if (!symbol)
		return (1);

	char *strtab = get_section_by_name_64(e, "dynstr");
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

int	fill_symbol_struct_64(t_symbol_part64 *symtab, t_elf64 *e)
{
	Elf64_Shdr	*symtabHeader = get_section_header_by_name_64(e, "symtab");
	if (!symtabHeader)
		return (1);
	symtab->size = symtabHeader->sh_size / symtabHeader->sh_entsize;

	symtab->symbol = (Elf64_Sym *)get_section_by_header_64(e, symtabHeader);
	if (!symtab->symbol)
		return (1);

	symtab->strtab = get_section_by_name_64(e, "strtab");
	if (!symtab->strtab)
		return (1);

	// ft_printf("===============\n");
	// for (int i = 0; i < symtab->size; i++)
	// {
	// 	ft_printf("%s\n", symtab->symbol[i].st_name + symtab->strtab);
	// }
	// ft_printf("===============\n");	

	// print_dynsym_64(e);
	return (0);
}

int	list_symbols_64(t_elf64 *e, int multiple_file)
{
	t_symbol_part64	symtab;

	if (fill_symbol_struct_64(&symtab, e))
		return (1);

	print_symbols_64(&symtab, e, multiple_file);

	return (0);
}

int	init_elf_64(t_elf64 *e, char *filename)
{
	e->file_map = NULL;

	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	e->filename = filename;

	e->file_size = size_of_file_64(fd, filename);
	if (e->file_size == -1)
	{
		close (fd);
		return (1);
	}

	// e->page_size = getpagesize();

	e->file_map = get_file_in_a_map_64(fd, e->file_size);
	if (!e->file_map)
	{
		close (fd);
		return (1);
	}
	close (fd);
	e->elf_header = get_elf_header_64(e);
	if (!e->elf_header)	
		return (1);

	e->sectionsHeader = get_sections_header_64(e);
	if (!e->sectionsHeader)
		return (1);

	e->shstrtab = get_section_by_header_64(e, &e->sectionsHeader[e->elf_header->e_shstrndx]);
	if (!e->shstrtab)
		return (1);

	return (0);
}


int nm64(char *filename, t_bonus *bonus, int multiple_file)
{
	t_elf64	e;

	if (init_elf_64(&e, filename))
		return (safe_exit_64(&e));
	e.bonus = bonus;

	if (list_symbols_64(&e, multiple_file))
		ft_dprintf(2, "nm: %s: no symbols\n", filename);

	safe_exit_64(&e);

	return (0);
}
