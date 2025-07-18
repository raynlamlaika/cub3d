#include "cub.h"

void	parse_line(t_game *game, char *line)
{
	if (is_config_line(line))
		parse_config_line(game, line);
	else
		save_map_line(game, line);
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}
