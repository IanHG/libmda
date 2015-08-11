all: libmda.a check_libmda_compiler_setting

libmda.a: ../util/print_variadic.cpp ../util/type_info.cpp ../util/rand_seed.cpp ../util/random_bool.cpp ../util/multiple_return.cpp ../testing/failed_data.cpp ../testing/unit_test.cpp ../testing/unit_assert.cpp ../functions.cpp ../util/output_call_addr.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../util/print_variadic.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../util/type_info.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../util/multiple_return.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../util/rand_seed.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../util/random_bool.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../util/output_call_addr.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../testing/failed_data.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../testing/unit_test.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../testing/unit_assert.cpp
	$(LIBMDA_COMPILER_SETTING) -std=c++11 -c ../functions.cpp
	ar -cvq libmda.a *.o

check_libmda_compiler_setting:
ifndef LIBMDA_COMPILER_SETTING
LIBMDA_COMPILER_SETTING=g++ -O3
endif

cleanlib: 
	rm libmda.a

clean:
	rm *.o
