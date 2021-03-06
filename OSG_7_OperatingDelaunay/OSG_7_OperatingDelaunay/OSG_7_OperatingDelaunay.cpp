// OSG_7_OperatingDelaunay.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


/*
创建顶点数组并添加数据
设置其他相关属性（可选）
创建osgUtil::DelaunayTriangulator类对象并生成三角网
创建几何体对象，把三角网类对象生成的绘制图元添加到几何体中
按w键显示网格化模型，可以看出网格密度不同
由于光照条件默认开启，旋转模型可以看出不同部位亮度显示不同
按l键显示关闭光照，旋转模型，可以看出亮度不变
*/

osg::Drawable *createTriangulate()
{
	//创建顶点数组
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();
	//不同于前面例子中添加数组数据的方法，先获取顶点的值并设置为数组，然后将数组值添加到顶点数组
	//设置顶点的值
	float vertex[][3] = { -5.0f,-5.0f, 0.4f,
		1.0f, -5.6f, 0.0f,
		5.0f, -4.0f, -0.5f,
		-6.2f, 0.0f, 4.2f,
		-1.0f,-0.5f, 4.8f,
		4.3f, 1.0f, 3.0f,
		-4.8f, 5.4f, 0.3f,
		0.6f, 5.1f,-0.8f,
		5.2f, 4.5f, 0.1f };
	//计算顶点数组的大小
	unsigned int n = sizeof(vertex) / sizeof(float[3]);
	//添加顶点数据
	for (unsigned int i = 0; i < n; i++)
	{
		coords->push_back(osg::Vec3(vertex[i][0], vertex[i][1], vertex[i][2]));
	}

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array();
	//添加颜色数据  
	color->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	color->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	color->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	color->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	color->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	color->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	color->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	color->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	color->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));

	//创建Delaunay三角网对象
	osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator(coords.get());
	//生成三角网
	dt->triangulate();

	//创建几何体
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//设置顶点数组
	geometry->setVertexArray(coords.get());
	//设置颜色数组
	geometry->setColorArray(color.get());
	//设置颜色的绑定方式为单个顶点
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	//添加到绘图基元
	geometry->addPrimitiveSet(dt->getTriangles());

	return geometry.release();
}

int main()
{
	//添加到叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(createTriangulate());

	//添加到根节点
	osg::ref_ptr<osg::Group> root = new osg::Group();
	root->addChild(geode.get());

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	//方便查看在多边形之间切换，以查看三角网
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
	viewer->setSceneData(root.get());
	viewer->realize();
	return viewer->run();
}

