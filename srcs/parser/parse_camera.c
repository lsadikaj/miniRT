+/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 13:08:16 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/12 13:10:35 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// parses camera line and fills the scene->camera, return 0 for succes
int	parse_camera(char *line, t_scene *scene)
{
	int		i;
	double	fov;
	t_vec3	position;
	t_vec3	direction;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (parse_vector(line, &i, &position))
		return (write(2, "Error\nInvalid camera position\n", 31), 0);
	if (parse_vector(line, &i, &direction))
		return (write(2, "Error\nInvalid camera direction\n", 32), 0);
	if (is_not_normalized(direction))
		return (write(2, "Error\nCamera direction not normalized\n", 39, 0));
	i = skip_whitespaces(line, i);
	fov = ft_atod(&line[i]);
	scene->camera.fov = fov;
	scene->camera.position = position;
	scene->camera.direction = direction;
	return (0);
}