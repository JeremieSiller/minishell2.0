CC = gcc

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include

INC			= -I./Libft -I./includes

CFLAGS =  $(LDFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra 

LFLAGS = -ltermcap -L libft/ -lft -lreadline

NAME		= minishell
LIB_PATH	= ./Libft
LIBFT_NAME	= ./Libft/libft.a

SOURCES =	sources/main.c																\
			sources/parser/parser.c														\
			sources/parser/parse_redirections.c											\
			sources/parser/parse_redirections_2.c										\
			sources/parser/parse_endstring.c											\
			sources/parser/parse_endcommand.c											\
			sources/parser/parse_asterix.c												\
			sources/parser/check_input.c												\
			sources/utilities/utilities_list.c											\
			sources/utilities/utilities_list_2.c										\
			sources/utilities/utilities_string.c										\
			sources/execute/execute.c													\
			sources/utilities/utils.c													\
			sources/execute/cmd_find.c													\
			sources/signals/signals.c													\
			sources/builtins/echo.c														\
			sources/builtins/cd.c														\
			sources/builtins/env.c														\
			sources/builtins/exit.c														\
			sources/builtins/export.c													\
			sources/builtins/unset.c													\
			sources/builtins/pwd.c														\
			sources/builtins/false.c													\
			sources/builtins/true.c														\
			sources/execute/execute_utils.c												\
			sources/execute/execute_utils_2.c											\
			sources/env/env_utils.c														\
			sources/execute/redirect.c													\
			sources/execute/manage_main.c
#COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
BLACK = "\033[38;2;52;52;52m"
UP = "\033[A"
CUT = "\033[K"

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c
	@$(CC) -Wall -Wextra -Werror $(CPPFLAGS) $(INC) -o $@ -c $<


all: $(NAME)
	@echo $(R)
	@echo " ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    " | fmt -c $$(tput cols)
	@echo "▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    " | fmt -c $$(tput cols)
	@echo "▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    " | fmt -c $$(tput cols)
	@echo "▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    " | fmt -c $$(tput cols)
	@echo "▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒" | fmt -c $$(tput cols)
	@echo "░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░" | fmt -c $$(tput cols)
	@echo "░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░" | fmt -c $$(tput cols)
	@echo "░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   " | fmt -c $$(tput cols)
	@echo "       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░" | fmt -c $$(tput cols)
	@echo $(BLACK)
	@echo "                                               by @nschumac & @jsiller" | fmt -c $$(tput cols)
	@echo $(X);

$(NAME): $(LIBFT_NAME) $(OBJECTS)
	@$(CC) $(OBJECTS) $(CFLAGS) $(LFLAGS) -o $@

$(LIBFT_NAME):
	@echo $(Y)
	@echo Compiling libft ... | fmt -c $$(tput cols)
	@echo $(G)
	@make -C $(LIB_PATH) | fmt -c $$(tput cols)

clean:
	@echo $(Y)
	@echo cleaning object-files | fmt -c $$(tput cols)
	@rm -f $(OBJECTS)
	@sleep 0.2
	@make fclean -C $(LIB_PATH)
	@echo $(G)
	@echo done removing object-files | fmt -c $$(tput cols)

fclean:
	@echo $(Y)
	@echo cleaning all binary files | fmt -c $$(tput cols)
	@make clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_PATH)
	@sleep 0.2
	@echo $(G)
	@echo fclean done | fmt -c $$(tput cols)
	@bash -c "echo -n"


re: fclean all

val:
	docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -ti -v $(PWD):/test memory-test:0.1 bash && cd test
