#include "../../includes/minirt.h"

// a ameliorer avec un switch case peut etre

//return 0 if all args are valid, 1 if not
int check_args(char *args)
{
    int i = 0;
    t_parser *checker = g_checkers;

    while(args[i])
    {
        int j = 0;
        int found = 0;
        while(checker[j].indentifier)
        {
            if (ft_strncmp(args, checker[j].indentifier, ft_strlen(checker[j].indentifier)) == 0)
            {
                if (checker[j].checker(args) == 1)
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