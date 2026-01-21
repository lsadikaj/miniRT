/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:06:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 22:12:30 by jiarcer          ###   ########.fr       */
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

//calcul la couleur d'un pixel en int,
//en prenant en compte de l'intensité de la lumière
int	calculate_light(t_scene scene, t_vec3 hit_point,
	t_vec3 normal, t_color obj_color)
{
	t_vec3	light_dir;
	double	angle;
	double	intensity;

	light_dir = vec_sub(scene.light.position, hit_point);
	light_dir = vec_normalize(light_dir);
	angle = vec_dot(normal, light_dir);
	if (angle < 0)
		angle = 0;
	// is_shadow()
	intensity = scene.light.brightness * angle;
	if (intensity > 1.0)
		intensity = 1.0;
	return (create_color(obj_color.r * intensity, obj_color.g * intensity,
			obj_color.b * intensity));
}
