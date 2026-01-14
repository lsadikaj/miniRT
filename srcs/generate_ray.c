/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:06:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/17 18:01:53 by marvin           ###   ########.fr       */
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
// est utilisé uniquement pour les sphères pour l'instant mais devra etre changé plus tard
int generate_ray(t_scene scene, t_ray ray)
{
    double      closest_t;
    double      current_t;
    t_sphere    *current_sphere;
    t_sphere    *closest_sphere;
    int         color;
    t_vec3      p;
    t_vec3      normal;
    t_vec3      light_dir;
    double      light_intensity;

    closest_t = INFINITY; // On initialise à "très loin"
    closest_sphere = NULL;
    current_sphere = scene.spheres; 

    while (current_sphere)
    {
        // Vérifie l'intersection avec la sphère courante
        current_t = intersect_sphere(ray, *current_sphere);

        if (current_t > 0.0 && current_t < closest_t)
        {
            closest_t = current_t;
            closest_sphere = current_sphere;
        }
        current_sphere = current_sphere->next;
    }
    if (closest_sphere)
    {
        // Calcul de la couleur en fonction de la lumière
        p = find_p(ray, closest_t);
        normal = vec_normalize(vec_sub(p, closest_sphere->center));        
        light_dir = vec_normalize(vec_sub(scene.light.position, p));

        light_intensity = vec_dot(normal, light_dir) * scene.light.brightness;
        if (light_intensity < 0)
            light_intensity = 0;
        color = create_color(
            (int)(closest_sphere->color.r * light_intensity),
            (int)(closest_sphere->color.g * light_intensity),
            (int)(closest_sphere->color.b * light_intensity)
        );
        return (color);
    }
    
    // 2. On a rien touché, on retourne la couleur de fond bleue
    return (0x000000FF); 
}