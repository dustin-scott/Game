cmake_minimum_required(VERSION 3.21)
project(Game)

set(CMAKE_CXX_STANDARD 14)

#target_compile_definitions(${PROJECT_NAME} PRIVATE TINYGLTF_NO_STB_IMAGE_WRITE=1)
# Add all headers files under the include directory
#find_package(GLEW REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
#find_package(OpenAL REQUIRED)
#find_package(DevIL REQUIRED)
#find_package(ALUT REQUIRED)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(
	src
)

# Add all cpp source files under the src directory
file(GLOB SUB_SOURCES "src/**/*.cpp")
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SUB_SOURCES} ${SOURCES})

target_link_libraries(
	${PROJECT_NAME} 
#	${GLEW_LIBRARIES} 
#	${OPENGL_LIBRARIES} 
#	${GLUT_LIBRARY} 
#	${IL_LIBRARIES} 
#	${ILU_LIBRARIES} 
#	${ILUT_LIBRARIES}
#	${OPENAL_LIBRARY} 
#	${ALUT_LIBRARIES} 
  	${CONAN_LIBS}
)
