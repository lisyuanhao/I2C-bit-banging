## Example folder contents

The project **sample_project** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── sdkconfig
├── README.md                  This is the file you are currently reading
├── main
│   ├── CMakeLists.txt
│   └── main.c
├── components
│   └── i2c_bitbang
│       ├── i2c_bitbang.c
│       └── i2c_bitbang.h