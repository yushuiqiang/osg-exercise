// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
#include <osg/Geode>
#include <osg/Geometry>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

//osgUtil 工具类库，提供通用的共用类，用于操作场景图形及内容，如更新、裁剪、遍历、数据统计及场景图的一些优化。包括Delaunay三角面绘制功能、法线生成功能等。
//SmoothingVisitor 快速法线生成工具
#include <osgUtil/SmoothingVisitor>

#include <osg/Texture2D>