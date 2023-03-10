/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:55:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/28 11:06:42 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_pos	get_player_pos_map_scaled(t_pos pos, t_minimap minimap)
{
	pos.x = pos.x / minimap.map_scale;
	pos.y = pos.y / minimap.map_scale;
	return (pos);
}

t_pos	get_minimap_init_pos(t_pos p_pos, t_minimap minimap)
{
	t_pos	pos;
	int		y_top;
	int		y_bot;
	int		x_left;
	int		x_right;

	pos.x = p_pos.x - minimap.half_size.x;
	pos.y = p_pos.y - minimap.half_size.y;
	y_top = pos.y;
	y_bot = pos.y + minimap.size.y;
	x_left = pos.x;
	x_right = pos.x + minimap.size.x;
	if (y_top < 0)
		pos.y = 0;
	if (y_bot >= minimap.scaled_map_size.y)
		pos.y = minimap.scaled_map_size.y - minimap.size.y;
	if (x_left < 0)
		pos.x = 0;
	if (x_right >= minimap.scaled_map_size.x)
		pos.x = minimap.scaled_map_size.x - minimap.size.x;
	return (pos);
}

int	get_pixel_color(t_pos pos, char **map, t_value map_size)
{
	pos = get_scaled_map_pos(pos);
	if (pos.x < 0 || pos.y < 0 || pos.x >= map_size.x || pos.y >= map_size.y)
		return (MINIMAP_COLOR_NONE);
	else if (map[pos.y][pos.x] == ' ')
		return (MINIMAP_COLOR_WALL);
	else if ((map[pos.y][pos.x] == '1')
		|| (map[pos.y][pos.x] >= 'A' && map[pos.y][pos.x] <= 'D'))
		return (MINIMAP_COLOR_WALL);
	else if ((map[pos.y][pos.x] >= 'G' && map[pos.y][pos.x] <= 'N')
		|| (map[pos.y][pos.x] > 'g' && map[pos.y][pos.x] <= 'n'))
		return (MINIMAP_COLOR_DOOR_CLOSE);
	else if (map[pos.y][pos.x] == 'g')
		return (MINIMAP_COLOR_DOOR_OPEN);
	else
		return (MINIMAP_COLOR_GROUND);
}

t_pos	get_scaled_map_pos(t_pos pos)
{
	if (pos.x > 0)
		pos.x = pos.x / MINIMAP_SQUARE_SIZE;
	if (pos.y > 0)
		pos.y = pos.y / MINIMAP_SQUARE_SIZE;
	return (pos);
}

t_pos	get_minimap_pos(t_pos pos, t_pos p_pos, t_minimap minimap)
{
	t_pos	minimap_init_pos;

	minimap_init_pos = get_minimap_init_pos(p_pos, minimap);
	pos.x += minimap.win_pos.x - minimap_init_pos.x;
	pos.y += minimap.win_pos.y - minimap_init_pos.y;
	return (pos);
}
