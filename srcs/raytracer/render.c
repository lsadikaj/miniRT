/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:06:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/22 15:45:26 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

	s.u_scale = screen.screen_width / (double)WIDTH;
	s.v_scale = screen.screen_height / (double)HEIGHT;
	s.y = 0;
	while (s.y < HEIGHT)
	{
		s.x = 0;
		while (s.x < WIDTH)
		{
			s.pixel_pos = screen.ul_corner;
			s.pixel_pos = vec_add(s.pixel_pos,
					vec_multi(screen.right_vector, s.x * s.u_scale));
			s.pixel_pos = vec_sub(s.pixel_pos,
					vec_multi(screen.up_vector, s.y * s.v_scale));
			s.ray.origin = scene.camera.position;
			s.ray.direction = vec_direction(scene.camera.position, s.pixel_pos);
			s.color = generate_ray(scene, s.ray);
			put_pixel(&data->img, s.x, s.y, s.color);
			s.x++;
		}
		s.y++;
	}
}
