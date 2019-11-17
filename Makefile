PREFIX		=	./srcs/

INCLUDES	=	./includes/

INCLUDES_L	=	./libft/includes/

SRCS 		=	$(addprefix $(PREFIX), cub3d.c)

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra -I $(INCLUDES) -I $(INCLUDES_L)

RM 			=	rm -f

MAKE_MLX	=	$(MAKE) -C./minilibx/

MAKE_MLX_B	=	$(MAKE) -C./minilibx_beta/

MAKE_LIBFT	=	$(MAKE) -C./libft/

MLX			=	-L./minilibx/ -lmlx -framework OpenGL -framework AppKit

MLX_B		= 	-L./minilibx_beta/ -lmlx -framework OpenGL -framework AppKit

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