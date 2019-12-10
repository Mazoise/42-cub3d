/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:42:05 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 10:39:58 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <fcntl.h>

static int			convert_line(char *str, t_params *params)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (str[i] == ' ')
		i++;
	if (!(ft_isdigit(str[i])))
		ret = conv_params(str, params);
	else
		ret = conv_grid(str, params);
	free(str);
	return (ret);
}

static int			convert_read(int fd, t_params *params)
{
	int		ret;
	char	*str;

	while ((ret = get_next_line(fd, &str)) > 0)
	{
		if (!(convert_line(str, params)))
			return (0);
	}
	if (ret == -1)
	{
		ft_dprintf(2, "Error\n%s\n", strerror(errno));
		ft_free_strs(params->grid);
		return (0);
	}
	if (!(convert_line(str, params)))
		return (0);
	return (1);
}

int					read_map(char *mapcub, t_params *params)
{
	int		fd;

	check_format(mapcub);
	if ((fd = open(mapcub, O_RDONLY)) < 0)
	{
		ft_dprintf(2, "Error\nOpen error : %s (map)\n", strerror(errno));
		exit(0);
	}
	if (!(convert_read(fd, params)))
		return (0);
	if (!params->grid)
	{
		ft_dprintf(2, "Error\nNo map grid\n");
		return (0);
	}
	return (1);
}
