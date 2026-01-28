#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <elf.h>
#include "nm64.h"
#include <sys/stat.h>
	
int	not_an_elf(char *map)
{
	if (map[0] != 0x7f || map[1] != 'E' || map[2] != 'L' || map[3] != 'F')
	{
		ft_putstr_fd("Not an ELF\n", 2);
		return (1);
	}
	return (0);
}

int	check_file(int fd)
{
	struct stat stat;

	if (fstat(fd, &stat))
	{
		ft_putstr_fd("Error: fsat\n", 2);
		return (1);
	}
	if (stat.st_size < EI_NIDENT)
	{
		ft_putstr_fd("File too small\n", 2);
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
	if (check_file(fd))
	{
		close(fd);
		return (0);
	}
	char	*map = mmap(NULL, EI_NIDENT, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED)
		return (0);
	close (fd);

	if (not_an_elf(map))
		return (0);
	class = map[EI_CLASS];
	munmap(map, EI_NIDENT);
	return (class);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);

	int elf_class = find_class(argv[argc - 1]);

	if (elf_class == ELFCLASS64)
	{
		if (nm64(argc, argv))
			return (1);
	}
		
	else if (elf_class == ELFCLASS32)
		printf("elf32\n");

	return (0);
}