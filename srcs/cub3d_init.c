/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:11:22 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/17 22:16:48 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		conv_resolution(char *str, t_map *map)
{
		(void)str;
		(void)map;
		return (1);
}

int		conv_texture(char *str, t_map *map)
{
		(void)str;
		(void)map;
		return (1);
}

int		conv_color(char *str, t_map *map)
{
		(void)str;
		(void)map;
		return (1);
}

void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
	}
	free(grid);
}

int		is_valid_grid_element(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int		grid_width(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (is_valid_grid_element(str[i]))
			j++;
		else if (str[i])
		{
			ft_printf("Error\nWrong grid element\n");
			return (0);
		}
		i++;
	}
	return (j);
}

int		is_save_request(char *str)
{
	int	i;

	i = ft_len_c(str, 0);
	if (i == 6 && str[0] == '-' && str[1] == '-' && str[2] == 's' 
		&& str[3] == 'a' && str[4] == 'v' && str[5] == 'e')
		return (1);
	return (0);
}

int		check_format(char *str)
{
	int	i;

	i = ft_len_c(str, 0);
	if (is_save_request(str))
	{
		ft_printf("Error\nMissing file format\n");
		return (0);
	}	
	else if (i < 5 || str[i - 1] != 'b' || str[i - 2] != 'u' 
		|| str[i - 3] != 'c' || str[i - 4] != '.')
	{
		ft_printf("Error\nInvalid file format\n");
		return (0);
	}
	return (1);
}

int		init_mapstruct(t_map *map)
{
	if (!(map = malloc(sizeof(t_map) * 1)))
		return (0);
	map->grid = 0;
	map->x_max = -1;
	map->y_max = -1;
	map->NO = 0;
	map->SO = 0;
	map->WE = 0;
	map->EA = 0;
	map->S = 0;
	map->F = -1;
	map->C = -1;
	return (1);
}

int		check_all_params(t_map *map)
{
	if (map->x_max < 0 || map->y_max < 0  || !map->NO || !map->SO || !map->WE
		|| !map->EA || !map->S || map->F < 0 || map->C < 0)
	{
		if (map->x_max < 0 || map->y_max < 0)
			ft_printf("Error\nMissing resolution format\n");
		if (!map->NO)
			ft_printf("Error\nMissing north texture path\n");
		if (!map->SO)
			ft_printf("Error\nMissing south texture path\n");
		if (!map->WE)
			ft_printf("Error\nMissing west texture path\n");
		if (!map->EA)
			ft_printf("Error\nMissing east texture path\n");
		if (!map->S)
			ft_printf("Error\nMissing sprite texture path\n");
		if (map->F < 0)
			ft_printf("Error\nMissing floor color format\n");
		if (map->C < 0)
			ft_printf("Error\nMissing ceiling color format\n");
		return (0);
	}
	return (1);
}
