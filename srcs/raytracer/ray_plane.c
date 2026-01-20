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