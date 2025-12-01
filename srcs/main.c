/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:19:21 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/01 22:35:50 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    exit(0);
    return (0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
        close_window(data);
    return (0);
}

int main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "miniRT");
    if (!data.win_ptr)
        return (1);
    mlx_hook(data.win_ptr, 17, 0, close_window, &data);
    mlx_key_hook(data.win_ptr, key_press, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}