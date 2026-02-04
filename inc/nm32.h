#ifndef NM32_H
# define NM32_H

#include <elf.h>
#include "libft.h"
#include "bonus.h"

typedef struct s_symbol_part32
{
	Elf32_Sym	*symbol;
	char	*strtab;
	int	size;
} t_symbol_part32;

typedef struct s_symbol32
{
	Elf32_Sym *symbol;
	char *name;

} t_symbol32;

typedef struct s_symbol_container32
{
	t_symbol32 *tab;
	size_t size;

} t_symbol_container32;

typedef struct s_elf32
{
	char *filename;
	int	file_size;
	void	*file_map;
	Elf32_Ehdr	*elf_header;
	Elf32_Shdr	*sectionsHeader;
	char	*shstrtab;
	t_bonus *bonus;
} t_elf32;

int	print_symbols_32(t_symbol_part32 *symtab, t_elf32 *e, int multiple_file);

void	*get_file_in_a_map_32(int fd, int page_size);
Elf32_Ehdr	*get_elf_header_32(t_elf32 *e);
Elf32_Shdr	*get_sections_header_32(t_elf32 *e);

char	*get_section_by_header_32(t_elf32 *e, Elf32_Shdr *sectionHeader);
char	*get_section_by_name_32(t_elf32 *e, const char *name);
Elf32_Shdr	*get_section_header_by_name_32(t_elf32 *e, const char *name);

void	print_all_symbols_32(t_symbol_container32 *s, t_elf32 *e);
int nm32(char *filename, t_bonus *bonus, int multiple_file);

#endif
