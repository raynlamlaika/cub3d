
#include "cub.h"

int	in_valid_ber_file(char *file_name)
{
	int	len;

	if (!file_name)
		return (0);
	len = 0;
	while (file_name[len])
		len++;
	if (len < 4)
		return (0);
	return (file_name[len - 4] == '.'
		&& file_name[len - 3] == 'c'
		&& file_name[len - 2] == 'u'
		&& file_name[len - 1] == 'b');
}

void	check_argument(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\n!In valid file");
		exit (1);
	}
	if (!in_valid_ber_file(av[1]))
	{
		printf("Error\n<----!file_name is not valid---->");
		exit (1);
	}
}

void	init_game_struct(t_game *game)
{
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.east = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player.x = -1;
	game->player.y = -1;
	game->player.direction = '\0';
}


int	main(int ac, char **av)
{
	t_game	*game;

	check_argument(ac, av);
	game = malloc(sizeof(t_game));
	if (!game)
	{
		perror("Error\n<----!Memory allocation failed---->");
		exit(1);
	}
	init_struct_game(game);
	return (0);
}
