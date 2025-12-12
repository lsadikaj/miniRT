/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:19:08 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/12 15:52:18 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// parses ambient light line and fills scene->ambient, return 0 for succes
int	parse_ambient(char *line, t_scene *scene)
{
	int		i;
	double	ratio;
	t_color	color;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i = skip_whitespaces(line, i);
	ratio = ft_atod(&line[i]);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i = skip_whitespaces(line, i);
	color = parse_color(&line[i]);
	if (color.r == -1)
		return (1);
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	return (0);
}

// parses camera line and fills scene->camera, return 0 for succes
int	parse_camera(char *line, t_scene *scene)
{
	int		i;
	t_vec3	position;
	t_vec3	direction;
	double	fov;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	if (parse_vector(line, &i, &position))
		return (1);
	if (parse_vector(line, &i, &direction))
		return (1);
	i = skip_whitespaces(line, i);
	fov = ft_atod(&line[i]);
	scene->camera.position = position;
	scene->camera.direction = direction;
	scene->camera.fov = fov;
	return (0);
}

// parses light line and fills scene->light, return 0 for succes
int	parse_light(char *line, t_scene *scene)
{
	int		i;
	t_vec3	position;
	double	brightness;
	t_color	color;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	if (parse_vector(line, &i, &position))
		return (1);
	i = skip_whitespaces(line, i);
	brightness = ft_atod(&line[i]);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i = skip_whitespaces(line, i);
	color = parse_color(&line[i]);
	if (color.r == -1)
		return (1);
	scene->light.position = position;
	scene->light.brightness = brightness;
	scene->light.color = color;
	return (0);
}
