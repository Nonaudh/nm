#include <sys/mman.h>
#include <fcntl.h>
#include <elf.h>
#include "nm64.h"
#include "nm32.h"
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc < 1)
		return (1);

	t_bonus bonus;
	ft_bzero(&bonus, sizeof(t_bonus));
	int elf_class;
	int i;
	int	files_nb = 0;
	int return_value = 0;
	char	*filename;

	for (i = 1; i < argc; i++)
	{
		if (argv[i] && ft_strchr(argv[i], '-') == argv[i])
		{
			if (is_an_option(argv[i], &bonus))
				return (1);
		}
	}

	files_nb = number_of_files(argc, argv);

	for (i = 1; i < argc || !files_nb; i++)
	{
		if ((argv[i] && ft_strchr(argv[i], '-') != argv[i]) || !files_nb)
		{
			filename = files_nb ? argv[i] : "a.out";
			elf_class = find_class(filename);
			if (elf_class == ELFCLASS64)
			{
				if (nm64(filename, &bonus, files_nb))
					return_value = 1;
			}
			else if (elf_class == ELFCLASS32)
			{
				if (nm32(filename, &bonus, files_nb))
					return_value = 1;
			}
			else
				return_value = 1;
		}
		if (!files_nb)
			files_nb = -1;
	}
	return (return_value);
}