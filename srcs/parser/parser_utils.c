/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:45:31 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/17 17:42:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// skip spaces and tabulations, return the new index
int	skip_whitespaces(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

// Pythagore to check if a vector is normalized, return 0 for succes
int	is_not_normalized(t_vec3 v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len < 0.99 || len > 1.01)
		return (1);
	return (0);
}

// parses 3D vectors (x, y, z) and fills t_vec3, return 0 for succes
int	parse_vector(char *str, int *i, t_vec3 *v)
{
	*i = skip_whitespaces(str, *i);
	v->x = ft_atod(&str[*i]);
	while (str[*i] && str[*i] != ',' && str[*i] != ' ' && str[*i] != '\t')
		(*i)++;
	if (str[*i] != ',')
		return (1);
	(*i)++;
	v->y = ft_atod(&str[*i]);
	while (str[*i] && str[*i] != ',' && str[*i] != ' ' && str[*i] != '\t')
		(*i)++;
	if (str[*i] != ',')
		return (1);
	(*i)++;
	v->z = ft_atod(&str[*i]);
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\n')
		(*i)++;
	return (0);
}

//parses color from string "R,G,B", fills and return a t_color 
t_color	parse_color(char *str)
{
	t_color	color;
	char	**components;

	components = ft_split(str, ',');
	if (!components)
	{
		color.r = -1;
		return (color);
	}
	color.r = ft_atoi(components[0]);
	color.g = ft_atoi(components[1]);
	color.b = ft_atoi(components[2]);
	ft_free_split(components);
	return (color);
}
