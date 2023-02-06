all: compile
.SUFFIXES:
#*
#* ************************************************************************** *#
#*                              Project Type                                  *#
#* ************************************************************************** *#
#*
LIBRARY         =
#*
#* ************************************************************************** *#
#*                             Executable name                                *#
#* ************************************************************************** *#
#*
NAME            =onto++
DEBUG_NAME      =deb_onto++
#*
#* ************************************************************************** *#
#*                               Run Arguments                                *#
#* ************************************************************************** *#
#*
RUN                     =
DEBUG_RUN               =
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
CC                      =clang++ -std=c++98
ARCHIVE                 =ar rc
CFLAG                   =-Wextra -Wall -Ofast
DEBUG_FLAG              =-g3 -Wextra -Wall
DFLAG                   =-MT $@ -MD -MP -MF $(DFILES_DIR)$*$(DFILES_EXT)
CLINK                   =#
DEPENDENCIES_PATHS      =#
#*
#* ************************************************************************** *#
#*                               Directories                                  *#
#* ************************************************************************** *#
#*
SRCS_DIR        =src/
INCLUDES_DIR    =include/
OBJS_DIR        =Objects/
DFILES_DIR      =HeaderDependencies/
DEPENDENCIES    =Dependencies/
DEP_INCLUDES    =
#*
#* ************************************************************************** *#
#*                                  Files                                     *#
#* ************************************************************************** *#
#*
SOURCES_NAME            = \
		console.cpp\
		main.cpp\
		server.cpp\

#*
#* ************************************************************************** *#
#*                               Conversions                                  *#
#* ************************************************************************** *#
#*
SOURCES                 = $(SOURCES_NAME)
DEPS                    =$(addprefix $(DEPENDENCIES), $(DEPENDENCIES_PATHS))

ifeq ($(SRCS_DIR),)
SRCS                    =$(SOURCES)
else
SRCS                    =$(addprefix $(SRCS_DIR),$(SOURCES))
endif

ifeq ($(OBJS_DIR),)
MAIN                    =$(patsubst %,%$(OBJS_EXT), $(MAIN_NAME))
else
MAIN                    =$(patsubst %,$(OBJS_DIR)%$(OBJS_EXT), $(MAIN_NAME))
endif

ifeq ($(OBJS_DIR),)
OBJS                    =$(patsubst %$(SRCS_EXT),%$(OBJS_EXT), $(SOURCES))
else
OBJS                    =$(patsubst %$(SRCS_EXT),$(OBJS_DIR)%$(OBJS_EXT), $(SOURCES))
endif

ifeq ($(DFILES_DIR),)
DFS                     =$(patsubst %$(SRCS_EXT),%$(DFILES_EXT), $(SOURCES))
else
DFS                     =$(patsubst %$(SRCS_EXT),$(DFILES_DIR)%$(DFILES_EXT), $(SOURCES))
endif

CADDLINK                =$(addprefix -L, $(dir $(DEPS)))

INCS                    =$(addprefix -I, $(INCLUDES_DIR) $(addprefix $(DEPENDENCIES), $(DEP_INCLUDES)))

#*
#* ************************************************************************** *#
#*                             Directories Rules                              *#
#* ************************************************************************** *#
#*
%/:
	mkdir -p $@
dirs: | $(SRCS_DIR) $(INCLUDES_DIR) $(DEPENDENCIES)
.PHONY: dirs
#*
#* ************************************************************************** *#
#*                            Dependencies rules                              *#
#* ************************************************************************** *#
#*
%.a:
	$(MAKE) -C $(dir $@)
#.PHONY: $(DEPS)
#*
#* ************************************************************************** *#
#*                             Compilation Rule                               *#
#* ************************************************************************** *#
ifneq ($(LIBRARY),)
$(NAME): $(OBJS) $(DEPS)
	$(ARCHIVE) $(NAME) $(OBJS)
else
$(NAME): $(OBJS) $(DEPS)
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

der: drun
.PHONY: run debug_run drun r dr der
endif
#*
#* ************************************************************************** *#
#*                                    Debug                                   *#
#* ************************************************************************** *#
#*
ifeq ($(LIBRARY),)
$(DEBUG_NAME): $(SRCS)
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
CLEAN_FILES= $(wildcard $(sort $(OBJS) $(BOBJS) $(DFS) $(OBJS_DIR) $(DFILES_DIR)) $(BDFS))
FCLEAN_FILES= $(wildcard $(NAME) $(DEBUG_NAME))

clean:
ifneq ($(CLEAN_FILES),)
	rm -fd $(CLEAN_FILES)
endif

fclean: clean
ifneq ($(FCLEAN_FILES),)
	rm -fd $(FCLEAN_FILES)
endif

re: fclean all

remake: re

.PHONY: clean fclean re remake
#*
#* ************************************************************************** *#
#*                               Objects Rule                                 *#
#* ************************************************************************** *#
#*
.SECONDEXPANSION:
$(OBJS_DIR)%$(OBJS_EXT): $(SRCS_DIR)%$(SRCS_EXT) | \
		$$(dir $$@) \
		$$(dir $$(DFILES_DIR)$$*$$(DFILES_EXT))
	$(CC) $(CFLAG) $(INCS) -c $< -o $@ $(DFLAG)

include $(wildcard $(DFS))
#*
#* ************************************************************************** *#
#*                                   Appendix                                 *#
#* ************************************************************************** *#
#*
