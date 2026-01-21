/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:35:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 23:08:59 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// create a node in linked list t_cylinder with malloc
static t_cylinder	*create_cylinder(t_cylinder *temp)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->center = temp->center;
	cylinder->direction = temp->direction;
	cylinder->radius = temp->radius;
	cylinder->height = temp->height;
	cylinder->color = temp->color;
	cylinder->next = NULL;
	return (cylinder);
}

// add node in back of linked list t_cylinder
static void	add_cylinder_to_list(t_scene *scene, t_cylinder *new_cylinder)
{
	t_cylinder	*current;

	if (!scene->cylinders)
	{
		scene->cylinders = new_cylinder;
		return ;
	}
	current = scene->cylinders;
	while (current->next)
		current = current->next;
	current->next = new_cylinder;
}

static int	create_and_add_cylinder(t_scene *scene, t_cylinder *temp)
{
	t_cylinder	*new_cylinder;

	new_cylinder = create_cylinder(temp);
	if (!new_cylinder)
		return (1);
	add_cylinder_to_list(scene, new_cylinder);
	return (0);
}

int	parse_cylinder2(char *line, int i, t_cylinder temp, t_scene *scene)
{
	double	diameter;

	diameter = ft_atod(&line[i]);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i = skip_whitespaces(line, i);
	temp.height = ft_atod(&line[i]);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i = skip_whitespaces(line, i);
	temp.color = parse_color(&line[i]);
	if (temp.color.r == -1)
		return (1);
	temp.radius = diameter / 2.0;
	return (create_and_add_cylinder(scene, &temp));
}

// parse cylinder line and fill linked list t_scene->cylinders
int	parse_cylinder(char *line, t_scene *scene)
{
	int			i;
	t_cylinder	temp;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	if (parse_vector(line, &i, &temp.center))
		return (1);
	if (parse_vector(line, &i, &temp.direction))
		return (1);
	temp.direction = vec_normalize(temp.direction);
	i = skip_whitespaces(line, i);
	return (parse_cylinder2(line, i, temp, scene));
}
