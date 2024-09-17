cmake_minimum_required(VERSION 3.26)
project(BasicsOfProgramming)

include_directories(/usr/local/include)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib REQUIRED)

add_executable(sorting_by_insertion "laba02/sorting_by_insertion.cpp")
add_executable(bracket_sequence "laba01/bracket_sequence.cpp")
add_executable(delete_in_place "laba01/delete_in_place.cpp")
add_executable(merge_sorting "laba02/merge_sorting.cpp")
add_executable(sorting_structures "laba02/sorting_structures.cpp")
add_executable(digital_sorting "laba03/digital_sorting.cpp")
add_executable(sorting_by_counting "laba03/sorting_by_counting.cpp")
add_executable(heap "laba04/heap.cpp")
add_executable(stack_of_minimums "laba04/stack_of_minimums.cpp")
add_executable(binary_search_approximate "laba06/binary_search_approximate.cpp")
add_executable(diplomas "laba06/diplomas.cpp")
add_executable(solution_of_the_equation "laba06/solution_of_the_equation.cpp")
add_executable(hashmap "laba05/hashmap.cpp")
add_executable(bagel "laba07/bagel.cpp")
add_executable(NVP "laba07/NVP.cpp")
add_executable(NOP "laba07/NOP.cpp")
add_executable(prefix_amounts "laba08/prefix_amounts.cpp")
add_executable(tree_of_segments_for_minima "laba08/tree_of_segments_for_minima.cpp")
add_executable(binary_search_tree "laba09/binary_search_tree.cpp")
add_executable(AVL_tree "laba09/AVL_tree.cpp")
add_executable(connectivity_component "laba10/connectivity_component.cpp")
add_executable(topological_sorting "laba10/topological_sorting.cpp")
add_executable(pizza_delivery "laba11/pizza_delivery.cpp")
add_executable(reverse_polish_entry "laba12/reverse_polish_entry.cpp")
add_executable(polish_calculator "laba12/polish_calculator.cpp")
add_executable(normal_calculator "laba12/normal_calculator.cpp")

target_link_libraries(pizza_delivery PUBLIC raylib)




