enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/libdata)
link_libraries(data)

file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test_*.c")

foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} data)
    target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/libdata)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach(TEST_SRC)
