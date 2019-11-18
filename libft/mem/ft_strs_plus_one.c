/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_plus_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:46:41 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/18 13:17:07 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		**ft_strs_plus_one(char **strs, char *add)
{
	int			size;
	char		**temp_grid;

	size = 0;
	temp_grid = strs;
	while (strs[size])
		size++;
	if (!(strs = malloc(sizeof(char*) * (size + 1))))
	{
		ft_free_strs(temp_grid);
		return (0);
	}
	strs[size--] = 0;
	strs[size--] = add;
	while (size >= 0)
	{
		strs[size] = temp_grid[size];
		size--;
	}
	free(temp_grid);
	return (strs);
}
