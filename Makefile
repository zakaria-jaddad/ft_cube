CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = cub

HF = cub.h

FRM = rm -f

SRC = cub.c parsing/main_parse.c ft_utils/

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