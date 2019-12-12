PREFIX_INIT	=	./srcs/init/

PREFIX_SCAN =	./srcs/scan/

PREFIX_B	=	./srcs/bonus/

PREFIX_NO_B	=	./srcs/no_bonus/

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

CC			=	gcc

CFLAGS		=	-g -Ofast -Wall -Werror -Wextra -I $(INCLUDES) -I $(INCLUDES_L)

RM 			=	rm -f

MAKE_LIBFT	=	$(MAKE) -C./libft/

MLX_SYS		=	-lmlx -framework OpenGL -framework AppKit

LIBFT		=	-L./libft/ -lft

NAME		= 	cub3d.out

$(NAME) :		all

makelib :
				$(MAKE_LIBFT)

bonus :			./includes/cub3d.h $(OBJS_B) makelib
				$(CC) $(OBJS_B) $(MLX_SYS) $(LIBFT) -lm -o $(NAME)

all :			./includes/cub3d.h $(OBJS) makelib
				$(CC) $(OBJS) $(MLX_SYS) $(LIBFT) -lm -o $(NAME)

clean :
				$(RM) $(OBJS) $(OBJS_B)
				$(MAKE_LIBFT) clean

fclean :		clean
				$(RM) $(NAME)
				$(MAKE_LIBFT) fclean

re :			fclean all

.PHONY :		makelib all clean fclean re bonus