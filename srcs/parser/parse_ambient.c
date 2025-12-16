
#include "../../includes/minirt.h"

//return 0 if valid color range, 1 if not
int check_color_range(char *str)
{
    char **components;
    int i;

    i = 0;
    components = ft_split(str, ',');
    //peut etre free split ici | ??
    //                         V
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
