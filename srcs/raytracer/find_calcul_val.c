#include "../includes/minirt.h"

//retourne le point d'intersection le long du rayon a la distance t
t_vec3 find_p(t_ray ray, double t)
{
    t_vec3    result;
    t_vec3    scaled_direction;

    scaled_direction = vec_multi(ray.direction, t);
    result = vec_add(ray.origin, scaled_direction);
   
    return (result);
}

//retourne la valeur du discriminant
double find_discriminant(double a, double b, double c)
{
    double    discriminant;

    discriminant = b * b - 4 * a * c;
    return (discriminant);
}

//retourne la valeur de t la plus petite positive
double find_small_t(double a, double b, double discriminant)
{
    double    t1;
    double    t2;
    double    t;

    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);
    if (t1 < 0 && t2 < 0)
        t = -1;
    else if (t1 < 0)
        t = t2;
    else if (t2 < 0)
        t = t1;
    else if (t1 < t2)
        t = t1;
    else
        t = t2;
    return (t);
}

//retourne la valeur de t la plus grande positive
double find_big_t(double a, double b, double discriminant)
{
    double    t1;
    double    t2;
    double    t;

    t1 = (-b + sqrt(discriminant)) / (2 * a);
    t2 = (-b - sqrt(discriminant)) / (2 * a);
    if (t1 < 0 && t2 < 0)
        t = -1;
    else if (t1 < 0)
        t = t2;
    else if (t2 < 0)
        t = t1;
    else if (t1 > t2)
        t = t1;
    else
        t = t2;
    return (t);
}
