NAME = magic_bar
CC = clang
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk4)
LIBS = $(shell $(PKGCONFIG) --libs gtk4)
RM	:= rm -rf

SRC =	magic_bar.c \
		config.c	\
		parser.c	\
		ui.c

OBJS = $(SRC:.c=.o)

all: $(NAME)
	$(RM) $(OBJS)

$(NAME): $(OBJS)
	$(CC) -o $(@F) $(LIBS) $(OBJS)

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

clean:
	$(RM) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:	clean all

.PHONY: all re clean fclean