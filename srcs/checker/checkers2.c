/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:25:29 by jiarcer           #+#    #+#             */
/*   Updated: 2026/01/22 17:06:18 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//return 0 if valid, 1 if not
int	is_valid_sphere(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (tokens[0][0] != 's' || tokens[0][1] != 'p' || tokens[0][2] != '\0'
		|| (tokens[4] != NULL && tokens[4][1] != '\0'))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2])
		|| ft_isdigit_str(tokens[3]) || check_vector(tokens[1])
		|| check_color_range(tokens[3]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_atod(tokens[2]) < 0)
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//faut-il check les limite de l'orientation ?
//return 0 if valid, 1 if not
int	is_valid_plane(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (tokens[0][0] != 'p' || tokens[0][1] != 'l' || tokens[0][2] != '\0'
		|| (tokens[4] != NULL && tokens[4][1] != '\0'))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2])
		|| ft_isdigit_str(tokens[3]) || check_vector(tokens[1])
		|| check_vector(tokens[2]) || check_color_range(tokens[3])
		|| is_normalised_range(tokens[2]))
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
//return 0 if valid, 1 if not
int	is_valid_cylinder(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (tokens[0][0] != 'c' || tokens[0][1] != 'y' || tokens[0][2] != '\0'
		|| (tokens[6] != NULL && tokens[6][1] != '\0'))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2])
		|| ft_isdigit_str(tokens[3]) || ft_isdigit_str(tokens[4])
		|| ft_isdigit_str(tokens[5]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (check_vector(tokens[1]) || check_vector(tokens[2]) || check_color_range
		(tokens[5]) || is_normalised_range(tokens[2]) || ft_atod
		(tokens[3]) < 0 || ft_atod(tokens[4]) < 0)
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}
