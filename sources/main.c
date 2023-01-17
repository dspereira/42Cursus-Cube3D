/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/17 13:08:32 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int main(void) 
{
	t_win	win;
	t_pos	init_pos;
	t_pos	end_pos;
	int red;

	red = 0x00FF0000;
	
	init_pos.x = 50;
	init_pos.y = 50;
	end_pos.x = 200;
	end_pos.y = 200;

	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, 640, 360, "Cube3D");
	mlx_draw_line(win, end_pos, init_pos, red);
	mlx_loop(win.mlx);
	return (0);
}