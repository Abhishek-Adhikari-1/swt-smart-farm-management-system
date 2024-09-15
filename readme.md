# Smart Farm Management System

The Smart Farm Management System is an application written in C to manage farm operations efficiently. It provides functionality for tracking crops, resources, and other aspects of farm management.

## Installation

To compile and run the program, you will need a C compiler. I recommend using the [GCC compiler](https://www.mingw-w64.org/downloads/) for Windows or an equivalent compiler for other systems.

### Steps to install:

1. Download and install the GCC compiler for your system.
2. Clone or download the repository:

    ```bash
    git clone https://github.com/Abhishek-Adhikari-1/swt-smart-farm-management-system.git
    ```

3. Navigate to the project directory, compile the code and run:
    ```bash
    gcc -o farm_manager main.c ; if($?) {.\farm_manager}
    ```

## Cross-Platform Pausing

The program includes a function to pause execution, but this varies depending on the operating system:

```c
void holdingTerminal()
{
    // Pausing in Windows
    system("pause");

    // Pausing in UNIX based systems -> Linux or MacOS
    //  system("read -n 1 -s")

    // Pausing in Enviroment Container -> Docker Container
    //  system("read -p 'Press Enter to continue...' var");
}
```

Make sure to uncomment the appropriate line for your platform and comment those line that is not related to you system before running the application.

## Author

[©Abhishek Adhikari](https://www.abhishek-adhikari.com.np/)
