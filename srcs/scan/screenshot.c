/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:37:30 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/28 22:44:43 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#define	INFO 54

static void	copy_screen(int fd, t_params *params, char *str)
{
	int		i;
	int		j;

	i = params->max.j - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < params->img.len)
		{
			ft_putchar_fd(str[i * params->img.len + j], fd);
			j++;
		}
		i--;
	}
}

static void put_int_fd(int nb, int fd, int len)
{
	int		k;

	k = 0;
	while (k < len)
	{
		ft_putchar_fd(nb / pow(256, k), fd);
		k++;
	}
}

static void	fill_info(int fd, t_params *params, int	size)
{
	ft_putchar_fd(66, fd);
	ft_putchar_fd(77, fd);
	put_int_fd(size + INFO, fd, 4);
	put_int_fd(0, fd, 4);
	put_int_fd(INFO, fd, 4);
	put_int_fd(INFO - 14, fd, 4);
	put_int_fd(params->max.i, fd, 4);
	put_int_fd(params->max.j, fd, 4);
	put_int_fd(1, fd, 2);
	put_int_fd(params->img.bpp, fd, 2);
	put_int_fd(0, fd, 4);
	put_int_fd(size, fd, 4);
	put_int_fd(params->max.i / 377952, fd, 4);
	put_int_fd(params->max.j / 377952, fd, 4);
	put_int_fd(0, fd, 8);
}

int			screenshot_bmp(t_params *params)
{
	int fd;
	int i;
	int	size;
 
	i = 0;
	if((fd = open("screenshot.bmp", O_WRONLY)) < 0)
	{
		return (0);
	}
	size = params->max.i * params->max.j; 
	fill_info(fd, params, size);
	copy_screen(fd, params, params->img.img);
	close(fd);
	return (1);
}
