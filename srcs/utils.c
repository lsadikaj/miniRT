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


//initialise l'écran virtuel en fonction de la caméra
//remplit la structure t_screen
//donne les vecteurs up, right et forward normalisés
//calcule le coin supérieur gauche de l'écran virtuel
void init_screen(t_scene scene, t_screen *screen)
{
    // 1. Calcul des dimensions (Distance focale = 1.0)
    double aspect_ratio = (double)WIDTH / (double)HEIGHT;
    
    screen->screen_width = 2.0 * tan((scene.camera.fov * (M_PI / 180.0)) / 2.0);
    screen->screen_height = screen->screen_width / aspect_ratio;

    t_vec3 world_up = {0, 1, 0};
    screen->forward_vector = vec_normalize(scene.camera.direction);

    // Gérer le cas où la caméra regarde presque verticalement
    if (fabs(screen->forward_vector.y) > 0.999)
        world_up = (t_vec3){0, 0, 1}; // On change l'axe de référence

    // Calcul du vecteur Droite (Right)
    screen->right_vector = vec_cross(screen->forward_vector, world_up);
    screen->right_vector = vec_normalize(screen->right_vector); // IMPORTANT !

    // Calcul du vecteur Haut (Up) local à la caméra
    screen->up_vector = vec_cross(screen->right_vector, screen->forward_vector);
    screen->up_vector = vec_normalize(screen->up_vector); // Par sécurité

    // 3. Calcul du coin supérieur gauche (Upper Left Corner)
    // Start = Pos + Forward - (Right * w/2) + (Up * h/2)
    t_vec3 center = vec_add(scene.camera.position, screen->forward_vector);
    t_vec3 left_part = vec_multi(screen->right_vector, screen->screen_width / 2.0);
    t_vec3 up_part = vec_multi(screen->up_vector, screen->screen_height / 2.0);

    // On part du centre, on monte (plus Up) et on va à gauche (moins Right)
    screen->ul_corner = vec_add(center, vec_sub(up_part, left_part));
}

