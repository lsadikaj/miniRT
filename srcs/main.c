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

int check_objnb(char **args)
{
	int i;
	int A;
	int C;
	int L;

	i = 0;
	A = 0;
	C = 0;
	L = 0;
	while (args[i])
	{
		if(args[i][0] == 'A' && args[i][1] == ' ')
			A++;
		else if(args[i][0] == 'C' && args[i][1] == ' ')
			C++;
		else if(args[i][0] == 'L' && args[i][1] == ' ')
			L++;
		i++;
	}
	if (A != 1 || C != 1 || L != 1)
	{
		ft_printf("Error\nInvalid number of A, C or L objects. A and C must be exactly 1, L at least 1.\n");
		return (1);
	}
	return (0);
}

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
	//int i;
    t_data	data;
	//char **args;

	//i = 0;
	if (argc != 2)
	{
		ft_printf("Usage: %s <scene_file>\n", argv[0]);
		return (1);
	}
	if (file_check(argv[1]))
		return (1);
	
	if (read_args(argv[1]))
	{
		ft_printf("Error\nCould not read file or is empty: %s\n", argv[1]);
		return (1);
	}
	/* if(check_args(args) || check_objnb(args))
		return (1); */
	
	/* while (args[i])
	{
		printf("ARG[%d]: %s", i, args[i]);
		i++;
	}
	i = 0; */


	if (!init_mlx(&data))
		return (1);
	init_image(&data);
	draw_gradient(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, 
		data.img.img_ptr, 0, 0);
		
		setup_hooks(&data);
		mlx_loop(data.mlx_ptr);
/* 		while(args[i])
		{
			free(args[i]);
			i++;
		} */
		return (0);
	}
