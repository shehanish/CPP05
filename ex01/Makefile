# ╔══════════════════════════════════╗
# ║       Bureaucrat Makefile       ║
# ╚══════════════════════════════════╝

NAME    := bureaucrat
CXX     := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

SRC     := main.cpp Bureaucrat.cpp Form.cpp
OBJ     := $(SRC:.cpp=.o)
HEADER  := Bureaucrat.hpp

# 🎨 Colors
GREEN   := \033[0;32m
YELLOW  := \033[1;33m
RED     := \033[0;31m
RESET   := \033[0m

# 🛠 Default target
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)[Linking Executable...]$(RESET)"
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "$(GREEN)✅ Done: $(NAME) built successfully!$(RESET)"

# 🧹 Clean object files
clean:
	@echo "$(RED)[Cleaning object files...]$(RESET)"
	@rm -f $(OBJ)

# 💣 Clean everything
fclean: clean
	@echo "$(RED)[Removing executable...]$(RESET)"
	@rm -f $(NAME)

# 🔁 Rebuild
re: fclean all

# 🚀 Run the program (optional)
run: $(NAME)
	@echo "$(YELLOW)[Running $(NAME)...]$(RESET)"
	@./$(NAME) Alice 42

# 📚 Dependencies
%.o: %.cpp $(HEADER)
	@echo "$(YELLOW)[Compiling $<...]$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean fclean re run
