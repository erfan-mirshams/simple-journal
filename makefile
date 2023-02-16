##
# journal-e-ablah
#
# @file
# @version 0.1

SRC = code.cpp
CFLAGS = -lstdc++ -Wall -Wextra -std=c++11 -fsanitize=address -fsanitize=leak -fsanitize=undefined

journal: ${SRC}
	gcc ${CFLAGS} ${SRC} -o $@

clean:
	rm -f journal

# end
