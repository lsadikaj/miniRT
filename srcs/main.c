/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:19:21 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/03 15:16:57 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int file_check(char *filename)
{
	int len = ft_strlen(filename);
	if (len < 3)
		return (1);
	if (filename[len - 3] != '.' && filename[len - 2] != 'r' && filename[len - 1] != 't')
	{
		printf("Error\nInvalid file extension. Expected .rt\n");
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int i;
    t_data	data;
	char **args;

	i = 0;
	if (argc != 2)
	{
		ft_printf("Usage: %s <scene_file>\n", argv[0]);
		return (1);
	}
	if (file_check(argv[1]))
		return (1);
	args = read_args(argv[1]);
	if (!args || args[0] == NULL)
	{
		ft_printf("Error\nCould not read file or is empty: %s\n", argv[1]);
		return (1);
	}
	if(check_args(args))
		return (1);



	if (!init_mlx(&data))
		return (1);
	init_image(&data);
	draw_gradient(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, 
		data.img.img_ptr, 0, 0);
		
		setup_hooks(&data);
		mlx_loop(data.mlx_ptr);
		while(args[i])
		{
			free(args[i]);
			i++;
		}
		return (0);
	}
