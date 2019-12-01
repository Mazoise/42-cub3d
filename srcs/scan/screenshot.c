/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:37:30 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/30 21:58:01 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
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
	int fd;
	int i;
	int	size;
 
	i = 0;
	if((fd = open("screenshot.bmp", O_WRONLY)) < 0)
	{
		ft_printf("Error\nScreenshot failed\n");
		mlx_destroy_image(params->ptr, params->fullscreen);
		ft_free_strs(params->grid);
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
		ft_printf("Error\nInitialisation of mlx img failed\n");
		free_all(params);
		exit(0);
	}
	fs = params->fullscreen;
	img->img = mlx_get_data_addr(fs, &img->bpp, &img->len, &img->endian);
	draw_three_d(params);
	screen_it(params);
}
