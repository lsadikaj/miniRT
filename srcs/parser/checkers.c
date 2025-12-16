#include "../../includes/minirt.h"


//NE PAS OUBLIER DE VERIFIER QUE LES OBJETS A C L 
//SONT BIEN APPELÉ UNE SEULE FOIS DANS LE FICHIER


//return 0 if valid, 1 if not
int is_valid_ambiant(char *line)
{
    char **tokens;
    
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

    tokens = ft_split(line, ' ');
    if (!tokens || tokens[0] == NULL || tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL || tokens[0][0] != 'C' || tokens[0][1] != '\0' || tokens[4] != NULL)
    {
        ft_free_split(tokens);
        return (1);
    }
    if( ft_isdigit_str(tokens[1]) || ft_isdigit_str(tokens[2]) || ft_isdigit_str(tokens[3])) //token 1 doit juste etre des chiffres mais peut normalement etre infini ???
    {
        ft_free_split(tokens);
        return (1);
    }
    if( ft_atod(tokens[3]) < 0.0 || ft_atod(tokens[3]) > 180.0)
    {
        ft_free_split(tokens);
        return (1);
    }
    if( ft_atod(tokens[2]) < -1.0 || ft_atod(tokens[2]) > 1.0) // verifier que c est bien un vecteur normalisé
    {
        ft_free_split(tokens);
        return (1);
    }
    ft_free_split(tokens);
    return (0);
}

//L -40.0,50.0,0.0 0.6 10,0,255
// check coordinates, ratio and color
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
