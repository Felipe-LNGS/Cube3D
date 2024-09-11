#ifndef CUBE_H
# define CUBE_H

# include "../.libft/libft.h"
# include "../.minilibx-linux/mlx.h"

typedef struct s_map
{
	char		**grid;
	char		**tmp_grid;
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	int			start_line;
	char		*f;
	char		*c;
	int			nb_lines;
	int			width;
	int			height;
}				t_map;

typedef struct s_player
{
	int			pos_y;
	int			pos_x;
}				t_player;

typedef struct s_data
{
	t_map		*map;
	t_player	*player;
}				t_data;

int				check_format(char *map);
void			get_width(t_data *data);
int				get_height(char *filename, t_data *data);
int				read_map(char *filename, t_data *data);
void			free_grid(t_data *data);
void			print_map(t_data *data);
void			rework_map(t_data *data);
char			*skip_space(char *line);
void			stock_info(char *line, t_data *data);
void			stock_info_bis(char *line, t_data *data);
int				is_info(char *line);
void			check_is_close(t_data *data);
void			parse_map(t_data *data);
void			check_valid_char(t_data *data);

#endif