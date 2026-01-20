/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:25:41 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/19 17:35:29 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	check_cylinders(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_cylinder	*tmp;
	double		t;

	tmp = scene->cylinders;
	while (tmp)
	{
		t = intersect_cylinder(ray, tmp);
		if (t > 0.001 && t < hit->t)
		{
			hit->t = t;
			hit->obj = tmp;
			hit->type = T_CYLINDER;
		}
		tmp = tmp->next;
	}
}

static t_vec3	calculate_cylinder_normal(t_cylinder *cy, t_vec3 p,
								double height_on_axis)
{
	t_vec3	axis_point;
	t_vec3	normal;
	double	epsilon;

	epsilon = 1e-4;
	if (fabs(height_on_axis) < epsilon)
		normal = vec_multi(cy->direction, -1.0);
	else if (fabs(height_on_axis - cy->height) < epsilon)
		normal = cy->direction;
	else
	{
		axis_point = vec_add(cy->center,
						vec_multi(cy->direction, height_on_axis));
		normal = vec_normalize(vec_sub(p, axis_point));
	}
	return (normal);
}

int	render_cylinder(t_scene scene, t_ray ray, t_hit hit)
{
	t_cylinder	*cy;
	t_vec3		p;
	t_vec3		n;
	double		height_on_axis;

	cy = (t_cylinder *)hit.obj;
	p = find_p(ray, hit.t);
	height_on_axis = vec_dot(vec_sub(p, cy->center), cy->direction);
	n = calculate_cylinder_normal(cy, p, height_on_axis);
	return (plane_light(scene, p, n, cy->color));
}