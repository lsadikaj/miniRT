/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:52:33 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/17 17:52:49 by marvin           ###   ########.fr       */
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

// init scene data with impossible value and null for pointers
void	init_scene(t_scene *scene)
{
	scene->ambient.ratio = -1;
	scene->camera.fov = -1;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
}
