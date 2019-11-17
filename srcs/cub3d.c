/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:45:55 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/17 12:20:37 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		x_size;
int		y_size;
void	*test;
void	*test2;

int	draw(int keycode,void *param)
{
	int x;
	int y;

	x = 50;
	y = 50;
	(void)param;
	printf("hey %d\n", keycode); //w
	if (keycode == 53)
	{
		mlx_destroy_window(test, test2);
		exit(0);
	}
	int c = (random() % 0xFFFFFF);
	// int c2 = c * 0.5;
	int c2 = (random() % 0xFFFFFF);
	while (x < x_size - 50)
	{
		y = 50;
		while (y < y_size - 50)
		{
			mlx_pixel_put(test, test2, x, y, (y % 100 > 50) ? c : c2);
			y++;
			if (y < y_size - 50)
			{
				mlx_pixel_put(test, test2, x, y, (x % 100 > 50) ? c2 : c);
				y++;
			}
		}
		x++;
	}
	c = (random() % 0xFFFFFF);
	c2 = (random() % 0xFFFFFF);
	while (x > 50)
	{
		y = y_size - 50;
		while (y > 50)
		{
			mlx_pixel_put(test, test2, x, y, (y % 100 > 50) ? c : c2);
			y--;
			if (y > 50)
			{
				mlx_pixel_put(test, test2, x, y, (x % 100 > 50) ? c2 : c);
				y--;
			}	
		}
		x--;
	}
	return (1);
}

int		main(int argc, char **argv)
{
	x_size = 1000;
	y_size = 1000;
	if (!(test = mlx_init()))
		printf("ERROR\n"); // ERROR //w
	if(!(test2 = mlx_new_window(test, x_size, y_size, "This is a test")))
		printf("ERROR WINDOW\n"); // ERROR //w

	mlx_key_hook(test2, NULL, NULL);
	mlx_loop_hook(test, draw, NULL);
	mlx_loop(test);
}
