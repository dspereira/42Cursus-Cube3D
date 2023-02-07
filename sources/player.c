/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:40:52 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/07 15:32:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void add_rays_to_player(t_player *player, int n_rays);

t_player *player_init(t_pos pos, int dir)
{
	t_player    *player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (0);
	player->pos = pos;
	player->dir = (float) dir;
	player->angle_step = (float)CAMERA_ANGLE / NUMBER_RAYS;
	player->rays = malloc(NUMBER_RAYS * sizeof(t_ray));
	if (!(player->rays))
		return (0);
	add_rays_to_player(player, NUMBER_RAYS);
	return (player);
}

void player_update_vision(t_player *player, int rot_angle)
{
	t_ray	*rays;
	int 	i;

	rays = player->rays;
	player->dir = normalizeAngles(player->dir + rot_angle);
	i = -1;
	while (++i < NUMBER_RAYS)
		ray_update_dir(&rays[i], rays[i].dir + rot_angle);
}

void player_move(t_player *player, int dir)
{
	float angle;

	angle = normalizeAngles((float)dir + player->dir);
	player->pos = get_new_dist_pos(player->pos, angle, MOVE_STEP);
}

static void add_rays_to_player(t_player *player, int n_rays)
{
	int     i;
	float   angle;

	angle = player->dir + (CAMERA_ANGLE / 2);
	i = 0;
	while (i < n_rays)
	{
		angle -= player->angle_step;
		ray_init(&(player->rays[i]), angle, player->dir);
		i++;
	}
}
