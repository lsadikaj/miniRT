/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:32:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/22 13:01:10 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static double	check_cylinder_height(t_ray ray, t_cylinder *cylinder, double t)
{
	t_vec3	p;
	double	height_on_axis;

	p = find_p(ray, t);
	height_on_axis = vec_dot(vec_sub(p, cylinder->center),
			cylinder->direction);
	if (height_on_axis < 0.0 || height_on_axis > cylinder->height)
		return (-1.0);
	return (t);
}

static double	intersect_cylinder_body(t_ray ray, t_cylinder *cylinder)
{
	t_vec3	oc;
	double	dot_values[2];
	double	abc[3];
	double	discriminant;
	double	t;

	oc = vec_sub(ray.origin, cylinder->center);
	dot_values[0] = vec_dot(oc, cylinder->direction);
	dot_values[1] = vec_dot(ray.direction, cylinder->direction);
	abc[0] = vec_dot(ray.direction, ray.direction)
		- (dot_values[1] * dot_values[1]);
	abc[1] = 2 * (vec_dot(oc, ray.direction)
			- (dot_values[0] * dot_values[1]));
	abc[2] = vec_dot(oc, oc) - (dot_values[0] * dot_values[0])
		- (cylinder->radius * cylinder->radius);
	discriminant = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (discriminant < 0)
		return (-1.0);
	t = find_small_t(abc[0], abc[1], discriminant);
	if (t < 0.0)
		return (-1.0);
	return (check_cylinder_height(ray, cylinder, t));
}

static double	intersect_cylinder_cap(t_ray ray, t_cylinder *cylinder,
					t_vec3 cap_center)
{
	double	denom;
	double	t;
	t_vec3	p;
	t_vec3	v;
	double	dist_squared;

	denom = vec_dot(ray.direction, cylinder->direction);
	if (fabs(denom) < 1e-6)
		return (-1.0);
	t = vec_dot(vec_sub(cap_center, ray.origin), cylinder->direction) / denom;
	if (t < 0.0)
		return (-1.0);
	p = find_p(ray, t);
	v = vec_sub(p, cap_center);
	dist_squared = vec_dot(v, v);
	if (dist_squared > (cylinder->radius * cylinder->radius))
		return (-1.0);
	return (t);
}

double	intersect_cylinder(t_ray ray, t_cylinder *cylinder)
{
	double	t_body;
	double	t_cap1;
	double	t_cap2;
	double	closest_t;
	t_vec3	top_center;

	t_body = -1;
	t_cap1 = -1;
	t_cap2 = -1;
	closest_t = INFINITY;
	t_body = intersect_cylinder_body(ray, cylinder);
	t_cap1 = intersect_cylinder_cap(ray, cylinder, cylinder->center);
	top_center = vec_add(cylinder->center,
			vec_multi(cylinder->direction, cylinder->height));
	t_cap2 = intersect_cylinder_cap(ray, cylinder, top_center);
	closest_t = INFINITY;
	if (t_body > 0.0 && t_body < closest_t)
		closest_t = t_body;
	if (t_cap1 > 0.0 && t_cap1 < closest_t)
		closest_t = t_cap1;
	if (t_cap2 > 0.0 && t_cap2 < closest_t)
		closest_t = t_cap2;
	if (closest_t == INFINITY)
		return (-1.0);
	return (closest_t);
}
