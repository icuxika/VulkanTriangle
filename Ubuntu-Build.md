## 基础环境 Windows 11 + WSL2（Ubuntu-22.04）
###  `wsl -v`  
```
WSL 版本： 1.2.5.0
内核版本： 5.15.90.1
WSLg 版本： 1.0.51
MSRDC 版本： 1.2.3770
Direct3D 版本： 1.608.2-61064218
DXCore 版本： 10.0.25131.1002-220531-1700.rs-onecore-base2-hyp
Windows 版本： 10.0.22621.1848
```


## 安装 Ubuntu Vulkan SDK
### Ubuntu 22.04 (Jammy Jellyfish) [Getting Started with the Ubuntu Vulkan SDK](https://vulkan.lunarg.com/doc/sdk/1.3.250.1/linux/getting_started_ubuntu.html)
```
wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-jammy.list http://packages.lunarg.com/vulkan/lunarg-vulkan-jammy.list
sudo apt update
sudo apt install vulkan-sdk
```

## 从源码安装 Cmake，apt提供的版本无法使用CMakePresets [cmake-3.26.4.tar.gz](https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4.tar.gz)
```
sudo apt install libssl-dev
./configure
make -j8
sudo make install
```

## 构建
### 构建项目时用到的依赖（根据报错缺啥装啥）
```
sudo apt install build-essential
sudo apt install pkg-config
sudo apt install libx11-xcb-dev libfontenc-dev libice-dev libsm-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxfixes-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxrandr-dev libxrender-dev libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxvmc-dev libxxf86vm-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev uuid-dev libxcb-cursor-dev libxcb-util-dev libxcb-util0-dev
```

### 构建 Debug （其他模式请查看<a href="Windows-Build.md">Windows构建说明</a>，与Windows构建使用的`Visual Studio 17 2022`相比，`Unix Makefiles`是一个`single-configuration generator`）
```
conan install . -s build_type=Debug --output-folder=cmake-build-debug --build=missing
cmake --preset conan-debug
cmake --build --preset conan-debug
```

### 运行（）
> 程序运行依赖于shaders文件位置，如果出现`failed to open file!`错误，可以注意下
```
cd cmake-build-debug
./VulkanTriangle
```