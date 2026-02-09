#include "nm64.h"

void	ft_swap_64(t_symbol64 *sym_biot, t_symbol64 *sym_phoni)
{
	t_symbol64 tmp;

	tmp = *sym_biot;
	*sym_biot = *sym_phoni;
	*sym_phoni = tmp;
}

char	*ft_strdup_ifalnum_64(const char *s)
{
	char	*tab;
	int		x;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	x = ft_strlen(s);
	tab = malloc(sizeof(char) * (x + 1));
	if (tab == NULL)
		return (NULL);
	x = 0;
	while (s[i])
	{
		if (ft_isalnum(s[i]))
		{
			tab[x] = s[i];
			x++;
		}
		i++;
	}
	tab[x] = 0;
	return (tab);
}

int	ft_strcmp_tolower_isalnum_64(char *s1, char *s2)
{
	int i = 0, k = 0;

	while (s1[i] && s2[k])
	{
		while (s1[i] && !ft_isalnum(s1[i]))
			i++;
		while (s2[k] && !ft_isalnum(s2[k]))
			k++;

		if (ft_tolower(s1[i]) != ft_tolower(s2[k]) || !s1[i] || !s2[k])
			break ;
		i++;
		k++;

	}
	return (ft_tolower(s1[i]) - ft_tolower(s2[k]));
}

int	ft_strcmp_isalnum_64(char *s1, char *s2)
{
	int i = 0, k = 0;

	while (s1[i] && s2[k])
	{
		while (s1[i] && !ft_isalnum(s1[i]))
			i++;
		while (s2[k] && !ft_isalnum(s2[k]))
			k++;

		if (s1[i] != s2[k] || !s1[i] || !s2[k])
			break ;
		i++;
		k++;
	}
	return (s1[i] - s2[k]);
}

int	ft_strcmp_underscore_64(t_symbol64 *symb_ouret, t_symbol64 *symb_leau)
{
	char	*tab_ouret = symb_ouret->name;
	char *tab_leau = symb_leau->name;

	if (!tab_leau || !tab_ouret)
		return (0);

	int result = ft_strcmp_tolower_isalnum_64(tab_ouret, tab_leau);
	if (result)
		return (result);

	result = ft_strcmp_isalnum_64(tab_ouret, tab_leau);
	if (result)
		return (result);
	
	// if (tab_ouret[0] == '.' && tab_leau[0] != '.')
	// 	return (-1);

	int max = ft_strlen(tab_ouret) > ft_strlen(tab_leau) ? ft_strlen(tab_ouret) : ft_strlen(tab_leau);
	result = ft_strncmp(tab_ouret, tab_leau, max);
	return (result);
}

void	bubbleSort_64(t_symbol64 *tab, size_t size, int bonus_r)
{
	int j, k;
	int	changes = 1;

	for (j = 0; changes && j < size - 1; j++)
	{
		changes = 0;
		for (k = 0; k < size - 1; k++)
		{
			if (!bonus_r && (ft_strcmp_underscore_64(&tab[k], &tab[k + 1]) > 0))
			{
				ft_swap_64(&tab[k], &tab[k + 1]);
				changes = 1;
			}
			
			else if (bonus_r && ft_strcmp_underscore_64(&tab[k], &tab[k + 1]) < 0)
			{
				ft_swap_64(&tab[k], &tab[k + 1]);
				changes = 1;
			}		
		}
	}
}

int	unique_symbol_64(char *name, t_symbol_container64 *s)
{
	int	i;

	for (i = 0; i < s->size; i++)
	{
		if (ft_strncmp(name, s->tab[i].name, ft_strlen(name)) == 0)
		{
			if (ft_strlen(name) == ft_strlen(s->tab[i].name) || 
				ft_strchr(s->tab[i].name, '@'))
				break ;
		}
	}
	if (i == s->size || ELF64_ST_TYPE(s->tab[i].symbol->st_info) == STT_FILE)
		return (1);
	return (0);
}

int	not_second_blank_64(Elf64_Sym *symbol, char *strtab, int i)
{
	char *name = symbol->st_name + strtab;
	if (ELF64_ST_TYPE(symbol->st_info) != STT_SECTION && name && !name[0] && i != 0)
		return (0);
	return (1);
}

t_symbol_container64	*erase_duplicate_symbol_64(t_symbol_part64 *symtab, t_elf64 *e)
{
	int i;
	t_symbol_container64	*s = malloc(sizeof(t_symbol_container64));
	if (!s)
		return (NULL);
	s->size = 0;
	s->tab = malloc((symtab->size) * sizeof(t_symbol64));
	if (!s->tab)
	{
		free(s);
		return (NULL);
	}
	
	for (i = 1; i < symtab->size; i++)
	{
		if (1 || not_second_blank_64(&symtab->symbol[i], symtab->strtab, i))
		{
			s->tab[s->size].symbol = &symtab->symbol[i];
			if (ELF64_ST_TYPE(symtab->symbol[i].st_info) != STT_SECTION)
				s->tab[s->size].name = symtab->strtab + symtab->symbol[i].st_name;
			else
			{
				s->tab[s->size].name = e->shstrtab + e->sectionsHeader[symtab->symbol[i].st_shndx].sh_name;
			}
			s->size++;
		}
	}
	return (s);
}

int	print_symbols_64(t_symbol_part64 *symtab, t_elf64 *e, int multiple_file)
{
	int i;
	t_symbol_container64	*s = erase_duplicate_symbol_64(symtab, e);
	if (!s)
		return (1);

	if (!e->bonus->p)
		bubbleSort_64(s->tab, s->size, e->bonus->r);
	if (multiple_file)
		ft_printf("\n%s:\n", e->filename);
	print_all_symbols_64(s, e);
	free(s->tab);
	free(s);

	return (0);
}
