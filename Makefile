CC = gcc

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include

INC			= -I./Libft -I./includes

CFLAGS		= -lreadline $(LDFLAGS) $(CPPFLAGS) $(INC) -L Libft/ -lft -Wall -Werror -Wextra


NAME		= minishell
LIB_PATH	= ./Libft
LIBFT_NAME	= ./Libft/libft.a

SOURCES =	sources/main.c																\

#COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	$(CC) -Wall -Werror -Wextra $(INC) -o $@ -c $<

all: $(NAME)
	@printf $(G)"                                               \n";
	@printf $(G)" ,-----.,--. ,--.,-----.  ,----. ,------.      \n";
	@echo $(G)"'  .--./|  | |  ||  |) /_ '.-.  ||  .-.  \     ";
	@echo $(G)"|  |    |  | |  ||  .-.  \  .' < |  |  \  :    ";
	@echo $(G)"'  '--'\'  '-'  '|  '--' //'-'  ||  '--'  /    ";
	@echo $(G)" \`-----' \`-----' \`------' \`----' \`-------'";
	@echo $(B)"                       by @nschumac & @jsiller ";

$(NAME): $(LIBFT_NAME) $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(LIBFT_NAME):
	@echo $(Y)Compiling $(B)libft $(Y)...
	@make -C $(LIB_PATH)
	@echo $(G)libft compiled
	@sleep 0.2

clean:
	@echo $(Y)removing object-files...
	@sleep 0.3
	@rm -f $(OBJECTS)
	@echo $(Y)cleaning libft...
	@make fclean -C $(LIB_PATH)
	@sleep 0.3
	@echo $(G)done removing object-fies

fclean:
	@echo $(Y)cleaning all binary files
	@sleep 0.2
	@make clean
	@sleep 0.2
	@echo $(Y)removing executable
	@rm -f $(NAME)
	@sleep 0.2
	@echo $(G)executable removed
	@echo $(Y)cleaning libft
	@make fclean -C $(LIB_PATH)
	@sleep 0.2
	@echo $(G)libft cleaned
	@sleep 0.2
	@echo $(G)fclean done


re: fclean all

val:
	docker run -ti -v $(PWD):/test memory-test:0.1 bash
