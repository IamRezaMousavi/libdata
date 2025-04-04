<br/>
<div align="center">
<h3 align="center">libdata</h3>
<p align="center">
Reusable Data Structures and Utilities for C Programming
<br/>
<br/>
<a href="https://github.com/iamrezamousavi/libdata/issues/new?labels=bug&template=bug-report---.md">Report Bug .</a>
<a href="https://github.com/iamrezamousavi/libdata/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
</p>
</div>

[![GitHub last commit](https://img.shields.io/github/last-commit/iamrezamousavi/libdata)](https://img.shields.io/github/last-commit/iamrezamousavi/libdata)
[![GitHub issues](https://img.shields.io/github/issues-raw/iamrezamousavi/libdata)](https://img.shields.io/github/issues-raw/iamrezamousavi/libdata)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/iamrezamousavi/libdata)](https://img.shields.io/github/issues-pr/iamrezamousavi/libdata)
[![GitHub](https://img.shields.io/github/license/iamrezamousavi/libdata)](https://img.shields.io/github/license/iamrezamousavi/libdata)

Reusable Data Structures and Utilities for C Programming

# Table of Contents

- [Usage](#usage)
- [Example](#example)
- [Contribute](#contribute)
- [License](#license)

# Usage

[(Back to top)](#table-of-contents)

## Library Mode

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

## Header-only Mode

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

# Example

[(Back to top)](#table-of-contents)

Check the [example](./example/) and [test](./test/) directories for demonstrations of how to use each module.

# Contribute

[(Back to top)](#table-of-contents)

We welcome contributions! Feel free to open an issue or submit a pull request.

- Fork the repository
- Create a new branch (`git checkout -b feature-name`)
- Commit your changes (`git commit -m "Add feature"`)
- Push the branch (`git push origin feature-name`)
- Open a pull request.

# License

[(Back to top)](#table-of-contents)

This project is licensed under the terms of the [GNU General Public License v3.0](./LICENSE).
You are free to use, modify, and distribute this library under the conditions of the GPL-3.0 license.

<div align="center"> Made with ❤️ for developers. </div>
