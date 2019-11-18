/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:01:01 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/18 13:01:44 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h> 
# include <math.h> 

typedef struct		s_map
{
	char	**grid;
	int		x_max;
	int		y_max;
	void	*NO;
	void	*SO;
	void	*WE;
	void	*EA;
	void	*S;
	int		F;
	int		C;
}					t_map;

void	free_grid(char **grid);
int		is_valid_grid_element(char c);
int		grid_width(char *str);
int		is_save_request(char *str);
int		check_format(char *str);
t_map	*init_mapstruct(void);
int		check_all_params(t_map *map);
int		fill_grid(char *str, t_map *map);
int		first_fill_grid(char *str, t_map *map);
int		conv_grid(char *str, t_map *map);
int		conv_params(char *str, t_map *map);
int		convert_line(char *str, t_map *map);
t_map	*read_map(char *mapcub);
int		conv_resolution(char *str, t_map *map);
int		conv_texture(char *str, t_map *map);
int		conv_color(char *str, t_map *map);

#endif