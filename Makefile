# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jzoltan <jzoltan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 04:30:43 by jzoltan           #+#    #+#              #
#    Updated: 2023/02/13 18:12:42 by jzoltan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#*
all: compile
MAKEFLAGS+=r
MAKEFLAGS+=s
.SUFFIXES:
#*
#* ************************************************************************** *#
#*                              Project Type                                  *#
#* ************************************************************************** *#
#*
LIBRARY     =
HAS_BONUS	=
#*
#* ************************************************************************** *#
#*                             Executable name                                *#
#* ************************************************************************** *#
#*
NAME            =ft_irc
DEBUG_NAME      =deb_ft_irc
BONUS_NAME      =
#*
#* ************************************************************************** *#
#*                               Run Arguments                                *#
#* ************************************************************************** *#
#*
RUN                     =
#*
#* ************************************************************************** *#
#*                          Compilation variables                             *#
#* ************************************************************************** *#
#*
DEBUG_PROGRAM           =gdb -tui -arg
SRCS_EXT                =.cpp
OBJS_EXT                =.cpp.o
HEADER_EXT              =.hpp
DFILES_EXT              =.cpp.d
CC                      =c++
ARCHIVE                 =ar rc
CFLAG                   =-Wextra -Wall -Werror -pedantic -Ofast -std=c++98# -fsanitize=address
DEBUG_FLAG              =-g3 -Wextra -Wall -Werror# -fsanitize=address
DFLAG                   =-MT $@ -MD -MP -MF $(DFILES_DIR)/$*$(DFILES_EXT)
CLINK                   =
DEPENDENCIES_PATHS      =
#*
#* ************************************************************************** *#
#*                               Directories                                  *#
#* ************************************************************************** *#
#*
SRCS_DIR        =src
INCLUDES_DIR    =include
OBJS_DIR        =Objects
DFILES_DIR      =HeaderDependencies
DEPENDENCIES    =Dependencies
#*
#* ************************************************************************** *#
#*                                  Files                                     *#
#* ************************************************************************** *#
#*

SOURCES         = \
	main.cpp server.cpp console.cpp irc_server.cpp irc_user.cpp channel.cpp

BONUS_SOURCES   =

MAIN_NAME       = \
	main.cpp

BONUS_MAIN_NAME =
#*
#* ************************************************************************** *#
#*                               Conversions                                  *#
#* ************************************************************************** *#
#*
SRCS_DIR               := $(addsuffix /, $(SRCS_DIR))
OBJS_DIR               := $(addsuffix /, $(OBJS_DIR))
DIRECTORIES             = $(SRCS_DIR) $(OBJS_DIR) $(DEPENDENCIES) $(DFILES_DIR) $(SOURCES)
DEPS                    =$(addprefix $(DEPENDENCIES)/, $(DEPENDENCIES_PATHS))

SRCS                    =$(addprefix $(SRCS_DIR),$(SOURCES))

OBJS                    =$(patsubst %$(SRCS_EXT),$(OBJS_DIR)%$(OBJS_EXT), $(SOURCES))

BOBJS                   =$(patsubst %$(SRCS_EXT),$(OBJS_DIR)%$(OBJS_EXT), $(SOURCES))

ifeq ($(DFILES_DIR),)
DFS                     =$(patsubst %$(SRCS_EXT),%$(DFILES_EXT), $(SOURCES) $(BONUS_SOURCES))
else
DFS                     =$(patsubst %$(SRCS_EXT),$(DFILES_DIR)/%$(DFILES_EXT), $(SOURCES) $(BONUS_SOURCES))
endif

CADDLINK                =$(addprefix -L, $(dir $(DEPS)))

INCS                    =$(addprefix -I, $(INCLUDES_DIR))

uniq = $(if $1,$(call uniq,$(filter-out $(lastword $1),$1)) $(lastword $1))

parent_dirs = $(if $(patsubst ./%,%,$(dir $(1))),$(dir $(1)) $(call parent_dirs,$(strip $(patsubst %/,%,$(dir $(1))))))

INTERMEDIATE_DIRECTORIES=$(call uniq, $(foreach path, $(sort $(foreach obj, $(OBJS) $(BOBJS) $(DFS), $(dir $(obj)))),$(call parent_dirs, $(path))))

.PRECIOUS:$(INTERMEDIATE_DIRECTORIES)
#*
#* ************************************************************************** *#
#*                              Directories Rule                              *#
#* ************************************************************************** *#
#*
$(INTERMEDIATE_DIRECTORIES):
	mkdir -p $@
#*
#* ************************************************************************** *#
#*                                Bonus Rule                                  *#
#* ************************************************************************** *#
#*
ifneq ($(HAS_BONUS),)
ifeq ($(BONUS_NAME),$(NAME))
bonus:
	@$(MAKE) SOURCES="$(BONUS_SOURCES_NAME)" \
		MAIN="$(BONUS_MAIN_NAME)" \
		BONUS_MAIN="$(MAIN_NAME)" all
else
$(BONUS_NAME): $(BOBJS) $(DEPS)
	rm -f $(BONUS_MAIN)
	$(CC) $(CFLAG) -o $(NAME) $(OBJS) $(CADDLINK) $(CLINK)
bonus:
	@$(MAKE) SOURCES="$(BONUS_SOURCES_NAME)" \
		MAIN="$(BONUS_MAIN_NAME)" \
		BONUS_MAIN="$(MAIN_NAME)" all
.PHONY:bonus
endif
endif
#*
#* ************************************************************************** *#
#*                            Dependencies rules                              *#
#* ************************************************************************** *#
#*
%.a:
	(cd $(dir $@) && $(MAKE))
#*
#* ************************************************************************** *#
#*                             Compilation Rule                               *#
#* ************************************************************************** *#
ifneq ($(LIBRARY),)
$(NAME): $(OBJS)
	rm -f $(BONUS_MAIN)
	$(ARCHIVE) $(NAME) $(OBJS)
else
$(NAME): $(OBJS)
	rm -f $(BONUS_MAIN)
	$(CC) $(CFLAG) -o $(NAME) $(OBJS) $(CADDLINK) $(CLINK)
endif
compile: $(NAME)
.PHONY: compile all
#*
#* ************************************************************************** *#
#*                                     Run                                    *#
#* ************************************************************************** *#
#*
ifeq ($(LIBRARY),)
run: $(NAME)
	./$(NAME) $(ARG)
debug_run: $(DEBUG_NAME)
	$(DEBUG_PROGRAM) $(DEBUG_NAME) $(ARG)
drun: debug_run

r: run

dr: drun
.PHONY: run debug_run drun r dr
endif
#*
#* ************************************************************************** *#
#*                                    Debug                                   *#
#* ************************************************************************** *#
#*
ifeq ($(LIBRARY),)
$(DEBUG_NAME): $(SRCS)
	rm -f $(BONUS_MAIN)
	$(CC) $(DEBUG_FLAG) $(INCS) -o $(DEBUG_NAME) $(SRCS) $(CADDLINK) $(CLINK)
debug: $(DEBUG_NAME)

de: debug

db: debug

.PHONY:de debug db
endif
#*
#* ************************************************************************** *#
#*                                    Cleanup                                 *#
#* ************************************************************************** *#
#*
CLEAN_FILES= $(wildcard $(sort $(OBJS) $(BOBJS) $(DFS)))
FCLEAN_FILES= $(wildcard $(NAME) $(DEBUG_NAME))
CLEAN_DIRS= $(wildcard $(INTERMEDIATE_DIRECTORIES))

clean:
ifneq ($(CLEAN_FILES),)
	rm -f $(CLEAN_FILES)
endif
ifneq ($(CLEAN_DIRS),)
	rm -d $(CLEAN_DIRS)
endif

fclean: clean
ifneq ($(FCLEAN_FILES),)
	rm -f $(FCLEAN_FILES)
endif

re: fclean all

remake: re

test:
	@echo "$(SRCS)"
	@echo "$(OBJS)"
	@echo '$(SUBDIRECTORIES)'
	@echo "$(INTERMEDIATE_DIRECTORIES)"

.PHONY: clean fclean re remake
#*
#* ************************************************************************** *#
#*                               Objects Rule                                 *#
#* ************************************************************************** *#
#*
.SECONDEXPANSION:
$(OBJS_DIR)%$(OBJS_EXT): $(SRCS_DIR)%$(SRCS_EXT) | \
		$$(dir $$@) \
		$$(dir $$(DFILES_DIR)/$$*$$(DFILES_EXT))
	$(CC) $(CFLAG) $(INCS) -c $< -o $@ $(DFLAG)

include $(wildcard $(DFS))
#*
#* ************************************************************************** *#
#*                                   Appendix                                 *#
#* ************************************************************************** *#
#*
