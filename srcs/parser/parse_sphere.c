/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:22:42 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/05 16:16:12 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// create a node in linked list t_sphere with malloc
static t_sphere	*create_sphere(t_vec3 center, double diameter, t_color color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->radius = diameter / 2.0;
	sphere->color = color;
	sphere->next = NULL;
	return (sphere);
}

// add node in back of linked list t_spheres
static void	add_sphere_to_list(t_scene *scene, t_sphere *new_sphere)
{
	t_sphere	*current;

	if (!scene->spheres)
	{
		scene->spheres = new_sphere;
		return ;
	}
	current = scene->spheres;
	while (current->next)
		current = current->next;
	current->next = new_sphere;
}

// parse sphere line and fills linked list t_scene->spheres
int	parse_sphere(char *line, t_scene *scene)
{
	int			i;
	t_vec3		center;
	double		diameter;
	t_color		color;
	t_sphere	*new_sphere;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	if (parse_vector(line, &i, &center))
		return (1);
	i = skip_whitespaces(line, i);
	diameter = ft_atod(&line[i]);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i = skip_whitespaces(line, i);
	color = parse_color(&line[i]);
	if (color.r == -1)
		return (1);
	new_sphere = create_sphere(center, diameter, color);
	if (!new_sphere)
		return (1);
	add_sphere_to_list(scene, new_sphere);
	return (0);
}
