/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:35:53 by lsadikaj          #+#    #+#             */
/*   Updated: 2026/01/05 16:20:39 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_parser(t_parser *checkers)
{
	checkers[0] = (t_parser){"A", &parse_ambient};
	checkers[1] = (t_parser){"C", &parse_camera};
	checkers[2] = (t_parser){"L", &parse_light};
	checkers[3] = (t_parser){"sp", &parse_sphere};
	checkers[4] = (t_parser){"pl", &parse_plane};
	checkers[5] = (t_parser){"cy", &parse_cylinder};
	checkers[6] = (t_parser){0, NULL};
}

//return 0 if all args are valid, 1 if not
int	parse_loop(char *args, t_scene *scene)
{
	t_parser	parcers[7];
	int			j;
	int			found;

	j = 0;
	found = 0;
	init_parser(parcers);
	while (parcers[j].indentifier)
	{
		if (ft_strncmp(args, parcers[j].indentifier,
				ft_strlen(parcers[j].indentifier)) == 0)
		{
			if (parcers[j].parser(args, scene) == 1)
			{
				printf("Error\nInvalid argument line: %s", args);
				return (1);
			}
			found = 1;
			break ;
		}
		j++;
	}
	if (!found)
	{
		if (args[0] != '\n' || args[0] != '\0')
		{
			printf("Error\nUnknown identifier in line: %s", args);
			return (1);
		}
	}
	return (0);
}

int	parse_all(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)))
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0' || line[i] == '\n')
		{
			free(line);
			i = 0;
			continue ;
		}
		if (line[i] == '\0' || line[i] == '\n')
		{
			free(line);
			i = 0;
			continue ;
		}
		if (parse_loop(line + i, &data->scene) == 1)
        {
            free(line);
            close(fd);
            return (1);
        }
		free(line);
		i = 0;
	}
	close(fd);
	return (0);
}