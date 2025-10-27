#-------------------------------NAME-------------------------------------------#
NAME = rpn_calculator

#-------------------------------FLAGS-----------------------------------------#
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -MP -MMD -std=c++98 -g
RM := rm -rf
#-------------------------------SRCS-------------------------------------------#
SRCS =	main.cpp \

BUILD_DIR := .build

#-------------------------------OBJECTS----------------------------------------#
OBJ = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
OBJ_DIR = $(sort $(shell dirname $(OBJ)))


#================== DEPENDENCY ==================#
DEP := $(SRCS:%.cpp=$(BUILD_DIR)/%.d)

# Calculate total objects
OBJS_TOTAL := $(words $(SRCS))
CURR_OBJ := 0

#-------------------------------RULES------------------------------------------#

.PHONY: all clean fclean re

# Default target to build the project
all: $(NAME)

# Link the objects and create the executable
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files and temporary files
clean :
	$(RM) $(BUILD_DIR)

# Fully clean the project (including executable and libft)
fclean : clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)