# USnake 🐍

USnake 是一个使用 C++ 和 Qt 开发的简约贪吃蛇游戏，支持键盘操作、计分、食物生成与碰撞检测，旨在提供清晰的游戏逻辑与界面绘制示范。

## ✨ 功能特色

- ✅ 使用 Qt Widgets 实现自定义绘制与交互
- ✅ 支持键盘控制方向（↑ ↓ ← →）
- ✅ 自适应游戏区域大小 (TODO) 与网格绘制
- ✅ 游戏结束弹窗提示
- ✅ 面向可扩展的架构设计

## 🚀 快速开始

### 构建依赖

- Qt 6.x（推荐使用官方安装器）
- CMake 3.16+
- C++20 编译器（如 g++、clang++、MSVC）

### 构建项目（使用 CMake）

```bash
git clone https://github.com/Siaospeed/USnake.git
cd USnake
mkdir build && cd build
cmake ..
make
./USnake
```

## 📁 项目结构

```
USnake/
├── include/          # 头文件
├── src/              # 源码文件
├── assets/           # 游戏贴图资源（如有）
├── CMakeLists.txt    # CMake 构建配置
└── README.md         # 项目说明
```

## 📜 许可证
本项目使用 Apache License 2.0 开源。

你可以自由使用、修改、分发本项目，但必须：

- 保留原作者署名（Siaospeed）
- 在引用时注明原项目来源

```
Copyright 2025 Siaospeed
```

## 🙋‍♂️ 联系与贡献
欢迎 Issue 或 Pull Request。如果你在使用中有建议或想法，也欢迎提出交流！
