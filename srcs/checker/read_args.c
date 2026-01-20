#include "../includes/minirt.h"

int	check_objnb(char **args)
{
	int	i;
	int	a;
	int	c;
	int	l;

	i = 0;
	a = 0;
	c = 0;
	l = 0;
	while (args[i])
	{
		if (args[i][0] == 'A' && args[i][1] == ' ')
			a++;
		else if (args[i][0] == 'C' && args[i][1] == ' ')
			c++;
		else if (args[i][0] == 'L' && args[i][1] == ' ')
			l++;
		i++;
	}
	if (a != 1 || c != 1 || l != 1)
	{
		printf("Error\nInvalid number of A, C or L objects. A and C must be exactly 1, L at least 1.\n");
		return (1);
	}
	return (0);
}

int	check_aclnb(int fd)
{
	int		i;
	int		j;
	char	**args;
	char	*line;

	i = 0;
	j = 0;
	args = malloc(sizeof(char *) * 1);
	while ((line = get_next_line(fd)))
	{
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		args = realloc(args, sizeof(char *) * (ft_strlen(line) + 1 - j + i));
		args[i] = ft_strdup(line + j);
		free(line);
		j = 0;
		i++;
	}
	args[i] = NULL;
	i = 0;
	if (check_objnb(args))
	{
		ft_free_split(args);
		close(fd);
		return (1);
	}
	ft_free_split(args);
	close(fd);
	return (0);
}

int	read_args(char *filename)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	if (check_aclnb(open(filename, O_RDONLY)))
		return (1);
	while ((line = get_next_line(fd)))
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0' || line[i] == '\n')
		{
			free(line);
			i = 0;
			continue ;
		}
		if (line[i] == '\0' || line[i] == '\n')
		{
			free(line);
			i = 0;
			continue ;
		}
		if (check_args(line + i) == 1)
		{
			printf("Error\nInvalid line in file: %s", line);
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		i = 0;
	}
	close(fd);
	return (0);
}

/* char** read_args(char *filename)
{
    int     fd;
    char    *line;
    char    **args;
    int     i;
    int     j;

    i = 0;
    j = 0;
    args = malloc(sizeof(char*) * 1);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    while((line = get_next_line(fd)))
    {
        while(line[j] == ' ' || line[j] == '\t')
            j++;
        args = realloc(args, sizeof(char*) * (ft_strlen(line) + 1 - j + i));
        args[i] = ft_strdup(line + j);
        free(line);
        j = 0;
        i++;
    }
    args[i] = NULL;
    i = 0;
    close(fd);
    return (args);
} */
