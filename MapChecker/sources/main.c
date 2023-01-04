/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:00:26 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/04 12:49:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **av)
{
	t_file	*myfile;

	if (ac == 2)
	{
		myfile = get_file_info((const char *)av[1]);
		if (!myfile)
			return (-1);
		if (!check_file(myfile))
			return (-1);
		//if (!is_valid_map(av[1]))
		//	return (-1);
		//printf("MAP: OK\n");
		free_file_mem(myfile);
		return (0);
	}
	printf("Error: Invalid number of Arguments\n");
	return (-1);
}
