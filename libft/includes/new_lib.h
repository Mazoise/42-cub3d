/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:01:41 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/18 13:15:53 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_LIB_H
# define NEW_LIB_H

# include <string.h>

char			*ft_strdup_no_sp(char *src);
char			**ft_strs_plus_one(char **strs, char *add);
void			ft_free_strs(char **grid);

#endif