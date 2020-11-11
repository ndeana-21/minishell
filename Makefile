# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/01 16:51:38 by ndeana            #+#    #+#              #
#    Updated: 2020/11/10 21:07:48 by ndeana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
DIR			=	./srcs
LFT_DIR		=	./libft
HEAD_DIR	=	./includes

FILES		=	ms_cd.c			ms_exit.c		ms_pwd.c		ms_unset.c		\
				ms_env.c		ms_export.c		parser.c		minishell.c		\
				utils.c			

HEAD_FILE	=	minishell.h		error.h			struct.h			

LFT			=	-L$(LFT_DIR) -lft
SRCS		=	$(addprefix $(DIR)/, $(FILES))
HEAD		=	$(addprefix $(HEAD_DIR)/, $(HEAD_FILE))
INCLUDES	=	-I$(HEAD_DIR) -I$(LFT_DIR)
OBJS		=	$(SRCS:.c=.o)

M_FLAGS		=	--no-print-directory
CC			=	gcc
CFLAGS		=	-Wall -Wextra -g -O0 $(INCLUDES) 
LIBS		=	-lm $(LFT)

all: $(NAME)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< $(LIBS) -o $@
	@$(PRINT) "\r$(FGREEN)COMPILE: $<            $(PNULL)"

lib:
	@make $(M_FLAGS) -C $(LFT_DIR)

$(NAME): lib $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@$(PRINT) "\r$(FGREEN)MAKE: ${NAME}      $(PNULL)\n"

clean:
	@$(PRINT) "$(addprefix \n$(FRED)REMOVE: $(FYELLOW), $(FILES:.c=.o))$(PNULL)"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@$(PRINT) "\n$(FRED)REMOVE: $(FYELLOW)$(NAME)$(PNULL)"
	@make fclean $(M_FLAGS) -C $(LFT_DIR)

re:	fclean lib all

norme:
	@make norme $(M_FLAGS) -C $(LIBFT_PATH) $(LFT_DIR)
	@norminette $(SRCS) $(HEADERS) | awk '{sub(/Norme/,"$(FGREEN)Norme$(PNULL)")}1' | awk '{sub(/Error/,"$(FRED)Error$(PNULL)")}1'

run: all
	@./$(NAME)

.PHONY: all clean fclean re norme run lib

# **************************************************************************** #
#								Utilits										   #
# **************************************************************************** #

# Цвета шрифта
FBLACK		= \033[30m
FRED		= \033[31m
FGREEN		= \033[32m
FYELLOW		= \033[33m
FBLUE		= \033[34m
FMAGENTA	= \033[35m
FCYAN		= \033[36m
FGREY		= \033[37m

# Цвета фона
BGBLACK		= \033[40m
BGRED		= \033[41m
BGGREEN		= \033[42m
BGYELLOW	= \033[43m
BGBLUE		= \033[44m
BGMAGENTA	= \033[45m
BGCYAN		= \033[46m
BGGREY		= \033[47m

# Свойства текста
PBOLD		= \033[1m#	жирный шрифт
PDBOLD		= \033[2m#	полу яркий цвет
PNBOLD		= \033[22m#	нормальная интенсивность
PUNDERLINE	= \033[4m#	подчеркивание
PBLINK		= \033[5m#	мигание
PINVERSE	= \033[7m#	инверсия
PNULL		= \033[0m#	отмена

PRINT		= printf
