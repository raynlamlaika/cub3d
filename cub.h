/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:56:59 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/07/18 03:56:59 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "mlx.h"

typedef struct s_textures {
	char *north;
	char *south;
	char *west;
	char *east;
} t_textures;

typedef struct s_player {
	int x;
	int y;
	char direction; // 'N', 'S', 'E', or 'W'
} t_player;

typedef struct s_game {
	t_textures textures;
	int floor_color;
	int ceiling_color;
	char **map;
	int map_width;
	int map_height;
	t_player player;
} t_game;


#endif