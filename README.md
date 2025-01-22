## wglad
 + ## `glad` for win32

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Version](https://img.shields.io/badge/version-1.0.0-green.svg)]()

`wglad` is a simplified and user-friendly wrapper around **glad**, designed to streamline OpenGL loading and make it more accessible for developers. With `wglad`, integrating GLAD into your project is faster, easier, and more flexible.

---

### 🚀 Features

- **Simplified Integration**: Replace complex GLAD setup with a streamlined interface.
- **Flexible Usage**: Multiple options to integrate WGLAD into your project.
- **Enhanced Usability**: Intuitive API for OpenGL loading and usage.
- **Cross-Platform Compatibility**: Works seamlessly on all major platforms.
- **Customizable Configurations**: Tailor the behavior to fit your project's requirements.
---

### 🛠️ Technologies

- **Language**: C/C++
- **GLAD**: The foundation for OpenGL loading.
- **Build Tools**: Supports integration with CMake or manual project setups.
- **Compilers**: msvc / llvm-clang / mingw-gcc
- **TODO**: intergration with linux (xlib)...

---

### 📦 Installation

#### Option 1: Clone and Build Example
1. Clone the repository:
    ```bash
    git clone https://github.com/ripcode0/wglad.git
    cd wglad
    cmake -S . -B build -DBUILD_EXAMPLE=ON
    cmake --build build
    ```
2. Include `wglad` source files in your project.
3. Ensure you have the necessary `GLAD` files generated from the [GLAD Generator](https://gen.glad.sh/).

#### Option 2: Add as a Submodule
1. Add `wglad` as a submodule to your repository:
    ```bash
    git submodule add https://github.com/ripcode0/wglad.git <submodule-path>/wglad
    ```
2. Update your build system to include WGLAD.

#### Option 3: Add Subdirectory
1. Clone or Submodule
2. Link the library to your project:
    - For CMake:
      ```cmake
      add_subdirectory(wglad)
      
      target_link_libraries(your_project PRIVATE wglad)
      or
      target_link_libraries(your_project PRIVATE wglad::wglad)
      ```
    - For manual linking, add the `.lib` or `.a` file to your linker options.

---

### 📖 Usage

1. Include `wglad` in your project:
    ```cpp
    #include "<wglad/wglad.h>
    ```

2. Initialize `wglad` in your OpenGL application:
    ```cpp
    HDC dc{};
    HGLRC rc{};

    wglad::create_context_from_hwnd(hwnd, &rc, &dc, true);
    ```

3. Render process:
    ```cpp
    glClearColor(0.2f, 0.25f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //render contents

    ::SwapBuffers(dc);
    ```
4. Discard `wglad` context:
    ```cpp
    wglad::release_context(hwnd, &rc, &dc);
    ```
---

### 🤝 Contributing

We welcome contributions to improve WGLAD:

1. Fork this repository.
2. Create a branch: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m "Add feature XYZ"`.
4. Push the branch: `git push origin feature-name`.
5. Submit a pull request.

---

### 📝 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

### 🌟 Show your support

If WGLAD makes your OpenGL development smoother, give it a ⭐ on GitHub!
