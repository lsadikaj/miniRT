/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:52:33 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/21 22:08:16 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (!data->win_ptr)
		return (0);
	return (1);
}

void	init_image(t_data *data)
{
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img.img_ptr)
	{
		write(2, "Error\nFailed to create image\n", 29);
		exit(1);
	}
	data->img.addr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel,
			&data->img.line_length,
			&data->img.endian);
}

//initialise l'écran virtuel en fonction de la caméra
//remplit la structure t_screen
//donne les vecteurs up, right et forward normalisés
//calcule le coin supérieur gauche de l'écran virtuel
void	init_screen(t_scene scene, t_screen *screen)
{
	double	aspect_ratio;
	t_vec3	world_up;
	t_vec3	center;
	t_vec3	left_part;
	t_vec3	up_part;

	// 1. Calcul des dimensions (Distance focale = 1.0)
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	world_up = (t_vec3){0, 1, 0};
	screen->screen_width = 2.0 * tan((scene.camera.fov * (M_PI / 180.0)) / 2.0);
	screen->screen_height = screen->screen_width / aspect_ratio;
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
	center = vec_add(scene.camera.position, screen->forward_vector);
	left_part = vec_multi(screen->right_vector, screen->screen_width / 2.0);
	up_part = vec_multi(screen->up_vector, screen->screen_height / 2.0);
	// On part du centre, on monte (plus Up) et on va à gauche (moins Right)
	screen->ul_corner = vec_add(center, vec_sub(up_part, left_part));
}
