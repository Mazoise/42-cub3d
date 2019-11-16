/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:45:55 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/16 20:53:13 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h> //
#include <stdlib.h> 
#include <math.h> 
#include <unistd.h>

int		x_size;
int		y_size;
void	*test;
void	*test2;
int x = 0;

int	draw(int keycode,void *param)
{
//	static int s = 0;
	static int y = 15;

	// x = (x + 50) % (x_size - 50);
//	s = s + 50;
//	x = 0;
	// int temp_x = x;
	// y = 15;
	(void)param;
	printf("hey %d\n", keycode); //w
	if (keycode == 53)
	{
		mlx_destroy_window(test, test2);
		exit(0);
	}
//	int c = (random() % 0xFFFFFF);
	// int c2 = c * 0.5;
//	int c2 = (random() % 0xFFFFFF);
	// while (x < x_size - 50)
	// {
	// 	y = temp_x;
	// 	while (y < y_size - 50)
	// 	{
	// 	//	mlx_pixel_put(test, test2, x, y, (y % 100 > 50) ? ((c + x) % 0xFFFFFF) : ((c2 + x) % 0xFFFFFF));
	// 	//	mlx_pixel_put(test, test2, y, x, (y % 100 > 50) ? ((c + x) % 0xFFFFFF) : ((c2 + x) % 0xFFFFFF));
	// 		y++;
	// 		if (y < y_size - 50)
	// 		{
	// 	//		mlx_pixel_put(test, test2, x, y, (x % 100 > 50) ? (((c2 + x)) % 0xFFFFFF) : ((c + x) % 0xFFFFFF));
	// 	//		mlx_pixel_put(test, test2, y, x, (x % 100 > 50) ? (((c2 + x)) % 0xFFFFFF) : ((c + x) % 0xFFFFFF));
	// 			y++;
	// 		}
	// 	}
	// 	x++;
	// }
	char s[2];
	s[0] = ((random() % (90 - 64)) + 65);
	s[1] = 0;
	x += 10;
	if (x > x_size - 10)
	{
		x = 15;
		y += 15;
	}
	mlx_string_put(test, test2, x, y, random() % 0xffffff, (char *)s);
	return (1);
}

int		main()
{
	x_size = 1300;
	y_size = 1300;
	if (!(test = mlx_init()))
		printf("ERROR\n"); // ERROR //w
	if(!(test2 = mlx_new_window(test, x_size, y_size, "This is a test")))
		printf("ERROR WINDOW\n"); // ERROR //w

	mlx_key_hook(test2, NULL, NULL);
	mlx_loop_hook(test, draw, NULL);
	mlx_loop(test);
}
