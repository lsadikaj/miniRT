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
