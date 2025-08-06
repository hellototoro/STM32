# STM32 Embedded Projects

基于 STM32H750XBH6 微控制器的嵌入式开发项目集合，主要针对 ART-PI 开发板。

## 项目结构

```text
STM32/
├── board/art-pi/projects/
│   ├── bootloader/          # 引导加载程序
│   ├── applications/        # 主应用程序
│   └── applications/simulation/  # LVGL 仿真程序
└── README.md
```

## 硬件平台

### ART-PI 开发板

- **主控芯片**: STM32H750XBH6 (ARM Cortex-M7, 400MHz)
- **Flash**: 外置 QSPI Flash (W25Q64)
- **RAM**: 1MB SRAM
- **显示**: LCD 接口支持
- **无线**: WiFi 模块 (AP6212)
- **项目主页**: [ART-PI项目地址](https://art-pi.github.io/website/)

## 子项目说明

### 1. Bootloader (引导程序)

位置: `board/art-pi/projects/bootloader/`

- **功能**: 系统引导加载器
- **Flash地址**: 0x08000000
- **构建系统**: CMake + Ninja
- **工具链**: ARM Compiler 6.24 或 GCC 11+

**编译命令**:

```bash
cd board/art-pi/projects/bootloader/build
cmake --preset=default ..
ninja
```

### 2. Applications (主应用程序)

位置: `board/art-pi/projects/applications/`

- **功能**: 主要应用程序，包含 LVGL GUI 和各种外设驱动
- **Flash地址**: 0x90000000 (QSPI Flash)
- **特性**:
  - LVGL 8.x 图形界面
  - WiFi 连接管理
  - FreeRTOS 实时操作系统
  - FatFS 文件系统
  - 多种外设驱动 (LCD, 触摸, SD卡等)

**主要组件**:

- **LVGL**: 嵌入式图形库
- **WiFi**: 基于 AP6212 模块的无线连接
- **FreeRTOS**: 实时操作系统
- **CLI**: 命令行接口
- **外设驱动**: LCD, 触摸屏, SD卡, W25Qxx Flash

**编译命令**:

```bash
cd board/art-pi/projects/applications/build
cmake --preset=default ..
ninja
```

**编译优化**:

- 支持 ARM Compiler 6.24 和 GCC 11+
- 程序大小: ~730KB Code + ~1MB RO-data

### 3. Simulation (LVGL 仿真)

位置: `board/art-pi/projects/applications/simulation/`

- **功能**: LVGL 图形界面的 PC 端仿真
- **平台**: Windows/Linux
- **工具链**: 系统默认编译器 (GCC/MSVC)

**编译命令**:

```bash
cd board/art-pi/projects/applications/simulation/build
cmake ..
make  # 或 ninja
```

## 开发环境配置

### 必需工具

1. **ARM 工具链**: 以下任一版本
   - ARM Compiler 6.24 或更高版本
   - GCC ARM Embedded 11.x 或更高版本 (arm-none-eabi-gcc)
2. **构建工具**: CMake 3.22+ 和 Ninja
3. **烧录工具**: STM32CubeProgrammer
4. **IDE** (可选): VS Code + CMake 插件

**工具链说明**:

- **ARM Compiler 6**: Keil MDK 官方编译器，优化效果好，支持专业调试
- **GCC ARM Embedded**: 开源免费，广泛兼容，社区支持丰富
- 项目已配置 CMake 预设，支持两种工具链自动切换

### VS Code 配置

项目包含完整的 VS Code 配置:

- `.vscode/tasks.json` - 构建和烧录任务
- `CMakePresets.json` - CMake 预设配置
- `compile_commands.json` - 代码智能提示

### 烧录配置

**Bootloader 烧录**:

```bash
STM32_Programmer_CLI --connect port=swd --download bootloader.elf --start
```

**Applications 烧录**:

```bash
STM32_Programmer_CLI --connect port=swd --download applications.elf 0x90000000 -el ART-Pi_W25Q64.stldr -hardRst -rst --start
```

## 功能特性

### GUI 界面

- 基于 LVGL 8.x 的现代化界面
- 支持多屏幕切换
- 触摸操作支持
- 自定义主题和样式

### 网络连接

- WiFi 连接管理
- TCP/IP 协议栈 (LwIP)
- 网络配置界面
- Ping 测试功能

### 文件系统

- FatFS 支持
- SD卡读写
- 文件管理操作

### 实时系统

- FreeRTOS 任务调度
- 任务间通信
- 内存管理
- 定时器服务

## 编译说明

### 警告优化

项目经过链接警告优化:

- ✅ CMake依赖修复 - 解决循环依赖
- ✅ 编译器标志优化 - 禁用非关键警告

### 内存布局

```text
0x08000000 - 0x0801FFFF : Bootloader (128KB)
0x90000000 - 0x907FFFFF : Applications (8MB QSPI Flash)
0x20000000 - 0x2001FFFF : SRAM1 (128KB)
0x30000000 - 0x30047FFF : SRAM2 (288KB) 
0x38000000 - 0x3800FFFF : SRAM4 (64KB)
```

## 许可证

本项目采用开源许可证，具体请查看各子项目的许可证文件。

## 贡献指南

1. Fork 本项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 创建 Pull Request

## 联系方式

- 项目维护者: hellototoro
- 问题反馈: 通过 GitHub Issues
