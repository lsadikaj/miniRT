/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:00:42 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/22 14:51:08 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	close_window(t_data *data)
{
	free_data(data);
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
