
#include "../../includes/minirt.h"

//return 0 if valid color range, 1 if not
int check_color_range(char *str)
{
    char **components;
    int i;

    i = 0;
    components = ft_split(str, ',');
    if (!components)
        return (1);
    while(components[i])
    {
        int value = ft_atoi(components[i]);
        if (value < 0 || value > 255)
        {
            ft_free_split(components);
            return (1);
        }
        i++;
    }
    ft_free_split(components);
    return (0);
}

//return 1 if ambiance line, 0 if not
int is_ambiant(char *line)
{
    if (line[0] == 'A' && line[1] == ' ')
        return (1);
    return (0);
}

/* //parses ambiance line and fills data->scene.ambient
int parse_ambiant(t_data *data, char *line)
{

    char **tokens;
    tokens = ft_split(line, ' ');
    if (!tokens)
        return (1);
    data->scene.ambient.ratio = ft_atod(tokens[1]);
    data->scene.ambient.color = parse_color(tokens[2]);
    ft_free_split(tokens);
    return (0);
} */

// parses ambient light line and fills data->scene.ambient
int	parse_ambient(char *line, t_scene *scene)
{
	int		i;
	double	ratio;
	t_color	color;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i = skip_whitespaces(line, i);
	ratio = ft_atod(&line[i]);
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	i = skip_whitespaces(line, i);
	color = parse_color(&line[i]);
	if (color.r == -1)
		return (1);
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	return (0);
}