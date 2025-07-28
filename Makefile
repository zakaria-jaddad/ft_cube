CC = cc

FLAGS =# -Wall -Wextra -Werror

NAME = cub

HF = cub.h

FRM = rm -f

SRC = cub.c parsing/main_parse.c  GNL/get_next_line_utils.c GNL/get_next_line.c parsing/free.c parsing/ft_split.c parsing/ft_strdup.c parsing/parse_helper.c

SRCB = 
  
OBJF = $(SRC:.c=.o)

BOBJF = $(SRCB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJF)

bonus: $(BOBJF)

%.o : %.c $(HF)
	$(CC) $(FLAGS) -c $< -o $@

clean : 
	$(FRM) $(OBJF) $(BOBJF)

fclean : clean
	$(FRM) $(NAME)

re : fclean all