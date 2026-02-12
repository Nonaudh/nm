#ifndef SHARED_HPP
# define SHARED_HPP

typedef struct s_bonus
{
	int a;
	int g;
	int u;
	int r;
	int p;
} t_bonus;

int	not_an_elf(char *map, char *filename);
int	check_file(int fd, char *filename);
int	find_class(char *filename);
int	fill_option_struct(char option, t_bonus *bonus);
int	is_an_option(char *str, t_bonus *bonus);
int	number_of_files(int argc, char **argv);

int	ft_strcmp_tolower_isalnum(char *s1, char *s2);
int max(int x, int y);

#endif