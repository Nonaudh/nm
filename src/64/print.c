#include "nm64.h"

char	define_symbol_type_64(Elf64_Sym *symtab, t_elf64 *e, char *name)
{
	int	bind = ELF64_ST_BIND(symtab->st_info);
	int	type = ELF64_ST_TYPE(symtab->st_info);
	char c = 0;

	if (symtab->st_shndx == SHN_UNDEF && (name && name[0]))
	{
		if (bind != STB_WEAK)
			return ('U');
		// return ('U');
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

void	print_local_or_global_64(char c, Elf64_Sym *symtab)
{
	if (c != 'U' && c != 'W' && c != 'V' && ELF64_ST_BIND(symtab->st_info) == STB_LOCAL)
		c = ft_tolower(c);
	ft_printf(" %c ", c);
}

void	print_hexa_padding_64(Elf64_Addr value, int base)
{
	char buff[17];
	char *hex = "0123456789abcdef";
	base /= 4;

	buff[base] = 0;
	for (int i = base - 1; i >= 0; i--)
	{
		buff[i] = hex[value & 0xF];
		value >>= 4;
	}
	ft_printf("%s", buff);
}

void	print_symbol_value_64(Elf64_Sym *symtab, char *name)
{
		if (symtab->st_shndx != SHN_UNDEF || (name && !name[0]))
			print_hexa_padding_64(symtab->st_value, 64);
	else
		for (int i = 0; i < 64 / 4; i++)
			ft_printf(" ");
}

void print_symbol_line_64(Elf64_Sym *symtab, char *name,  t_elf64 *e)
{
	print_symbol_value_64(symtab, name);

	char c = define_symbol_type_64(symtab, e, name);
	print_local_or_global_64(c, symtab);

	ft_printf("%s\n", name);
}

int	symbol_to_print_64(t_symbol64 *symbol, t_elf64 *e)
{
	// return (1);
	if (e->bonus->u)
	{
		if (symbol->symbol->st_shndx == SHN_UNDEF && symbol->name && symbol->name[0])
			return (1);
		return (0);
	}
	if (e->bonus->g)
	{
		if (symbol->symbol->st_shndx == SHN_UNDEF && symbol->name && symbol->name[0] || ELF64_ST_BIND(symbol->symbol->st_info) == STB_GLOBAL)
			return (1);
		return (0);
	}
	if (e->bonus->a)
		return (1);
	if (ELF64_ST_TYPE(symbol->symbol->st_info) != STT_FILE && ELF64_ST_TYPE(symbol->symbol->st_info) != STT_SECTION && symbol->name && symbol->name[0])
		return (1);
	// if ((symbol->symbol->st_shndx != SHN_ABS || ELF64_ST_BIND(symbol->symbol->st_info) == STB_GLOBAL) && symbol->name && symbol->name[0])
	// 	return (1);
	return (0);
}

void	print_all_symbols_64(t_symbol_container64 *s, t_elf64 *e)
{
	for (int i = 0; i < s->size; i++)
	{
		if (symbol_to_print_64(&s->tab[i], e))
			print_symbol_line_64(s->tab[i].symbol, s->tab[i].name, e);
	}
}
