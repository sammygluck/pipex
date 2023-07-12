# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRCDIR = src
OBJDIR = obj
BINDIR = bin
NAME = pipex
LIBFT_DIR = libft

# Source Files
SRC = $(wildcard $(SRCDIR)/*.c)
HDRS = $(NAME).h
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Targets
all: $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean: libft_clean
	rm -f $(OBJ)

libft_clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean libft_fclean
	rm -f $(BINDIR)/$(NAME)
	-rmdir $(OBJDIR) $(BINDIR)

libft_fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean re fclean libft_clean libft_fclean
