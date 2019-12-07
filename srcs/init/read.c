/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:42:05 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 19:59:05 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <fcntl.h>

static int			conv_params(char *str, t_params *params)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == 'R')
		ret = conv_resolution(&str[i + 1], params);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ret = conv_texture(&str[i + 1], params, 's');
	else if (is_compas(str[i]))
		ret = conv_texture(&str[i + 2], params, str[i]);
	else if (BONUS == 0 && (str[i] == 'F' || str[i] == 'C'))
		ret = conv_color(&str[i + 1], params, str[i]);
	else if (BONUS == 1 && (str[i] == 'F' || str[i] == 'C'))
		ret = conv_texture(&str[i + 1], params, str[i]);
	else if (str[i])
	{
		ft_dprintf(2, "Error\nWrong information syntax\n");
		return (0);
	}
	if (ret == -1 && ret++)
		ft_dprintf(2, "Error\nWrong color syntax (R,G,B)");
	return (ret);
}

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
		exit (0);
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
