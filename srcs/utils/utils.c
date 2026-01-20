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

double vec_dot(t_vec3 v1, t_vec3 v2)
{
    double   result;

    result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return (result);
}

//retourne le vecteur direction allant de "from" a "to" normalisé
t_vec3 vec_direction(t_vec3 from, t_vec3 to)
{
    t_vec3    result;

    result = vec_sub(to, from);
    result = vec_normalize(result);
    return (result);
}
