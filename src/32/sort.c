#include "nm32.h"

void	ft_swap_32(t_symbol32 *sym_biot, t_symbol32 *sym_phoni)
{
	t_symbol32 tmp;

	tmp = *sym_biot;
	*sym_biot = *sym_phoni;
	*sym_phoni = tmp;
}

char	*ft_strdup_ifalnum_32(const char *s)
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

int	ft_strcmp_underscore_32(char *tab_ouret, char *tab_leau)
{
	if (!tab_leau || !tab_ouret)
		return (0);

	char *tmp_ouret = ft_strdup_ifalnum_32(tab_ouret);
	char *tmp_leau = ft_strdup_ifalnum_32(tab_leau);

	int i;

	for (i = 0; tmp_ouret[i]; i++)
		tmp_ouret[i] = ft_tolower(tmp_ouret[i]);
	
	for (i = 0; tmp_leau[i]; i++)
		tmp_leau[i] = ft_tolower(tmp_leau[i]);	

	int max = ft_strlen(tmp_ouret) > ft_strlen(tmp_leau) ? ft_strlen(tmp_ouret) : ft_strlen(tmp_leau);
	int result = ft_strncmp(tmp_ouret, tmp_leau, max);

	if (result == 0 && tab_leau[0] == '_')
	{
		max = ft_strlen(tab_ouret) > ft_strlen(tab_leau) ? ft_strlen(tab_ouret) : ft_strlen(tab_leau);
		result = ft_strncmp(tab_ouret, tab_leau, max);
		// ft_printf("%s   %s\n", tab_ouret, tab_leau);
		// result = 1;
	}

	if (tmp_ouret)
		free(tmp_ouret);
	if (tmp_leau)
		free(tmp_leau);

	return (result);
}

void	bubbleSort_32(t_symbol32 *tab, size_t size, int bonus_r)
{
	int j, k;

	for (j = 0; j < size - 1; j++)
	{
		for (k = 0; k < size - 1; k++)
		{
			if (!bonus_r && (ft_strcmp_underscore_32(tab[k].name, tab[k + 1].name) > 0))
				ft_swap_32(&tab[k], &tab[k + 1]);
			else if (bonus_r && ft_strcmp_underscore_32(tab[k].name, tab[k + 1].name) < 0)
				ft_swap_32(&tab[k], &tab[k + 1]);
		}
	}
}

int	unique_symbol_32(char *name, t_symbol_container32 *s)
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
	if (i == s->size || ELF32_ST_TYPE(s->tab[i].symbol->st_info) == STT_FILE)
		return (1);
	return (0);
}

int	not_second_blank_32(char *name, int i)
{
	if (name && !name[0] && i != 0)
		return (0);
	return (1);
}

t_symbol_container32	*erase_duplicate_symbol_32(t_symbol_part32 *symtab, t_elf32 *e)
{
	int i;
	t_symbol_container32	*s = malloc(sizeof(t_symbol_container32));
	if (!s)
		return (NULL);
	s->size = 0;
	s->tab = malloc((symtab->size) * sizeof(t_symbol32));
	if (!s->tab)
	{
		free(s);
		return (NULL);
	}
	
	for (i = 0; i < symtab->size; i++)
	{
		if (not_second_blank_32(symtab->strtab + symtab->symbol[i].st_name, i))
		{
			s->tab[s->size].symbol = &symtab->symbol[i];
			s->tab[s->size].name = symtab->strtab + symtab->symbol[i].st_name;
			// ft_printf("%s\n", s->tab[s->size].name);
			s->size++;
		}
	}
	return (s);
}

int	print_symbols_32(t_symbol_part32 *symtab, t_elf32 *e, int multiple_file)
{
	int i;
	t_symbol_container32	*s = erase_duplicate_symbol_32(symtab, e);
	if (!s)
		return (1);

	if (!e->bonus->p)
		bubbleSort_32(s->tab, s->size, e->bonus->r);
	if (multiple_file)
		ft_printf("\n%s:\n", e->filename);
	print_all_symbols_32(s, e);
	free(s->tab);
	free(s);

	return (0);
}
