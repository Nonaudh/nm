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
	t_symbol *list;
	size_t size;

} t_symbol_container;

int	print_symbols(Elf64_Shdr *symtabHeader, Elf64_Sym *symtab, char *strtab, Elf64_Shdr *dynsymHeader, Elf64_Sym *dynsym, char *dynstr);
Elf64_Ehdr	*get_elf_header(int fd, int page_size);
Elf64_Shdr	*get_sections_header(int fd, Elf64_Ehdr *elfHeader, int page_size);
char	*get_section_by_header(int fd, Elf64_Shdr *sectionNameHeader, int page_size);
char	*get_section_by_name(int fd, const char *str, Elf64_Shdr *sectionHeader, char *shstrtab, int page_size, int shnum);
Elf64_Shdr	*get_section_header_by_name(const char *str, Elf64_Shdr	*sectionHeader, char *shstrtab, int shnum);

void	print_all_symbols(t_symbol_container *s);

uint16_t swap16(uint16_t x);
uint32_t swap32(uint32_t x);
uint64_t swap64(uint64_t x);

#endif
