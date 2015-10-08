OBJ=main.cpp
FUNC=
CXX=g++
CXXOPTIMFLAGS=-O3
CXXDEBUGFLAGS=-g -O0
LIB=../../lib/libmda.a

gcc: $(OBJ) $(FUNC)
	export LIBMDA_COMPILER_SETTING="$(CXX) $(CXXOPTIMFLAGS) -std=c++11" && cd ../../lib && make
	$(CXX) $(CXXOPTIMFLAGS) -fexpensive-optimizations -Drestrict= -std=c++0x -o main $(OBJ) $(FUNC) $(LIB)
	./main

gcc_debug: $(OBJ) $(FUNC)
	export LIBMDA_COMPILER_SETTING="$(CXX) $(CXXDEBUGFLAGS) -std=c++11" && cd ../../lib && make
	$(CXX) $(CXXDEBUGFLAGS) -std=c++0x -o main $(OBJ) $(FUNC) $(LIB)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./main

intel: $(OBJ)
	export LIBMDA_COMPILER_SETTING="icpc -O3 -ip -ipo -fast -std=c++11" && cd ../../lib && make
	icpc $(CXXOPTIMFLAGS) -ip -ipo -fast -std=c++11 -Wcontext-limit=100 -o main $(OBJ) $(LIB)
	./main

intel_debug: $(OBJ)
	export LIBMDA_COMPILER_SETTING="icpc $(CXXDEBUGFLAGS) -std=c++11" && cd ../../lib && make
	icpc $(CXXDEBUGFLAGS) -std=c++11 -Wcontext-limit=100 -o main $(OBJ) $(LIB)
	valgrind --tool=memcheck --leak-check=yes ./main

clang: $(OBJ)
	export LIBMDA_COMPILER_SETTING="clang++ $(CXXOPTIMFLAGS) -std=c++11" && cd ../../lib && make
	clang++-3.5 $(CXXOPTIMFLAGS) -std=c++0x -o main $(OBJ) $(LIB)
	./main

clang_debug: $(OBJ)
	export LIBMDA_COMPILER_SETTING="clang++ $(CXXDEBUGFLAGS) -std=c++11" && cd ../../lib && make
	clang++-3.5 $(CXXDEBUGFLAGS) -std=c++0x -o main $(OBJ) $(LIB)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./main

clean:
	rm -f *core main
