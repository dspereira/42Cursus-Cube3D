/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:04 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/23 15:05:19 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define PLAYER_SIZE		10
#define PLAYER_COLOR	0x00E28743
#define WALL_COLOR		0x002596BE

static void render_map(t_win win, char map[MAP_WIDTH][MAP_HEIGHT]);
static void render_player(t_win win, t_player player, char map[MAP_WIDTH][MAP_HEIGHT]);

void render_scene_2d(t_win win, t_player player, char map[MAP_WIDTH][MAP_HEIGHT])
{
	render_map(win, map);
	render_player(win, player, map);
}

static void render_map(t_win win, char map[MAP_WIDTH][MAP_HEIGHT])
{
	int		square_size;
	int		i;
	int		j;
	t_pos	pos;

	square_size = WIN_HEIGHT / MAP_HEIGHT;
	i = 0;
	while (i < MAP_HEIGHT) 
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			pos.x = j * square_size;
			pos.y = i * square_size;
			if (map[i][j])
				mlx_draw_fill_square(win, pos, square_size, WALL_COLOR);
			else 
				mlx_draw_stroke_square(win, pos, square_size, 0x002596BE);
			j++;
		}
		i++;
	}
}

static void render_player(t_win win, t_player player, char map[MAP_WIDTH][MAP_HEIGHT])
{
	int		i;
	int		n_rays;
	t_pos	end;
	t_pos	p_pos;


	p_pos.x = player.pos.x - PLAYER_SIZE / 2;
	p_pos.y = player.pos.y - PLAYER_SIZE / 2;

	mlx_draw_fill_square(win, p_pos, PLAYER_SIZE, PLAYER_COLOR);

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	i = 0;
	while (i < n_rays)
	{
		end = get_new_pos(player.pos, player.rays[i].cos, player.rays[i].sin,  player.rays[i].length_win);
		mlx_draw_line(win, player.pos, end, 0x00FF0000);
		i++;
	}
}
