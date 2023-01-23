/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:07:59 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/19 10:50:21 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int			is_line_empty(char *line);
void		map_resizer(char ***src);
static void	get_map_line(char **content, char *src);
static void	realloc_map(int actual_len, char ***content);
static void	clear_map(char ***map);
static char	*get_begin_line(int fd);

int	get_map_content(char ***content, int fd)
{
	char	*line;
	int		i;

	*content = ft_calloc(2, sizeof(char *));
	if (!*content)
		return (FALSE);
	line = get_begin_line(fd);
	i = 0;
	while (line && !is_line_empty(line))
	{
		get_map_line(&((*content)[i]), line);
		free(line);
		if (!(*content)[i])
		{
			clear_map(content);
			return (FALSE);
		}
		line = get_next_line(fd);
		realloc_map(i + 2, content);
		i++;
	}
	map_resizer(content);
	if (!check_map(*content))
		return (FALSE);
	return (TRUE);
}

static void	clear_map(char ***map)
{
	int		i;
	char	**free_map;

	free_map = &(**map);
	i = 0;
	if (!free_map)
		return ;
	while (free_map[i])
	{
		free(free_map[i]);
		i++;
	}
	free(free_map);
}

static void	get_map_line(char **content, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return ;
	*content = ft_calloc(ft_strlen(src), sizeof(char));
	if (!(*content))
		return ;
	while (src[i] != '\n' && src[i])
	{
		(*content)[i] = src[i];
		i++;
	}
}

static void	realloc_map(int actual_len, char ***content)
{
	char	**new_content;
	int		i;

	new_content = ft_calloc(actual_len + 1, sizeof(char *));
	if (!new_content)
		return ;
	i = 0;
	while (i < actual_len)
	{
		new_content[i] = (*content)[i];
		i++;
	}
	free(*content);
	*content = new_content;
}

static char	*get_begin_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (is_line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}