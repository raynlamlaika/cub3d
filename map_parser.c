#include "cub.h"

void save_map_line(t_game *game, char *line)
{
    int len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0'; // Remove trailing newline

    t_line *new = malloc(sizeof(t_line));
    if (!new)
        return; // Or handle error

    new->line = ft_strdup(line);
    new->next = NULL;

    if (!game->map_lines)
        game->map_lines = new;
    else
    {
        t_line *tmp = game->map_lines;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

