from conans import ConanFile, CMake, tools


class TweetnaclConan(ConanFile):
    name = "tweetnacl"
    version = "20140427"
    license = "Public Domain"
    homepage = "https://tweetnacl.cr.yp.to/"
    url = "https://github.com/conan-community/conan-tweetnacl"
    description = "TweetNaCl is the world's first auditable high-security cryptographic library"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "src/*"
    build_policy = "missing"

    def configure(self):
        del self.settings.compiler.libcxx

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
