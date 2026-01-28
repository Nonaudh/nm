#ifndef NM64_H
# define NM64_H

#include <elf.h>
#include "libft.h"

typedef struct s_symbol64
{
	Elf64_Sym *symbol;
	char *name;

} t_symbol64;

typedef struct s_symbol_container64
{
	t_symbol64 *tab;
	size_t size;

} t_symbol_container64;

typedef struct s_elf64
{
	int page_size;
	int	file_size;
	void	*file_map;
	Elf64_Ehdr	*elf_header;
	Elf64_Shdr	*sectionsHeader;
	char	*shstrtab;
} t_elf64;

int	print_symbols(Elf64_Shdr *symtabHeader, Elf64_Sym *symtab, char *strtab, Elf64_Shdr *dynsymHeader, Elf64_Sym *dynsym, char *dynstr, t_elf64 *e);

void	*get_file_in_a_map(int fd, int page_size);
Elf64_Ehdr	*get_elf_header(t_elf64 *e);
Elf64_Shdr	*get_sections_header(t_elf64 *e);

char	*get_section_by_header(t_elf64 *e, Elf64_Shdr *sectionHeader);
char	*get_section_by_name(t_elf64 *e, const char *name);
Elf64_Shdr	*get_section_header_by_name(t_elf64 *e, const char *name);

void	print_all_symbols(t_symbol_container64 *s, t_elf64 *e);
int nm64(int argc, char **argv);

#endif
