# Настройки проекта.
cmake_minimum_required(VERSION 3.10)
project("CoinDetector")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

message(STATUS "=== OpenCV_LIBS: ${OpenCV_LIBS} ===")

file(GLOB lib_src
	CMAKE_CONFIGURE_DEPENDS "src/*.cpp"
)

add_library(${PROJECT_NAME}_lib STATIC
	${lib_src}
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
	${PROJECT_SOURCE_DIR}/include
	${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}_lib PUBLIC
	${OpenCV_LIBS}
)

# Создание файла Executable.

add_executable (${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${PROJECT_NAME}_lib
	${OpenCV_LIBS}
)
