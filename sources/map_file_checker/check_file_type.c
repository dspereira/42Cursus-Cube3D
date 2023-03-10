/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:08:40 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/09 12:39:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int		find_last_char_index(char *file, char to_find);
static int		ft_strcmp(char *s1, char *s2);
static char		*ft_substr(char const *s, unsigned int start, size_t len);

int	is_valid_file_type(char *file)
{
	char	*extension;
	int		dot_index;

	dot_index = find_last_char_index(file, '.');
	extension = ft_substr(file, dot_index, (ft_strlen(file) - dot_index));
	if (!extension)
		return (FALSE);
	if (ft_strcmp(extension, ".cub"))
	{
		free(extension);
		print_error_msg("Invalid File Type");
		return (FALSE);
	}
	free(extension);
	return (TRUE);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	a;
	size_t	i;
	char	*substring;

	if (!s)
		return (0);
	i = start;
	a = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s) + 1;
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (0);
	while (i < ft_strlen(s) && a < len)
		substring[a++] = s[i++];
	substring[a] = '\0';
	return (substring);
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	find_last_char_index(char *file, char to_find)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	while (i >= 0)
	{
		if (file[i] == to_find)
			break ;
		i--;
	}
	return (i);
}
