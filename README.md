# Raccoon C++ Game Engine

[![License: Apache-2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## Introduction

Raccoon is a C++ game engine designed for building 2D and 3D games. Additionally, it serves as a valuable resource for learning game engine development.

## Getting Started

### Installing
  
1. Clone the repository:

```bash

git clone --recursive https://github.com/OlehDvorychanskyi/Raccoon.git

```
    
### Building

1. Make sure CMake is installed on your computer.
2. Run one of the bash scripts to build Raccoon:

```bash

.\build_MinGW_debug.bat

```
3. Now you can go to "build/MinGW_Debug/Sandbox/Sandbox.exe" and run .exe file. 

## Branches

Raccoon repository utilizes multiple branches to organize and manage development and stability. Here's a brief overview of the main branches:

### Main Branch

The `main` branch houses stable versions of Raccoon. It serves as the primary branch for production-ready releases. You can depend on this branch for reliable and tested versions of the engine.

### Dev Branch

The `dev` branch is where active development takes place. It's the current working branch for ongoing feature development, bug fixes, and enhancements. While generally stable, it may occasionally contain experimental features or changes undergoing testing.

### YouTube Branch

The `youtube` branch is dedicated to supporting educational content, particularly our YouTube series. Each step of the tutorial series is meticulously explained in videos, and the associated code changes are reflected in this branch. If you're following along with our YouTube tutorials, this branch provides a snapshot of the codebase at each lesson.

### Other Branches

In addition to these main branches, contributors may create feature branches, bug fix branches, or experimental branches as needed. These branches are typically short-lived and are merged back into `dev` once their changes are complete and tested.

We encourage contributors to follow our branching strategy and guidelines outlined in the [Contribution Guidelines](#contributing) to ensure a smooth and collaborative development process.

## Contributing 

We welcome contributions from the community! If you'd like to contribute to this project, please follow these guidelines.

### How to Contribute

1. **Fork the repository:** Click the "Fork" button in the top-right corner of this repository to create your own copy.

2. **Clone the repository:** Clone your forked repository to your local machine using the following command:
    ```bash
    git clone --recursive https://github.com/OlehDvorychanskyi/Raccoon.git
    ```
    
3. **Create a new branch:** Before making any changes, create a new branch to work in. Use a descriptive branch name that reflects the changes you intend to make. If you're adding a feature or fixing a bug, base your branch off the dev branch.
    ```bash
    git checkout -b your-branch-name dev
    ```

4. **Make your changes:** Make your desired changes to the codebase. Ensure that your changes follow the project's coding conventions and guidelines.

5. **Test your changes:** If applicable, test your changes to ensure they work as expected.

6. **Commit your changes:** Once you're happy with your changes, commit them to your branch with a clear and descriptive commit message.

7. **Push your changes:** Push your changes to your forked repository on GitHub.

8. **Submit a pull request:** Finally, navigate to the original repository and click the "New pull request" button. Choose the dev branch as the base branch and your branch as the compare branch. Provide a brief summary of your changes and submit your pull request for review.

### Code Style and Standards

### Reporting Issues
If you encounter any issues with the project or would like to suggest improvements, please [create a new issue](https://github.com/OlehDvorychanskyi/Raccoon/issues/new)  on the GitHub repository.

### Contact
If you have any questions, feedback, or need further assistance, feel free to contact the project maintainers:

- **Email:** [oleh.dvorychanskyi@gmail.com](mailto:oleh.dvorychanskyi@gmail.com)

We appreciate your interest and are happy to assist you with any inquiries related to the project.