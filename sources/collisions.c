/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:58:37 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/08 11:44:19 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int check_collision_player_wall(t_pos p_pos, t_pos w_pos);

int check_collisions(t_pos p_pos, char **map)
{
	t_pos	m_pos;
	t_pos	start_map_pos;
	t_pos	wall_pos;
	int 	i;
	int		j;

	m_pos = get_map_pos(p_pos);
	start_map_pos.x = m_pos.x - 1;
	start_map_pos.y = m_pos.y - 1;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			wall_pos.y = start_map_pos.y + j;
			wall_pos.x = start_map_pos.x + i;
			if (map[wall_pos.y][wall_pos.x] != '0')
			{
				if (check_collision_player_wall(p_pos, get_win_pos(wall_pos)))
					return (1);
			}
		}
	}
	return (0);
}

static int check_collision_player_wall(t_pos p_pos, t_pos w_pos)
{
	t_pos	test_pos;
	t_value	dist;
	double	collision_dist;
	
	test_pos = p_pos;
	test_pos.x = clamp(w_pos.x, w_pos.x + WIN_WIDTH / MAP_WIDTH, test_pos.x);
	test_pos.y = clamp(w_pos.y, w_pos.y + WIN_HEIGHT / MAP_HEIGHT, test_pos.y);
	dist.x = p_pos.x - test_pos.x;
	dist.y = p_pos.y - test_pos.y;
	collision_dist = sqrt((dist.x * dist.x) + (dist.y * dist.y));
	if (collision_dist < PLAYER_RADIUS)
		return (1);
	return (0);
}
