all:
	clang++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address main.cpp -o test
test: all
	./test
clean:
	rm -rf test
