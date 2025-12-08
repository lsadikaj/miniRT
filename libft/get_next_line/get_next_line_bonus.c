/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:37:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2024/11/19 11:42:00 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_fd_list	*get_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	temp = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!temp)
		return (NULL);
	temp->fd = fd;
	temp->left_c = NULL;
	temp->next = *head;
	*head = temp;
	return (temp);
}

static void	remove_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*temp;
	t_fd_list	*prev;

	temp = *head;
	prev = NULL;
	while (temp)
	{
		if (temp->fd == fd)
		{
			if (prev)
				prev->next = temp->next;
			else
				*head = temp->next;
			free(temp->left_c);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
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

static int	read_and_store(int fd, char **left_c)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	while (!ft_strchr(*left_c, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return (0);
		if (bytes_read < 0)
			return (-1);
		buffer[bytes_read] = '\0';
		temp = *left_c;
		*left_c = ft_strjoin(temp, buffer);
		free(temp);
		if (!*left_c)
			return (-1);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*head;
	t_fd_list			*fd_node;
	char				*line;
	int					status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_node = get_fd_node(&head, fd);
	if (!fd_node)
		return (NULL);
	status = read_and_store(fd, &(fd_node->left_c));
	if (status == -1 || (status == 0 && (!fd_node->left_c
				|| fd_node->left_c[0] == '\0')))
	{
		remove_fd_node(&head, fd);
		return (NULL);
	}
	line = extract_line(&(fd_node->left_c));
	if (!line || *line == '\0')
	{
		free(line);
		remove_fd_node(&head, fd);
		return (NULL);
	}
	return (line);
}
