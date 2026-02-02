#include "nm32.h"
#include <stdio.h>

void	ft_swap_32(t_symbol32 *sym_biot, t_symbol32 *sym_phoni)
{
	t_symbol32 tmp;

	// printf("%s   %s\n", sym_biot->name, sym_phoni->name);

	tmp = *sym_biot;
	*sym_biot = *sym_phoni;
	*sym_phoni = tmp;
}

char	*ft_strdup_without_underscore_and_dot_32(const char *s)
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
		if (s[i] != '_' && s[i] != '.')
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
	{
		printf("Error : ft_strcmp_underscore\n");
		return (0);
	}
	char *tmp_ouret = ft_strdup_without_underscore_and_dot_32(tab_ouret);
	char *tmp_leau = ft_strdup_without_underscore_and_dot_32(tab_leau);

	int x, y, i;

	// for (x = 0; tmp_ouret[x] && (tmp_ouret[x] == '_' || tmp_ouret[x] == '.'); x++)
	// 	;
	// for (y = 0; tmp_leau[y] && (tmp_leau[y] == '_' || tmp_leau[x] == '.'); y++)
	// 	;


	for (i = 0; tmp_ouret[i]; i++)
		tmp_ouret[i] = ft_tolower(tmp_ouret[i]);
	
	for (i = 0; tmp_leau[i]; i++)
		tmp_leau[i] = ft_tolower(tmp_leau[i]);	

	int max = ft_strlen(tmp_ouret) > ft_strlen(tab_leau) ? ft_strlen(tab_ouret) : ft_strlen(tab_leau);
	int result = ft_strncmp(tmp_ouret, tmp_leau, max);

	if (result == 0 && tab_leau[0] == '_')
		result = 1;

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

t_symbol_container32	*erase_duplicate_symbol_32(t_symbol_part32 *symtab, t_symbol_part32 *dynsym, t_elf32 *e)
{
	int i;
	t_symbol_container32	*s = malloc(sizeof(t_symbol_container32));
	if (!s)
		return (NULL);
	s->size = 0;
	s->tab = malloc((symtab->size + dynsym->size) * sizeof(t_symbol32));
	if (!s->tab)
	{
		free(s);
		return (NULL);
	}
	
	for (i = 0; i < symtab->size; i++)
	{

		if (unique_symbol_32(symtab->strtab + symtab->symbol[i].st_name, s))
		{
			s->tab[s->size].symbol = &symtab->symbol[i];
			s->tab[s->size].name = symtab->strtab + symtab->symbol[i].st_name;
			s->size++;
		}
	}
		
	for (i = 0; i < dynsym->size; i++)
	{
		if (unique_symbol_32(dynsym->strtab + dynsym->symbol[i].st_name, s))
		{
			s->tab[s->size].symbol = &dynsym->symbol[i];
			s->tab[s->size].name = dynsym->strtab + dynsym->symbol[i].st_name;
			s->size++;
		}
	}
	return (s);
}

int	print_symbols_32(t_symbol_part32 *symtab, t_symbol_part32 *dynsym, t_elf32 *e)
{
	int i;
	t_symbol_container32	*s = erase_duplicate_symbol_32(symtab, dynsym, e);
	if (!s)
		return (1);

	if (!e->bonus->p)
		bubbleSort_32(s->tab, s->size, e->bonus->r);
	print_all_symbols_32(s, e);
	free(s->tab);
	free(s);

	return (0);
}
