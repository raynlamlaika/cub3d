#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "/home/abouabba/Desktop/Cup_3D/libft/libft.h"

typedef struct s_textures {
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_player {
	int		x;
	int		y;
	char	direction;
}	t_player;

typedef struct s_line {
	char			*line;
	struct s_line	*next;
}	t_line;

typedef struct s_game {
	t_textures	textures;
	int			floor_color;
	int			ceiling_color;
	t_line		*map_lines;
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
}	t_game;

// ---- Function prototypes ----
void	check_argument(int ac, char **av);
void	init_game_struct(t_game *game);
int		is_config_line(char *line);
int		is_empty_line(char *line);
void	parse_line(t_game *game, char *line);
void	parse_config_line(t_game *game, char *line);
void	save_map_line(t_game *game, char *line);

// helper
char	*ft_strdup(const char *s);
char	*get_next_line(int fd); // must be included from your GNL

#endif
