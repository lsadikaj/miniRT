/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:35:39 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 17:34:22 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
/*
#include <stdio.h>
#include <fcntl.h>  // Pour open

int	main(void)
{
	int	fd;

	// Test 1: Écrire dans la sortie standard (écran)
	ft_putstr_fd("Hello, World!\n", 1);

	// Test 2: Écrire dans un fichier
	fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Unable to open file\n", 1);
	}

	ft_putstr_fd("This is a test string in the file.\n", fd);
	close(fd);

	return (0);
}
*/