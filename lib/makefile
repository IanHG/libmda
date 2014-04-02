all: libmda.a

libmda.a: ../util/print_variadic.cpp ../testing/failed_data.cpp ../testing/unit_test.cpp ../testing/unit_assert.cpp ../util/type_info.cpp ../imda/imda_rand.cpp 
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../util/print_variadic.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../util/type_info.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../testing/failed_data.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../testing/unit_test.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../testing/unit_assert.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../imda/imda_rand.cpp
	ar -cvq libmda.a *.o

cleanlib: 
	rm libmda.a

clean:
	rm *.o
