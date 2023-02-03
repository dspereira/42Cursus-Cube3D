/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:18:16 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/23 09:21:37 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	init_map_struct(t_map *init)
{
	init->wall_textures = ft_calloc(4, sizeof(char *));
	init->rgb_colors = ft_calloc(2, sizeof(int));
	if (!init->wall_textures || !init->rgb_colors)
	{
		if (init->wall_textures)
			free(init->wall_textures);
		if (init->rgb_colors)
			free(init->rgb_colors);
		return (FALSE);
	}
	init->rgb_colors[RGB_C] = RGB_NO_COLOR;
	init->rgb_colors[RGB_F] = RGB_NO_COLOR;
	return (TRUE);
}

int	get_all_map_info(t_map **map, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (!fd)
		return (0);
	if (!get_map_textures(map, fd) || !get_map_content(&(*map)->content, fd)
		|| !get_player_info((*map)->content, &(*map)->orientation, \
		&(*map)->pos))
		return (FALSE);
	return (TRUE);
}