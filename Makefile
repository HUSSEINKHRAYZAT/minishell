# Variables
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR)/includes -I$(PRINTF_DIR)/includes -I$(GNL_DIR)
LDFLAGS = -lreadline
LIBS = $(LIBFT_DIR)/libft.a $(PRINTF_DIR)/ft_printf.a $(GNL_DIR)/get_next_line.a

# Directories
LIBFT_DIR = mylib/libft
PRINTF_DIR = mylib/ft_printf
GNL_DIR = mylib/get_next_line

# Color and attribute codes
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
BOLD = \033[1m
ITALIC = \033[3m
RESET = \033[0m

# Source files
SRCS = srcs/Minishell.c srcs/Boolean.c srcs/Builtin.c srcs/redirections.c srcs/PrintingFunctions.c  \
srcs/MainFunctions.c srcs/LexerFunctions.c srcs/herdocs.c srcs/Handling.c srcs/GettingFunctions.c \
srcs/ExecutionFunctions.c srcs/EnvFunctions.c srcs/Piping.c srcs/Cleaningfunctions.c srcs/Changedirectory.c  \
srcs/signal.c srcs/Parser.c srcs/Getting2.c srcs/Handling2.c srcs/Env2.c srcs/Env3.c srcs/Cleaning2.c \
srcs/Utilities.c srcs/Utilities2.c srcs/Execution2.c srcs/Handling3.c srcs/Handling4.c srcs/Handling5.c \
srcs/Parser2.c srcs/Piping2.c srcs/redirection2.c srcs/signalheredoc.c
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	@echo "$(BLUE)$(BOLD)$(ITALIC)	Compiling...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LDFLAGS) -g
	@echo "$(GREEN)$(BOLD)$(ITALIC)	MINISHELL Creation Completed$(RESET)"
	@echo "$(RED)$(BOLD)$(ITALIC)	THIS MINISHELL DONE BY HUSSEIN KHRAYZAT AND KAMEL ABBASS ...$(RESET)"

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR) --silent

$(PRINTF_DIR)/ft_printf.a:
	@$(MAKE) -C $(PRINTF_DIR) --silent

$(GNL_DIR)/get_next_line.a:
	@$(MAKE) -C $(GNL_DIR) --silent

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@$(MAKE) -C $(PRINTF_DIR) clean --silent
	@$(MAKE) -C $(GNL_DIR) clean --silent

fclean: clean
	@if [ -f $(NAME) ]; then \
		rm -f $(NAME); \
		echo "$(RED)$(BOLD)	Cleaning and Deleting Objects...$(RESET)"; \
		$(MAKE) -C $(LIBFT_DIR) fclean --silent; \
		$(MAKE) -C $(PRINTF_DIR) fclean --silent; \
		$(MAKE) -C $(GNL_DIR) fclean --silent; \
		echo "$(GREEN)$(BOLD)	Full Clean Complete.$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re 
