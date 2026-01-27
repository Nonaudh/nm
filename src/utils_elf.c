#include "nm.h"
#include <sys/mman.h>
#include <stdio.h>
	
int	not_an_elf(char *map)
{
	if (map[0] != 0x7f || map[1] != 'E' || map[2] != 'L' || map[3] != 'F')
	{
		ft_putstr_fd("Not an ELF\n", 2);
		return (1);
	}
	return (0);
}

// Elf64_Ehdr	*get_elf_header_tmp(int fd, int page_size)
// {
// 	char	*map = mmap(NULL, page_size, PROT_READ, MAP_PRIVATE, fd, 0);
// 	if (map == MAP_FAILED)
// 		return (NULL);

// 	if (not_an_elf(map))
// 		return (NULL);

// 	Elf64_Ehdr	*elf = (Elf64_Ehdr	*)map;

// 	Elf64_Ehdr	*ptr = malloc(elf->e_ehsize);
// 	if (!ptr)
// 		return (NULL);

// 	ft_memcpy(ptr, map, elf->e_ehsize);

// 	if (munmap(map, page_size))
// 		return (NULL);
// 	return (ptr);
// }

void	*get_file_in_a_map(int fd, int file_size)
{
	void	*map = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		return (NULL);

	if (not_an_elf(map))
		return (NULL);

	return (map);
}

Elf64_Ehdr	*get_elf_header(t_elf *e)
{
	Elf64_Ehdr	*elf_header;

	elf_header = (Elf64_Ehdr *)e->file_map;

	return (elf_header);
}

Elf64_Shdr	*get_sections_header(t_elf *e)
{
	return (e->file_map + e->elf_header->e_shoff);
}

// Elf64_Shdr	*get_sections_header_tmp(int fd, Elf64_Ehdr *elfHeader, int page_size)
// {
// 	int	aligned = elfHeader->e_shoff - (elfHeader->e_shoff % page_size);

// 	int delta = elfHeader->e_shoff - aligned;

// 	void	*map = mmap(NULL, (elfHeader->e_shentsize * elfHeader->e_shnum) + delta,
// 			PROT_READ, MAP_PRIVATE, fd, aligned);
// 	if (map == MAP_FAILED)
// 		return (NULL);

// 	Elf64_Shdr	*ptr = malloc(elfHeader->e_shentsize * elfHeader->e_shnum);
// 	if (!ptr)
// 		return (NULL);

// 	ft_memcpy(ptr, map + delta, elfHeader->e_shentsize * elfHeader->e_shnum);

// 	if (munmap(map, (elfHeader->e_shentsize * elfHeader->e_shnum) + delta))
// 		return (NULL);
// 	return (ptr);
// }

char	*get_section_by_header(t_elf *e, Elf64_Shdr *sectionHeader)
{
	if (!sectionHeader)
		return (NULL);

	char *ptr = e->file_map + sectionHeader->sh_offset;

	// int	aligned = sectionHeader->sh_offset - (sectionHeader->sh_offset % e->page_size);

	// int delta = sectionHeader->sh_offset - aligned;

	// void	*map = mmap(NULL, sectionHeader->sh_size + delta,
	// 		PROT_READ, MAP_PRIVATE, e->fd, aligned);
	// if (map == MAP_FAILED)
	// 	return (NULL);

	// char *ptr = malloc(sectionHeader->sh_size * sizeof(char));
	// if (!ptr)
	// 	return (NULL);

	// ft_memcpy(ptr, map + delta, sectionHeader->sh_size);

	// if (munmap(map, sectionHeader->sh_size + delta))
	// 	return (NULL);
	return (ptr);
}

char	*get_section_by_name(t_elf *e, const char *name)
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
		printf("Section not found : %s\n", name);
		return (NULL);
	}
	ptr = get_section_by_header(e, &e->sectionsHeader[i]);
	return (ptr);
}

Elf64_Shdr	*get_section_header_by_name(t_elf *e, const char *name)
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
		printf("Section Header not found : %s\n", name);
		return (NULL);
	}
	return (&e->sectionsHeader[i]);
}
