<!-- markdownlint-disable MD033 MD041 -->
<br />
<div align="center">
    <h3 align="center">libdata</h3>
    <p align="center">
        A static library of powerful and widely-used data structures and algorithms for high-performance C programming
        <br />
        <br />
        <a href="https://github.com/iamrezamousavi/libdata/issues/new?labels=bug&template=bug-report---.md">Report Bug.</a>
        <a href="https://github.com/iamrezamousavi/libdata/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
    </p>
</div>

[![GitHub last commit](https://img.shields.io/github/last-commit/iamrezamousavi/libdata)](https://img.shields.io/github/last-commit/iamrezamousavi/libdata)
[![GitHub issues](https://img.shields.io/github/issues-raw/iamrezamousavi/libdata)](https://img.shields.io/github/issues-raw/iamrezamousavi/libdata)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/iamrezamousavi/libdata)](https://img.shields.io/github/issues-pr/iamrezamousavi/libdata)
[![GitHub](https://img.shields.io/github/license/iamrezamousavi/libdata)](https://img.shields.io/github/license/iamrezamousavi/libdata)

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Installation](#installation)
  - [Example](#example)
- [Roadmap](#roadmap)
- [Contribute](#contribute)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Features

🚀 **High Performance Optimization**

- **Blazing fast speed** using modern, optimized algorithms
- **Low memory footprint** with intelligent dynamic memory management

📦 **Lightweight & Dependency-Free**

- **Extremely small size** (ideal for embedded systems and space-sensitive applications)
- **Static linking support** - no need to install the library on target systems
- **Zero external dependencies** - works out of the box

👌 **Easy to Use & Flexible**

- **Clean, readable implementation** with thorough documentation
- **Simple integration** with two options:
  - **Library Mode** for large projects
  - **Header-only Mode** for quick integration in small projects

🧪 **Reliable & Stable**

- **Comprehensive unit tests** ensuring correctness
- **Ready-to-use examples** in [`examples/`](examples/) for quick start

### Why Choose libdata?

✔ **The optimal choice** for projects prioritizing **speed, memory efficiency and small size**  
✔ **No installation headaches** across different systems (thanks to static linking)  
✔ **Clean modular code** that's easy to maintain and extend  

## Getting Started

[(Back to top)](#table-of-contents)

### Installation

#### Library Mode

1. Build the library:

    ```bash
    cmake -Bbuild -H.
    cd build/
    make
    ```

2. Install the library:

    ```bash
    sudo make install
    ```

3. Use header files in your code:

    ```c
    #include <libdata/datastruct/queue.h>
    ```

4. Build your binary with this command:

    ```bash
    gcc program.c -ldata
    ```

#### Header-only Mode

1. Copy the `*.h` and `*.c` files you need.
2. Paste them alongside your header and source files.
3. Include the header files in your code:

    ```c
    #include "queue.h"
    ```

4. Build your program with the copied source files.

    ```bash
    gcc program.c queue.c
    ```

### Example

The [example](./example/) and [test](./test/) directories contain practical usage demonstrations:

- `examples/` → Basic usage samples
- `test/` → Advanced test cases

## Roadmap

[(Back to top)](#table-of-contents)

See the [open issues](https://github.com/IamRezaMousavi/libdata/issues) for a list of proposed features (and known issues).

## Contribute

[(Back to top)](#table-of-contents)

We welcome contributions! Feel free to open an issue or submit a pull request.

- Fork the repository
- Create a new branch (`git checkout -b feature-name`)
- Commit your changes (`git commit -m "Add feature"`)
- Push the branch (`git push origin feature-name`)
- Open a pull request.

## License

[(Back to top)](#table-of-contents)

This project is licensed under the terms of the [GNU General Public License v3.0](./LICENSE).
You are free to use, modify, and distribute this library under the conditions of the GPL-3.0 license.

## Acknowledgements

[(Back to top)](#table-of-contents)

- [TheAlgorithms/C](https://github.com/TheAlgorithms/C)

---

<div align="center"> Made with ❤️ for developers. </div>
