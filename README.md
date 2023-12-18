# TankWar

***

## 项目介绍 Project introduction
BUAA  2023秋单片机基础大作业

使用STM32G474RE开发板，配合助教 zyy 的 PCB 板实现 **坦克动荡** 游戏

## 项目贡献者 contributors
* 张尚谋
* 王博冉
* 曾楚翔
* copilot
* zyy - 助教
* ywth - 助教

## 文件结构 file structure

![image](Images/FileStructure.svg)

## 文件介绍 file introduction
|      文件名      |     功能     |  主要贡献者  |
|:-------------:|:----------:|:-------:|
|     main      |   各板载外设    | CubeMx  |
|     audio     |   音频宏定义    |   zyy   |
|    global     | 通用类型、宏、函数等 |   张尚谋   |
| lever_control |    摇杆映射    |   曾楚翔   |
|    record     | EEPROM 存档  |   曾楚翔   |
|     touch     |   触屏信息读取   |   王博冉   |
|     sound     |    音频播放    |   曾楚翔   |
|     crash     |    碰撞类型    |   王博冉   |
|  lcd_driver   |   LCD 驱动   | zyy、张尚谋 |
|      map      | 地图生成、撞墙判断  |   张尚谋   |
|   showScore   |    分数显示    |   曾楚翔   |
|     tank      |    坦克实现    |   张尚谋   |
|    bullet     |    子弹实现    |   王博冉   |
|     laser     |  2p 激光实现   |   张尚谋   |
|    target     |  1p 靶子实现   |   王博冉   |
|   mainMenu    |   主菜单逻辑    |   张尚谋   |





