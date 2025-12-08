#include "../includes/minirt.h"

char** read_args(char *filename)
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
}

