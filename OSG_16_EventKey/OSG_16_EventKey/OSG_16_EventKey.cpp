// OSG_16_EventKey.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


/*
 *定义人机交互事件处理器
 */
class KeyboardHandler :public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *)
	{
		osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer *>(&aa); //将动作适配器us转换为场景视图，通常作为动作适配器的对象都是当前的场景视图
		if (!viewer)
			return false;

		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN:
			//按下空格键时，获取窗口大小，并把鼠标光标限制到窗口中心 
			//KEY_Space 空格
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)
			{
				//获取事件所来源的图形窗口的位置和尺寸信息，如果该事件来源于窗口的话
				int width = ea.getWindowWidth();
				int height = ea.getWindowHeight();
				viewer->requestWarpPointer(width * 0.5, height * 0.5);
			}
			else
			{
				//按下1或2键，切换开关节点的两个子节点，按1键显示正常飞机，按2键显示着火飞机
				//主键盘上的字母键、数字键，及各种标点符号键都以各自本身来代表，如下面的1就代表主键盘上的1
				osg::Switch *root = dynamic_cast<osg::Switch *>(viewer->getSceneData());
				if (!root)
					return false;
				if (ea.getKey() == '1')
				{
					root->setValue(0, true);
					root->setValue(1, false);
				}
				else if (ea.getKey() == '2')
				{
					root->setValue(0, false);
					root->setValue(1, true);
				}
				return true;
			}
			break;
		default:break;
		}
		return false;
	}
};

int main()
{
	osg::ref_ptr<osg::Switch> root = new osg::Switch();
	root->addChild(osgDB::readNodeFile("cessna.osg"), true);
	root->addChild(osgDB::readNodeFile("cessnafire.osg"), false);

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	viewer->addEventHandler(new KeyboardHandler); //将时间处理器使用addEventHandler()方法传递给当前视景器
	viewer->setSceneData(root.get());
	viewer->realize();

	return viewer->run();
}

