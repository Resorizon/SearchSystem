cmake_minimum_required(VERSION 3.29)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(Src
    main.cpp
    ConverterJSON.cpp
    InvertedIndex.cpp
    SearchServer.cpp
    Utils.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(SearchSystem ${Src})

target_link_libraries(SearchSystem PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(SearchSystem PUBLIC ${MY_INCLUDE_DIR})