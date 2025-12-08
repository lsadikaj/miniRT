#include "../../includes/minirt.h"

// a ameliorer avec un switch case peut etre
//et ou tableau de function pointers

int check_args(char **args)
{
    int i = 0;
    t_parser *checker = g_checkers;
    while(args[i])
    {
        int j = 0;
        int found = 0;
        while(checker[j].indentifier)
        {
            if (ft_strncmp(args[i], checker[j].indentifier, ft_strlen(checker[j].indentifier)) == 0)
            {
                if (checker[j].checker(args[i]) == 1)
                {
                    ft_printf("Error\nInvalid argument line: %s", args[i]);
                    return (1);
                }
                found = 1;
                break;
            }
            j++;
        }
        if (!found)
        {
            ft_printf("Error\nUnknown identifier in line: %s", args[i]);
            return (1);
        }
        i++;
    }
    return (0);
}