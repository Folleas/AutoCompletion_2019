##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

GPP			=	g++

RM			=	rm -rf

NAME		=	autoCompletion

COMPILEFLAG	=	-g

INCLUDE		=	-Iinclude/

CPPFLAGS    =	$(COMPILEFLAG) $(INCLUDE)

SRC			=	src/Core/main.cpp					\
				src/Core/Engine.cpp					\
				src/Core/Address.cpp				\
				src/Core/AddressBook.cpp			\
				src/Core/Input.cpp					\
				src/Miscellaneous/ErrorHandling.cpp	\
				src/Miscellaneous/Parser.cpp		\
				src/Miscellaneous/Utils.cpp

OBJ			=	$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	@echo -e "\033[01m\033[31mLinking ...\033[00m"
	@$(GPP) $(OBJ) -o $(NAME) $(CPPFLAGS) $(CPPFLAGS)
	@echo -e "\033[01m\033[32mStandard compilation done => ${NAME}\033[00m"

clean:
	@$(RM) src/*.o src/Core/*.o src/Miscellaneous/*.o *.gcda
	@echo -e "\033[01m\033[31mRemoving useless files ...\033[00m"

fclean:	clean
	@$(RM) $(NAME) unit_tests
	@echo -e "\033[01m\033[31mRemoving binary : {${NAME}} ...\033[00m"

re:	fclean
	@make all --no-print-directory

.PHONY:	all clean fclean re
