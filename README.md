# conan-tweetnacl

[Conan.io](https://conan.io) package for [tweetnacl](http://tweetnacl.cr.yp.to/index.html) project.

The packages generated with this *conanfile.py* can be found in [Bintray](https://bintray.com/conan-community/conan/tweetnacl%3Aconan).

## Basic setup

    $ conan install tweetnacl/20140427@conan/stable

## Project setup

If you handle multiple dependencies in your project is better to add a *conanfile.txt*:

    [requires]
    tweetnacl/20140427@conan/stable

    [generators]
    txt
    cmake

## Example

See [example.cpp](test_package/example.cpp) on how to use the library which needs
the external implementation of a [C function randombytes](test_package/example.cpp#L13)
with the following signature:


```c
void randombytes(unsigned char * ptr,unsigned int length)
```

## License

Public Domain
