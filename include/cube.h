#ifndef CUBE_H
# define CUBE_H

# include <math.h>
# include "../.libft/libft.h"
# include "../.minilibx-linux/mlx.h"
#define SIZE_TAB 3
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
	int		width;		//map width
	int		height;		//map height
}			t_map;

typedef struct img_s
{
	int		height;
	int		width;
	
	// void	*img_wall;
	// void	*img_path;
	// char	*wall;
	// char	*path;

}			t_imgs;

typedef struct s_data
{
	int		posx_p;	//x-coordinate start position player on .cub grid
	int		posy_p;	//y-coordinate start position player ...
	int		map_x; 	//x-coordinate continuous position of player on rendered grid
	int		map_y; 	//y-coordinate continuous position of player ...


	int		sizex; 	//computer display width
	int		sizey; 	//comupter display height
	void	*window;
	void	*mlx;
	// t_imgs	img;
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
/*-------------------UTILS-------------------*/
char		*ft_strducube(char *s, t_data *data);
/*--------------------FREE--------------------*/
void		free_all(t_data *data);
void		free_map(t_data *data);
void		free_grid(t_data *data);
void		free_grid2(char **grid, int height);
void		free_struct(t_data *data);
void		exit_free(t_data *data, char *str);
/*--------------------MLX--------------------*/
void		initiate_mlx(t_data *data);

#endif