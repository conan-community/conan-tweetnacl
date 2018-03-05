from conans import ConanFile, CMake, tools


class TweetnaclConan(ConanFile):
    name = "tweetnacl"
    version = "20140427"
    license = "Public Domain"
    homepage = "https://tweetnacl.cr.yp.to"
    url = "https://github.com/conan-community/conan-tweetnacl"
    description = "TweetNaCl is the world's first auditable high-security cryptographic library"
    exports = ["PUBLIC_DOMAIN_LICENSE.md", "LICENSE.md"]
    exports_sources = ["CMakeLists.txt"]
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"

    def configure(self):
        del self.settings.compiler.libcxx

    def source(self):
        url = "%s/%s/" % (self.homepage, self.version)
        sources = ["tweetnacl.h", "tweetnacl.c"]
        for s in sources:
            tools.download(url+s, s)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy(pattern="*LICENSE*", dst="licenses")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
