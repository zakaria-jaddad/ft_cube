CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

NAME = cub3D

NAME_B = cub3D_bonus

LIBFT = ./lib/libft/ft_isalpha.c	\
				./lib/libft/ft_isdigit.c	\
				./lib/libft/ft_isalnum.c	\
				./lib/libft/ft_isascii.c	\
				./lib/libft/ft_isprint.c	\
				./lib/libft/ft_strlen.c	\
				./lib/libft/ft_memset.c	\
				./lib/libft/ft_bzero.c	\
				./lib/libft/ft_memcpy.c	\
				./lib/libft/ft_memmove.c	\
				./lib/libft/ft_strlcpy.c 	\
				./lib/libft/ft_strlcat.c 	\
				./lib/libft/ft_toupper.c 	\
				./lib/libft/ft_tolower.c 	\
				./lib/libft/ft_strchr.c 	\
				./lib/libft/ft_strrchr.c 	\
				./lib/libft/ft_strncmp.c 	\
				./lib/libft/ft_strcmp.c 	\
				./lib/libft/ft_memchr.c 	\
				./lib/libft/ft_memcmp.c 	\
				./lib/libft/ft_strnstr.c 	\
				./lib/libft/ft_atoi.c 	\
				./lib/libft/ft_calloc.c 	\
				./lib/libft/ft_strdup.c 	\
				./lib/libft/ft_substr.c 	\
				./lib/libft/ft_strjoin.c 	\
				./lib/libft/ft_strtrim.c	\
				./lib/libft/ft_split.c	\
				./lib/libft/ft_split_pro.c	\
				./lib/libft/ft_split_pro_max.c\
				./lib/libft/ft_itoa.c		\
				./lib/libft/ft_strmapi.c	\
				./lib/libft/ft_striteri.c	\
				./lib/libft/ft_putchar_fd.c	\
				./lib/libft/ft_putstr_fd.c	\
				./lib/libft/ft_putendl_fd.c	\
				./lib/libft/ft_putnbr_fd.c	\
				./lib/libft/ft_lstnew_bonus.c	\
				./lib/libft/ft_lstadd_front_bonus.c	\
				./lib/libft/ft_lstsize_bonus.c	\
				./lib/libft/ft_lstlast_bonus.c	\
				./lib/libft/ft_lstfirst_bonus.c	\
				./lib/libft/ft_lstadd_back_bonus.c	\
				./lib/libft/ft_lstdelone_bonus.c	\
				./lib/libft/ft_lstclear_bonus.c	\
				./lib/libft/ft_lst_rm_one.c	\
				./lib/libft/ft_add_node.c	\
				./lib/libft/ft_fprintf/ft_fprintf.c \
				./lib/libft/ft_fprintf/ft_fprintf_put_unsigned_nbr_fd.c \
				./lib/libft/ft_fprintf/ft_fprintf_putaddress_fd.c \
				./lib/libft/ft_fprintf/ft_fprintf_putchar_fd.c \
				./lib/libft/ft_fprintf/ft_fprintf_puthex_fd.c \
				./lib/libft/ft_fprintf/ft_fprintf_putnbr_fd.c \
				./lib/libft/ft_fprintf/ft_fprintf_putstr_fd.c \
				./lib/libft/ft_fprintf/ft_fprintf_strlen.c \
				./lib/libft/ft_gnl/ft_gnl.c \
				./lib/libft/ft_strpbrk.c \

# -- START MANDATORY PART
PARSING_M = ./mandatory/parsing/main_parse.c \
						./mandatory/parsing/parse_helper_0.c \
						./mandatory/parsing/free.c \
						./mandatory/parsing/parse_helper_1.c \
						./mandatory/parsing/map_parsing.c \
						./mandatory/parsing/map_parsing_v2.c \
						./mandatory/parsing/map_parsing_v3.c \
						./mandatory/parsing/textures.c \
						./mandatory/parsing/padding.c \
						./mandatory/parsing/parsing_utils.c \
						./mandatory/parsing/parsing_color_utils.c

EXECUTION_HH_M = ./mandatory/raycast/actions.c \
								 ./mandatory/raycast/direction.c \
								 ./mandatory/raycast/ft_cube.c \
								 ./mandatory/raycast/hooks.c \
								 ./mandatory/raycast/mlx.c \
								 ./mandatory/raycast/player.c \
								 ./mandatory/raycast/raycast.c \
								 ./mandatory/raycast/vector.c  \
								 ./mandatory/raycast/ft_cube_utils_1.c \

MAIN_M = ./mandatory/cub.c
# -- END MANDATORY PART

# -- START BONUS PART
PARSING_B = ./bonus/parsing/main_parse_bonus.c \
						./bonus/parsing/parse_helper_0_bonus.c \
						./bonus/parsing/free_bonus.c \
						./bonus/parsing/parse_helper_1_bonus.c \
						./bonus/parsing/map_parsing_bonus.c \
						./bonus/parsing/map_parsing_v2_bonus.c \
						./bonus/parsing/map_parsing_v3_bonus.c \
						./bonus/parsing/textures_bonus.c \
						./bonus/parsing/padding_bonus.c \
						./bonus/parsing/doors_bonus.c \
						./bonus/parsing/parsing_utils_bonus.c \
						./bonus/parsing/parsing_utils_2_bonus.c \
						./bonus/parsing/parsing_utils_3_bonus.c \
						./bonus/parsing/padding_utils_bonus.c

EXECUTION_HH_B = ./bonus/raycast/actions_bonus.c \
								 ./bonus/raycast/direction_bonus.c \
								 ./bonus/raycast/ft_cube_bonus.c \
								 ./bonus/raycast/hooks_bonus.c \
								 ./bonus/raycast/mini_map_shit_bonus.c \
								 ./bonus/raycast/mlx_bonus.c \
								 ./bonus/raycast/player_bonus.c \
								 ./bonus/raycast/raycast_bonus.c \
								 ./bonus/raycast/vector_bonus.c  \
								 ./bonus/raycast/ft_cube_utils_1_bonus.c \

MAIN_B = ./bonus/cub_bonus.c
# -- END BONUS PART

SRC_M = $(LIBFT) $(MAIN_M) $(PARSING_M) $(EXECUTION_HH_M)

SRC_B = $(LIBFT) $(MAIN_B) $(PARSING_B) $(EXECUTION_HH_B)
  
OBG_M = $(SRC_M:.c=.o)

OBG_B = $(SRC_B:.c=.o)

all : $(NAME)

$(NAME) : $(OBG_M)
	$(CC) $(CFLAGS) $(OBG_M) -lm -lmlx42 -L./lib/MLX42/build -lglfw -o $(NAME)

bonus: $(OBG_B)
	$(CC) $(CFLAGS) $(OBG_B) -lm -lmlx42 -L./lib/MLX42/build -lglfw -o $(NAME_B)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

clean : 
	rm -rf $(OBG_M) $(OBG_B) $(OBG_M:.o=.d) $(OBG_B:.o=.d)

fclean : clean
	rm -rf $(NAME) $(NAME_B)

re : fclean all

-include $(OBG_M:.o=.d)
-include $(OBG_B:.o=.d)
