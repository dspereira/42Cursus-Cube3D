/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:54:55 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/08 15:00:03 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define TRUE	1
#define FALSE	0

static int	door_check_interaction(t_ray ray, char **map, t_player *player);
static char	door_status_update(char old_status);

void	doors_interaction(t_map map, t_player *player)
{
	t_ray	view;
	t_pos	door;

	view = player->rays[NUMBER_RAYS / 2];
	if (!door_check_interaction(view, map.content, player))
		return ;
	door = view.door_pos;
	if (map.content[door.y][door.x] == D_FRAME_OPEN_0)
		map.content[door.y][door.x] = D_FRAME_OPEN_1;
	else if (map.content[door.y][door.x] == D_FRAME_CLOSE_0)
		map.content[door.y][door.x] = D_FRAME_CLOSE_7;
}

void	doors_control(t_map map)
{
	int		i;
	int		x;
	int		y;
	char	**content;

	content = map.content;
	i = 0;
	if (!map.doors)
		return ;
	while (map.doors[i].x != -1)
	{
		x = map.doors[i].x;
		y = map.doors[i].y;
		if ((content[y][x] > 'g' && content[y][x] <= 'n')
			|| (content[y][x] > 'G' && content[y][x] <= 'N'))
		{
			if (doors_time_check_ms(DOOR_TIME_SPRITES))
				content[y][x] = door_status_update(content[y][x]);
		}
		i++;
	}
}

static int	door_check_interaction(t_ray ray, char **map, t_player *player)
{
	t_pos		p_map_pos;

	p_map_pos = get_map_pos(player->pos);
	if (!ray.is_door)
		return (FALSE);
	else if (ray.door_dist > DIST_OPEN_DOOR || ray.door_dist < 0.10)
		return (FALSE);
	else if (ray.door_pos.x < 0 || ray.door_pos.y < 0)
		return (FALSE);
	else if ((map[p_map_pos.y][p_map_pos.x] >= 'G'
		&& map[p_map_pos.y][p_map_pos.x] <= 'N')
		|| (map[p_map_pos.y][p_map_pos.x] >= 'g'
		&& map[p_map_pos.y][p_map_pos.x] <= 'n'))
		return (FALSE);
	return (TRUE);
}

static char	door_status_update(char old_status)
{
	char	new_status;

	new_status = '\0';
	if (old_status > D_FRAME_CLOSE_1 && old_status <= D_FRAME_CLOSE_7)
		new_status = old_status - 1;
	else if (old_status >= D_FRAME_OPEN_1 && old_status < D_FRAME_OPEN_7)
		new_status = old_status + 1;
	else if (old_status == D_FRAME_OPEN_7)
		new_status = D_FRAME_CLOSE_0;
	else if (old_status == D_FRAME_CLOSE_1)
		new_status = D_FRAME_OPEN_0;
	return (new_status);
}
