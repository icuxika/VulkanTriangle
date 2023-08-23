Vulkan 三角形
==========

### 项目构建
- <a href="Windows-Build.md">Windows构建说明</a>
- <a href="Ubuntu-Build.md">WSL2（Ubuntu-22.04）</a>

### `vcpkg.json`中`builtin-baseline`的来源
在 vcpkg 项目根目录下，执行以下命令获取
```
git rev-parse HEAD
```

### shader 编译（构建后的程序需要spv文件才能正常运行）
> 执行如下脚本会在`shaders-bin`目录下生成`shader`对应的`spv`文件

#### Windows
```
.\shaders-generate.ps1
```

#### Ubuntu
```
zsh shaders-generate.sh
```

> 项目在`build`成功时会自动将`spv`文件拷贝到程序执行目录
