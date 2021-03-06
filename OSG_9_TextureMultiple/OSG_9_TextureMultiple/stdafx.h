// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
#include <osg/Node>  
#include <osg/Geometry>  
#include <osg/Geode> //是个几何节点，可以说是一个几何Group节点，一般的可绘制几何体都是通过它来传向root进行渲染，是OSG几何绘制的最高管理节点  
#include <osg/Group> //对节点起到组织作用，一般作为父节点或者根节点出现

#include <osg/Texture2D> //二维纹理映射类
#include <osg/TexGen> //指定用于自动生成纹理坐标的函数，可以设置纹理的计算方式是以物体坐标空间还是相机坐标空间来进行不同的计算
#include <osg/TexEnv> //设置当前纹理映射方式 

#include <osgDB/ReadFile>  
#include <osgDB/WriteFile>  

#include <osgViewer/Viewer>  

#include <osgUtil/Optimizer> 