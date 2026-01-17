/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:06:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/17 16:54:10 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double intersect_sphere(t_ray ray, t_sphere sphere)
{
    double  a;
    double  b;
    double  c;
    double  discriminant;
    t_vec3  oc;

    // 1. Calcul du vecteur L (Origin - Center)
    oc = vec_sub(ray.origin, sphere.center);

    // 2. Calcul des coefficients a, b, c
    a = vec_dot(ray.direction, ray.direction);
    b = 2.0 * vec_dot(oc, ray.direction);
    c = vec_dot(oc, oc) - (sphere.radius * sphere.radius);

    // 3. Calcul du discriminant
    discriminant = find_discriminant(a, b, c);

    // Si discriminant < 0, le rayon rate la sphère
    if (discriminant < 0)
        return (-1.0);

    // 4. On retourne la plus petite distance positive
    return (find_small_t(a, b, discriminant));
}
int ray_sphere2(t_sphere *closest_sphere, t_ray ray, t_scene scene)
{
    int color;
    double light_intensity;
     // Calcul de la couleur en fonction de la lumière
        closest_sphere->p = find_p(ray, scene.spheres->closest_t);
        closest_sphere->normal = vec_normalize(vec_sub(closest_sphere->p, closest_sphere->center));        
        scene.light.light_dir = vec_normalize(vec_sub(scene.light.position, closest_sphere->p));
        light_intensity = vec_dot(scene.spheres->normal, scene.light.light_dir) * scene.light.brightness;
        if (light_intensity < 0)
            light_intensity = 0;
        color = create_color(
            (int)(closest_sphere->color.r * light_intensity),
            (int)(closest_sphere->color.g * light_intensity),
            (int)(closest_sphere->color.b * light_intensity)
        );
        return (color);
}

int ray_sphere(t_ray ray, t_scene scene)
{
    double      current_t;
    t_sphere    *current_sphere;
    t_sphere    *closest_sphere;

    scene.spheres->closest_t = INFINITY; // On initialise à "très loin"
    closest_sphere = NULL;
    current_sphere = scene.spheres; 
    while (current_sphere)
    {
        // Vérifie l'intersection avec la sphère courante
        current_t = intersect_sphere(ray, *current_sphere);

        if (current_t > 0.0 && current_t < scene.spheres->closest_t)
        {
            scene.spheres->closest_t = current_t;
            closest_sphere = current_sphere;
        }
        current_sphere = current_sphere->next;
    }
    if (closest_sphere)
       return (ray_sphere2(closest_sphere, ray, scene));
    // 2. On a rien touché, on retourne la couleur de fond bleue
    return (0x000000FF); 
}

static int	test_spheres(t_scene scene, t_ray ray, double *distance)
{
	int	color;

	*distance = INFINITY;
	color = 0x000000FF;
	if (scene.spheres)
	{
		scene.spheres->closest_t = INFINITY;
		color = ray_sphere(ray, scene);
		*distance = scene.spheres->closest_t;
	}
	return (color);
}

static int	test_cylinders(t_scene scene, t_ray ray, double *distance)
{
	int	color;

	*distance = INFINITY;
	color = 0x000000FF;
	if (scene.cylinders)
	{
		scene.cylinders->closest_t = INFINITY;
		color = ray_cylinder(ray, scene);
		*distance = scene.cylinders->closest_t;
	}
	return (color);
}

// est utilisé uniquement pour les sphères et les cylindre pour l'instant mais devra etre changé plus tard
int generate_ray(t_scene scene, t_ray ray)
{
	int		sphere_color;
	int		cylinder_color;
	double	sphere_t;
	double	cylinder_t;

	sphere_color = test_spheres(scene, ray, &sphere_t);
	cylinder_color = test_cylinders(scene, ray, &cylinder_t);
	if (sphere_t < cylinder_t && sphere_t != INFINITY)
		return (sphere_color);
	if (cylinder_t != INFINITY)
		return (cylinder_color);
	return (0x000000FF);
}
