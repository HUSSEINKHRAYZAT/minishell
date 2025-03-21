GNL_DIR = get_next_line
LIBFT_DIR = libft
PRINTF_DIR = ft_printf
LIB_NAME = mylib.a

all: $(LIB_NAME)

$(LIB_NAME): $(GNL_DIR)/$(GNL_DIR).a $(LIBFT_DIR)/$(LIBFT_DIR).a $(PRINTF_DIR)/$(PRINTF_DIR).a
	@ar rcs $(LIB_NAME) $^

$(GNL_DIR)/$(GNL_DIR).a:
	@$(MAKE) -C $(GNL_DIR) --no-print-directory --silent 

$(LIBFT_DIR)/$(LIBFT_DIR).a:
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory --silent

$(PRINTF_DIR)/$(PRINTF_DIR).a:
	@$(MAKE) -C $(PRINTF_DIR) --no-print-directory --silent

clean:
	@$(MAKE) -C $(GNL_DIR) clean --no-print-directory --silent
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory --silent
	@$(MAKE) -C $(PRINTF_DIR) clean --no-print-directory --silent

fclean: clean
	@$(MAKE) -C $(GNL_DIR) fclean --no-print-directory --silent
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory --silent
	@$(MAKE) -C $(PRINTF_DIR) fclean --no-print-directory --silent
	@rm -f $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re
