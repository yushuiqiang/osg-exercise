// OSG_2_NodeSwitch.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


/*从NodeCallback类派生，并重构执行函数operator(),实现自定义的节点回调功能
定义名为CessnaCallback的节点更新回调，它使用getFrameNumber()随时取得当前的运行帧数
当帧数大于预先设定的切换值120时，使用setValue()执行子节点的切换*/
class CessnaCallback :public osg::NodeCallback
{
public:
	static const int _fireStartFrame = 120; //起火开始时间，即切换模型时的运行帧数，秒

	//虚函数。当回调动作发生时，将会执行这一操作符的内容，并将节点和访问器对象作为参数传入
	//重载第一个(),而(osg::Node *node, osg::NodeVisitor *nv)是该重载函数的参数表，前者为场景节点，后者为访问器对象，即访问器当前访问的节点
	virtual void operator()(osg::Node *node, osg::NodeVisitor *nv)
	{
		//dynamic_cast将一个基类对象指针(或引用)cast到继承类指针，dynamic_cast会根据基类指针是否真正指向继承类指针来做相应处理
		//dynamic_cast <type-id> (expression) 该运算符把expression转换成type-id类型的对象，Type-id 必须是类的指针、类的引用或者void*，它可以在执行期决定真正的类型
		//如果type-id是类指针类型，那么expression也必须是一个指针，如果 type-id 是一个引用，那么 expression 也必须是一个引用
		//dynamic_cast主要用于类层次间的上行转换(和static_cast效果一样)和下行转换(具有类型检查的功能，比static_cast更安全)，还可以用于类之间的交叉转换
		osg::Switch *cessnaSwitch = dynamic_cast<osg::Switch *>(node); 
		if (cessnaSwitch && nv)
		{
			//实例化类osg::FrameStamp
			//getFrameStamp()获取节点的帧数信息
			const osg::FrameStamp *frameStamp = nv->getFrameStamp();
			if (frameStamp)
			{
				//比较起火时的帧数和当前帧数，120帧以后关闭飞机模型cessna.osg开启起火后飞机模型cessnafire.osg
				if (_fireStartFrame < frameStamp->getFrameNumber()) //获取上一帧的帧号，即时间，秒
				{
					//setValue()执行子节点的切换
					cessnaSwitch->setValue(0, false);
					cessnaSwitch->setValue(1, true);
				}
			}
		}
		traverse(node, nv); //向下一个需要访问的节点推进
	}
};

int main(int argc, char **argv)
{
	//在osg智能指针中定义开关节点
	osg::ref_ptr<osg::Switch> root = new osg::Switch;
	//读取模型并将之添加到开关节点中
	//默认开启子节点飞机模型cessna.osg，默认关闭（切换后开启）子节点起火后的飞机模型cessnafire.osg
	root->addChild(osgDB::readNodeFile("cessna.osg"), true);
	root->addChild(osgDB::readNodeFile("cessnafire.osg"), false);
	//setUpdateCallback自定义回调类CessnaCallback作为更新回调传递给节点，设置人机交互回调为node->setEventCallback(new CessnaCallback)
	root->setUpdateCallback(new CessnaCallback);

	//实例化显示图像的类osgViewer::Viewer
	osgViewer::Viewer viewer;
	//设置viewer显示的场景
	viewer.setSceneData(root.get());
	//开始执行渲染操作，返回值一般为1，程序退出或出错返回0
	return viewer.run();
}

