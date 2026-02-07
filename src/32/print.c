#include "nm32.h"

char	define_symbol_type_32(Elf32_Sym *symtab, t_elf32 *e, char *name)
{
	int	bind = ELF32_ST_BIND(symtab->st_info);
	int	type = ELF32_ST_TYPE(symtab->st_info);
	char c = 0;

	if (type == STT_GNU_IFUNC)
    {
        return ('i');
    }

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

	Elf32_Shdr *shdr = &e->sectionsHeader[symtab->st_shndx];

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
	return ('N');
}

void	print_local_or_global_32(char c, Elf32_Sym *symtab)
{
	if (c != 'U' && c != 'W' && c != 'V' && ELF32_ST_BIND(symtab->st_info) == STB_LOCAL)
		c = ft_tolower(c);
	ft_printf(" %c ", c);
}

void	print_hexa_padding_32(Elf32_Addr value, int base)
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

void	print_symbol_value_32(Elf32_Sym *symtab, char *name)
{
		if (symtab->st_shndx != SHN_UNDEF || (name && !name[0]))
			print_hexa_padding_32(symtab->st_value, 32);
	else
		for (int i = 0; i < 32 / 4; i++)
			ft_printf(" ");
}

void print_symbol_line_32(Elf32_Sym *symtab, char *name,  t_elf32 *e)
{
	print_symbol_value_32(symtab, name);

	char c = define_symbol_type_32(symtab, e, name);
	print_local_or_global_32(c, symtab);

	ft_printf("%s\n", name);
}

int	symbol_to_print_32(t_symbol32 *symbol, t_elf32 *e)
{
	if (e->bonus->u)
	{
		if (symbol->symbol->st_shndx == SHN_UNDEF && symbol->name && symbol->name[0])
			return (1);
		return (0);
	}
	if (e->bonus->g)
	{
		if (symbol->symbol->st_shndx == SHN_UNDEF && symbol->name && symbol->name[0] || ELF32_ST_BIND(symbol->symbol->st_info) == STB_GLOBAL || ELF32_ST_BIND(symbol->symbol->st_info) == STB_WEAK)
			return (1);
		return (0);
	}
	if (e->bonus->a)
		return (1);
	if (ELF32_ST_TYPE(symbol->symbol->st_info) != STT_FILE && ELF32_ST_TYPE(symbol->symbol->st_info) != STT_SECTION && symbol->name && symbol->name[0])
		return (1);
	return (0);
}

void	print_all_symbols_32(t_symbol_container32 *s, t_elf32 *e)
{
	for (int i = 0; i < s->size; i++)
	{
		if (symbol_to_print_32(&s->tab[i], e))
			print_symbol_line_32(s->tab[i].symbol, s->tab[i].name, e);
	}
}
