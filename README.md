Vulkan 三角形
==========

### 安装依赖

```shell
conan install . -s build_type=Debug --install-folder=cmake-build-debug --build
```

### shader 编译

```shell
glslc shader.vert -o vert.spv
glslc shader.frag -o frag.spv
```

### 执行

> 拷贝 `shaders` 目录到 `cmake-build-debug/bin` 下