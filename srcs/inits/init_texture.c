/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:47:58 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/18 10:24:37 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void	bzero_img(t_imgs *img)
{
	img->mlx_img = NULL;
	img->addr_ptr = NULL;
	img->pixel_bits = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

// fill addr and xpm file to img
static void	load_xpm(t_data *data, t_imgs *tmp, char *tex)
{
	bzero_img(tmp);
	tmp->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, tex, &tmp->width,
			&tmp->height);
	if (!tmp->mlx_img)
		exit_free(data, "Error\nXpm doesn't exist");
	tmp->addr_ptr = (int *)mlx_get_data_addr(tmp->mlx_img, &tmp->pixel_bits,
			&tmp->line_len, &tmp->endian);
}

// load texture from an XPM image file into a 1D integer array
static int	*fill_texture_tab(t_data *data, char *tex)
{
	int		x;
	int		y;
	t_imgs	tmp;
	int		*tab;

	// tmp = ft_calloc()
	load_xpm(data, &tmp, tex);
	tab = ft_calloc(1, sizeof(int) * (SIZE_IMG * SIZE_IMG));
	if (!tab)
		exit_free(data, MERROR);
	x = 0;
	while (x < SIZE_IMG)
	{
		y = 0;
		while (y < SIZE_IMG)
		{
			tab[x * SIZE_IMG + y] = tmp.addr_ptr[x * SIZE_IMG + y];
			y++;
		}
		x++;
	}
	mlx_destroy_image(data->mlx_ptr, tmp.mlx_img);
	return (tab);
}

void	init_texture(t_data *data, t_imgs *img)
{
	img->texture = ft_calloc(5, sizeof(int *));
	if (!img->texture)
		exit_free(data, MERROR);
	img->texture[NO] = fill_texture_tab(data, data->map->north_path);
	img->texture[SO] = fill_texture_tab(data, data->map->south_path);
	img->texture[WE] = fill_texture_tab(data, data->map->west_path);
	img->texture[EA] = fill_texture_tab(data, data->map->east_path);
}
