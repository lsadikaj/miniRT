#include "../includes/minirt.h"

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