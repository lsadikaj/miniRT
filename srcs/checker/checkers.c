/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:08:39 by jiarcer           #+#    #+#             */
/*   Updated: 2026/01/22 17:04:33 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	is_normalised_range(char *args)
{
	t_vec3	vec;
	char	**res;

	res = ft_split(args, ',');
	vec.x = ft_atod(res[0]);
	vec.y = ft_atod(res[1]);
	vec.z = ft_atod(res[2]);
	ft_free_split(res);
	if (vec.x < -1 || vec.x > 1)
		return (1);
	if (vec.y < -1 || vec.y > 1)
		return (1);
	if (vec.z < -1 || vec.z > 1)
		return (1);
	return (0);
}

int	check_vector(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (token[i] == ',')
			count++;
		i++;
	}
	if (count != 2 || token[i - 1] == ',')
		return (1);
	return (0);
}

//return 0 if valid, 1 if not
int	is_valid_ambiant(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL
		|| tokens[0][0] != 'A' || tokens[0][1] != '\0' || (tokens[3] != NULL
		&& tokens[3][1] != '\0'))
	{
		ft_free_split(tokens);
		return (1);
	}
	if ((ft_atod(tokens[1]) < 0.0 || ft_atod(tokens[1]) > 1.0)
		|| ft_isdigit_str(tokens[1]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (check_color_range(tokens[2]) || ft_isdigit_str(tokens[2]))
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//return 0 if valid, 1 if not
int	is_valid_camera(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL
		|| tokens[3] == NULL || tokens[0][0] != 'C' || tokens[0][1] != '\0'
		|| (tokens[4] != NULL && tokens[4][1] != '\0'))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2]) || ft_isdigit_str
		(tokens[3]) || check_vector(tokens[1]) || check_vector(tokens[2]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_atod(tokens[3]) < 0.0 || ft_atod(tokens[3]) > 180.0 || tokens[3][0]
		== ' ' || tokens[3][0] == '\n' || is_normalised_range(tokens[2]))
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//return 0 if valid, 1 if not
int	is_valid_light(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL
		|| tokens[3] == NULL || tokens[0][0] != 'L' || tokens[0][1] != '\0'
		|| (tokens[4] != NULL && tokens[4][1] != '\0'))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2])
		|| ft_isdigit_str(tokens[3]) || check_vector(tokens[1]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_atod(tokens[2]) < 0.0 || ft_atod(tokens[2]) > 1.0
		|| check_color_range(tokens[3]))
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}
