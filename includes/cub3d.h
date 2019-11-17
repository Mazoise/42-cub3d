/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:01:01 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/17 13:41:43 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h> 
# include <math.h> 

typedef struct	s_map
{
	char	**grid;
	int		x_max;
	int		y_max;
	void	*NO;
	void	*SO;
	void	*WE;
	void	*EA;
	void	*S;
	void	*F;
	void	*C;
}					t_map;

#endif