/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmerveil <lmerveil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:24:37 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/16 16:09:48 by lmerveil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../.libft/libft.h"
# include "../.minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
#include <sys/time.h>
# include <math.h>


# define SIZE_TAB 3
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define X	0
# define Y	1
# define SCREEN_W 1280
# define SCREEN_H 720
# define SIZE_IMG 64
# define MERROR "Error : malloc"
# define P_SPEED 0.03
# define R_SPEED 0.04

typedef struct {
    int r;  // Red component
    int g;  // Green component
    int b;  // Blue component
} ColorRGB;

extern const ColorRGB RGB_Red;
extern const ColorRGB RGB_Green;
extern const ColorRGB RGB_Blue;
extern const ColorRGB RGB_White;
extern const ColorRGB RGB_Yellow;

// colors.c

typedef struct s_map
{
	char	**grid;
	char	**tmp_grid;
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	int		start_line;
	char	*f;
	char	*c;
	int		f_color;
	int		c_color;
	int		f_tab[SIZE_TAB];
	int		c_tab[SIZE_TAB];
	int		nb_lines;
	int		width;		// map width
	int		height; 	// map height
}			t_map;

typedef struct s_img
{
	int		height;
	int		width;
	void	*mlx_img;
	int		*addr_ptr;
	int		pixel_bits;
	int		line_len;
	int		endian;
	int		**texture;
}			t_imgs;

typedef struct s_data
{	
	double 	pos[2]; 		// xy-coordinate start position player on .cub grid
	double 	dir[2];			// vecteur de direction initiale
	double 	plane[2];		// la version 2d raycaster du plan de camera
	int 	map_p[2];  		// xy-coordinate of current square of the map the ray is in
	double 	camerax;   		// xy-coordinate of point on camera plane
	double 	ray_dir[2];		//exact poisition of ray in grid
	double 	ddist[2];		//distance the ray has to travel to go from 1 x-unit to the next x-unit
	double	side_dist[2];	//dist the ray has to travel from its start position to the first x-unit
    int 	step[2];		//what direction to step in x or y-direction (either +1 or -1)
	int 	hit;			//was there a wall hit?
	int 	side;			//was a NS or a EW wall hit?
	double	perpwalldist;
	int		line_h;
	int		line_w;
	int		draw_start;
	int		draw_end;
	int		y;
	int		color;
	int		move[2];
	int 	moved;
	int		rotate;
	double	wallx;			//exact value where the wall was hit
	int		tex[2];			//x-coordinate of the texture
	int		texstep;
	int		texpos;
	int 	texnum;			//value of the current map square minus 1
	void	*mlx_ptr;
	void	*win_ptr;
	t_imgs	*img;
	t_map	*map;
}			t_data;

/*-------------------GESTION MAP-------------------*/
int			check_format(char *map);
void		get_width(t_data *data);
int			get_height(char *filename, t_data *data);
int			read_map(char *filename, t_data *data);
void		print_map(t_data *data);
void		rework_map(t_data *data);
/*-------------------PARSING-------------------*/
char		*skip_space(char *line);
void		stock_info(char *line, t_data *data);
void		stock_info_bis(char *line, t_data *data);
int			is_info(char *line);
void		check_valid_char(t_data *data);
void		check_is_close(t_data *data);
void		split_rgb(t_data *data, char *rgb, char who);
int			rgb_to_int(int *rgb);
void		parse_map(t_data *data);
void		get_pos(t_data *data);
/*-------------------UTILS-------------------*/
char		*ft_strducube(char *s, t_data *data);
/*--------------------FREE--------------------*/
void	free_all(t_data *data);
void		exit_free(t_data *data, char *str);
/*--------------------MLX--------------------*/
void		initiate_mlx(t_data *data);
void		init_texture(t_data *data, t_imgs *img);
void    	init_struct(t_data *data);
/*-----------------RAYCASTING----------------*/
void    	raycast(t_data *data);
int	displaymoves(t_data *data);
int	moving(t_data *data);
void    raycast(t_data *data);
int	l_rotate(t_data *data);
int	r_rotate(t_data *data);

void		print_tmp_grid(t_data *data);

#endif