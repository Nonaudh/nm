#include "nm64.h"
#include <stdio.h>

char	define_symbol_type(Elf64_Sym *symtab, t_elf64 *e, char *name)
{
	int	bind = ELF64_ST_BIND(symtab->st_info);
	int	type = ELF64_ST_TYPE(symtab->st_info);
	char c = 0;

	if (symtab->st_shndx == SHN_UNDEF && (name && name[0]))
	{
		if (bind == STB_WEAK)
			return ('w');
		return ('U');
	}

	if (symtab->st_shndx == SHN_ABS || (name && !name[0]))
		return ('A');

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
		{
			if (symtab->st_shndx == SHN_UNDEF)
				return ('v');
			else
				return ('V');
		}
		if (symtab->st_shndx == SHN_UNDEF)
			return ('w');
		else
			return ('W');
	}

	Elf64_Shdr *shdr = &e->sectionsHeader[symtab->st_shndx];

	if (shdr->sh_flags & SHF_EXECINSTR)
		return ('T');

	if ((shdr->sh_flags & SHF_ALLOC) &&
			!(shdr->sh_flags & SHF_WRITE) &&
			!(shdr->sh_flags & SHF_EXECINSTR))
		return ('R');

	if ((shdr->sh_flags & SHF_ALLOC) && (shdr->sh_flags & SHF_WRITE))
	{
		if (shdr->sh_type == SHT_NOBITS)
			return ('B');
		else
			return ('D');
	}
	return ('?');
}

void	print_local_or_global(char c, Elf64_Sym *symtab)
{
	if (c != 'U' && c != 'W' && c != 'V' && ELF64_ST_BIND(symtab->st_info) == STB_LOCAL)
		c = ft_tolower(c);
	printf(" %c ", c);
}

void	print_symbol_value(Elf64_Sym *symtab, char *name)
{
		if (symtab->st_value)
		printf("%016lx", symtab->st_value);
	else
		printf("                ");
}

void print_symbol_line(Elf64_Sym *symtab, char *name,  t_elf64 *e)
{
	print_symbol_value(symtab, name);

	char c = define_symbol_type(symtab, e, name);
	print_local_or_global(c, symtab);

	printf("%s\n", name);
}

void	print_all_symbols(t_symbol_container64 *s, t_elf64 *e)
{
	for (int i = 0; i < s->size; i++)
	{
		print_symbol_line(s->tab[i].symbol, s->tab[i].name, e);
	}
}
