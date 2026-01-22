/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiarcer <jiarcer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:17:48 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/22 12:51:32 by jiarcer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
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

# define WIDTH 900
# define HEIGHT 700

# define T_SPHERE 1
# define T_PLANE 2
# define T_CYLINDER 3

//hit point info
typedef struct s_hit
{
	double		t;
	void		*obj;
	int			type;
}	t_hit;

// Rendering infos
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

// Color infos
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// Vector infos
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

// Ray infos
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

// Ambient lighting infos
typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

// Camera infos
typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	double	fov;
}	t_camera;

// Diffuse light infos
typedef struct s_light
{
	t_vec3			position;
	t_vec3			light_dir;
	double			brightness;
	t_color			color;
}	t_light;

// Sphere infos
typedef struct s_sphere
{
	t_vec3			center;
	double			radius;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

// Plane infos
typedef struct s_plane
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

typedef struct s_screen
{
	double	screen_width;
	double	screen_height;
	double	up;
	double	right;
	t_vec3	ul_corner;
	t_vec3	up_vector;
	t_vec3	right_vector;
	t_vec3	forward_vector;
}	t_screen;

// Complet scene infos
typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	t_screen	screen;
}	t_scene;

// Global infos
typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_scene	scene;
}	t_data;

typedef struct s_checker
{
	char	*indentifier;
	int		(*checker)(char *line);
}	t_checker;

typedef struct s_parser
{
	char	*indentifier;
	int		(*parser)(char *line, t_scene *scene);
}	t_parser;

//variable de la fonction render
// en struct pour la norm
typedef struct s_render
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;
	t_vec3	pixel_pos;
	double	u_scale;
	double	v_scale;
}	t_render;

// init.c
int		init_mlx(t_data *data);
void	init_image(t_data *data);
void	init_scene(t_scene *scene);

// hooks.c
void	setup_hooks(t_data *data);

// render.c
void	put_pixel(t_img *img, int x, int y, int color);
int		create_color(int r, int g, int b);
void	draw_gradient(t_data *data);

// read_args.c
int		read_args(char *filename);

// parser
int		is_ambiant(char *line);
int		check_color_range(char *str);
int		check_args(char *args);

// parse_acl.c
int		parse_ambient(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);
void	init_screen(t_scene scene, t_screen *screen);

// parser_utils.c
int		skip_whitespaces(char *str, int i);
int		parse_vector(char *str, int *i, t_vec3 *v);
t_color	parse_color(char *str);

// vec_utils.c
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
double	vec_length(t_vec3 v);
t_vec3	vec_normalize(t_vec3 v);
int		is_normalized(char *args);

// parse objects
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);

//checkers.c
int		is_valid_ambiant(char *line);
int		is_valid_camera(char *line);
int		is_valid_light(char *line);
int		is_valid_sphere(char *line);
int		is_valid_plane(char *line);
int		is_valid_cylinder(char *line);
int		check_vector(char *token);
int		is_normalised_range(char *args);
int		check_aclnb(int fd);


void	render(t_scene scene, t_screen screen, t_data *data);
int		parse_all(char *filename, t_data *data);
int		generate_ray(t_scene scene, t_ray ray);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

double	intersect_cylinder(t_ray ray, t_cylinder *cylinder);
void	check_cylinders(t_scene *scene, t_ray ray, t_hit *hit);
int		render_cylinder(t_scene scene, t_ray ray, t_hit hit);

int		calculate_light(t_scene scene,
			t_vec3 hit_point, t_vec3 normal, t_color obj_color);

void	check_spheres(t_scene *scene, t_ray ray, t_hit *hit);
void	check_planes(t_scene *scene, t_ray ray, t_hit *hit);
int		render_sphere(t_scene scene, t_ray ray, t_hit hit);
int		render_plane(t_scene scene, t_ray ray, t_hit hit);

//calculs utils
double	find_big_t(double a, double b, double discriminant);
double	find_small_t(double a, double b, double discriminant);
double	find_discriminant(double a, double b, double c);
t_vec3	vec_direction(t_vec3 from, t_vec3 to);
double	vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3	find_p(t_ray ray, double t);
t_vec3	vec_divide(t_vec3 vec, double divider);
t_vec3	vec_multi(t_vec3 vec, double multiplier);
t_vec3	vec_sub(t_vec3 start, t_vec3 end);
t_vec3	vec_add(t_vec3 start, t_vec3 end);

int		check_color_range(char *str);
int		is_ambiant(char *line);
void	free_data(t_data *data);

#endif
