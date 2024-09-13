/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:53:50 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/13 18:22:52 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void	load_xpm(t_data *data, t_imgs *img, char *tex)
{
	ft_bzero(img, sizeof(t_imgs));
	printf("w[%d]h[%d]",data->map->width, data->map->height);
	printf("Loading texture from: [%s]\n", tex);

	img->img = mlx_xpm_file_to_image(data->mlx_ptr, tex, &data->map->width,
			&data->map->height);
	if (!img->img)
		exit_free(data, MERROR);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits,
			&img->line_len, &img->endian);
}

static int	*fill_texture_tab(t_data *data, char *tex)
{
	t_imgs	tmp;
	int		*tab;
	int		x;
	int		y;

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
			tab[x * SIZE_IMG + y] = tmp.addr[x * SIZE_IMG + y];
			y++;
		}
		x++;
	}
	mlx_destroy_image(data->mlx_ptr, tmp.img);
	return (tab);
}

void	init_texture(t_data *data)
{
	data->img = ft_calloc(1, sizeof(t_imgs));
	if (!data->img)
		exit_free(data, MERROR);
	data->img->texture = ft_calloc(5, sizeof(int *));
	if (!data->img->texture)
		exit_free(data, MERROR);
	data->img->texture[NO] = fill_texture_tab(data, data->map->north_path);
	data->img->texture[SO] = fill_texture_tab(data, data->map->south_path);
	data->img->texture[WE] = fill_texture_tab(data, data->map->west_path);
	data->img->texture[EA] = fill_texture_tab(data, data->map->east_path);
}
