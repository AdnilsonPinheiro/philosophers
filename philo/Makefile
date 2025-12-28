#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpinhei <adpinhei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/26 15:24:18 by adpinhei          #+#    #+#              #
#    Updated: 2025/12/28 17:05:08 by adpinhei         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

###############################################################################
#                            Target and Compiler                              #
###############################################################################
NAME := philo

CC := cc

###############################################################################
#                                    Flags                                    #
###############################################################################
FLAGS = -Wall -Wextra -Werror -pthread

###############################################################################
#                                    vpath                                    #
###############################################################################
vpath %.h includes
vpath %.c src error

###############################################################################
#                              Builds' Directory                              #
###############################################################################
BUILD_DIR := build

###############################################################################
#                               Source Files                                  #
###############################################################################

SRC_FILES := main.c philo_utils.c clean.c routine.c time.c\
			monitor_routine.c

###############################################################################
#                               Object Files                                  #
###############################################################################
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

###############################################################################
#                                 Includes                                    #
###############################################################################
INCLUDES := philo.h

###############################################################################
#                                Debug Flags                                  #
###############################################################################
gdb: FLAGS += -g
leak: FLAGS += -fsanitize=address,undefined -g
thr: FLAGS += -fsanitize=thread,undefined -g

###############################################################################
#                                Basic Rules                                  #
###############################################################################
.PHONY: all clean fclean re valgrind norm gdb leak thread

all: $(BUILD_DIR) $(NAME)

###############################################################################
#                               Create ./build                                #
###############################################################################
$(BUILD_DIR):
	@mkdir -p $@
	@echo "$(GREEN)Creating$(RESET) $(BUILD_DIR)"
	@echo "$(GREEN)Compiled objects$(RESET)"

###############################################################################
#                        Compile objects into /build                          #
###############################################################################
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

###############################################################################
#                               Build executable                              #
###############################################################################
$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJ_FILES) $(LIBFT) $(LDFLAGS) -o $@
	@echo "$(YELLOW)Compiled$(RESET) $(NAME)"

###############################################################################
#                                Debug Rules                                  #
###############################################################################
norm:
	@norminette -R CheckForbiddenSourceHeader

valgrind: $(NAME)
	@echo "$(YELLOW)Valgrind Report$(RESET)"
	@valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--trace-children=yes \
	--track-fds=yes \
	./$(NAME) 5 8000 800 800

gdb: $(NAME)
	@gdb --tui ./$(NAME) 2 2 8 2

leak: $(NAME)
	@echo "$(YELLOW)Running with sanitizers (adress, leak, undefined)$(RESET)"
	@./$(NAME) 5 8000 800 800 5

thr: $(NAME)
	@echo "$(YELLOW)Running with sanitizers (threads, undefined)$(RESET)"
	@./$(NAME) 5 8000 800 800 5

###############################################################################
#                                  Clean up                                   #
###############################################################################
clean:
	@rm -rf $(BUILD_DIR)
	@echo "$(BLUE)Cleaned object files$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)Cleaned executables$(RESET) $(NAME)"

re: fclean all

###############################################################################
#                                    Help                                     #
###############################################################################
help:
	@echo "$(YELLOW)Available targets:$(RESET)"
	@echo "  all           - Build the mandatory executable"
	@echo "  clean         - Remove object files"
	@echo "  fclean        - Remove all built files"
	@echo "  re            - Clean and rebuild everything"
	@echo "  norm          - Run norminette checks"
	@echo "  valgrind      - Run valgrind on mandatory"
	@echo "  gdb           - Start gdb on mandatory"
	@echo "  leak          - Start LSan for memory leaks"
	@echo "  thr           - Start LSan for threads"

###############################################################################
#                               Color Codes                                   #
###############################################################################
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

BLUE = \033[1;34m

RESET = \033[0m
