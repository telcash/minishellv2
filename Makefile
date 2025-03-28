NAME = minishell

GREEN			= \033[0;32m
RED				= \033[0;31m
RESET			= \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(LIBFT_DIR) -fsanitize=address
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_DIR = /opt/homebrew/opt/readline
CFLAGS += -I$(READLINE_DIR)/include
LDFLAGS = -L$(READLINE_DIR)/lib -lreadline -lcurses

SRCS = $(SRC_DIR)/main.c \
	   $(addprefix $(SRC_DIR)/init/, init.c) \
	   $(addprefix $(SRC_DIR)/error/, error.c) \
	   $(addprefix $(SRC_DIR)/free/, free.c) \
	   $(addprefix $(SRC_DIR)/parse/, token.c utils.c) \
	   $(addprefix $(SRC_DIR)/pipeline/, pipeline.c process_command.c fds.c) \
	   $(addprefix $(SRC_DIR)/builtins/, exec.c exit.c pwd.c) \
	   $(addprefix $(SRC_DIR)/bins/, exec.c) \
	   $(addprefix $(SRC_DIR)/redirections/, process.c out.c append.c in.c) \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)
			@echo "$(NAME): $(GREEN)$(NAME) was compiled.$(RESET)"

$(LIBFT):
			@echo
			@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		@echo
		@rm -rf $(OBJ_DIR)
		@make -C $(LIBFT_DIR) clean
		@echo

fclean: clean
		@echo
		@rm -f $(NAME)
		@make -C $(LIBFT_DIR) fclean
		@echo "$(NAME): $(GREEN)$(NAME) is clean.$(RESET)"

re:		fclean all
		@echo

.PHONY: all clean fclean re