/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:09:45 by jiarcer           #+#    #+#             */
/*   Updated: 2026/01/21 22:54:21 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	process_line_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	if (check_args(line + i) == 1)
	{
		printf("Error\nInvalid line in file: %s", line);
		return (1);
	}
	return (0);
}

static int	process_lines_loop(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (process_line_check(line))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	read_args(char *filename)
{
	int	fd;

	if (check_aclnb(open(filename, O_RDONLY)))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	if (process_lines_loop(fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
