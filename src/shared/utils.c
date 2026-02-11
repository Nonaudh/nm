#include <elf.h>
#include <sys/stat.h>
#include <stdio.h>
#include "shared.h"
#include <sys/mman.h>
#include <fcntl.h>
#include "libft.h"

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

int	more_than_one_file(int argc, char **argv)
{
	int num = 0;

	for (int i = 1; i < argc && num <= 1; i++)
	{
		if (argv[i] && ft_strchr(argv[i], '-') != argv[i])
			num++;
	}
	return(num - 1);
}

int	ft_strcmp_tolower_isalnum(char *s1, char *s2)
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

int max(int x, int y)
{
	return (x > y) ? x : y;
}
