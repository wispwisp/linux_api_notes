cmake_minimum_required(VERSION 3.8)

project(epoll LANGUAGES CXX)

add_subdirectory(server)
add_subdirectory(load_tests)

# # Sanitizers
# target_compile_options(server
#   PUBLIC "-g"
#   PUBLIC "-fno-omit-frame-pointer"
#   PUBLIC "-fno-optimize-sibling-calls"
#   PUBLIC "-fsanitize=address")
# target_link_libraries(server
#   -fsanitize=address)

# # debug
# target_compile_definitions(server
#   PUBLIC _GLIBCXX_DEBUG
#   PUBLIC _GLIBCXX_DEBUG_PEDANTIC)

# # Gtests:
# find_library(GTEST_LIBRARY gtest)
# find_library(GMOCK_LIBRARY gmock)
# target_link_libraries(server
#   Server
#   ${GTEST_LIBRARY}
#   ${GMOCK_LIBRARY})
