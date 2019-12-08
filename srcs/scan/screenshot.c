/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:37:30 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 21:52:50 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <sys/errno.h>
#define	INFO 54

static void	copy_screen(int fd, t_params *params, char *str)
{
	int		i;

	i = params->max.j - 1;
	while (i >= 0)
	{
		write(fd, &str[i * params->img.len], params->img.len);
		i--;
	}
}

static void put_int_fd(int nb, int fd, int len)
{
	int		k;

	k = 0;
	while (k < len)
	{
		ft_putchar_fd(nb / (int)pow(256, k), fd);
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
	put_int_fd(11811, fd, 4);
	put_int_fd(11811, fd, 4);
	put_int_fd(0, fd, 8);
}

void		screen_it(t_params *params)
{
	int		fd;
	int		i;
	int		size;
	char	*str;
 
	i = 0;
	str = ft_sprintf("Screenshot(%d).bmp", i);
	while((fd = open(str, O_CREAT | O_EXCL | O_WRONLY, S_IRWXU)) < 0 && errno == 17)
	{
		free(str);
		str = ft_sprintf("Screenshot(%d).bmp", i);
		i++;
	}
	free(str);
	if (fd == -1 && errno != 17)
	{
		ft_dprintf(2, "Error\nOpen error : %s (map)\n", strerror(errno));
		free_all(params);
		exit(0);
	}
	size = params->max.i * params->max.j; 
	fill_info(fd, params, size);
	copy_screen(fd, params, params->img.img);
	close(fd);
	free_all(params);
	exit(0);
}

void		screenshot_bmp(t_params *params)
{
	t_mlx_img	*img;
	t_idx		max;
	void		*fs;

	img = &params->img;
	max = params->max;
	if (!(params->fullscreen = mlx_new_image(params->ptr, max.i, max.j)))
	{
		ft_dprintf(2, "Error\nMlx error : %s (image)\n", strerror(errno));
		free_all(params);
		exit(0);
	}
	fs = params->fullscreen;
	img->img = mlx_get_data_addr(fs, &img->bpp, &img->len, &img->endian);
	full_scan(params);
	screen_it(params);
}
