/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:41:20 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/17 14:19:34 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <fcntl.h>

int		convert_line(char *str, t_map *map)
{
	int		i;
	int		ret;

	i = 0;
	while(str[i] && str[i] == ' ')
		i++;
	if (ft_is_digit(str[i]) && (ret = conv_grid(str, map)) <= 0)
	{
		if (ret == -1)
			printf("Error\nAllocation fail\n");
		else
			printf("Error\nWrong grid format\n");
		free(str);
		return (0);
	}
	else
		if(!(conv_params(str, map)))
		{
			printf("Error\nWrong parameters\n");
			free(str);
			return (0);
		}
	free(str);
	return(1);
}

t_map	*read_map(char *mapcub)
{
	t_map	map;
	char	*str;
	int		fd;
	int		ret;
	
	if (!(ft_format(mapcub)))
	{
		ft_printf("Error\nWrong map format, should end in .cub\n");
		return (0);
	}
	else if (!(fd = open(mapcub, O_RDONLY)))
	{
		ft_printf("Error\nDid not manage to open map file\n");
		return (0);
	}
	ft_init_mapstruct(&map);
	while ((ret = get_next_line(fd, &str)))
	{
		if (!(convert_line(str, &map)))
			return (0);
	}
}
