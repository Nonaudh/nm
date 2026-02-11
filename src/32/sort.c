#include "nm32.h"

void	ft_swap_32(t_symbol32 *sym_biot, t_symbol32 *sym_phoni)
{
	t_symbol32	tmp;

	tmp = *sym_biot;
	*sym_biot = *sym_phoni;
	*sym_phoni = tmp;
}

int	ft_strcmp_underscore_32(t_symbol32 *symb_ouret, t_symbol32 *symb_leau)
{
	char	*tab_ouret = symb_ouret->name;
	char	*tab_leau = symb_leau->name;

	if (!tab_leau || !tab_ouret)
		return (0);

	int result = ft_strcmp_tolower_isalnum(tab_ouret, tab_leau);
	if (result)
		return (result);

	int weak_ouret = ELF32_ST_BIND(symb_ouret->symbol->st_info) == STB_WEAK;
	int weak_leau  = ELF32_ST_BIND(symb_leau->symbol->st_info) == STB_WEAK;

	if (weak_ouret != weak_leau)
		return (weak_ouret - weak_leau);

	result = ft_strncmp(tab_ouret, tab_leau, max(ft_strlen(tab_ouret), ft_strlen(tab_leau)));
	return (result);
}

void	bubbleSort_32(t_symbol32 *tab, size_t size, int bonus_r)
{
	int j, k;
	int	changes = 1;

	for (j = 0; changes && j < size - 1; j++)
	{
		changes = 0;
		for (k = 0; k < size - 1; k++)
		{
			if (!bonus_r && ft_strcmp_underscore_32(&tab[k], &tab[k + 1]) > 0)
			{
				ft_swap_32(&tab[k], &tab[k + 1]);
				changes = 1;
			}
			
			else if (bonus_r && ft_strcmp_underscore_32(&tab[k], &tab[k + 1]) < 0)
			{
				ft_swap_32(&tab[k], &tab[k + 1]);
				changes = 1;
			}		
		}
	}
}

int	sort_and_print_symbols_32(t_symbol_container32 *s, t_elf32 *e, int multiple_file)
{
	if (!e->bonus->p)
		bubbleSort_32(s->tab, s->size, e->bonus->r);
	if (multiple_file)
		ft_printf("\n%s:\n", e->filename);
	print_all_symbols_32(s, e);
	free(s->tab);
	free(s);

	return (0);
}
