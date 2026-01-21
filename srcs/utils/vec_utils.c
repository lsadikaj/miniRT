/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:33:47 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 22:03:40 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// Calculate the vectorial product of 2 vectors
// return a vector perpendicular of the 2 given in parameter
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

// Calculate and return the length of a vector
double	vec_length(t_vec3 v)
{
	double	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (len);
}

// Normalize a vector
t_vec3	vec_normalize(t_vec3 v)
{
	double	len;
	t_vec3	result;

	len = vec_length(v);
	if (len < 0.0001)
	{
		result.x = 0;
		result.y = 0;
		result.x = 0;
		return (result);
	}
	return (vec_divide(v, len));
}

// Pythagore to check if a vector is normalized, return 0 for succes
int	is_normalized(char *args)
{
	double	len;
	t_vec3	v;
	char	**res;

	res = ft_split(args, ',');
	v.x = ft_atod(res[0]);
	v.y = ft_atod(res[1]);
	v.z = ft_atod(res[2]);
	len = vec_length(v);
	ft_free_split(res);
	if (len < 0.99 || len > 1.01)
		return (1);
	return (0);
}

//retourne le vecteur direction allant de "from" a "to" normalisé
t_vec3	vec_direction(t_vec3 from, t_vec3 to)
{
	t_vec3	result;

	result = vec_sub(to, from);
	result = vec_normalize(result);
	return (result);
}
