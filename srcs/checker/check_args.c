#include "../../includes/minirt.h"

// a ameliorer avec un switch case peut etre
void	init_checkers(t_checker *checkers)
{
	checkers[0] = (t_checker){"A", &is_valid_ambiant};
	checkers[1] = (t_checker){"C", &is_valid_camera};
	checkers[2] = (t_checker){"L", &is_valid_light};
	checkers[3] = (t_checker){"sp", &is_valid_sphere};
	checkers[4] = (t_checker){"pl", &is_valid_plane};
	checkers[5] = (t_checker){"cy", &is_valid_cylinder};
	checkers[6] = (t_checker){0, NULL};
}
int not_found(char *args)
{
	if (args[0] != '\n' || args[0] != '\0')
	{
		printf("Error\nUnknown identifier in line: %s", args);
		return (1);
	}
	return (0);
}

int exec_checker(t_checker *checkers, int j, char *args)
{
	if (checkers[j].checker(args) == 1)
	{
		printf("Error\nInvalid argument line: %s", args);
		return (1);
	}
	return (0);
}

//return 0 if all args are valid, 1 if not
int	check_args(char *args)
{
	t_checker	checkers[7];
	int			j;
	int			found;

	j = 0;
	found = 0;
	init_checkers(checkers);
	while (checkers[j].indentifier)
	{
		if (ft_strncmp(args, checkers[j].indentifier,
				ft_strlen(checkers[j].indentifier)) == 0)
		{
			if(exec_checker(checkers, j, args) == 1)
				return (1);
			found = 1;
			break ;
		}
		j++;
	}
	if (!found)
	{
		if(not_found(args) == 1)
			return (1);
	}
	return (0);
}
