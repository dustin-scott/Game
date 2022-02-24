cmake_minimum_required(VERSION 3.21)
project(Game)

set(CMAKE_CXX_STANDARD 14)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


# Add all cpp source files under the src directory
file(GLOB SUB_SOURCES "src/**/*.cpp")
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SUB_SOURCES} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(DevIL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(ALUT REQUIRED)

include_directories(
	src 
	${GLEW_INCLUDE_DIRS} 
	${OPENGL_INCLUDE_DIRS} 
	${GLUT_INCLUDE_DIRS} 
	${IL_INCLUDE_DIR} 
	${OPENAL_INCLUDE_DIR} 
	${ALUT_WORKAROUND_INCLUDE_DIRS} 
	${ALUT_INCLUDE_DIRS} )

target_link_libraries(
	${PROJECT_NAME} 
	${GLEW_LIBRARIES} 
	${OPENGL_LIBRARIES} 
	${GLUT_LIBRARY} 
	${IL_LIBRARIES} 
	${ILU_LIBRARIES} 
	${ILUT_LIBRARIES}
	${OPENAL_LIBRARY} 
	${ALUT_LIBRARIES} )
