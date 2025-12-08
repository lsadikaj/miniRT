#include "../../includes/minirt.h"


//NE PAS OUBLIER DE VERIFIER QUE LES OBJETS A C L 
//SONT BIEN APPELÉ UNE SEULE FOIS DANS LE FICHIER


//return 0 if valid, 1 if not
int is_valid_ambiant(char *line)
{
    char **tokens;
// ft_split a changer
    tokens = ft_split(line, ' ');
    if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL || tokens[0][0] != 'A' || tokens[0][1] != '\0' || tokens[3] != NULL)
    {
        ft_free_split(tokens);
        return (1);
    }
    if ((ft_atod(tokens[1]) < 0.0 || ft_atod(tokens[1]) > 1.0) || ft_isdigit_str(tokens[1]))
    {
        ft_free_split(tokens);
        return (1);
    }
    if (check_color_range(tokens[2]) || ft_isdigit_str(tokens[2]))
    {
        ft_free_split(tokens);
        return (1);
    }
    ft_free_split(tokens);
    return (0);
}

int is_valid_camera(char *line)
{
    char **tokens;
//ft_split a changer
    tokens = ft_split(line, ' ');
    if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL || tokens[0][0] != 'C' || tokens[0][1] != '\0' || tokens[4] != NULL)
    {
        ft_free_split(tokens);
        return (1);
    }
    if( ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2]) || ft_isdigit_str(tokens[3]))
    {
        ft_free_split(tokens);
        return (1);
    }
    if( ft_atod(tokens[3]) < 0.0 || ft_atod(tokens[3]) > 180.0)
    {
        ft_free_split(tokens);
        return (1);
    }
    if( ft_atod(tokens[2]) < -1.0 || ft_atod(tokens[2]) > 1.0)
    {
        ft_free_split(tokens);
        return (1);
    }
    // faut encore check le token 1 qui est la position de la camera je suis pas sur des limites
    ft_free_split(tokens);
    return (0);
}
int is_valid_light(char *line)
{
    (void) line;
    return (0);
}
int is_valid_sphere(char *line)
{
    (void) line;
    return (0);
}
int is_valid_plane(char *line)
{
    (void) line;
    return (0);
}
int is_valid_cylinder(char *line)
{
    (void) line;
    return (0);
}

t_parser g_checkers[] = {
    {"A", &is_valid_ambiant},
    {"C", &is_valid_camera},
    {"L", &is_valid_light},
    {"sp", &is_valid_sphere},
    {"pl", &is_valid_plane},
    {"cy", &is_valid_cylinder},
    {0, NULL}
};