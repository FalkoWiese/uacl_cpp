cmake_minimum_required(VERSION 2.8)
project(tests)

# The following it's a bit confusing. You've to set this path relative to ./tests folder! Due to the easier installation
# procedure of the GTest SDK, we have to deal with it as it were a part of our source path. That's why, you've
# to clone it directly to ./tests/lib or you've to create a symbolic link from the tests/lib directory to the GTEST
# installation folder.
add_subdirectory(lib/googletest/googletest)

add_subdirectory(utils_tests)
add_subdirectory(server_tests)
add_subdirectory(client_tests)
