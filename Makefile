PREFIX_INIT	=	./srcs/init/

PREFIX_SCAN =	./srcs/scan/

INCLUDES	=	./includes/

INCLUDES_L	=	./libft/includes/

VAR_BONUS	= 	./libft/includes/

SRCS_INIT	=	$(addprefix $(PREFIX_INIT), read.c readgraph.c readgrid.c initialisation.c init_utils.c initplayer.c)

SRCS_SCAN	=	$(addprefix $(PREFIX_SCAN), bonus.c scan_utils.c sprite.c cub3d.c quarter_scan.c draw.c utils.c window.c keys.c screenshot.c scan.c)

ALL_SRCS	=	$(SRCS_INIT) $(SRCS_SCAN)

OBJS		=	${ALL_SRCS:.c=.o}

CC			=	gcc

CFLAGS		=	-g -Ofast -Wall -Werror -Wextra -I $(INCLUDES) -I $(INCLUDES_L)

RM 			=	rm -f

MAKE_LIBFT	=	$(MAKE) -C./libft/

MLX_SYS		=	-lmlx -framework OpenGL -framework AppKit

LIBFT		=	-L./libft/ -lft

NAME		= 	cub3d.out

$(NAME) :		./includes/cub3d.h $(OBJS) makelib
				$(CC) $(OBJS) $(MLX_SYS) $(LIBFT) -lm -o $(NAME)
				rm -rf screenshot.bmp && touch screenshot.bmp

makelib :
				$(MAKE_LIBFT)

bonus :			./includes/cub3d.h $(OBJS) makelib
				$(CC) $(OBJS) $(MLX_SYS) $(LIBFT) -lm -o $(NAME)
				rm -rf screenshot.bmp && touch screenshot.bmp

all :
				$(NAME)

clean :
				$(RM) $(OBJS)
				$(MAKE_LIBFT) clean

fclean :		clean
				$(RM) $(NAME)
				$(MAKE_LIBFT) fclean

re :			fclean all

# .PHONY :		makelib makemlx all clean fclean re