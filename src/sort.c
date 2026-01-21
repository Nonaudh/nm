#include "nm.h"
#include <stdio.h>

void	ft_swap(t_symbol *sym_biot, t_symbol *sym_phoni)
{
	t_symbol tmp;

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
	char *tmp_ouret;
	char *tmp_leau;

	tmp_ouret = ft_strtrim(tab_ouret, "_");
	tmp_leau = ft_strtrim(tab_leau, "_");

	for (int i = 0; tmp_ouret[i]; i++)
		tmp_ouret[i] = ft_tolower(tmp_ouret[i]);
	
	for (int i = 0; tmp_leau[i]; i++)
		tmp_leau[i] = ft_tolower(tmp_leau[i]);	

	int max = ft_strlen(tab_ouret) > ft_strlen(tab_leau) ? ft_strlen(tab_ouret) : ft_strlen(tab_leau);
	int result = ft_strncmp(tmp_ouret, tmp_leau, max);

	if (result == 0 && tab_leau[0] == '_')
		result = 1;

	free(tmp_leau);
	free(tmp_ouret);
	return (result);
}

void	bubbleSort(t_symbol *list, size_t size)
{
	int j, k;

	for (j = 0; j < size - 1; j++)
	{
		for (k = 0; k < size - 1; k++)
		{
			if (ft_strcmp_underscore(list[k].name, list[k + 1].name) > 0)
			{			
				ft_swap(&list[k], &list[k + 1]);
			}
		}
	}
}

int	unique_symbol(char *name, t_symbol_container *s)
{
	int	i;

	for (i = 0; i < s->size; i++)
	{
		if (ft_strncmp(name, s->list[i].name, ft_strlen(name)) == 0)
		{
			if (ft_strlen(name) == ft_strlen(s->list[i].name) || 
				ft_strchr(s->list[i].name, '@'))
				break ;
		}
	}
	if (i == s->size)
		return (1);
	return (0);
}

void	print_container(t_symbol_container *s)
{
	for (int i = 0; i < s->size; i++)
	{
		printf("%s\n", s->list[i].name);
	}
}

int	print_symbols(Elf64_Shdr *symtabHeader, Elf64_Sym *symtab, char *strtab, Elf64_Shdr *dynsymHeader, Elf64_Sym *dynsym, char *dynstr)
{
	int i;
	t_symbol_container	s;

	s.size = 0;
	s.list = malloc(((symtabHeader->sh_size / symtabHeader->sh_entsize) + (dynsymHeader->sh_size / dynsymHeader->sh_entsize)) * sizeof(t_symbol));
	if (!s.list)
		return (1);
	
	for (i = 0; i < symtabHeader->sh_size / symtabHeader->sh_entsize; i++)
	{

		if (unique_symbol(strtab + symtab[i].st_name, &s))
		{
			s.list[s.size].symbol = &symtab[i];
			s.list[s.size].name = strtab + symtab[i].st_name;
			s.size++;
		}
	}
		
	for (i = 0; i < dynsymHeader->sh_size / dynsymHeader->sh_entsize; i++)
	{
		if (unique_symbol(dynstr + dynsym[i].st_name, &s))
		{
			s.list[s.size].symbol = &dynsym[i];
			s.list[s.size].name = dynstr + dynsym[i].st_name;
			s.size++;
		}
	}

	bubbleSort(s.list, s.size);
	print_all_symbols(&s);

	return (0);
}
