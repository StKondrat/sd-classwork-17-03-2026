CXXFLAGS += -Wall -Wextra -std=c++14 -MMD
-incluse main.d
main: main.o
	$(CXX) $^ -o $@