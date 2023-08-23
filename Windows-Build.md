### 构建命令
> 关于使用 vcpkg 清单模式 + cmake-presets 来构建C++项目的细节，可以查看[vcpkg-cmake-presets](https://github.com/icuxika/vcpkg-cmake-presets)项目的演示，如下是使用随Visual Studio一起安装的`clang-cl`编译工具来构建项目的命令
```
cmake --preset clang-cl-user
cmake --build --preset clang-cl-release
```

### 字符乱码问题
- 使用`default`预设且`main.cpp`的文件格式为`UTF-8 with BOM`时没有乱码，但是文件格式为`UTF-8`时编译不会通过
- 使用`clang-cl`预设时无论`main.cpp`的文件格式为`UTF-8 with BOM`还是`UTF-8`都会乱码，但程序可以正常编译运行