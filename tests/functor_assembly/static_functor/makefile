OBJ=main.cc 
FUNC=
CXX=g++
CXXOPTIMFLAGS=-O3
CXXDEBUGFLAGS=-g -O0


gcc: $(OBJ) $(FUNC)
	$(CXX) $(CXXOPTIMFLAGS) -fexpensive-optimizations -Drestrict= -std=c++0x -o main $(OBJ) $(FUNC)
	./main

gcc_debug: $(OBJ) $(FUNC)
	$(CXX) $(CXXDEBUGFLAGS) -std=c++0x -o main $(OBJ) $(FUNC)
	valgrind --tool=memcheck --leak-check=yes ./main

gcc_assembly: $(OBJ) $(FUNC)
	$(CXX) $(CXXDEBUGFLAGS) -O3 -S -std=c++0x $(OBJ) $(FUNC)

intel: $(OBJ)
	icc $(CXXOPTIMFLAGS) -ip -ipo -fast -std=c++11 -Wcontext-limit=100 -o main $(OBJ)
	./main

intel_debug: $(OBJ)
	icc $(CXXDEBUGFLAGS) -std=c++11 -Wcontext-limit=100 -o main $(OBJ)
	valgrind --tool=memcheck --leak-check=yes ./main

clang: $(OBJ)
	clang++ $(CXXOPTIMFLAGS) -std=c++0x -o main $(OBJ)
	./main

clang_debug: $(OBJ)
	clang++ $(CXXDEBUGFLAGS) -std=c++0x -o main $(OBJ)
	valgrind --tool=memcheck --leak-check=yes ./main

clang_assembly: $(OBJ)
	clang++ $(CXXDEBUGFLAGS) -O3 -S -std=c++0x $(OBJ)

clean:
	rm -f *core main
