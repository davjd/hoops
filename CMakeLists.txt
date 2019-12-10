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
                 src/adapters/attribute_adapter.cpp
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
                 src/hoops_env.cpp)

include_directories(src/)

include(FindPackageHandleStandardArgs)
 
# Here you can define what libraries of wxWidgets you need for your
# application. You can figure out what libraries you need here;
# https://www.wxwidgets.org/manuals/2.8/wx_librarieslist.html
# We need the Find package for wxWidgets to work
# NOTE: if you're using aui, include aui in this required components list.

# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
find_package(wxWidgets COMPONENTS core base REQUIRED)

# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )

add_library(gumboquery STATIC IMPORTED)
set_property(TARGET gumboquery PROPERTY IMPORTED_LOCATION /Users/David/Git/gumbo-query/lib/libgumbo_query_static.a)
#set_property(TARGET gumboquery PROPERTY IMPORTED_LOCATION lib/libgumbo_query_static_1.a)

add_library(gumboparser STATIC IMPORTED)
set_property(TARGET gumboparser PROPERTY IMPORTED_LOCATION /usr/local/Cellar/gumbo-parser/0.10.1/lib/libgumbo.a)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

# add_executable(hoops main.cpp ${HEADER_FILES})

# For convenience we define the sources as a variable. You can add 
# header files and cpp/c files and CMake will sort them out
set(SRCS main.cpp ${HEADER_FILES})

# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
if(WIN32)
  set(SRCS ${SRCS} minimal.rc)
endif(WIN32)

# Here we define the executable minimal.exe or minimal on other systems
# the above paths and defines will be used in this build
add_executable(hoops WIN32 ${SRCS})

# We add to our target 'minimal' the wxWidgets libraries. These are
# set for us by the find script. If you need other libraries, you
# can add them here as well. 
target_link_libraries(hoops ${wxWidgets_LIBRARIES})


include_directories(~/git/gumbo-query/src)
include_directories(/usr/local/Cellar/gumbo-parser/0.10.1/include)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(hoops gumboparser gumboquery ${CURL_LIBRARIES})