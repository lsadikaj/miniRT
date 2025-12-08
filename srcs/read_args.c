#include "../includes/minirt.h"


int read_args(char *filename)
{
    int     fd;
    char    *line;
    int     i;

    i = 0;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (1);
    while((line = get_next_line(fd)))
    {
        while(line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '\0' || line[i] == '\n')
        {
            free(line);
            i = 0;
            continue;
        }
        if (line[i] == '\0' || line[i] == '\n')
        {
            free(line);
            i = 0;
            continue;
        }
      if(check_args(line + i) == 1)
        {
            free(line);
            close(fd);
            ft_printf("Error\nInvalid line in file: %s", line);
            return (1);
        }
        free(line);
        i = 0;
    }
    close(fd);
    return (0);
}

/* char** read_args(char *filename)
{
    int     fd;
    char    *line;
    char    **args;
    int     i;
    int     j;

    i = 0;
    j = 0;
    args = malloc(sizeof(char*) * 1);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    while((line = get_next_line(fd)))
    {
        while(line[j] == ' ' || line[j] == '\t')
            j++;
        args = realloc(args, sizeof(char*) * (ft_strlen(line) + 1 - j + i));
        args[i] = ft_strdup(line + j);
        free(line);
        j = 0;
        i++;
    }
    args[i] = NULL;
    i = 0;
    close(fd);
    return (args);
} */

