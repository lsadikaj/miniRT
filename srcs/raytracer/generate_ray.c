/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:06:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 23:55:56 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

//lance une serie de fonction pour initialiser le plus petit t
//de chaque ray dans hit->t pour ensuite render hit->type
int	generate_ray(t_scene scene, t_ray ray)
{
	t_hit	hit;

	hit.t = INFINITY;
	hit.type = 0;
	hit.obj = NULL;
	if (scene.spheres)
		check_spheres(&scene, ray, &hit);
	if (scene.planes)
		check_planes(&scene, ray, &hit);
	if (scene.cylinders)
		check_cylinders(&scene, ray, &hit);
	if (hit.type == T_SPHERE)
		return (render_sphere(scene, ray, hit));
	if (hit.type == T_PLANE)
		return (render_plane(scene, ray, hit));
	if (hit.type == T_CYLINDER)
		return (render_cylinder(scene, ray, hit));
	return (0x000000FF);
}

static int	is_in_shadow(t_scene scene, t_vec3 point, t_vec3 light_pos)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	double	distance_to_light;
	t_vec3	to_light;

	to_light = vec_sub(light_pos, point);
	distance_to_light = vec_length(to_light);
	shadow_ray.origin = point;
	shadow_ray.direction = vec_normalize(to_light);
	shadow_hit.t = INFINITY;
	shadow_hit.type = 0;
	shadow_hit.obj = NULL;
	if (scene.spheres)
		check_spheres(&scene, shadow_ray, &shadow_hit);
	if (scene.planes)
		check_planes(&scene, shadow_ray, &shadow_hit);
	if (scene.cylinders)
		check_cylinders(&scene, shadow_ray, &shadow_hit);
	if (shadow_hit.t > 0.001 && shadow_hit.t < distance_to_light)
		return (1);
	return (0);
}

//calcul la couleur d'un pixel en int,
//en prenant en compte de l'intensité de la lumière
int	calculate_light(t_scene scene, t_vec3 hit_point,
	t_vec3 normal, t_color obj_color)
{
	t_vec3	light_dir;
	double	angle;
	double	diffuse_intensity;
	double	total_intensity;

	light_dir = vec_sub(scene.light.position, hit_point);
	light_dir = vec_normalize(light_dir);
	angle = vec_dot(normal, light_dir);
	if (angle < 0)
		angle = 0;
	if (is_in_shadow(scene, hit_point, scene.light.position))
		total_intensity = scene.ambient.ratio;
	else
	{
		diffuse_intensity = scene.light.brightness * angle;
		total_intensity = scene.ambient.ratio + diffuse_intensity;
	}
	if (total_intensity > 1.0)
		total_intensity = 1.0;
	return (create_color(
			(int)(obj_color.r * total_intensity),
		(int)(obj_color.g * total_intensity),
		(int)(obj_color.b * total_intensity)));
}
