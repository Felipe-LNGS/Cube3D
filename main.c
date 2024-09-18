#include "include/cube.h"

int	on_destroy(t_data *data)
{
	free_all(data, data->img);
	printf("Exit\n");
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_data *cub)
{
	if (keysym == XK_Escape)
		on_destroy(cub);
	if (keysym == XK_w)
		cub->move[Y] = 1;
	if (keysym == XK_s)
		cub->move[Y] = -1;
	if (keysym == XK_a)
		cub->move[X] = -1;
	if (keysym == XK_d)
		cub->move[X] = 1;
	if (keysym == XK_Left)
		cub->rotate -= 1;
	if (keysym == XK_Right)
		cub->rotate += 1;
	return (0);
}

int	handle_keyrelease(int key, t_data *cub)
{
	if (key == XK_w && cub->move[Y] == 1)
		cub->move[Y] = 0;
	if (key == XK_s && cub->move[Y] == -1)
		cub->move[Y] = 0;
	if (key == XK_a && cub->move[X] == -1)
		cub->move[X] = 0;
	if (key == XK_d && cub->move[X] == 1)
		cub->move[X] = 0;
	if (key == XK_Left && cub->rotate <= 1)
		cub->rotate = 0;
	if (key == XK_Right && cub->rotate >= 1)
		cub->rotate = 0;
	return (0);
}
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (ft_printf(RED "Error\nThere must be 2 arguments\n" RESET));
	else
	{
		init_struct(&data);
		get_height(av[1], &data);
		read_map(av[1], &data);
		parse_map(&data);
		initiate_mlx(&data);           // creation: mlx_ptr + window
		init_texture(&data, data.img); // init xpm textures
		raycast(&data);
		mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
		mlx_hook(data.win_ptr, DestroyNotify, 0, &on_destroy, &data);
		mlx_loop_hook(data.mlx_ptr, &displaymoves, &data);
		
		mlx_loop(data.mlx_ptr);
		// print_map(&data);
		// exit_free(&data, "FIN");
	}
	// free_grid(&data);
	// free(data);
}
