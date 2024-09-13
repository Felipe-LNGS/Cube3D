#include "include/cube.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;

	if (ac == 2)
	{
		ft_bzero(&map, sizeof(t_map));
		ft_bzero(&data, sizeof(t_data));
		data.map = &map;
		get_height(av[1], &data);
		read_map(av[1], &data);
		parse_map(&data);
		initiate_mlx(&data);
		init_texture(&data);
		mlx_loop(data.mlx_ptr);
		exit_free(&data, "FIN");
		// print_map(&data);
	}
	// free_grid(&data);
	// free(data);
}
