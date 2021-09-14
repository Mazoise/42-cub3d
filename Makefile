# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 19:30:25 by mchardin          #+#    #+#              #
#    Updated: 2021/09/14 20:23:13 by mchardin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX_INIT	=	./srcs/init/

PREFIX_SCAN =	./srcs/scan/

PREFIX_B	=	./srcs/bonus/

PREFIX_NO_B	=	./srcs/no_bonus/

PREFIX_MLX	=	./srcs/mlx/

INCLUDES	=	./includes/

INCLUDES_L	=	./libft/includes/

SRCS_INIT	=	$(addprefix $(PREFIX_INIT), read.c readgraph.c readgrid.c initialisation.c init_utils.c initplayer.c init_errors.c)

SRCS_SCAN	=	$(addprefix $(PREFIX_SCAN), scan_utils.c sprite.c draw.c utils.c window.c keys.c screenshot.c scan.c)

SRCS_BONUS	=	$(addprefix $(PREFIX_B), minimap.c bonus.c bonus_draw.c bonus_utils.c)

SRCS_NO_B	=	$(addprefix $(PREFIX_NO_B), cub3d.c init.c no_bonus.c)

NB_SRCS		=	$(SRCS_INIT) $(SRCS_SCAN) $(SRCS_NO_B)

B_SRCS		=	$(SRCS_INIT) $(SRCS_SCAN) $(SRCS_BONUS)

OBJS		=	${NB_SRCS:.c=.o}

OBJS_B		=	${B_SRCS:.c=.o}

CC			=	clang-9

CFLAGS		=	-g -Ofast -Wall -Werror -Wextra -I $(INCLUDES) -I $(INCLUDES_L) -I$(PREFIX_MLX) 

RM 			=	rm -f

MAKE_LIBFT	=	$(MAKE) -C./libft/

MAKE_MLX	=	$(MAKE) -C$(PREFIX_MLX)

MLX_SYS		=	-lmlx -lm -lXext -lX11 -L$(PREFIX_MLX) -L/usr/lib/

LIBFT		=	-L./libft/ -lft

NAME		= 	Cub3D

$(NAME) :		all

makelib :
				$(MAKE_LIBFT)

makemlx :
				$(MAKE_MLX)

bonus :			./includes/cub3d.h $(OBJS_B) makelib makemlx
				$(CC) $(OBJS_B) $(MLX_SYS) $(LIBFT) -lm -o $(NAME)

all :			./includes/cub3d.h $(OBJS) makelib makemlx
				$(CC) $(OBJS) $(MLX_SYS) $(LIBFT) -lm -o $(NAME)

clean :
				$(RM) $(OBJS) $(OBJS_B)
				$(MAKE_LIBFT) clean
				$(MAKE_MLX) clean

fclean :		clean
				$(RM) $(NAME)
				$(MAKE_LIBFT) fclean
				$(MAKE_MLX) clean

re :			fclean all

.PHONY :		makelib all clean fclean re bonus