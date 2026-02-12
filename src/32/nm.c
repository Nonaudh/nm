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

t_symbol_container32	*fill_container_32(t_elf32 *e)
{
	int i;
	t_symbol_container32	*s;
	Elf32_Shdr	*symtabHeader;
	int symtab_size;
	Elf32_Sym	*symtab;
	char	*strtab;

	s = malloc(sizeof(t_symbol_container32));
	if (!s)
		return (NULL);
	symtabHeader = get_section_header_by_name_32(e, "symtab");
	if (!symtabHeader)
		return (NULL);
	symtab_size = symtabHeader->sh_size / symtabHeader->sh_entsize;
	symtab = (Elf32_Sym *)get_section_by_header_32(e, symtabHeader);
	if (!symtab)
		return (NULL);
	strtab = get_section_by_name_32(e, "strtab");
	if (!strtab)
		return (NULL);

	s->size = 0;
	s->tab = malloc((symtab_size) * sizeof(t_symbol32));
	if (!s->tab)
	{
		free(s);
		return (NULL);
	}
	
	for (i = 1; i < symtab_size; i++)
	{
		s->tab[s->size].symbol = &symtab[i];
		if (ELF32_ST_TYPE(symtab[i].st_info) != STT_SECTION)
			s->tab[s->size].name = strtab + symtab[i].st_name;
		else
			s->tab[s->size].name = e->shstrtab + e->sectionsHeader[symtab[i].st_shndx].sh_name;
		s->size++;
	}
	return (s);
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

int nm32(char *filename, t_bonus *bonus, int *file_nb)
{
	t_elf32	e;
	t_symbol_container32 *s;

	if (init_elf_32(&e, filename))
		return (safe_exit_32(&e));
	e.bonus = bonus;

	s = fill_container_32(&e);
	if (!s)
		ft_dprintf(2, "nm: %s: no symbols\n", filename);
	
	sort_and_print_symbols_32(s, &e, *file_nb);

	if (!(*file_nb))
		*file_nb = 1;

	safe_exit_32(&e);

	return (0);
}
