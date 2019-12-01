PREFIX_INIT	=	./srcs/init/

PREFIX_SCAN =	./srcs/scan/

INCLUDES	=	./includes/

INCLUDES_L	=	./libft/includes/

SRCS_INIT	=	$(addprefix $(PREFIX_INIT), read.c readgraph.c readgrid.c initialisation.c init_utils.c initplayer.c)

SRCS_SCAN	=	$(addprefix $(PREFIX_SCAN), scan_utils.c sprite.c cub3d.c quarter_scan.c draw.c utils.c window.c keys.c screenshot.c scan.c)

ALL_SRCS	=	$(SRCS_INIT) $(SRCS_SCAN)

OBJS		=	${ALL_SRCS:.c=.o}

CC			=	gcc

CFLAGS		=	-g -Ofast -Wall -Werror -Wextra -I $(INCLUDES) -I $(INCLUDES_L)

RM 			=	rm -f

MAKE_MLX	=	$(MAKE) -C./minilibx/

MAKE_MLX_B	=	$(MAKE) -C./minilibx_beta/

MAKE_LIBFT	=	$(MAKE) -C./libft/

MLX			=	-L./minilibx/ -lmlx -framework OpenGL -framework AppKit

MLX_B		= 	-L./minilibx_beta/ -lmlx -framework OpenGL -framework AppKit

MLX_SYS		=	-lmlx -framework OpenGL -framework AppKit

LIBFT		=	-L./libft/ -lft

NAME		= 	cub3d.out

$(NAME) :		$(OBJS) makelib makemlx
				$(CC) $(OBJS) $(MLX) $(LIBFT) -lm -o $(NAME)

makelib :	
				$(MAKE_LIBFT)

makemlx :	
				$(MAKE_MLX)

makemlxb :		
				$(MAKE_MLX_B)

beta :			$(OBJS) makelib makemlxb
				$(CC) $(OBJS) $(MLX_B) $(LIBFT) -lm -o $(NAME)
				export DYLD_LIBRARY_PATH=~/42cursus/Cub3D/minilibx_beta

sys :			$(OBJS) makelib
				$(CC) $(OBJS) $(MLX_SYS) $(LIBFT) -lm -o $(NAME)
				rm -rf screenshot.bmp && touch screenshot.bmp

all :
				$(NAME)

clean :
				$(RM) $(OBJS)
				$(MAKE_LIBFT) clean
				$(MAKE_MLX) clean


fclean :		clean
				$(RM) $(NAME)
				$(MAKE_LIBFT) fclean

re :			fclean all

# .PHONY :		makelib makemlx all clean fclean re