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
//calcul la couleur d'un pixel en int,
//en prenant en compte de l'intensité de la lumière
int plane_light(t_scene scene, t_vec3 hit_point, t_vec3 normal, t_color obj_color)
{
    t_vec3 light_dir;
    double angle;
    double intensity;

    light_dir = vec_sub(scene.light.position, hit_point);
    light_dir = vec_normalize(light_dir);
    angle = vec_dot(normal, light_dir);
    if(angle < 0)
        angle = 0;
    intensity = scene.light.brightness * angle;

    if(intensity > 1.0)
        intensity = 1.0;
    return(create_color(obj_color.r * intensity, obj_color.g * intensity, obj_color.b * intensity));
}

// t = (plane.point - ray.origin) . plane.normal / (ray.direction . plane.normal)
double intersect_plane(t_ray ray, t_plane planes)
{
    double denominator;
    double t;
    t_vec3 plane_normal;

    plane_normal = vec_normalize(planes.direction);
    denominator = vec_dot(ray.direction, plane_normal);
    if(denominator > -0.0001 && denominator < 0.0001) // fabs ???
        return (-1); // Le rayon est parallèle au plan, on retourne une couleur par défaut
    t = vec_dot(vec_sub(planes.point, ray.origin), plane_normal) / denominator;
    if(t < 0)
        return (-1); // Le plan est derrière le rayon, on retourne une couleur par défaut

    return (t);
}

//calcul le discriminant et si il y a une intersection calcule et retourne le petit t de la sphere
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

//cherche le petit t de sphere et le stock dans hit->t uniquement si il est plus petit
//que le hit->t precedement calculé pour les autres formes
 void    check_spheres(t_scene *scene, t_ray ray, t_hit *hit)
{
    t_sphere    *tmp;
    double      t;

    tmp = scene->spheres;
    while (tmp)
    {
        t = intersect_sphere(ray, *tmp);
        if (t > 0.001 && t < hit->t)
        {
            hit->t = t;
            hit->obj = tmp;
            hit->type = T_SPHERE;
        }
        tmp = tmp->next;
    }
}
//cherche le petit t de plan et le stock dans hit->t uniquement si il est plus petit
//que le hit->t precedement calculé pour les autres formes
void    check_planes(t_scene *scene, t_ray ray, t_hit *hit)
{
    t_plane     *tmp;
    double      t;

    tmp = scene->planes;
    while (tmp)
    {
        t = intersect_plane(ray, *tmp);
        if (t > 0.001 && t < hit->t)
        {
            hit->t = t;
            hit->obj = tmp;
            hit->type = T_PLANE;
        }
        tmp = tmp->next;
    }
}
void    check_cylinders(t_scene *scene, t_ray ray, t_hit *hit)
{
	double		current_t;
	t_cylinder	*current_cyl;

	scene->cylinders->closest_t = INFINITY;
	current_cyl = scene->cylinders;
	while (current_cyl)
	{
		current_t = intersect_cylinder(ray, current_cyl);
		if (current_t > 0.0 && current_t < hit->t)
		{
			scene->cylinders->closest_t = current_t;
			hit->t = current_t;
			hit->obj = current_cyl;
			hit->type = T_CYLINDER;

		}
		current_cyl = current_cyl->next;
	}
}
//calcule la couleur du pixel d'une sphere grace au p,t,n
int     render_sphere(t_scene scene, t_ray ray, t_hit hit)
{
    t_sphere    *sp;
    t_vec3      p;
    t_vec3      n;

    sp = (t_sphere *)hit.obj; // On cast le void* en t_sphere*
    p = find_p(ray, hit.t);
    n = vec_normalize(vec_sub(p, sp->center));
    
    // Appel à ta fonction de lumière générique
    return (plane_light(scene, p, n, sp->color));
}
//calcule la couleur du pixel d'un plan grace au p,t,n
int     render_plane(t_scene scene, t_ray ray, t_hit hit)
{
    t_plane     *pl;
    t_vec3      p;
    t_vec3      n;

    pl = (t_plane *)hit.obj; // On cast le void* en t_plane*
    p = find_p(ray, hit.t);
    n = pl->direction;
    if (vec_dot(ray.direction, n) > 0)
        n = vec_multi(n, -1.0);
        
    // Appel à ta fonction de lumière générique
    return (plane_light(scene, p, n, pl->color));
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

//lance une serie de fonction pour initialiser le plus petit t
//de chaque ray dans hit->t pour ensuite render hit->type
int generate_ray(t_scene scene, t_ray ray)
{
    t_hit   hit;

    // 1. Initialisation
    hit.t = INFINITY;
    hit.type = 0;
    hit.obj = NULL;

    // 2. Recherche (Mise à jour de hit)
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
        return(test_cylinders(scene, ray, &hit.t));
        
    return (0x000000FF); // fond bleu
}