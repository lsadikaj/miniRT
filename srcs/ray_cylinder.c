/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:25:41 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/17 17:41:50 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_vec3	calculate_body_normal(t_cylinder *cylinder, double h_o_axis)
{
	t_vec3	axis_point;
	t_vec3	normal;
	
	axis_point = vec_add(cylinder->center,
						vec_multi(cylinder->direction, h_o_axis));
	normal = vec_normalize(vec_sub(cylinder->p, axis_point));
	return (normal);
}

static t_vec3	calculate_cylinder_normal(t_cylinder *cylinder, double h_o_axis)
{
	t_vec3	normal;
	double	epsilon;

	epsilon = 1e-4;
	if (fabs(h_o_axis) < epsilon)
		normal = vec_multi(cylinder->direction, -1.0);
	else if (fabs(h_o_axis - cylinder->height) < epsilon)
		normal = cylinder->direction;
	else
		normal = calculate_body_normal(cylinder, h_o_axis);
	cylinder->normal = normal;
	return (normal);
}

static int	apply_cylinder_lighting(t_cylinder *cylinder, t_vec3 normal,
				t_scene scene)
{
	t_vec3	light_dir;
	double	light_intensity;
	int		color;

	light_dir = vec_normalize(vec_sub(scene.light.position, cylinder->p));
	light_intensity = vec_dot(normal, light_dir) * scene.light.brightness;
	if (light_intensity < 0.0)
		light_intensity = 0.0;
	color = create_color(
			(int)(cylinder->color.r * light_intensity),
			(int)(cylinder->color.g * light_intensity),
			(int)(cylinder->color.b * light_intensity));
	return (color);
}

static int	ray_cylinder2(t_cylinder *closest_cyl, t_scene scene)
{
	t_vec3	normal;
	double	height_on_axis;

	height_on_axis = vec_dot(vec_sub(closest_cyl->p, closest_cyl->center),
								closest_cyl->direction);
	normal = calculate_cylinder_normal(closest_cyl, height_on_axis);
	return (apply_cylinder_lighting(closest_cyl, normal, scene));
}

int	ray_cylinder(t_ray ray, t_scene scene)
{
	double		current_t;
	t_cylinder	*current_cyl;
	t_cylinder	*closest_cyl;

	scene.cylinders->closest_t = INFINITY;
	closest_cyl = NULL;
	current_cyl = scene.cylinders;
	while (current_cyl)
	{
		current_t = intersect_cylinder(ray, current_cyl);
		if (current_t > 0.0 && current_t < scene.cylinders->closest_t)
		{
			scene.cylinders->closest_t = current_t;
			closest_cyl = current_cyl;
		}
		current_cyl = current_cyl->next;
	}
	if (closest_cyl)
		return (ray_cylinder2(closest_cyl, scene));
	return (0x000000FF);
}