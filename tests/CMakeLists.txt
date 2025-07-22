find_package(GTest REQUIRED)

add_executable(run_tests 
	operations_sin_test.cpp
	operations_plus_test.cpp
	operations_minus_test.cpp
	operations_negate_test.cpp
	operations_multiplies_test.cpp
	operations_divides_test.cpp
	operations_exp_test.cpp
	operations_log_test.cpp
	operations_pow_test.cpp
	operations_sqrt_test.cpp
	operations_cos_test.cpp
)

target_link_libraries(run_tests 
	dual
	GTest::GTest 
	GTest::Main 
	pthread
)

add_test(NAME RunAllTests COMMAND run_tests)
