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

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length
				+ x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	create_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_gradient(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = create_color(x * 255 / WIDTH, y * 255 / HEIGHT, 128);
			put_pixel(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}



void render(t_scene scene, t_screen screen, t_data *data)
{
    int     x;
    int     y;
    double  u_scale; // Taille d'un pixel en largeur dans le monde 3D
    double  v_scale; // Taille d'un pixel en hauteur dans le monde 3D
    t_ray   ray;
    int     color;

    // Calcul de la taille d'un pixel sur ton écran virtuel
    u_scale = screen.screen_width / (double)WIDTH;
    v_scale = screen.screen_height / (double)HEIGHT;
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            // 1. Calculer la position du point sur l'écran virtuel pour le pixel (x, y)
            // On part du coin haut-gauche
            // On se décale à droite (x * Right * u_scale)
            // On se décale en bas (y * Up * v_scale) -> Attention au signe selon ton Up vector !
            t_vec3 pixel_pos = screen.ul_corner;
            // Décalage horizontal
            pixel_pos = vec_add(pixel_pos, vec_multi(screen.right_vector, x * u_scale));
            // Décalage vertical (on descend, donc on soustrait le vecteur UP)
            pixel_pos = vec_sub(pixel_pos, vec_multi(screen.up_vector, y * v_scale));
            // 2. Définir le rayon
            ray.origin = scene.camera.position;
            ray.direction = vec_direction(scene.camera.position, pixel_pos); // Normalisé ici
            // 3. Lancer le rayon dans la scène (Intersection)
            // C'est la prochaine grosse fonction à écrire !
            color = generate_ray(scene, ray);
            // 4. Mettre le pixel à l'écran (my_mlx_pixel_put)
            put_pixel(&data->img, x, y, color);
            x++;
        }
        y++;
    }
}

