find_package(GTest REQUIRED)

add_executable(run_tests 
	operations_sin_test.cpp
)

target_link_libraries(run_tests 
	dual
	GTest::GTest 
	GTest::Main 
	pthread
)

add_test(NAME RunAllTests COMMAND run_tests)
