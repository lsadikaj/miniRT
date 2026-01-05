/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:19:21 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/17 18:02:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	file_check(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 3)
		return (1);
	if (filename[len - 3] != '.' && filename[len - 2] != 'r'
		&& filename[len - 1] != 't')
	{
		printf("Error\nInvalid file extension. Expected .rt\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Usage: %s <scene_file>\n", argv[0]);
		return (1);
	}
	if (file_check(argv[1]))
		return (1);
	if (read_args(argv[1]))
	{
		printf("Error\nCould not read file or is empty: %s\n", argv[1]);
		return (1);
	}
	if (!init_mlx(&data))
		return (1);
	init_image(&data);
	draw_gradient(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr,
		data.img.img_ptr, 0, 0);
	setup_hooks(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
