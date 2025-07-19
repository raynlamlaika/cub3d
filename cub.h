#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
#endif

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
int		in_valid_ber_file(char *file_name);
void	parse_config_line(t_game *game, char *line);
int	parse_color(char *line);
void    finalize_map(t_game *game);
void print_map(char **map);


// helper
char	*ft_strdup(const char *s);
char	*get_next_line(int fd); // must be included from your GNL
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
int	ft_atoi(const char	*str);
int	ft_isdigit(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
