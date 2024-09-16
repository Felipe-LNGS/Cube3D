/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/16 11:10:25 by lmerveil         ###   ########.fr       */
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
static void	load_xpm(t_data *data, t_imgs *img, char *tex)
{
	bzero_img(data->img);
	img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, tex, &data->img->width,
			&data->img->height);
	if (!img->mlx_img)
		exit_free(data, MERROR);
	printf("w[%d]h[%d] :", data->img->width, data->img->height);
	printf("Loading texture from: [%s]\n", tex);
	img->addr_ptr = (int *)mlx_get_data_addr(img->mlx_img, &img->pixel_bits,
			&img->line_len, &img->endian);
}

// load texture from an XPM image file into a 1D integer array
static int	*fill_texture_tab(t_data *data, char *tex)
{
	int	x;
	int	y;

	t_imgs tmp; // struct for given image
	int *tab;   // tab stock xpm
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
			tab[x * SIZE_IMG + y] = tmp->addr_ptr[x * SIZE_IMG + y];
			y++;
		}
		x++;
	}
	mlx_destroy_image(data->mlx_ptr, tmp.mlx_img);
	return (tab);
}

void	init_texture(t_data *data)
{
	data->img->texture = ft_calloc(5, sizeof(int *));
	if (!data->img->texture)
		exit_free(data, MERROR);
	data->img->texture[NO] = fill_texture_tab(data, data->map->north_path);
	data->img->texture[SO] = fill_texture_tab(data, data->map->south_path);
	data->img->texture[WE] = fill_texture_tab(data, data->map->west_path);
	data->img->texture[EA] = fill_texture_tab(data, data->map->east_path);
	printf(GREEN "Textures loaded\n" RESET);
}
