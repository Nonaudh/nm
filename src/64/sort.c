#include "nm64.h"

void	ft_swap_64(t_symbol64 *sym_biot, t_symbol64 *sym_phoni)
{
	t_symbol64	tmp;

	tmp = *sym_biot;
	*sym_biot = *sym_phoni;
	*sym_phoni = tmp;
}

int	ft_strcmp_underscore_64(t_symbol64 *symb_ouret, t_symbol64 *symb_leau)
{
	char	*tab_ouret = symb_ouret->name;
	char	*tab_leau = symb_leau->name;

	if (!tab_leau || !tab_ouret)
		return (0);

	int result = ft_strcmp_tolower_isalnum(tab_ouret, tab_leau);
	if (result)
		return (result);

	int weak_ouret = ELF64_ST_BIND(symb_ouret->symbol->st_info) == STB_WEAK;
	int weak_leau  = ELF64_ST_BIND(symb_leau->symbol->st_info) == STB_WEAK;

	if (weak_ouret != weak_leau)
		return (weak_ouret - weak_leau);

	result = ft_strncmp(tab_ouret, tab_leau, max(ft_strlen(tab_ouret), ft_strlen(tab_leau)));
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
			if (!bonus_r && ft_strcmp_underscore_64(&tab[k], &tab[k + 1]) > 0)
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

int	sort_and_print_symbols_64(t_symbol_container64 *s, t_elf64 *e, int multiple_file)
{
	if (!e->bonus->p)
		bubbleSort_64(s->tab, s->size, e->bonus->r);
	if (multiple_file)
		ft_printf("\n%s:\n", e->filename);
	print_all_symbols_64(s, e);
	free(s->tab);
	free(s);

	return (0);
}
