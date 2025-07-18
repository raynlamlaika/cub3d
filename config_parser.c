#include "cub.h"

int	is_config_line(char *line)
{
	while (*line == ' ')
		line++;
	return (
		strncmp(line, "NO ", 3) == 0 ||
		strncmp(line, "SO ", 3) == 0 ||
		strncmp(line, "WE ", 3) == 0 ||
		strncmp(line, "EA ", 3) == 0 ||
		strncmp(line, "F ", 2) == 0 ||
		strncmp(line, "C ", 2) == 0
	);
}

void	parse_config_line(t_game *game, char *line)
{
	while (*line == ' ')
		line++;
	if (strncmp(line, "NO ", 3) == 0)
		game->textures.north = ft_strdup(line + 3);
	else if (strncmp(line, "SO ", 3) == 0)
		game->textures.south = ft_strdup(line + 3);
	else if (strncmp(line, "WE ", 3) == 0)
		game->textures.west = ft_strdup(line + 3);
	else if (strncmp(line, "EA ", 3) == 0)
		game->textures.east = ft_strdup(line + 3);
	else if (strncmp(line, "F ", 2) == 0)
		game->floor_color = parse_color(line + 2); // To implement
	else if (strncmp(line, "C ", 2) == 0)
		game->ceiling_color = parse_color(line + 2); // To implement
}
