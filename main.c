#include "include/cube.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		init_struct(&data);
		get_height(av[1], &data);
		read_map(av[1], &data);
		parse_map(&data);
		initiate_mlx(&data);
		init_texture(&data);
		// raycast(&data);
		// mlx_loop(data.mlx_ptr);
		print_map(&data);
		exit_free(&data, "FIN");
	}
	// free_grid(&data);
	// free(data);
}
