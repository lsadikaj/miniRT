/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_aclnb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:55:25 by jiarcer           #+#    #+#             */
/*   Updated: 2026/01/21 22:55:32 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_zero(int *i, int *a, int *c, int *l)
{
	if (i)
		*i = 0;
	if (a)
		*a = 0;
	if (c)
		*c = 0;
	if (l)
		*l = 0;
}

int	check_objnb(char **args)
{
	int	i;
	int	a;
	int	c;
	int	l;

	set_zero(&i, &a, &c, &l);
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
		printf("Error\nInvalid number of A, C or L\
			 objects. A and C must be exactly 1, L at least 1.\n");
		return (1);
	}
	return (0);
}

static char	**process_line_add(char **args, char *line, int i)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	args = realloc(args, sizeof(char *) * (ft_strlen(line) + 1 - j + i));
	if (!args)
		return (NULL);
	args[i] = ft_strdup(line + j);
	free(line);
	return (args);
}

static char	**read_all_lines(int fd)
{
	char	**args;
	char	*line;
	int		i;

	args = malloc(sizeof(char *) * 1);
	if (!args)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		args = process_line_add(args, line, i);
		if (!args)
			return (NULL);
		i++;
		line = get_next_line(fd);
	}
	args[i] = NULL;
	return (args);
}

int	check_aclnb(int fd)
{
	char	**args;
	int		ret;

	args = read_all_lines(fd);
	if (!args)
	{
		close(fd);
		return (1);
	}
	ret = check_objnb(args);
	ft_free_split(args);
	close(fd);
	return (ret);
}
