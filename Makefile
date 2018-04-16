# @Author: Debray Arnaud <zleub>
# @Date:   2017-05-02T11:56:38+02:00
# @Email:  adebray@student.42.fr
# @Last modified by:   adebray
# @Last modified time: 2017-05-08T17:36:57+02:00

NAME = avm
SRC = $(shell find . -name "*.cpp")
OBJ = $(subst .cpp,.o,$(SRC))

CXX = clang++
CXXFLAGS = -Iinc -Wall -Wextra -Werror -std=c++11 -fsanitize=address -g

XX = $(shell echo test)

all: depend $(NAME)

include .depend

depend: $(SRC) main.cpp
	@ rm -f ./.depend
	@ $(foreach var, $^, $(CXX) $(CXXFLAGS) -MT $(subst .cpp,.o,$(var)) -MM $(var) >> ./.depend;)

%.o:%.cpp
	@echo $<" -> "$@
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo $^" -> "$@
	@$(CXX) $(CXXFLAGS) -o $(NAME) $^

clean:
	rm -rf main.o
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean depend
