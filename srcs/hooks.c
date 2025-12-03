/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:00:42 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/03 15:17:15 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

static int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_key_hook(data->win_ptr, key_press, data);
}
