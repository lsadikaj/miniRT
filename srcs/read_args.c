#include "../includes/minirt.h"

char** read_args(char *filename)
{
    int     fd;
    char    *line;
    char    **args;
    int     i;

    i = 0;
    args = malloc(sizeof(char*) * 1);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    while((line = get_next_line(fd)))
    {
        args = realloc(args, sizeof(char*) * ft_strlen(line) + 1);
        args[i] = ft_strdup(line);
        free(line);
        i++;
    }
    args[i] = NULL;
    i = 0;
    close(fd);
    return (args);
}

