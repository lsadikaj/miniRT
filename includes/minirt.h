/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:17:48 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/01 22:18:52 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>

# ifdef __APPLE__
#  include "../minilibx_mms_20200219/mlx.h"
#  define KEY_ESC 53
# else
#  include "../minilibx-linux/mlx.h"
#  define KEY_ESC 65307
# endif

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int		close_window(t_data *data);
int		key_press(int keycode, t_data *data);

#endif