### About the engine
Krux is a game engine (**_currently in development_**).

The engine is built using C++17, OpenGL, GLFW, and GLEW. This project uses [Premake5](https://premake.github.io/download) for build configuration and project generation.

Prerequisites
- Visual Studio 2019 or 2022
- Windows OS (Current configuration targets Windows x64)

### Installation & Generation

1. Clone the repository

```
git clone https://github.com/stapxd/Krux.git
cd Krux
```

2. Initialize submodules

```
git submodule update --init --recursive
```

3. Generate Project

Navigate to the scripts folder and run the batch file:

> If you want to use .bat file ensure that you have premake5.exe in `vendor\bin\premake` folder

```
# Runs Premake5 and creates the .sln file
GenerateProjects.bat
```

4. Build the Project

- Open Krux.sln in Visual Studio.
- Set your configuration (e.g., Debug or Release).
- Hit Build

### Acknowledgments 

Special thanks to [The Cherno](https://github.com/thecherno) and [Hazel Engine](https://github.com/TheCherno/Hazel/)
