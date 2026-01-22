/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:52:33 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/22 15:47:15 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	world_up = (t_vec3){0, 1, 0};
	screen->screen_width = 2.0 * tan((scene.camera.fov * (PI / 180.0)) / 2.0);
	screen->screen_height = screen->screen_width / aspect_ratio;
	screen->forward_vector = vec_normalize(scene.camera.direction);
	if (fabs(screen->forward_vector.y) > 0.999)
		world_up = (t_vec3){0, 0, 1};
	screen->right_vector = vec_cross(world_up, screen->forward_vector);
	screen->right_vector = vec_normalize(screen->right_vector);
	screen->up_vector = vec_cross(screen->forward_vector, screen->right_vector);
	screen->up_vector = vec_normalize(screen->up_vector);
	center = vec_add(scene.camera.position, screen->forward_vector);
	left_part = vec_multi(screen->right_vector, screen->screen_width / 2.0);
	up_part = vec_multi(screen->up_vector, screen->screen_height / 2.0);
	screen->ul_corner = vec_add(center, vec_sub(up_part, left_part));
}
