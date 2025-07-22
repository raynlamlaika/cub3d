#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
 // add --------------
# include "mlx.h"
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
#endif
#define FOV 60.0 * (M_PI / 180)
# define ROTATE_SPEED 3
# define KEY_W 13      // W
# define KEY_S 1       // S
# define KEY_A 0       // A
# define KEY_D 2       // D
# define ESC 53        // Escape

# define UP 126        // Up arrow
# define DOWN 125      // Down arrow
# define RIGHT 124     // Right arrow
# define LEFT 123      // Left arrow
# define TILE_P 3
# define TILE_SIZE 30
# define TWO_PI 6.28318530718
 // add --------------

typedef struct s_textures {
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;




typedef struct s_player {
	int		x;
	int		y;
	int		move;
	int		c_count;
	char	direction;
}	t_player;

typedef struct s_line {
	char			*line;
	struct s_line	*next;
}	t_line;

// add --------------

typedef  struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}		t_mlx;
// add --------------

typedef struct s_ray
{
    double ray_x;
    double ray_y;
    double ray_angle; // allready exist
    double ray_dir_x;
    double ray_dir_y;
    double delta_dist_x;
    double delta_dist_y;
    int map_x;
    int map_y;
	double perp_wall_dist;
	double hit_x;
	double hit_y;
	double side;
} t_ray;


typedef struct s_game {
	t_mlx		*helper; // mlx init helper
	// t_ray		*ray;
	double 		angle;
	int			screen_height;
	int			screen_width;
	t_textures	textures;
	int			floor_color;
	int			ceiling_color;
	t_line		*map_lines;
	char		**map;
	int			map_started;
	int			map_ended;
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
void	validate_map(t_game *game);
void	print_error(const char *message);


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


// rayn's part
void init_game(t_game *game);
int close_window(t_game *game);
int render_map(t_game *game);
void cast_all_rays(t_game *game);
void my_mlx_pixel_put(t_game *game, int x, int y, int color);
int bottoms(int keycode, t_game *game);
void ray_cast_all_dda(t_game *game);

int key_press(int keycode, t_game* game);
#endif
