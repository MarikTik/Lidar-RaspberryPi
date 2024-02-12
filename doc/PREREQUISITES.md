# Prerequisites

Before you begin, ensure you have met the following requirements:

    A compatible operating system (Windows, macOS, or Linux)
    Internet access for downloading software packages

Installing G++ and CMake
# Windows

## G++:

    Download and install MinGW or TDM-GCC.
    During the installation, make sure to select the g++ component.
    Add the bin directory of MinGW or TDM-GCC to your system's PATH environment variable.

## CMake:

    Download the latest version of CMake from the official website.
    Run the installer and follow the on-screen instructions.
    Ensure to select the option to add CMake to the system PATH.

# macOS

## G++:
```bash
brew install gcc
```

## CMake:

```bash
brew install cmake
```

# Linux (Ubuntu/Debian)

## G++:
 
```bash
sudo apt-get update
sudo apt-get install g++
```
## CMake:

``` bash
sudo apt-get install cmake
```


# Verifying the Installation

### After installation, you can verify the installation of G++ and CMake by checking their versions:
 
```bash
g++ --version
cmake --version
```
 