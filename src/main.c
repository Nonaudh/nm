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
	int	multiple_file = 0;
	int return_value = 0;
	char *file = NULL; // to re-do

	for (i = 1; i < argc; i++)
	{
		if (argv[i] && ft_strchr(argv[i], '-') == argv[i])
		{
			if (is_an_option(argv[i], &bonus))
				return (1);
		}
		else
			file = (void *)1;
	}

	for (i = 1; i < argc; i++)
	{
		if (argv[i] && ft_strchr(argv[i], '-') != argv[i])
		{
			multiple_file = more_than_one_file(argc, argv);
			elf_class = find_class(argv[i]);
			if (elf_class == ELFCLASS64)
			{
				if (nm64(argv[i], &bonus, multiple_file))
					return_value = 1;
			}
			else if (elf_class == ELFCLASS32)
			{
				if (nm32(argv[i], &bonus, multiple_file))
					return_value = 1;
			}
			else
				return_value = 1;
		}
	}
	return (return_value);
}