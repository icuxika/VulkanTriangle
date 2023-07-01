Vulkan 三角形
==========

### 项目构建
- <a href="Windows-Build.md">Windows构建说明</a>


### shader 编译（构建后的程序需要spv文件才能正常运行）
> 执行如下脚本会在`shaders-bin`目录下生成`shader`对应的`spv`文件

#### Windows
```
.\shaders-generate.ps1
```

> 项目在`build`成功时会自动将`spv`文件拷贝到程序执行目录
