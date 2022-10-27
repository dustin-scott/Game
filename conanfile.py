from conans import ConanFile, CMake

class GameConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        ("freeglut/3.2.1"),
        ("glew/2.2.0"),
        ("openal/1.19.1"),
        ("audiofile/1.1.0"),
        ("stb/20200203"),
        ("tinygltf/2.5.0")
    ]
    generators = "cmake", "CMakeDeps", "CMakeToolchain", "gcc"
    default_options = {"poco:shared": True, "openssl:shared": True}

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        cmake.configure()
        cmake.build()
