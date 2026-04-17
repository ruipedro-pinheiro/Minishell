NAME = minishell

SRCDIR = src
OBJDIR = .obj
INCDIR = include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFT_DIR)
SRC = main.c \
      historer.c \
      execution/here_doc.c \
      execution/utils.c \
      execution/multi_pipe.c \
      execution/closer.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

################################################################################
#                                PROGRESS BAR                                  #
################################################################################

CNT = /tmp/.mini_cnt
RESET := $(shell echo 0 > $(CNT))
C = \033[1;36m
Y = \033[1;33m
R = \033[1;31m
B = \033[1m
X = \033[0m

define progress
n=$$(($$(cat $(CNT)) + 1)); echo $$n > $(CNT); \
t=$(1); pct=$$((n * 100 / t)); f=$$((n * 20 / t)); \
bar=""; i=0; \
while [ $$i -lt $$f ]; do bar="$${bar}█"; i=$$((i+1)); done; \
while [ $$i -lt 20 ]; do bar="$${bar}░"; i=$$((i+1)); done; \
printf "\r\033[K $(C)🔧 [$(NAME)] $(Y)$$bar $(B)$$pct%%$(X)"
endef

################################################################################
#                                   RULES                                      #
################################################################################

all: $(NAME) libft/
	@if [ $$(cat $(CNT)) -gt 0 ]; then printf "\n"; fi
	@printf " $(C)✅ [$(NAME)] $(B)Build complete$(X)\n"
	@$(MAKE) --silent -C libft/ all

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -L$(LIBFT_DIR) $(OBJ) $(LIBFT) -lreadline -lncurses -o $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)/execution $(OBJDIR)/parsing $(OBJDIR)/builtins

$(LIBFT):
	@$(MAKE) --silent -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call progress,$(words $(SRC)))

clean:
	@printf "$(R)🗑️  [$(NAME)] Cleaned$(X)\n"
	@rm -rf $(OBJDIR)
	@$(MAKE) --silent -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re