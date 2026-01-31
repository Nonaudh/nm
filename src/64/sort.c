#include "nm64.h"
#include <stdio.h>

void	ft_swap(t_symbol64 *sym_biot, t_symbol64 *sym_phoni)
{
	t_symbol64 tmp;

	tmp = *sym_biot;
	*sym_biot = *sym_phoni;
	*sym_phoni = tmp;
}

int	ft_strcmp_underscore(char *tab_ouret, char *tab_leau)
{
	if (!tab_leau || !tab_ouret)
	{
		printf("Error : ft_strcmp_underscore\n");
		return (0);
	}
	char *tmp_ouret = ft_strdup(tab_ouret);
	char *tmp_leau = ft_strdup(tab_leau);

	int x, y;

	for (x = 0; tmp_ouret[x] && tmp_ouret[x] == '_'; x++)
		;
	for (y = 0; tmp_leau[y] && tmp_leau[y] == '_'; y++)
		;

	for (int i = x; tmp_ouret[i]; i++)
		tmp_ouret[i] = ft_tolower(tmp_ouret[i]);
	
	for (int i = y; tmp_leau[i]; i++)
		tmp_leau[i] = ft_tolower(tmp_leau[i]);	

	int max = ft_strlen(&tmp_ouret[x]) > ft_strlen(&tab_leau[y]) ? ft_strlen(&tab_ouret[x]) : ft_strlen(&tab_leau[y]);
	int result = ft_strncmp(&tmp_ouret[x], &tmp_leau[y], max);

	if (result == 0 && tab_leau[0] == '_')
		result = 1;

	if (tmp_ouret)
		free(tmp_ouret);
	if (tmp_leau)
		free(tmp_leau);

	return (result);
}

void	bubbleSort(t_symbol64 *tab, size_t size, int bonus_r)
{
	int j, k;

	for (j = 0; j < size - 1; j++)
	{
		for (k = 0; k < size - 1; k++)
		{
			if (!bonus_r && ft_strcmp_underscore(tab[k].name, tab[k + 1].name) > 0)	
				ft_swap(&tab[k], &tab[k + 1]);
			else if (bonus_r && ft_strcmp_underscore(tab[k].name, tab[k + 1].name) < 0)
				ft_swap(&tab[k], &tab[k + 1]);
		}
	}
}

int	unique_symbol(char *name, t_symbol_container64 *s)
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

t_symbol_container64	*erase_duplicate_symbol(t_symbol_part64 *symtab, t_symbol_part64 *dynsym, t_elf64 *e)
{
	int i;
	t_symbol_container64	*s = malloc(sizeof(t_symbol_container64));
	if (!s)
		return (NULL);
	s->size = 0;
	s->tab = malloc((symtab->size + dynsym->size) * sizeof(t_symbol64));
	if (!s->tab)
	{
		free(s);
		return (NULL);
	}
	
	for (i = 0; i < symtab->size; i++)
	{

		if (unique_symbol(symtab->strtab + symtab->symbol[i].st_name, s))
		{
			s->tab[s->size].symbol = &symtab->symbol[i];
			s->tab[s->size].name = symtab->strtab + symtab->symbol[i].st_name;
			s->size++;
		}
	}
		
	for (i = 0; i < dynsym->size; i++)
	{
		if (unique_symbol(dynsym->strtab + dynsym->symbol[i].st_name, s))
		{
			s->tab[s->size].symbol = &dynsym->symbol[i];
			s->tab[s->size].name = dynsym->strtab + dynsym->symbol[i].st_name;
			s->size++;
		}
	}
	return (s);
}

int	print_symbols(t_symbol_part64 *symtab, t_symbol_part64 *dynsym, t_elf64 *e)
{
	int i;
	t_symbol_container64	*s = erase_duplicate_symbol(symtab, dynsym, e);
	if (!s)
		return (1);

	if (!e->bonus->p)
		bubbleSort(s->tab, s->size, e->bonus->r);
	print_all_symbols(s, e);
	free(s->tab);
	free(s);

	return (0);
}
