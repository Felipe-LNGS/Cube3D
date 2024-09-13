/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:24:37 by plangloi          #+#    #+#             */
/*   Updated: 2024/09/13 19:14:46 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../.libft/libft.h"
# include "../.minilibx-linux/mlx.h"
# include <math.h>

# define SIZE_IMG 64
# define SIZE_TAB 3
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define SCREEN_W 1280
# define SCREEN_H 720
# define MERROR "Error : malloc"

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

typedef struct img_s
{
	int		height;
	int		width;
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		line_len;
	int		endian;
	// void	*img_wall;
	// void	*img_path;
	// char	*wall;
	// char	*path;
	int		**texture;

}			t_imgs;

typedef struct s_data
{	
	double 	posx_p; 		// x-coordinate start position player on .cub grid
	double 	posy_p; 		// y-coordinate start position player ...
	double 	dir_x;
	double 	dir_y;
	double 	plane_x;
	double 	plane_y;
		
	int 	map_x;  		// x-coordinate of current square of the map the ray is in
	int 	map_y;  		// y-coordinate ...
	double 	camerax;   		// x-coordinate of point on camera plane
	double 	ray_dir_x;		//exact poisition of ray in 
	double 	ray_dir_y;		// ...
	// double	ray_dist_x;
	// double	ray_dist_y;
	double 	delta_dist_x;	//distance the ray has to travel to go from 1 x-unit to the next x-unit
	double 	delta_dist_y;	// ...
	double	unit_dist_x;	//dist the ray has to travel from its start position to the first x-unit
	double	unit_dist_y;	// ...
    int 	step_x;			//what direction to step in x or y-direction (either +1 or -1)
    int 	step_y;
	int 	hit;			//was there a wall hit?
	int 	side;			//was a NS or a EW wall hit?

	
	int		sizex;			// computer display width
	int		sizey;			// comupter display height
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
void		exit_free(t_data *data, char *str);
/*--------------------MLX--------------------*/
void		initiate_mlx(t_data *data);
void		init_texture(t_data *data);
void    	init_struct(t_data *data);
#endif