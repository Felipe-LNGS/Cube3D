/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:19:15 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/13 19:23:50 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube.h"

raycast(t_data *data)
{
    int i;
    double time;
    time = 0; //time of current frame
    double oldTime;
    oldTime = 0; //time of previous frame
    
    i = 0;
    while (i < data->map->width)
    {
        data->camerax = 2 * i / data->map->width - 1;
        data->ray_dir_x = data->dir_x + data->plane_x * data->camerax;
        data->ray_dir_y = data->dir_y + data->plane_y * data->camerax;         

//DDA algortihm starts HERE//
        
    //which box of the map we're in
      data->map_x = data->posx_p;
      data->map_y = data->posy_p;

       //length of ray from one x or y-side to next x or y-side
      data->delta_dist_x = (data->ray_dir_x == 0) ? 1e30 : std::abs(1 / data->ray_dir_x);
      data->delta_dist_y = (data->ray_dir_y == 0) ? 1e30 : std::abs(1 / data->ray_dir_y);
      double perpWallDist;

    //calculate step and initial sideDist
    if (data->ray_dir_x < 0)
    {
        data->step_x = -1;
        data->unit_dist_x = (data->posx_p - data->map_x) * data->delta_dist_x;
    }
    else
    {
        data->step_x = 1;
        data->unit_dist_x = (data->map_x + 1.0 - data->posx_p) * data->delta_dist_x;
    }
    if (data->ray_dir_y < 0)
    {
        data->step_y = -1;
        data->unit_dist_y = (data->posy_p - data->map_y) * data->delta_dist_y;
    }
    else
    {
        data->step_y = 1;
        data->unit_dist_y = (data->map_y + 1.0 - data->posy_p) * data->delta_dist_y;
    }

    
//     //perform DDA
//     while (data->hit == 0)
//     {
//     //jump to next map square, either in x-direction, or in y-direction
//     if (data->sideDistX < sideDistY)
//     {
//         sideDistX += deltaDistX;
//         mapX += stepX;
//         side = 0;
//     }
//     else
//     {
//         sideDistY += deltaDistY;
//         mapY += stepY;
//         side = 1;
//     }
//     //Check if ray has hit a wall
//     if (worldMap[mapX][mapY] > 0) hit = 1;
//     }
//      //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
//       if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//       else          perpWallDist = (sideDistY - deltaDistY);
//        //Calculate height of line to draw on screen
//       int lineHeight = (int)(h / perpWallDist);

//       //calculate lowest and highest pixel to fill in current stripe
//       int drawStart = -lineHeight / 2 + h / 2;
//       if(drawStart < 0)drawStart = 0;
//       int drawEnd = lineHeight / 2 + h / 2;
//       if(drawEnd >= h)drawEnd = h - 1;
//       //choose wall color
//       ColorRGB color;
//       switch(worldMap[mapX][mapY])
//       {
//         case 1:  color = RGB_Red;  break; //red
//         case 2:  color = RGB_Green;  break; //green
//         case 3:  color = RGB_Blue;   break; //blue
//         case 4:  color = RGB_White;  break; //white
//         default: color = RGB_Yellow; break; //yellow
//       }

//       //give x and y sides different brightness
//       if (side == 1) {color = color / 2;}

//       //draw the pixels of the stripe as a vertical line
//       verLine(x, drawStart, drawEnd, color);
//     }
//     //timing for input and FPS counter
//     oldTime = time;
//     time = getTicks();
//     double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
//     print(1.0 / frameTime); //FPS counter
//     redraw();
//     cls();

//     //speed modifiers
//     double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
//     double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
//     readKeys();
//     //move forward if no wall in front of you
//     if (keyDown(SDLK_UP))
//     {
//       if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
//       if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
//     }
//     //move backwards if no wall behind you
//     if (keyDown(SDLK_DOWN))
//     {
//       if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
//       if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
//     }
//     //rotate to the right
//     if (keyDown(SDLK_RIGHT))
//     {
//       //both camera direction and camera plane must be rotated
//       double oldDirX = dirX;
//       dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//       dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//       double oldPlaneX = planeX;
//       planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//       planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//     }
//     //rotate to the left
//     if (keyDown(SDLK_LEFT))
//     {
//       //both camera direction and camera plane must be rotated
//       double oldDirX = dirX;
//       dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//       dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//       double oldPlaneX = planeX;
//       planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//       planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//     }
//   }
    i++;
    }
}