/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:52:33 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/08 16:38:21 by lsadikaj         ###   ########.fr       */
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
