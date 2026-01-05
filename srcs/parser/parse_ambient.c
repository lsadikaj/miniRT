#include "../../includes/minirt.h"

//return 0 if valid color range, 1 if not
int	check_color_range(char *str)
{
	char	**components;
	int		i;
	int		value;

	i = 0;
	if (ft_isdigit_str(str))
		return (1);
	components = ft_split(str, ',');
	if (!components || components[3] != NULL || components[2] == NULL
		|| components[2][0] == '\n') //free split ???
		return (1);
	while (components[i])
	{
		value = ft_atoi(components[i]);
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
int	is_ambiant(char *line)
{
	if (line[0] == 'A' && line[1] == ' ')
		return (1);
	return (0);
}
