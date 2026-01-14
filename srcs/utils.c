#include "../includes/minirt.h"

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    // Calcul de l'offset (décalage) en mémoire :
    // (y * line_length) -> On descend de 'y' lignes
    // (x * (bpp / 8))   -> On se décale de 'x' pixels vers la droite
    // Note : on divise bpp par 8 pour passer de bits à octets (32 bits = 4 octets)

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    
    // On écrit la couleur à cet endroit
    *(unsigned int*)dst = color;
}


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

//retourne le vecteur direction allant de "from" a "to" normalisé
t_vec3 vec_direction(t_vec3 from, t_vec3 to)
{
    t_vec3    result;

    result = vec_sub(to, from);
    result = vec_normalize(result);
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

