/*
	2016年8月9日17:44:34
	有时候不调用复制构造函数倒是不行的
*/
# include <iostream>
using namespace std;

class Hello
{
public:
	Hello(int x){i = x;cout << "调用构造函数,创建了一个对象...\n";}
	Hello(Hello&a){i = a.i;cout << "执行复制构造函数，创建该对象的一个副本。\n";}
	~Hello(){cout << "析构函数运行中...\n";}
	int get()const{return i;}
private:
	int i;
};

//返回值类型为引用时，输出不正常。但是当删除&之后，输出正常。因为按值返回会调用复制构造函数创建a的副本，main函数中r作为了a副本的别名
Hello func()
{
	cout << "跳转到func()函数中!\n" << endl;
	Hello a(50);
	cout << "对象a的地址：" << &a << endl;
	return a;
}
int main (void)
{
	Hello & r = func();//由于func()函数执行完毕后对象a的空间就会释放，所以引用r虽是a的别名，但是没办法使用已经释放的a的空间
	//Hello * s = &func();
	cout << "对象a的副本的地址为:" << &r << endl;
	cout << r.get() << endl;
	//cout << s->get() << endl;

	return 0;
}

/*
	引用运行结果：

		跳转到func()函数中!

		调用构造函数,创建了一个对象...
		对象a的地址：0018FEC0
		执行复制构造函数，创建该对象的一个副本。			//按值返回会创建副本
		析构函数运行中...                                  //func()函数执行完后，释放局部对象a
		对象a的副本的地址为:0018FF2C
		50
		析构函数运行中...								//释放的是a副本的内存
		Press any key to continue

	指针运行结果：

		跳转到func()函数中!

		调用构造函数,创建了一个对象...
		对象a的地址：0018FECC
		执行复制构造函数，创建该对象的一个副本。
		析构函数运行中...							 //func()函数执行完后，释放局部对象a
		析构函数运行中...							//func()函数执行完后，释放局部对象a的副本
		对象a的副本的地址为:0018FF3C
		50
		Press any key to continue



由于对于引用来说，引用的若是一个临时变量，这个临时变量的存在时间不会小于引用的存在时间，而当main函数执行完毕时，引用r生命周期才截止，所以
临时变量（a的副本）的生命周期也截止，此时才调用析构函数释放a的副本的内存。

但是对于指针来说，就没有这个特点。当func()函数执行完毕返回a的副本之际，就会调用析构函数，析构对象a的副本.但是副本的内存只要未被系统分配出去，
数据就依旧存在，而且只要知道地址就可以使用，所以还是会输出a的已经释放的副本的成员值。
*/