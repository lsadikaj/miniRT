#include "../../includes/minirt.h"

int	check_vector(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (token[i] == ',')
			count++;
		i++;
	}
	if (count != 2 || token[i - 1] == ',')
		return (1);
	return (0);
}

//return 0 if valid, 1 if not
int	is_valid_ambiant(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL
		|| tokens[0][0] != 'A' || tokens[0][1] != '\0' || tokens[3] != NULL)
	{
		ft_free_split(tokens);
		return (1);
	}
	if ((ft_atod(tokens[1]) < 0.0 || ft_atod(tokens[1]) > 1.0)
		|| ft_isdigit_str(tokens[1]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (check_color_range(tokens[2]) || ft_isdigit_str(tokens[2]))
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//return 0 if valid, 1 if not
int	is_valid_camera(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL
		|| tokens[3] == NULL || tokens[0][0] != 'C' || tokens[0][1] != '\0'
		|| tokens[4] != NULL)
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2]) || ft_isdigit_str
		(tokens[3]) || check_vector(tokens[1]) || check_vector(tokens[2]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_atod(tokens[3]) < 0.0 || ft_atod(tokens[3]) > 180.0
		|| tokens[3][0] == ' ' || tokens[3][0] == '\n')
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_atod(tokens[2]) < -1.0 || ft_atod(tokens[2]) > 1.0)
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//return 0 if valid, 1 if not
int	is_valid_light(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL
		|| tokens[3] == NULL || tokens[0][0] != 'L' || tokens[0][1] != '\0'
		|| tokens[4] != NULL)
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2])
		|| ft_isdigit_str(tokens[3]) || check_vector(tokens[1]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_atod(tokens[2]) < 0.0 || ft_atod(tokens[2]) > 1.0)
	{
		ft_free_split(tokens);
		return (1);
	}
	if (check_color_range(tokens[3]))
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//return 0 if valid, 1 if not
int	is_valid_sphere(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (tokens[0][0] != 's' || tokens[0][1] != 'p' || tokens[0][2] != '\0')
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2])
		|| ft_isdigit_str(tokens[3]) || check_vector(tokens[1])
		|| check_color_range(tokens[3]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_atod(tokens[2]) < 0)
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//faut-il check les limite de l'orientation ?
//return 0 if valid, 1 if not
int	is_valid_plane(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (tokens[0][0] != 'p' || tokens[0][1] != 'l' || tokens[0][2] != '\0')
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2])
		|| ft_isdigit_str(tokens[3]) || check_vector(tokens[1])
		|| check_vector(tokens[2]) || check_color_range(tokens[3]))
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}

//cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
//return 0 if valid, 1 if not
int	is_valid_cylinder(char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (tokens[0][0] != 'c' || tokens[0][1] != 'y' || tokens[0][2] != '\0')
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2])
		|| ft_isdigit_str(tokens[3]) || ft_isdigit_str(tokens[4])
		|| ft_isdigit_str(tokens[5]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (check_vector(tokens[1]) || check_vector(tokens[2])
		|| check_color_range(tokens[5]))
	{
		ft_free_split(tokens);
		return (1);
	}
	if (ft_atod(tokens[3]) < 0 || ft_atod(tokens[4]) < 0)
	{
		ft_free_split(tokens);
		return (1);
	}
	ft_free_split(tokens);
	return (0);
}
