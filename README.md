## WGLAD `opengl for window api`

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Version](https://img.shields.io/badge/version-1.0.0-green.svg)]()

`WGLAD` is a simplified and user-friendly wrapper around **GLAD**, designed to streamline OpenGL loading and make it more accessible for developers. With `WGLAD`, integrating GLAD into your project is faster, easier, and more flexible.

---

## 🚀 Features

- **Simplified Integration**: Replace complex GLAD setup with a streamlined interface.
- **Flexible Usage**: Multiple options to integrate WGLAD into your project.
- **Enhanced Usability**: Intuitive API for OpenGL loading and usage.
- **Cross-Platform Compatibility**: Works seamlessly on all major platforms.
- **Customizable Configurations**: Tailor the behavior to fit your project's requirements.
---

## 🛠️ Technologies

- **Language**: C/C++
- **GLAD**: The foundation for OpenGL loading.
- **Build Tools**: Supports integration with CMake or manual project setups.
- **Compilers**: msvc / llvm-clang / mingw-gcc
- **TODO**: intergration with linux ...

---

## 📦 Installation

### Option 1: Clone and Include
1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/WGLAD.git
    cd WGLAD
    ```
2. Include WGLAD source files in your project.
3. Ensure you have the necessary GLAD files generated from the [GLAD Generator](https://gen.glad.sh/).

### Option 2: Add as a Submodule
1. Add WGLAD as a submodule to your repository:
    ```bash
    git submodule add https://github.com/yourusername/WGLAD.git
    ```
2. Update your build system to include WGLAD.

### Option 3: Precompiled Library
1. Download the precompiled WGLAD library from the [Releases](https://github.com/yourusername/WGLAD/releases).
2. Link the library to your project:
    - For CMake:
      ```cmake
      target_link_libraries(your_project PRIVATE WGLAD)
      ```
    - For manual linking, add the `.lib` or `.a` file to your linker options.

---

## 📖 Usage

1. Include WGLAD in your project:
    ```cpp
    #include "wglad.h"
    ```

2. Initialize WGLAD in your OpenGL application:
    ```cpp
    if (!wglad::initialize()) {
        std::cerr << "Failed to initialize WGLAD!" << std::endl;
        return -1;
    }
    ```

3. Start writing OpenGL code without worrying about the loading process:
    ```cpp
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ```

---

## 🤝 Contributing

We welcome contributions to improve WGLAD:

1. Fork this repository.
2. Create a branch: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m "Add feature XYZ"`.
4. Push the branch: `git push origin feature-name`.
5. Submit a pull request.

---

## 📝 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## 📧 Contact

For inquiries, suggestions, or feedback:

- **Email**: yourname@example.com
- **GitHub**: [yourusername](https://github.com/yourusername)

---

### 🌟 Show your support

If WGLAD makes your OpenGL development smoother, give it a ⭐ on GitHub!
