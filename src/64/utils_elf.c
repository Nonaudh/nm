#include "nm64.h"
#include <sys/mman.h>
#include <stdio.h>

void	*get_file_in_a_map_64(int fd, int file_size)
{
	void	*map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		return (NULL);
	return (map);
}

Elf64_Ehdr	*get_elf_header_64(t_elf64 *e)
{
	Elf64_Ehdr	*elf_header;

	elf_header = (Elf64_Ehdr *)e->file_map;

	return (elf_header);
}

Elf64_Shdr	*get_sections_header_64(t_elf64 *e)
{
	if (e->elf_header->e_shoff + (e->elf_header->e_shnum * sizeof(Elf64_Shdr)) > e->file_size)
	{
		ft_dprintf(2, "ft_nm: %s: file format not recognized\n", e->filename);
		return (NULL);
	}
	return (e->file_map + e->elf_header->e_shoff);
}

char	*get_section_by_header_64(t_elf64 *e, Elf64_Shdr *sectionHeader)
{
	if (!sectionHeader || sectionHeader->sh_offset + sizeof(Elf64_Shdr) > e->file_size)
		return (NULL);

	char *ptr = e->file_map + sectionHeader->sh_offset;

	return (ptr);
}

char	*get_section_by_name_64(t_elf64 *e, const char *name)
{
	int i = 1;
	char *ptr;

	while (i < e->elf_header->e_shnum)
	{
		if (!ft_strncmp(name, e->shstrtab + e->sectionsHeader[i].sh_name + 1, ft_strlen(name)) 
			&& ft_strlen(name) == ft_strlen(e->shstrtab + e->sectionsHeader[i].sh_name + 1))
			break ;
		i++;
	}
	if (i == e->elf_header->e_shnum)
	{
		// printf("Section not found : %s\n", name);
		return (NULL);
	}
	ptr = get_section_by_header_64(e, &e->sectionsHeader[i]);
	return (ptr);
}

Elf64_Shdr	*get_section_header_by_name_64(t_elf64 *e, const char *name)
{
	int i = 1;

	while (i < e->elf_header->e_shnum)
	{
		if (!ft_strncmp(name, e->shstrtab + e->sectionsHeader[i].sh_name + 1, ft_strlen(name)) 
			&& ft_strlen(name) == ft_strlen(e->shstrtab + e->sectionsHeader[i].sh_name + 1))
			break ;
		i++;
	}
	if (i == e->elf_header->e_shnum)
	{
		// printf("Section Header not found : %s\n", name);
		return (NULL);
	}
	return (&e->sectionsHeader[i]);
}
