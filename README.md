Vulkan 三角形
==========

### 安装依赖（`Conan version 2.0.6`）

```shell
conan install . --output-folder=cmake-build-debug --build=missing
```

### shader 编译

```shell
glslc shader.vert -o vert.spv
glslc shader.frag -o frag.spv
```

### 执行

> 拷贝 `shaders` 目录到 `cmake-build-debug/bin` 下