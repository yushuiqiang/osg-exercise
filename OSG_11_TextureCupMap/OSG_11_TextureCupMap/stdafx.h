// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
#include <osg/Geometry> 
#include <osg/Geode>    

#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/Matrix>

#include <osg/ShapeDrawable> //预定义几何体类，派生自osg::Drawable类。OSG中使用该类来将OSG内嵌的预定义几何体与osg::Drawable关联以渲染这些几何体
#include <osg/Transform> //一个组节点，所有子节点都通过4x4矩阵进行变换，通常用于在场景中定位对象，生成轨迹球功能或用于动画
#include <osg/NodeCallback > //节点更新回调
#include <osg/Depth> //封装OpenGL glDepthFunc / Mask / Range函数
#include <osg/CullFace>

#include <osg/TexMat>
#include <osg/TexGen> //指定用于自动生成纹理坐标的函数，可以设置纹理的计算方式是以物体坐标空间还是相机坐标空间来进行不同的计算
#include <osg/TexEnv>
#include <osg/TextureCubeMap> //立方体纹理映射

#include <osgViewer/Viewer>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>