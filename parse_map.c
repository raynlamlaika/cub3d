# include "cub.h"

int get_max_map_width(t_line *lines)
{
    int max = 0;
    while (lines)
    {
        int len = ft_strlen(lines->line);
        if (len > max)
            max = len;
        lines = lines->next;
    }
    return max;
}

int get_map_height(t_line *lines)
{
    int count = 0;
    while (lines)
    {
        count++;
        lines = lines->next;
    }
    return count;
}

void print_map(char **map)
{
	int i = 0;

	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}


void finalize_map(t_game *game)
{
    int height = get_map_height(game->map_lines);
    int width = get_max_map_width(game->map_lines);

    game->map = malloc(sizeof(char *) * (height + 1));
    if (!game->map)
	{
		perror("Map allocation failed");
	}

    t_line *current = game->map_lines;
    int i = 0;
    while (current)
    {
        game->map[i] = malloc(width + 1);
        memset(game->map[i], ' ', width);
        memcpy(game->map[i], current->line, ft_strlen(current->line));
        game->map[i][width] = '\0';

        current = current->next;
        i++;
    }
    game->map[i] = NULL;
}
