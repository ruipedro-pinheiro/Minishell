NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fPIC

SRC = ft_atoll.c \
      ft_bzero.c \
      ft_calloc.c \
      ft_displayptr.c \
      ft_isalnum.c \
      ft_isalpha.c \
      ft_isascii.c \
      ft_isdigit.c \
      ft_isprint.c \
      ft_itoa.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_memset.c \
      ft_printf.c \
      ft_putchar.c \
      ft_putchar_fd.c \
      ft_putendl_fd.c \
      ft_putnbr.c \
      ft_putnbr_fd.c \
      ft_putnbr_hex_lowercase.c \
      ft_putnbr_hex_uppercase.c \
      ft_putnbr_unsigned.c \
      ft_putstr.c \
      ft_putstr_fd.c \
      ft_split.c \
      ft_strchr.c \
      ft_strdup.c \
      ft_strfree.c \
      ft_striteri.c \
      ft_strjoin.c \
      ft_strjoin_char.c \
      ft_strlcat.c \
      ft_strlcpy.c \
      ft_strlen.c \
      ft_strmapi.c \
      ft_strncmp.c \
      ft_strnstr.c \
      ft_strrchr.c \
      ft_strtrim.c \
      ft_substr.c \
      ft_tolower.c \
      ft_toupper.c \
      get_next_line.c \
      get_next_line_utils.c \
	  ft_strapnd.c 

OBJ = $(SRC:.c=.o)

################################################################################
#                                PROGRESS BAR                                  #
################################################################################

CNT = ~/.tmp/.libft_cnt
RESET := $(shell echo 0 > $(CNT))
C = \033[1;35m
Y = \033[1;33m
B = \033[1m
X = \033[0m

define progress
n=$$(($$(cat $(CNT)) + 1)); echo $$n > $(CNT); \
t=$(words $(SRC)); pct=$$((n * 100 / t)); f=$$((n * 20 / t)); \
bar=""; i=0; \
while [ $$i -lt $$f ]; do bar="$${bar}█"; i=$$((i+1)); done; \
while [ $$i -lt 20 ]; do bar="$${bar}░"; i=$$((i+1)); done; \
printf "\r\033[K $(C)📚 [libft] $(Y)$$bar $(B)$$pct%%$(X)"
endef

################################################################################
#                                   RULES                                      #
################################################################################

all: $(NAME)
	@if [ $$(cat $(CNT)) -gt 0 ]; then printf "\n"; fi

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(call progress)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
