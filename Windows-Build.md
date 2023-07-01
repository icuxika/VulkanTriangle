## 说明
因为使用了conan，以下命令中cmake-build-debug目录并不是CLion中默认为Debug配置的模式，conan通过CMakePresets在同一个目录中同时管理Release和Debug两种配置

## conan 文档
[CMakeToolchain: Building your project using CMakePresets](https://docs.conan.io/2/examples/tools/cmake/cmake_toolchain/build_project_cmake_presets.html)

## 快速构建
### `multi-configuration generator`
#### `Release`
```
conan install . --output-folder=cmake-build-debug --build=missing
cmake --preset conan-default
cmake --build --preset conan-release
```
#### `Debug`
```
conan install . -s build_type=Debug --output-folder=cmake-build-debug --build=missing
cmake --preset conan-default
cmake --build --preset conan-debug
```

### `single-configuration generator`
#### `Release`
```
conan install . --output-folder=cmake-build-debug --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
```
#### `Debug`
```
conan install . -s build_type=Debug --output-folder=cmake-build-debug --build=missing
cmake --preset conan-debug
cmake --build --preset conan-debug
```

## 完整构建说明
### 生成项目
> 对于`conanfile.txt`指定的依赖依据不同配置下载和构建不同的`Release`和`Debug`版本
#### 生成Release配置的项目
```
conan install . --output-folder=cmake-build-debug --build=missing
```
#### 生成Debug配置的项目
```
conan install . -s build_type=Debug --output-folder=cmake-build-debug --build=missing
```

### 配置预设
> 对于`Visual Studio 17 2022`这个`generator`是`multi-configuration generator`，一个`配置预设[configurePresets]`就可以对应多个`生成预设[buildPresets]`
```
cmake --preset conan-default
```
> 当使用了`single-configuration generator`时，就可能有多种选择，一个`配置预设[configurePresets]`对应一个`生成预设[buildPresets]`
```
cmake --preset conan-debug
```
```
cmake --preset conan-release
```

### 构建项目
> 要与前面选择的`Release`或`Debug`对应
#### 构建Release配置的项目
```
cmake --build --preset conan-release
```
#### 构建Debug配置的项目
```
cmake --build --preset conan-debug
```