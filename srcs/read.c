/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:42:05 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/19 17:14:03 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <fcntl.h>

int			conv_grid(char *str, t_params *params)
{
	if (!(check_all_params(params)))
		return (0);
	if (!params->grid)
	{
		if (!(params->grid = malloc(sizeof(char*) * 2)))
		{
			ft_printf("Error\nAllocation fail\n");
			return (0);
		}
		if (!(first_fill_grid(str, params)))
			return (0);
		params->grid[1] = 0;
	}
	else if (!(fill_grid(str, params)))
		return (0);
	return (1);
}

int			conv_params(char *str, t_params *params)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'R')
		ret = conv_resolution(&str[i + 1], params);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ret = conv_texture(&str[i + 1], params, 's');
	else if (str[i] == 'N' || str[i] == 'W' || str[i] == 'E' || str[i] == 'S')
		ret = conv_texture(&str[i + 2], params, str[i]);
	else if (str[i] == 'F' || str[i] == 'C')
		ret = conv_color(&str[i + 1], params, str[i]);
	else if (str[i])
		ft_printf("Error\nWrong information syntax\n");
	else
		ret = 1;
	return (ret);
}

int			convert_line(char *str, t_params *params)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!(ft_isdigit(str[i])))
	{
		if (!(conv_params(str, params)))
		{
			free(str);
			return (0);
		}
	}
	else if (!(conv_grid(str, params)))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

int			convert_read(int fd, t_params *params)
{
	int		ret;
	char	*str;
	
	while ((ret = get_next_line(fd, &str)))
	{
		if (!(convert_line(str, params)))
			return (0);
	}
	if (!(convert_line(str, params)))
		return (0);
	if (ret == -1)
	{
		ft_printf("Error\nAllocation fail\n");
		ft_free_strs(params->grid);
		return (0);
	}
	return (1);
}

int			read_map(char *mapcub, t_params *params)
{
	int		fd;


	if (!(check_format(mapcub)))
		return (0);
	else if ((fd = open(mapcub, O_RDONLY)) < 0)
	{
		ft_printf("Error\nDid not manage to open map file\n");
		return (0);
	}
	if (!(convert_read(fd, params)))
		return (0);
	if (!params->grid)
	{
		ft_printf("Error\nNo map grid\n");
		return (0);
	}
	return (1);
}
