/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louismdv <louismdv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:52:01 by louismdv          #+#    #+#             */
/*   Updated: 2024/09/18 11:02:15 by louismdv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../.libft/libft.h"
# include "../.minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <sys/time.h>

# define SIZE_TAB 3
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define X 0
# define Y 1
# define SCREEN_W 1280
# define SCREEN_H 720
# define SIZE_IMG 64
# define MERROR "Error : malloc"
# define P_SPEED 0.05
# define R_SPEED 0.06

typedef struct s_color_rgb
{
	int	r; // Red component
	int	g; // Green component
	int	b; // Blue component
}		t_color_rgb;

typedef struct s_map
{
	char				**grid;
	char				**tmp_grid;
	char				*north_path;
	char				*south_path;
	char				*east_path;
	char				*west_path;
	int					start_line;
	char				*f;
	char				*c;
	int					f_color;
	int					c_color;
	int					f_tab[SIZE_TAB];
	int					c_tab[SIZE_TAB];
	int					nb_lines;
	int					width;		//width of map grid
	int					height;		//height of map grid
}						t_map;

typedef struct s_img
{
	int					height;
	int					width;
	void				*mlx_img;
	int					*addr_ptr;
	int					pixel_bits;
	int					line_len;
	int					endian;
	int					**texture;
}						t_imgs;

typedef struct s_data
{
/*-------------------GESTION MAP-------------------*/
	double				pos[2];			// xy start pos player on .cub grid
	double				dir[2];			// vecteur de direction initiale
	double				plane[2];		// plan de camera
	int					map_p[2];		// xy of square of the map ray is in 
	double				camerax;		// xy of point on camera plane
/*--------------------RAYCASTING-------------------*/
	double				ray_dir[2];		// exact poisition of ray in grid
	double				side_dist[2];	// dist ray has from start pos2 1st side
	double				ddist[2];		// dist ray has from 1 xy to the next xy
	int					hit;			// was there a wall hit?
	int					side;			// was a NS or a EW wall hit?
	int					step[2];		// what dir to step in x or y (+1 or -1)
/*--------------------PROJECTION PREP-------------------*/
	double				perpwalldist;	//distance projected on camera direction
	int					line_h;			//height of vertical line2draw on screen
	int					draw_start;		//low and high pixel to fill in line_h
	int					draw_end;
/*-----------------------TEXTURING----------------------*/
	double				wallx;			//exact x-value where the wall was hit
	int					y;
	int					color;
	int					move[2];
	int					moved;
	int					rotate;
	int					tex[2];			//x-coordinate of the texture
	double				texstep;
	double				texpos;
	int					texnum;			//value of the current map square -1
	void				*mlx_ptr;
	void				*win_ptr;
	t_imgs				*img;
	t_map				*map;
}						t_data;

/*-------------------GESTION MAP-------------------*/
int						check_format(char *map);
void					get_width(t_data *data);
int						get_height(char *filename, t_data *data);
int						read_map(char *filename, t_data *data);
void					rework_map(t_data *data);
/*-------------------PARSING-------------------*/
char					*skip_space(char *line);
void					stock_info(char *line, t_data *data);
void					stock_info_bis(char *line, t_data *data);
int						is_info(char *line);
void					check_valid_char(t_data *data);
void					check_is_close(t_data *data);
void					split_rgb(t_data *data, char *rgb,
							char who, char **tab);
int						rgb_to_int(int *rgb);
void					parse_map(t_data *data);
void					get_pos(t_data *data);
int						open_file(t_data *data, char *filename);
/*-------------------UTILS-------------------*/
char					*ft_strducube(char *s, t_data *data);
/*--------------------FREE--------------------*/
void					free_all(t_data *data, t_imgs *img);
void					exit_free(t_data *data, char *str);
/*--------------------MLX--------------------*/
void					initiate_mlx(t_data *data);
void					init_texture(t_data *data, t_imgs *img);
void					init_struct(t_data *data);
/*-----------------RAYCASTING----------------*/
void					raycast(t_data *data);
int						displaymoves(t_data *data);
int						moving(t_data *data);
void					raycast(t_data *data);
int						l_rotate(t_data *data);
int						r_rotate(t_data *data);
void					init_texture(t_data *data, t_imgs *img);
int						**init_buffer(t_data *data);
void					reset_buffer(int **buffer);
void					ft_img_addr(t_data *data, int **buffer, t_imgs *img);
void					init_raycast(t_data *data, int x);

#endif
