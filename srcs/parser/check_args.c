#include "../../includes/minirt.h"

// a ameliorer avec un switch case peut etre
void init_checkers(t_parser *checkers)
{
    checkers[0] = (t_parser){"A", &is_valid_ambiant};
    checkers[1] = (t_parser){"C", &is_valid_camera};
    checkers[2] = (t_parser){"L", &is_valid_light};
    checkers[3] = (t_parser){"sp", &is_valid_sphere};
    checkers[4] = (t_parser){"pl", &is_valid_plane};
    checkers[5] = (t_parser){"cy", &is_valid_cylinder};
    checkers[6] = (t_parser){0, NULL};
}
//return 0 if all args are valid, 1 if not
int check_args(char *args)
{
    int i = 0;
    t_parser checkers[7];

    init_checkers(checkers);
    while(args[i])
    {
        int j = 0;
        int found = 0;
        while(checkers[j].indentifier)
        {
            if (ft_strncmp(args, checkers[j].indentifier, ft_strlen(checkers[j].indentifier)) == 0)
            {
                if (checkers[j].checker(args) == 1)
                {
                    printf("Error\nInvalid argument line: %s", args);
                    return (1);
                }
                found = 1;
                break;
            }
            j++;
        }
        if (!found)
        {
            if(args[0] != '\n' || args[0] != '\0')
            {
                printf("Error\nUnknown identifier in line: %s", args);
                return (1);
            }
        }
        i++;
    }
    return (0);
}