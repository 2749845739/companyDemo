find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
add_executable(demo_graineval EXCLUDE_FROM_ALL
    demo_graineval.cpp
)

option(DEMO_BY_FILES "demo by read image files" OFF)

target_include_directories(demo_graineval PRIVATE
    ${OpenCV_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

target_compile_definitions(demo_graineval
    PRIVATE $<$<BOOL:${DEMO_BY_FILES}>:DEMO_BY_FILES>
  )

target_link_libraries(demo_graineval PRIVATE
    Boost::filesystem ${OpenCV_LIBS} generator graineval dcdf_save logging)
