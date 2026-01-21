/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:06:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 22:22:55 by jiarcer          ###   ########.fr       */
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

void	render(t_scene scene, t_screen screen, t_data *data)
{
	t_render	s;
	// Calcul de la taille d'un pixel sur ton écran virtuel
	s.u_scale = screen.screen_width / (double)WIDTH; // Taille d'un pixel en largeur dans le monde 3D
	s.v_scale = screen.screen_height / (double)HEIGHT;  // Taille d'un pixel en largeur dans le monde 3D
	s.y = 0;
	while (s.y < HEIGHT)
	{
		s.x = 0;
		while (s.x < WIDTH)
		{
			// 1. Calculer la position du point sur l'écran virtuel pour le pixel (x, y)
			// On part du coin haut-gauche
			// On se décale à droite (x * Right * u_scale)
			// On se décale en bas (y * Up * v_scale) -> Attention au signe selon ton Up vector !
			s.pixel_pos = screen.ul_corner;
			// Décalage horizontal
			s.pixel_pos = vec_add(s.pixel_pos, vec_multi(screen.right_vector, s.x * s.u_scale));
			// Décalage vertical (on descend, donc on soustrait le vecteur UP)
			s.pixel_pos = vec_sub(s.pixel_pos, vec_multi(screen.up_vector, s.y * s.v_scale));
			// 2. Définir le rayon
			s.ray.origin = scene.camera.position;
			s.ray.direction = vec_direction(scene.camera.position, s.pixel_pos); // Normalisé ici
			// 3. Lancer le rayon dans la scène (Intersection)
			s.color = generate_ray(scene, s.ray);
			put_pixel(&data->img, s.x, s.y, s.color);
			s.x++;
		}
		s.y++;
	}
}
