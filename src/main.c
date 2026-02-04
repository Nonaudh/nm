#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include "nm64.h"
#include "nm32.h"
#include <sys/stat.h>
	
int	not_an_elf(char *map, char *filename)
{
	if (map[0] != 0x7f || map[1] != 'E' || map[2] != 'L' || map[3] != 'F')
	{
		ft_dprintf(2, "ft_nm: %s: file format not recognized\n", filename);
		return (1);
	}
	return (0);
}

int	check_file(int fd, char *filename)
{
	struct stat stat;

	if (fstat(fd, &stat))
	{
		ft_putstr_fd("Error: fsat\n", 2);
		return (1);
	}
	if (!stat.st_size)
		return (1);
	if (stat.st_size < EI_NIDENT)
	{
		ft_dprintf(2, "ft_nm: %s: file format not recognized\n", filename);
		return (1);
	}
	return (0);		
}

int	find_class(char *filename)
{
	int class;
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (0);
	}
	if (check_file(fd, filename))
	{
		close(fd);
		return (0);
	}
	char	*map = mmap(NULL, EI_NIDENT, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		return (0);
	close (fd);

	if (not_an_elf(map, filename))
		return (0);
	class = map[EI_CLASS];
	munmap(map, EI_NIDENT);
	return (class);
}

int	fill_option_struct(char option, t_bonus *bonus)
{
	switch (option)
	{
		case 'a':
			bonus->a = 1;
			break;
		case 'g':
			bonus->g = 1;
			break;
		case 'u':
			bonus->u = 1;
			break;
		case 'r':
			bonus->r = 1;
			break;
		case 'p':
			bonus->p = 1;
			break;
		default:
			ft_dprintf(2, "ft_nm: invalid option '%c'\n", option);
			return (1);
	}
	return (0);
}

int	is_an_option(char *str, t_bonus *bonus)
{
	int i;

	for (i = 1; str[i]; i++)
	{
		if (fill_option_struct(str[i], bonus))
			break ;
	}
	if (i != ft_strlen(str))
		return (1);
	return (0);
}

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

	for (i = 1; i < argc; i++)
	{
		if (argv[i] && ft_strchr(argv[i], '-') == argv[i])
		{
			if (is_an_option(argv[i], &bonus))
				return (1);
		}
	}

	for (i = 1; i < argc; i++)
	{
		if (argv[i] && ft_strchr(argv[i], '-') != argv[i])
		{
			if (i != argc - 1)
				multiple_file = 1;
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