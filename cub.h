/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:56:59 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/07/17 09:06:46 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB_H
# define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "mlx.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FOV (M_PI / 3)  // 60 degrees Field of View

#define TWO_PI 6.28318530718  // 2 * PI

typedef struct s_player t_player;
typedef struct s_screen t_screen;


typedef struct s_screen 
{
    t_player *player;
	void	*init;
	void	*wind;
	void	*img;
    char	*addr;
	int		bits_for_pixel;
	int		line_length;
	int		endian;


} t_screen;

typedef struct s_player {
    t_screen *window;
    double x_axes;
    double y_axes;
    double angle;         // Player's view angle
    double x_dir;         // X direction unit vector
    double y_dir;         // Y direction unit vector
    double step_size;
    char **map;
} t_player;

int	init_window(t_screen *window);


#endif