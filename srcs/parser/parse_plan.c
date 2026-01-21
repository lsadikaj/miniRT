/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:58:16 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 17:59:44 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// create a node in link list t_plane with malloc
static t_plane	*create_plane(t_vec3 point, t_vec3 direction, t_color color)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->point = point;
	direction = vec_normalize(direction);
	plane->direction = direction;
	plane->color = color;
	plane->next = NULL;
	return (plane);
}

// add node in back of link list t_planes
static void	add_plane_to_list(t_scene *scene, t_plane *new_plane)
{
	t_plane	*current;

	if (!scene || !new_plane)
		return ;
	new_plane->next = NULL;
	if (!scene->planes)
	{
		scene->planes = new_plane;
		return ;
	}
	current = scene->planes;
	while (current->next)
		current = current->next;
	current->next = new_plane;
}

// extract plane data and fill scenes->planes
static int	extract_plane_data(char *line, t_vec3 *point,
						t_vec3 *direction, t_color *color)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	if (parse_vector(line, &i, point))
		return (1);
	if (parse_vector(line, &i, direction))
		return (1);
	i = skip_whitespaces(line, i);
	*color = parse_color(&line[i]);
	if (color->r == -1)
		return (1);
	return (0);
}

// parse plane line and fill scenes->planes link list
int	parse_plane(char *line, t_scene *scene)
{
	t_vec3	point;
	t_vec3	direction;
	t_color	color;
	t_plane	*new_plane;

	if (extract_plane_data(line, &point, &direction, &color))
		return (1);
	new_plane = create_plane(point, direction, color);
	if (!new_plane)
		return (1);
	add_plane_to_list(scene, new_plane);
	return (0);
}
