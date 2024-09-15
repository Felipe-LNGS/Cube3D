/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:19:15 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/15 11:28:29 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

void verLine(void *mlx_ptr, void *win_ptr, int x, int drawStart, int drawEnd, ColorRGB color)
{
    int y;
    
    // Loop through the y-coordinates from drawStart to drawEnd
    for (y = drawStart; y <= drawEnd; y++)
    {
        // Plot the pixel at position (x, y) with the specified color
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, (color.r << 16) | (color.g << 8) | color.b);
    }
}

unsigned long getTicks()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    raycast(t_data *data)
{
    int i;
    // double time;
    // double oldTime;
    double perpWallDist;
    // double moveSpeed;
    // double rotSpeed;
    

    i = 0;
    // time = 0; //time of current frame
    // oldTime = 0; //time of previous frame
    while (i < data->map->width)
    {
        data->camerax = 2 * i / data->map->width - 1;
        data->ray_dir[X] = data->dir[X] + data->plane[X] * data->camerax;
        data->ray_dir[Y] = data->dir[Y] + data->plane[Y] * data->camerax;         

        //DDA algortihm starts HERE//
        
        //which box of the map we're in
        data->map_p[X] = data->pos[X];
        data->map_p[Y] = data->pos[Y];

        //length of ray from one x or y-side to next x or y-side
        if (data->ray_dir[X] == 0)
            data->ddist[X] = 1e30;
        else 
            data->ddist[X] = fabs(1 / data->ray_dir[X]);
        if (data->ray_dir[Y] == 0)
            data->ddist[Y] = 1e30;
        else 
            data->ddist[Y] = fabs(1 / data->ray_dir[Y]);

        //calculate step and initial sideDist
        if (data->ray_dir[X] < 0)
        {
            data->step[X] = -1;
            data->unit_dist[X] = (data->pos[X] - data->map_p[X]) * data->ddist[X];
        }
        else
        {
            data->step[X] = 1;
            data->unit_dist[X] = (data->map_p[X] + 1.0 - data->pos[X]) * data->ddist[X];
        }
        if (data->ray_dir[Y] < 0)
        {
            data->step[Y] = -1;
            data->unit_dist[Y] = (data->pos[Y] - data->map_p[Y]) * data->ddist[Y];
        }
        else
        {
            data->step[Y] = 1;
            data->unit_dist[Y] = (data->map_p[Y] + 1.0 - data->pos[Y]) * data->ddist[Y];
        }
    
    //perform DDA
    while (data->hit == 0)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if (data->unit_dist[X] < data->unit_dist[Y])
        {
            data->unit_dist[X] += data->ddist[X];
            data->map_p[X] += data->step[X];
            data->side = 0;
        }
        else
        {
            data->unit_dist[Y] += data->ddist[Y];
            data->map_p[Y] += data->step[Y];
            data->side = 1;
        }
        //Check if ray has hit a wall
        if (data->map->tmp_grid[data->map_p[X]][data->map_p[Y]] > 0)
            data->hit = 1;
    }
        //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        if(data->side == 0)
            perpWallDist = (data->unit_dist[X] - data->ddist[X]);
        else
            perpWallDist = (data->unit_dist[Y] - data->ddist[Y]);
        //Calculate height of line to draw on screen
        int lineHeight = (int)(data->map->height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + data->map->width / 2;
      if(drawStart < 0)
        drawStart = 0;
     int drawEnd = lineHeight / 2 + data->map->height / 2;
      if(drawEnd >= data->map->height)
        drawEnd = data->map->height - 1;
      
      //choose wall color
      ColorRGB color;
      switch(data->map->tmp_grid[data->map_p[X]][data->map_p[Y]])
      {
        case 1:  color = RGB_Red;  break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }
    

      //give x and y sides different brightness
    if (data->side == 1)
    {
        color.r /= 2;  // Divide red component by 2
        color.g /= 2;  // Divide green component by 2
        color.b /= 2;  // Divide blue component by 2
    }
      //draw the pixels of the stripe as a vertical line
    verLine(data->mlx_ptr, data->win_ptr, 400, 100, 300, color); 
    
    //timing for input and FPS counter
    // oldTime = time;
    // time = getTicks();
    // double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // ft_print(1.0 / frameTime); //FPS counter
    // redraw();
    // cls();

    //speed modifiers
    // moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    // readKeys();
    //move forward if no wall in front of you
    // if (keyDown(SDLK_UP))
    // {
    //   if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if (keyDown(SDLK_DOWN))
    // {
    //   if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    // }
    // //rotate to the right
    // if (keyDown(SDLK_RIGHT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    // }
    // //rotate to the left
    // if (keyDown(SDLK_LEFT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    // }
    i++;
    }
}