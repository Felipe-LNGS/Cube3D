#include "../include/cube.h"

void    free_map(t_data *data)
{
    if (data->map->grid)
        free_grid(data);
    if (data->map->tmp_grid)
        free_split(data->map->tmp_grid);
    if(data->map->north_path)
        free(data->map->north_path);
    if(data->map->south_path)
         free(data->map->south_path);
    if(data->map->east_path)
         free(data->map->east_path);
    if(data->map->west_path)
        free(data->map->west_path);
    if(data->map->f)
         free(data->map->f);
    if(data->map->c)
         free(data->map->c);
    // if(data->map->f)
    //      free(data->map->f_tab);
    // if(data->map->c)
    //      free(data->map->c_tab);
}

void    free_all(t_data *data)
{
    free_map(data);
}

void    exit_free(t_data *data,char *str)
{
    ft_printf(RED"%s\n"RESET,str);
    free_map(data);
}