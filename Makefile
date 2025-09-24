# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macoulib <macoulib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/22 18:56:36 by macoulib          #+#    #+#              #
#    Updated: 2025/09/24 20:27:13 by macoulib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          =   cc
CFLAGS      =   -g3 -O0 -Wall -Wextra -Werror
DEBUGFLAGS  =   -g3 -O0 -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fsanitize=leak

LDFLAGS     =   -lreadline -Llibrairie/ft_libft -lft
AR          =   ar rcs
RM          =   rm -f

NAME        =   minishell  # Nom de l'exécutable

SRC_DIR     =   ./src
SRC_MAIN    =   $(SRC_DIR)/minishell.c
SRC_PARSING =   $(wildcard $(SRC_DIR)/parsing/*.c)  # Récupérer tous les fichiers .c dans parsing
SRC         =   $(SRC_MAIN) $(SRC_PARSING)  # Combine tous les fichiers .c sources

LIBFT_DIR   =   ./librairie/ft_libft
LIBFT_SRC   =   $(wildcard $(LIBFT_DIR)/*.c)  # Récupérer tous les fichiers .c dans ft_libft
LIBFT_OBJ   =   $(LIBFT_SRC:.c=.o)  # Objets générés à partir de ces fichiers

INCLUDES    =   ./includes/minishell.h  # Le fichier d'en-tête principal

OBJ_DIR     =   ./obj
OBJ         =   $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o))) $(addprefix $(OBJ_DIR)/, $(notdir $(LIBFT_OBJ)))

# Color codes
GREEN       =   \033[0;32m
YELLOW      =   \033[0;33m
RED         =   \033[0;31m
BLUE        =   \033[0;34m
PURPLE      =   \033[0;35m
CYAN        =   \033[0;36m
NC          =   \033[0m

# Target principal
all: $(NAME)

# Création de l'exécutable
$(NAME): $(LIBFT_OBJ) $(OBJ_DIR) $(OBJ)
	@echo "$(GREEN)Building $(NC)$(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Compilation des fichiers .c de la librairie libft
$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c $(INCLUDES)
	@echo "$(CYAN)Compiling $(NC)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation des fichiers .c dans src/ et src/parsing/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@echo "$(CYAN)Compiling $(NC)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/parsing/%.c $(INCLUDES)
	@echo "$(CYAN)Compiling $(NC)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Règle pour créer le répertoire des objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Suppression des fichiers objets
clean:
	@$(MAKE) -C librairie/ft_libft clean --no-print-directory
	@echo "$(CYAN)Cleaning object files"
	@$(RM) $(OBJ)
	@rmdir $(OBJ_DIR) 2>/dev/null || true

# Suppression des fichiers objets et de l'exécutable
fclean: clean
	@$(MAKE) -C librairie/ft_libft fclean --no-print-directory
	@echo "$(CYAN)Cleaning $(NC)$(NAME)"
	@$(RM) $(NAME)

# Rebuild complet
re: fclean all

# Build en mode debug
debug: $(LIBFT_OBJ) $(OBJ_DIR) $(OBJ)
	@echo "$(YELLOW)Building $(NC)$(NAME) $(YELLOW)with debug flags"
	@$(CC) $(DEBUGFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Lancer Valgrind
valgrind: $(NAME)
	@echo "$(YELLOW)🔍 Launching Valgrind on ./minishell...$(NC)"
	@valgrind -q --suppressions=./ignore --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
		./minishell

.PHONY: all clean fclean re debug valgrind
