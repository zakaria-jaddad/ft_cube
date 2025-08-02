CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
NAME = cub

MAIN = cub.c
LIBFT = ./libft/ft_isalpha.c	\
				./libft/ft_isdigit.c	\
				./libft/ft_isalnum.c	\
				./libft/ft_isascii.c	\
				./libft/ft_isprint.c	\
				./libft/ft_strlen.c	\
				./libft/ft_memset.c	\
				./libft/ft_bzero.c	\
				./libft/ft_memcpy.c	\
				./libft/ft_memmove.c	\
				./libft/ft_strlcpy.c 	\
				./libft/ft_strlcat.c 	\
				./libft/ft_toupper.c 	\
				./libft/ft_tolower.c 	\
				./libft/ft_strchr.c 	\
				./libft/ft_strrchr.c 	\
				./libft/ft_strncmp.c 	\
				./libft/ft_strcmp.c 	\
				./libft/ft_memchr.c 	\
				./libft/ft_memcmp.c 	\
				./libft/ft_strnstr.c 	\
				./libft/ft_atoi.c 	\
				./libft/ft_calloc.c 	\
				./libft/ft_strdup.c 	\
				./libft/ft_substr.c 	\
				./libft/ft_strjoin.c 	\
				./libft/ft_strtrim.c	\
				./libft/ft_split.c	\
				./libft/ft_split_pro.c	\
				./libft/ft_split_pro_max.c\
				./libft/ft_itoa.c		\
				./libft/ft_strmapi.c	\
				./libft/ft_striteri.c	\
				./libft/ft_putchar_fd.c	\
				./libft/ft_putstr_fd.c	\
				./libft/ft_putendl_fd.c	\
				./libft/ft_putnbr_fd.c	\
				./libft/ft_lstnew_bonus.c	\
				./libft/ft_lstadd_front_bonus.c	\
				./libft/ft_lstsize_bonus.c	\
				./libft/ft_lstlast_bonus.c	\
				./libft/ft_lstfirst_bonus.c	\
				./libft/ft_lstadd_back_bonus.c	\
				./libft/ft_lstdelone_bonus.c	\
				./libft/ft_lstclear_bonus.c	\
				./libft/ft_lst_rm_one.c	\
				./libft/ft_add_node.c	\
				./libft/ft_fprintf/ft_fprintf.c \
				./libft/ft_fprintf/ft_fprintf_put_unsigned_nbr_fd.c \
				./libft/ft_fprintf/ft_fprintf_putaddress_fd.c \
				./libft/ft_fprintf/ft_fprintf_putchar_fd.c \
				./libft/ft_fprintf/ft_fprintf_puthex_fd.c \
				./libft/ft_fprintf/ft_fprintf_putnbr_fd.c \
				./libft/ft_fprintf/ft_fprintf_putstr_fd.c \
				./libft/ft_fprintf/ft_fprintf_strlen.c \
				./libft/ft_gnl/ft_gnl.c \
				./libft/ft_strpbrk.c \

PARSING = parsing/main_parse.c \
					parsing/parse_helper_0.c \
					parsing/free.c \
					parsing/parse_helper_1.c \
					parsing/map_parsing.c \
					parsing/map_parsing_v2.c \
					parsing/map_parsing_v3.c \

EXECUTION_HH = raycast.c \


SRC = $(LIBFT) $(MAIN) $(PARSING) $(EXECUTION_HH)

SRCB = 
  
OBJF = $(SRC:.c=.o)

BOBJF = $(SRCB:.c=.o)

all : $(NAME) stock

$(NAME) : $(OBJF)
	$(CC) $(CFLAGS) $(OBJF) -lmlx42 -L./MLX42/build -lglfw -o $(NAME)

bonus: $(BOBJF)

%.o : %.c $(HF)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

stock : $(OBJS)
	mv libft/*.o obj && mv libft/*.d obj && mv libft/ft_fprintf/*.o obj && mv libft/ft_fprintf/*.d obj && mv libft/ft_gnl/*.o obj && mv libft/ft_gnl/*.d obj && mv *.o obj && mv *.d obj && mv parsing/*.o obj && mv parsing/*.d obj

clean : 
	rm -rf $(OBJF) $(BOBJF) $(OBJF:.o=.d) obj/*.o obj/*.d

fclean : clean
	rm -rf $(NAME)

re : fclean all

-include $(OBJF:.o=.d)
