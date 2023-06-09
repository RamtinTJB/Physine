# Physine
A Simple 2D C++ Physics Engine and collision detector library. This is a hobby project and it contains a lot of issues and bugs. I try to maintain this project and work on the issues over time. Please feel free to open issues or create a pull request. Any contribution is welcome!

## Install and Build
This project has very few dependencies, only **CMake 3.12+** and **SFML 2.5+**. You can follow the instructions on their official [website](https://www.sfml-dev.org/tutorials/2.5/) to install the library.

Run the following commands to build and install the library on your system:

```sh
git clone https://github.com/RamtinTJB/Physine
cd Physine
cmake -B build
cd build
sudo make install
```

## Usage

In your CMake project, this is how you find and link this library with your targets:

```cmake
find_package(physine 1.0 REQUIRED)

add_executable(App main.cpp)

include_directories(${physine_INCLUDE_DIRS})
target_link_libraries(App PhysineCore)
```

And in your main.cpp:

```cpp
#include <Physine/world.h>

int main(int argc, const char** argv) {
    World world(1000, 1000);

    world.add_event_listener(EventType::Closed, [&world](Event e) { world.close(); });

    world.mainloop();

    return 0;
}
```

Check [this folder](examples/) to see some examples of the library's usage.

## Future Work

- [ ] Write documentation and comment the code
- [ ] Decompose sources into different folders
- [ ] Drawables:
    - [ ] Image Drawable
    - [ ] Text Drawable
- [ ] Collision
    - [ ] Non-axis aligned rect vs rect
- [ ] Physics
    - [ ] Solve for angular velocities after collision

## License

<img align="right" src="https://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The project is licensed under the [MIT License](https://opensource.org/licenses/MIT):

Copyright &copy; 2023 Ramtin Tajbakhsh
