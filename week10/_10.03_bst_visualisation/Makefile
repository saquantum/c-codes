#! /usr/bin/env bash
	
bst: bst.h basic_ops.c compact.c readfile.c
	gcc basic_ops.c compact.c readfile.c -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal -fsanitize=address -fsanitize=undefined -Werror -o exe -lm
	
demo: bst.h basic_ops.c compact.c driver.c
	gcc basic_ops.c compact.c driver.c -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal -fsanitize=address -fsanitize=undefined -Werror -o demo -lm
	./demo
	
