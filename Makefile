# @Author: Debray Arnaud <zleub>
# @Date:   2017-05-02T11:56:38+02:00
# @Email:  adebray@student.42.fr
# @Last modified by:   adebray
# @Last modified time: 2017-05-07T18:00:32+02:00

NAME = avm
SRC = $(shell find ./src -name "*.cpp")
OBJ = $(subst .cpp,.o,$(SRC))

CXX = clang++
CXXFLAGS = -Iinc -Wall -Wextra -Werror -std=c++11 -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ) main.cpp
	@echo $^" -> "$@
	@$(CXX) $(CXXFLAGS) -o $(NAME) $^

%.o:%.cpp
	@echo $<" -> "$@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf main.o
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
