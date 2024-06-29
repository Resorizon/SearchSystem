include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SrcFiles
	${MY_SRC_DIR}/InvertedIndex.cpp
	${MY_SRC_DIR}/SearchServer.cpp
	${MY_SRC_DIR}/ConverterJSON.cpp
    ${MY_SRC_DIR}/Utils.cpp
)

set(TestsFiles
    tests_main.cpp
    tests_InvertedIndex.cpp
    tests_SearchServer.cpp
)

add_executable(SearchSystemTests ${TestsFiles} ${SrcFiles})

target_include_directories(SearchSystemTests PRIVATE ${CMAKE_SOURCE_DIR}/nlohmann_json/include)
target_link_libraries(SearchSystemTests PRIVATE gtest gtest_main nlohmann_json::nlohmann_json)

include(GoogleTest)
gtest_discover_tests(SearchSystemTests)