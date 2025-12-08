/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:17:48 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/03 15:32:33 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

# ifdef __APPLE__
#  include "../minilibx_mms_20200219/mlx.h"
#  define KEY_ESC 53
# else
#  include "../minilibx-linux/mlx.h"
#  define KEY_ESC 65307
# endif

# define WIDTH 800
# define HEIGHT 600

// Rendering infos
typedef struct	s_img
{
    void	*img_ptr;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
	int		endian;
}   t_img;

// Color infos
typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// Vector infos
typedef struct	s_vec3
{
	double	x;
	double 	y;
	double	z;
}	t_vec3;

// Ray infos
typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

// Ambient lighting infos
typedef struct	s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

// Camera infos
typedef struct	s_camera
{
	t_vec3	position;
	t_vec3	direction;
	double	fov;
}	t_camera;

// Diffuse light infos
typedef struct	s_light
{
	t_vec3			position;
	double			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

// Sphere infos
typedef struct	s_sphere
{
	t_vec3			center;
	double			radius;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

// Plane infos
typedef struct	s_plane
{
	t_vec3			point;
	t_vec3			direction;
	t_color			color;
	struct s_plane	*next;
}	t_plane;

// Cylinder infos
typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				direction;
	double				radius;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
}	t_cylinder;

// Complet scene infos
typedef struct	s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_scene;

// Global infos
typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_scene	scene;
}	t_data;

// init.c
int		init_mlx(t_data *data);
void	init_image(t_data *data);

// hooks.c
void	setup_hooks(t_data *data);

// render.c
void	put_pixel(t_img *img, int x, int y, int color);
int		create_color(int r, int g, int b);
void	draw_gradient(t_data *data);

// read_args.c
int		read_args(char *filename);

// parser
int		parse_ambiant(t_data *data, char *line);
t_color parse_color(char *str);
int 	is_ambiant(char *line);
int 	check_color_range(char *str);
int		check_args(char *args);

//checkers.c
int 	is_valid_ambiant(char *line);
int		is_valid_camera(char *line);
int		is_valid_light(char *line);
int		is_valid_sphere(char *line);
int		is_valid_plane(char *line);
int		is_valid_cylinder(char *line);
typedef struct s_parser
{
	char* indentifier;
	int (*checker)(char *line);
} t_parser;

extern t_parser g_checkers[];

#endif
