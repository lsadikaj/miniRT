/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:31 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 17:31:24 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isdigit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] == '.' || (str[i] == '-' || str[i] == ','))
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(str[i]) && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	
	i = 1;
	(void)argc;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]))
				printf("%c is digit\n", argv[i][j]);
			else 
				printf("%c is not digit\n", argv[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}
*/