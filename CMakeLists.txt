cmake_minimum_required(VERSION 3.7)
set (CMAKE_CXX_STANDARD 14)

project(hoops_project)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(HEADER_FILES src/util.cpp
                 src/env_namespace.cpp
                 src/bball_page.cpp
                 src/content_loader.h
                 src/content_page.h
                 src/loader.cpp
                 src/page_reader.h
                 src/player_extractor.h
                 src/player_metadata.cpp
                 src/adapters/attribute_interface.cpp
                 src/adapters/attribute_adapter_impl.cpp
                 src/adapters/advanced_adapter.cpp
                 src/adapters/advanced_playoffs_adapter.cpp
                 src/adapters/per_36_adapter.cpp
                 src/adapters/per_36_playoffs_adapter.cpp
                 src/adapters/per_100_adapter.cpp
                 src/adapters/per_100_playoffs_adapter.cpp
                 src/adapters/per_game_adapter.cpp
                 src/adapters/per_game_playoffs_adapter.cpp
                 src/adapters/play_adapter.cpp
                 src/adapters/play_playoffs_adapter.cpp
                 src/adapters/shooting_adapter.cpp
                 src/adapters/shooting_playoffs_adapter.cpp
                 src/adapters/totals_adapter.cpp
                 src/adapters/totals_playoffs_adapter.cpp
                 src/adapters/totals_all_star_adapter.cpp
                 src/adapters/game_highs_adapter.cpp
                 src/adapters/game_highs_playoffs_adapter.cpp
                 src/profile_loader.cpp
                 src/index_loader.cpp
                 src/stats_adapters.cpp
                 src/meta_section_parser.cpp
                 src/scraper_wrapper.cpp
                 src/gumbo_scraper.cpp
                 src/commands/command.cpp
                 src/commands/help_command.cpp
                 src/commands/pull_command.cpp
                 src/commands/quit_command.cpp
                 src/commands/fun_command.cpp
                 src/commands/compare_command.cpp
                 src/hoops_env.cpp
                 src/hoops_engine.cpp)

include_directories(src/)

add_library(gumboquery STATIC IMPORTED)
set_property(TARGET gumboquery PROPERTY IMPORTED_LOCATION /Users/David/Git/gumbo-query/lib/libgumbo_query_static.a)
#set_property(TARGET gumboquery PROPERTY IMPORTED_LOCATION lib/libgumbo_query_static_1.a)

add_library(gumboparser STATIC IMPORTED)
set_property(TARGET gumboparser PROPERTY IMPORTED_LOCATION /usr/local/Cellar/gumbo-parser/0.10.1/lib/libgumbo.a)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

add_executable(hoops main.cpp ${HEADER_FILES})

include_directories(~/git/gumbo-query/src)
include_directories(/usr/local/Cellar/gumbo-parser/0.10.1/include)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(hoops gumboparser gumboquery ${CURL_LIBRARIES})