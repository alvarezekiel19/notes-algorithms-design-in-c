cmake_minimum_required(VERSION 3.16)
project(DSA_Algorithms_Project C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -DDEBUG -fsanitize=address -fsanitize=undefined")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2 -DNDEBUG")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Function to sanitize directory names for CMake targets
function(sanitize_name input_name output_name)
    string(REPLACE " " "_" temp_name ${input_name})
    string(REPLACE "-" "_" temp_name ${temp_name})
    string(TOLOWER ${temp_name} temp_name)
    set(${output_name} ${temp_name} PARENT_SCOPE)
endfunction()

# Function to create executables and tests for each topic directory
function(add_topic_tests topic_dir)
    get_filename_component(topic_name ${topic_dir} NAME)
    sanitize_name(${topic_name} safe_topic_name)
    
    message(STATUS "Processing topic: ${topic_name}")
    
    # Find all .c files in this topic directory
    file(GLOB TOPIC_SOURCES "${topic_dir}/*.c")
    
    if(NOT TOPIC_SOURCES)
        message(STATUS "No .c files found in ${topic_name}")
        return()
    endif()
    
    set(MAIN_SOURCES "")
    set(TEST_SOURCES "")
    
    # Separate main sources from test sources
    foreach(source_file ${TOPIC_SOURCES})
        get_filename_component(filename ${source_file} NAME)
        if(filename MATCHES "^test_.*\\.c$")
            list(APPEND TEST_SOURCES ${source_file})
        else()
            list(APPEND MAIN_SOURCES ${source_file})
        endif()
    endforeach()
    
    # Create library from main sources (if any non-test sources exist)
    if(MAIN_SOURCES)
        set(lib_name "${safe_topic_name}_lib")
        add_library(${lib_name} STATIC ${MAIN_SOURCES})
        target_link_libraries(${lib_name} m)
        
        # Create example executable for each main source
        foreach(main_source ${MAIN_SOURCES})
            get_filename_component(source_name ${main_source} NAME_WE)
            set(exec_name "${safe_topic_name}_${source_name}")
            
            # Check if source has main function
            file(READ ${main_source} SOURCE_CONTENT)
            if(SOURCE_CONTENT MATCHES "int[ \t\n]+main[ \t\n]*\\(")
                add_executable(${exec_name} ${main_source})
                target_link_libraries(${exec_name} m)
                message(STATUS "Created executable: ${exec_name}")
            endif()
        endforeach()
    endif()
    
    # Create test executables
    foreach(test_source ${TEST_SOURCES})
        get_filename_component(test_name ${test_source} NAME_WE)
        set(test_target "${safe_topic_name}_${test_name}")
        
        # Create test executable
        add_executable(${test_target} ${test_source})
        
        # Link with topic library if it exists
        if(MAIN_SOURCES)
            target_link_libraries(${test_target} ${lib_name})
        endif()
        
        # Link math library
        target_link_libraries(${test_target} m)
        
        # Add as test
        add_test(NAME ${test_target} COMMAND ${test_target})
        set_tests_properties(${test_target} PROPERTIES 
            TIMEOUT 30
            LABELS "${safe_topic_name}"
        )
        
        message(STATUS "Created test: ${test_target}")
    endforeach()
endfunction()

# Process all topic directories
file(GLOB TOPIC_DIRS "${CMAKE_SOURCE_DIR}/src/*")
foreach(topic_dir ${TOPIC_DIRS})
    if(IS_DIRECTORY ${topic_dir})
        add_topic_tests(${topic_dir})
    endif()
endforeach()

# Integration tests
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/integration_tests.c")
    add_executable(integration_tests tests/integration_tests.c)
    target_link_libraries(integration_tests m)
    add_test(NAME integration_tests COMMAND integration_tests)
    set_tests_properties(integration_tests PROPERTIES TIMEOUT 60)
endif()

# Custom targets for organized testing
add_custom_target(test_algorithms)
add_custom_target(test_data_structures)
add_custom_target(test_fundamentals)

# Group tests by category
set(ALGORITHM_TOPICS 
    "basic_sorting_algorithms" "mergesort_algorithm" "quicksort_algorithm" 
    "heapsort_algorithm" "digital_sorting" "searching_sorted_arrays"
    "searching_for_a_word_in_a_text" "enumeration_algorithms")

set(DATA_STRUCTURE_TOPICS 
    "arrays" "linked_lists" "queues" "stacks" "binary_trees" 
    "binary_search_trees" "hashing")

set(FUNDAMENTAL_TOPICS 
    "logarithms" "recursion_and_recursive_algorithms" "bytes_numbers_and_characters"
    "the_types_int_and_char" "strings_and_character_chains" "string_manipulation"
    "addresses_and_pointers" "records_and_structs" "dynamic_memory_allocation")

# Add dependencies to custom targets
foreach(topic ${ALGORITHM_TOPICS})
    add_dependencies(test_algorithms ${topic}_test)
endforeach()

foreach(topic ${DATA_STRUCTURE_TOPICS})
    add_dependencies(test_data_structures ${topic}_test)
endforeach()

foreach(topic ${FUNDAMENTAL_TOPICS})
    add_dependencies(test_fundamentals ${topic}_test)
endforeach()

# Print build summary
message(STATUS "=== Build Configuration Summary ===")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Standard: C${CMAKE_C_STANDARD}")
message(STATUS "Source Directory: ${CMAKE_SOURCE_DIR}")
message(STATUS "Binary Directory: ${CMAKE_BINARY_DIR}")
