/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/07 16:04:14 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "../includes/header.h"

int	key(int keycode, t_player *player);
int render_win(void *data);
static int get_game_configs(int ac, char **av, t_map *map);
void	setup_textures(char **tex_files, t_tex *texture, void *mlx);

int main(int argc, char **argv) 
{
	t_win		win;
	t_pos		pos1;
	t_pos		pos2;
	int			red;
	int 		size;
	t_player	*player;
	t_map		map;
	t_data		data;
	t_tex		tex;

	if (!get_game_configs(argc, argv, &map))
		return (-1);
	player = player_init((t_pos){100, 100}, 0);
	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	win.frame.mlx_img = mlx_new_image(win.mlx, WIN_WIDTH, WIN_HEIGHT);
	win.frame.addr = mlx_get_data_addr(win.frame.mlx_img, &(win.frame.bpp), &(win.frame.line_len), &(win.frame.endian));
	setup_textures(map.wall_textures, &tex, win.mlx);
	data.win = &win;
	data.player = player;
	data.map = map;
	data.tex = tex;
	mlx_loop_hook(win.mlx, render_win, &data);
	mlx_key_hook(win.mlx_win, key, player);
	mlx_loop(win.mlx);
	
	return (0);
}

int render_win(void *data)
{
	static int	frames_count = 0;
	t_player	*player;
	t_map		map;
	t_win		win;

	player = ((t_data*)data)->player;
	map = ((t_data*)data)->map;
	win = *((t_data*)data)->win;

	raycast_all(player, map.content);
	//render_scene_2d(win.frame, *player, map.content);
	render_scene_3d(win.frame, *player);
	render_scene_3d_tex(win.frame, *player, ((t_data*)data)->tex);
	mlx_put_image_to_window(win.mlx, win.mlx_win, win.frame.mlx_img, 0, 0);

	frames_count++;
	if (check_time_ms(1000))
	{
		printf("fps: %d\n", frames_count);
		frames_count = 0;
	}
}

static int get_game_configs(int ac, char **av, t_map *map)
{
	if (ac == 2)
	{
		if (check_file(av[1]))
		{
			if (!init_map_struct(map))
				return (0);
			if (!get_all_map_info(&map, av[1]))
			{
				printf("Map KO\n");
				return (0);
			}
			else
				printf("Map OK\n");
		}
		else
		{
			printf("Map KO\n");
			return (0);
		}
		//free_memory(map);
		return (1);
	}
	printf("Error: Invalid number of Arguments\n");
	return (0);
}

void	setup_textures(char **tex_files, t_tex *texture, void *mlx)
{
	texture->no.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_NO], \
		&(texture->no.width), &(texture->no.height));
	texture->no.addr = mlx_get_data_addr(texture->no.mlx_img, \
		&(texture->no.bpp), &(texture->no.line_len), &(texture->no.endian));
	texture->so.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_SO], \
		&(texture->so.width), &(texture->so.height));
	texture->so.addr = mlx_get_data_addr(texture->so.mlx_img, \
		&(texture->so.bpp), &(texture->so.line_len), &(texture->so.endian));
	texture->ea.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_EA], \
		&(texture->ea.width), &(texture->ea.height));
	texture->ea.addr = mlx_get_data_addr(texture->ea.mlx_img, \
		&(texture->ea.bpp), &(texture->ea.line_len), &(texture->ea.endian));
	texture->we.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_WE], \
		&(texture->we.width), &(texture->we.height));
	texture->we.addr = mlx_get_data_addr(texture->we.mlx_img, \
		&(texture->we.bpp), &(texture->we.line_len), &(texture->we.endian));
}
