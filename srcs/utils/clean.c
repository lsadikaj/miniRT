/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 23:40:45 by jiarcer           #+#    #+#             */
/*   Updated: 2026/01/22 15:46:23 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	free_spheres(t_sphere *spheres)
{
	t_sphere	*tmp;

	while (spheres)
	{
		tmp = spheres;
		spheres = spheres->next;
		free(tmp);
	}
}

static void	free_planes(t_plane *planes)
{
	t_plane	*tmp;

	while (planes)
	{
		tmp = planes;
		planes = planes->next;
		free(tmp);
	}
}

static void	free_cylinders(t_cylinder *cylinders)
{
	t_cylinder	*tmp;

	while (cylinders)
	{
		tmp = cylinders;
		cylinders = cylinders->next;
		free(tmp);
	}
}

static void	free_mlx(t_data *data)
{
	if (!data->mlx_ptr)
		return ;
	if (data->img.img_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
		data->img.img_ptr = NULL;
	}
	if (data->win_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_spheres(data->scene.spheres);
	free_planes(data->scene.planes);
	free_cylinders(data->scene.cylinders);
	free_mlx(data);
}
