#include "../includes/minirt.h"


t_vec3 vec_add(t_vec3 start, t_vec3 end)
{
    t_vec3	result;

    result.x = start.x + end.x;
    result.y = start.y + end.y;
    result.z = start.z + end.z;
   
    return (result);
}

t_vec3 vec_sub(t_vec3 start, t_vec3 end)
{
    t_vec3    result;

    result.x = start.x - end.x;
    result.y = start.y - end.y;
    result.z = start.z - end.z;
   
    return (result);
}

t_vec3 vec_multi(t_vec3 vec, double multiplier)
{
    t_vec3    result;

    result.x = vec.x * multiplier;
    result.y = vec.y * multiplier;
    result.z = vec.z * multiplier;
   
    return (result);
}

t_vec3 vec_divide(t_vec3 vec, double divider)
{
    t_vec3    result;

    result.x = vec.x / divider;
    result.y = vec.y / divider;
    result.z = vec.z / divider;
   
    return (result);
}
//retourne le point d'intersection le long du rayon a la distance t
t_vec3 find_p(t_ray ray, double t)
{
    t_vec3    result;
    t_vec3    scaled_direction;

    scaled_direction = vec_multi(ray.direction, t);
    result = vec_add(ray.origin, scaled_direction);
   
    return (result);
}

double vec_dot(t_vec3 v1, t_vec3 v2)
{
    double   result;

    result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return (result);
}

//retourne le vecteur direction allant de "from" a "to"
t_vec3 vec_direction(t_vec3 from, t_vec3 to)
{
    t_vec3    result;

    result = vec_sub(to, from);   
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