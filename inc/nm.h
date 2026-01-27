#ifndef NM_H
# define NM_H

#include <elf.h>
#include "libft.h"

typedef struct s_symbol
{
	Elf64_Sym *symbol;
	char *name;

} t_symbol;

typedef struct s_symbol_container
{
	t_symbol *tab;
	size_t size;

} t_symbol_container;

typedef struct s_elf
{
	int fd;
	int page_size;
	int	file_size;
	void	*file_map;
	Elf64_Ehdr	*elf_header;
	Elf64_Shdr	*sectionsHeader;
	char	*shstrtab;
} t_elf;

int	print_symbols(Elf64_Shdr *symtabHeader, Elf64_Sym *symtab, char *strtab, Elf64_Shdr *dynsymHeader, Elf64_Sym *dynsym, char *dynstr, t_elf *e);

void	*get_file_in_a_map(int fd, int page_size);
Elf64_Ehdr	*get_elf_header(t_elf *e);
Elf64_Shdr	*get_sections_header(t_elf *e);

char	*get_section_by_header(t_elf *e, Elf64_Shdr *sectionHeader);
char	*get_section_by_name(t_elf *e, const char *name);
Elf64_Shdr	*get_section_header_by_name(t_elf *e, const char *name);

void	print_all_symbols(t_symbol_container *s, t_elf *e);

#endif
