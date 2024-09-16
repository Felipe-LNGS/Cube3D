/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:19:15 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/16 17:28:28 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

static void reset_buffer(int **buffer)
{
    int j;

    j = -1;
    while (++j < SCREEN_H)  // Loop over the height
        free(buffer[j]);    // Free each row
    free(buffer);           // Free the array of pointers
}

static void	ft_img_addr(t_data *data, int **buffer)
{
    int     i;
	int		j;
	int		index;
	t_imgs	img;

	ft_bzero(&img, sizeof(t_imgs));
	img.mlx_img = mlx_new_image(data->mlx_ptr, SCREEN_W, SCREEN_H);
	img.addr_ptr = (int *)mlx_get_data_addr(img.mlx_img, &img.pixel_bits, &img.line_len, &img.endian);
    i = 0;
    while (i < SCREEN_H)
	{
		j = 0;
		while (j < SCREEN_W)
		{
			index = i * (img.line_len / 4) + j;
			if (buffer[i][j] > 0)
				img.addr_ptr[index] = buffer[i][j];
			else if (i < SCREEN_H / 2)
				img.addr_ptr[index] = data->map->c_color;
			else
				img.addr_ptr[index] = data->map->f_color;
            j++;
		}
        i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img.mlx_img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, img.mlx_img);
}


void    raycast(t_data *data)
{
    int             x;
    int             **buffer;
    int             bufindex;

    x = 0;
    bufindex = 0;
    buffer = ft_calloc(SCREEN_H + 1, sizeof(int *));
    if (!buffer)
        exit_free(data, "Error\nBuffer calloc\n");
    while (bufindex < SCREEN_H)
	{
		buffer[bufindex] = ft_calloc(SCREEN_W + 1, sizeof(int));
		if (!buffer[bufindex])
		{
			while (x < bufindex)
			{
				free(buffer[bufindex]);
				x++;
			}
			free(buffer);
			exit_free(data, MERROR);
		}
        bufindex++;
	}

    while (x < SCREEN_W)
    {
        //init core vectors
        data->camerax = 2.0 * x / (double)SCREEN_W - 1;
        data->ray_dir[X] = data->dir[X] + data->plane[X] * data->camerax;
        data->ray_dir[Y] = data->dir[Y] + data->plane[Y] * data->camerax;         
        
        //init coordinates of box of the map we're in
        data->map_p[X] = (int)data->pos[X];
        data->map_p[Y] = (int)data->pos[Y];

        //calculating ddist : length of ray from one x or y-side to next x or y-side
        data->ddist[X] = fabs(1 / data->ray_dir[X]);
        data->ddist[Y] = fabs(1 / data->ray_dir[Y]);

        //calculate step and initial unitDist
        if (data->ray_dir[X] < 0)
        {
            data->step[X] = -1;
            data->side_dist[X] = ((data->pos[X] - data->map_p[X]) * data->ddist[X]);
        }
    	else if (data->ray_dir[X] > 0)
        {
            data->step[X] = 1;
            data->side_dist[X] = (data->map_p[X] + 1.0 - data->pos[X]) * data->ddist[X];
        }
        if (data->ray_dir[Y] < 0)
        {
            data->step[Y] = -1;
            data->side_dist[Y] = (data->pos[Y] - data->map_p[Y]) * data->ddist[Y];
        }
        else if (data->ray_dir[Y] > 0)

        {
            data->step[Y] = 1;
            data->side_dist[Y] = (data->map_p[Y] + 1.0 - data->pos[Y]) * data->ddist[Y];
        }

        //perform DDA
        data->hit = 0;
        while (data->hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (data->side_dist[X] < data->side_dist[Y])
            {
                data->side_dist[X] += data->ddist[X];
                data->map_p[X] += data->step[X];
                data->side = X;  //hit a x-side axis
            }
            else
            {
                data->side_dist[Y] += data->ddist[Y];
                data->map_p[Y] += data->step[Y];
                data->side = Y; //hit a y-side axis
            }
            // Check if ray has hit a wall
           	if (data->map_p[X] < 0 || data->map_p[Y] < 0 || data->map_p[X] >= data->map->width || data->map_p[Y] >= data->map->height)
				break;
            if (data->map->tmp_grid[data->map_p[X]][data->map_p[Y]] == '1')
                data->hit = 1;
        }
        //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        if (data->side == X)
            data->perpwalldist = (data->side_dist[X] - data->ddist[X]);
        else
            data->perpwalldist = (data->side_dist[Y] - data->ddist[Y]);
        
        //Calculate height of line to draw on screen
        data->line_h = (int)(SCREEN_H / data->perpwalldist);

        //calculate lowest and highest pixel to fill in current stripe
        data->draw_start = -(data->line_h) / 2 + SCREEN_H / 2;
		
        if (data->draw_start < 0)
            data->draw_start = 0;
        data->draw_end = data->line_h / 2 + SCREEN_H / 2;
        

		if (data->draw_end >= SCREEN_H)
            data->draw_end = SCREEN_H - 1;
        
        if (data->side == 0)
        {
            if (data->ray_dir[X] < 0)
                data->texnum = WE;
            else
                data->texnum = EA;
        }
        else
        {
            if (data->ray_dir[Y] > 0)
                data->texnum = SO;
            else
                data->texnum = NO;
		}
        //texturing calculations
        // data->texnum = ft_atoi(&data->map->tmp_grid[data->map_p[X]][data->map_p[Y]]);
        //calculate value of wallX
        if (data->side == 0)
            data->wallx = data->pos[Y] + data->perpwalldist * data->ray_dir[Y];
        else
            data->wallx = data->pos[X] + data->perpwalldist * data->ray_dir[X];
        data->wallx -= floor((data->wallx));

        //x coordinate on the texture
        data->tex[X] = (int)(data->wallx * (double)SIZE_IMG);
        if(data->side == 0 && data->ray_dir[X] > 0)
            data->tex[X] = SIZE_IMG - data->tex[X] - 1;
        if(data->side == 1 && data->ray_dir[Y] < 0)
            data->tex[X] = SIZE_IMG - data->tex[X] - 1;
        // How much to increase the texture coordinate per screen pixel
        data->texstep = 1.0 * SIZE_IMG / data->line_h;
        // Starting texture coordinate
        data->texpos = (data->draw_start - SCREEN_H / 2.0 + data->line_h / 2.0) * data->texstep;
        data->y = data->draw_start - 1.0;
        while (++data->y < data->draw_end)
        {
            data->tex[Y] = (int)data->texpos & (SIZE_IMG - 1);
            data->texpos += data->texstep;
			// printf("data->texnum: %d\n", data->texnum);
			// printf("texture %d\n", data->img->texture[data->texnum][SIZE_IMG * data->tex[Y] + data->tex[X]]);
            data->color = data->img->texture[data->texnum][SIZE_IMG * data->tex[Y] + data->tex[X]];
            if (data->y >= 0 && data->y < SCREEN_H)
    			buffer[data->y][x] = data->color;
        }
    x++;
    }
    ft_img_addr(data, buffer);
    reset_buffer(buffer);
}

