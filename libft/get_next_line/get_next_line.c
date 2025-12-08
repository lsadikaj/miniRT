/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:38:20 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/12/26 12:07:46 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	read_buffer(int fd, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
		buffer[bytes_read] = '\0';
	return (bytes_read);
}

static char	*append_buffer(char *left_c, char *buffer)
{
	char	*temp;

	if (!left_c)
		left_c = ft_strdup(buffer);
	else
	{
		temp = left_c;
		left_c = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (left_c);
}

static char	*fill_line_buffer(int fd, char *left_c)
{
	ssize_t	bytes_read;
	char	buffer[BUFFER_SIZE + 1];

	bytes_read = read_buffer(fd, buffer);
	while (bytes_read > 0)
	{
		left_c = append_buffer(left_c, buffer);
		if (!left_c)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read_buffer(fd, buffer);
	}
	if (bytes_read == -1)
	{
		free(left_c);
		return (NULL);
	}
	return (left_c);
}

static char	*extract_line(char **left_c)
{
	size_t	i;
	char	*line;
	char	*new_left_c;

	if (!*left_c || **left_c == '\0')
		return (NULL);
	i = 0;
	while ((*left_c)[i] && (*left_c)[i] != '\n')
		i++;
	if ((*left_c)[i] == '\n')
		i++;
	line = ft_substr(*left_c, 0, i);
	if (!line)
		return (NULL);
	new_left_c = ft_strdup(*left_c + i);
	free(*left_c);
	*left_c = new_left_c;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*left_c = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (left_c)
			free(left_c);
		left_c = NULL;
		return (NULL);
	}
	left_c = fill_line_buffer(fd, left_c);
	if (!left_c)
		return (NULL);
	line = extract_line(&left_c);
	if (!line)
	{
		free(left_c);
		left_c = NULL;
	}
	return (line);
}
