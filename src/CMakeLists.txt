add_executable(SnakeGM main.cpp game.cpp snake.cpp grid.cpp food.cpp Node.cpp)

# Include raylib headers
target_include_directories(SnakeGM PRIVATE ${CMAKE_SOURCE_DIR}/third_party/raylib-msvc/include)

# Tell the linker where to find raylib library binaries 
target_link_directories(SnakeGM PRIVATE ${CMAKE_SOURCE_DIR}/third_party/raylib-msvc/lib)

# Link third party libraries here along with required Windows system libs
target_link_libraries(SnakeGM PRIVATE ${CMAKE_SOURCE_DIR}/third_party/raylib-msvc/lib/raylib.lib winmm gdi32)

set_target_properties(SnakeGM PROPERTIES LINK_FLAGS "/NODEFAULTLIB:msvcrt")
