#include <iostream>
#include <vector>
#include <QSharePtr.h>
#include <pthread.h>
#include <list>
#include <map>

using namespace std;


class Base
{
public:
	explicit Base(int i=0):x(i)
	{
		cout<<"Base()"<<endl;
	};
	virtual ~Base(){
		cout<<"~Base()"<<endl;
	};
	Base(const Base& a){
		cout<<"Base(Base&a)"<<endl;
		this->x = a.x;
	}
	Base(const QSharePtr<Base>& a){
		this->x = a->x;
		cout<<"Base(QSharePtr<Base>&a)"<<endl;
	}
	Base &operator=(const Base &a){
		cout<<"Base &operator=(Base&a)"<<endl;
		this->x = a.x;
		return *this;
	}
	virtual void print()
	{
		cout<<"Derive print(): "<<x<<endl;
	}
	int x;

};

class Derive:public Base
{
public:
	explicit Derive(int i=0):n(i),Base(i)
	{
		cout<<"Derive()"<<endl;
	};
	virtual ~Derive(){
		cout<<"~Derive()"<<endl;
	};
	Derive(const Derive& a):Base(a),n(a.n){
		cout<<"Derive(Derive&a)"<<endl;
	}
	Derive(const QSharePtr<Derive>& a):Base(*(a.get_pointer())){
		this->n = a->n;
		cout<<"Derive(QSharePtr<Derive>&a)"<<endl;
	}
	Derive &operator=(const Derive &a){
		cout<<"Derive &operator=(Derive&a)"<<endl;
		Base::operator=(a);
		return *this;
	}
	virtual void print()
	{
		cout<<"Derive print(): "<<n<<endl;
	}
	int n;

};

vector<QSharePtr<Base> > func()
{
	vector<QSharePtr<Base> > vec;
	
	QSharePtr<Derive> a = QSharePtr<Derive>(new Derive(10));
	QSharePtr<Derive> b = QSharePtr<Derive>(new Derive(11));
	a->x = 100;
	b->x = 100;
	vec.push_back(QSharePtr<Base>(new Derive(QSharePtr<Derive>(a))));
	vec.push_back(QSharePtr<Base>(new Derive(QSharePtr<Derive>(b))));
	return vec;
}
vector<Base* > func1()
{
	vector<Base* > vec;
	
	Derive *a = new Derive(10);
	Derive *b = new Derive(11);
	a->x = 100;
	b->x = 100;
	vec.push_back(new Derive(*a));
	vec.push_back(new Derive(*b));
	return vec;
}


class Simple {
 public:
  Simple() {
    std::cout << "Simple: " << std::endl; 
  }
 
  ~Simple() {
    std::cout << "~Simple: " << std::endl;
  }
  void PrintSomething() {
    cout << "PrintSomething: "<< endl;
  }
};

void TestAutoPtr2() {
  QSharePtr<Simple> my_memory(new Simple());
  //if (my_memory.get()) {
    QSharePtr<Simple> my_memory2(new Simple());   // 创建一个新的 my_memory2 对象
    my_memory2 = my_memory;             // 复制旧的 my_memory 给 my_memory2
    my_memory2->PrintSomething();       // 输出信息，复制成功
    my_memory->PrintSomething();        // 
  //}
  Simple *p = new Simple();
  QSharePtr<Simple> my_memory11(new Simple());
  //return 0;
  	
}
list<QSharePtr<Simple> > TestAutoPtrAdd(int n) {
  list<QSharePtr<Simple> > list_;
  for(int i=0; i<n ;i++)
  {
  	QSharePtr<Simple> ptr = QSharePtr<Simple>(new Simple());
  	list_.push_back(ptr);
  }
  return list_;
}

map<int, QSharePtr<Simple> > TestMap(int n)
{
	map<int, QSharePtr<Simple> > quant_data_map;
	for(int i=0; i<n ;i++)
  {
  	QSharePtr<Simple> ptr = QSharePtr<Simple>(new Simple());
  	quant_data_map[i] = ptr;
  }
  return quant_data_map;
}

int main(int argc, char **argv)
{
	//while(1) {
	/*list<QSharePtr<Simple> > ll;
	ll = TestAutoPtrAdd(10);
	sleep(1);
	//}
	list<QSharePtr<Simple> >::iterator it;
	for(it = ll.begin(); it != ll.end();)
	{
		(*it)->PrintSomething();
		it = ll.erase(it);
	}*/
	cout<<"+++++++++++++++++++++++"<<endl;
	
	map<int, QSharePtr<Simple> > quant_data_map;
	QSharePtr<Simple> iip;
	
	quant_data_map = TestMap(10);
	for(int i=0;i<10;i++)
	{
		map<int, QSharePtr<Simple> >::iterator iter = quant_data_map.find(i);
		if(iter == quant_data_map.end())
		{
			cout<<"coun't find "<<i<<endl;
		}
		else
		{
			iip = iter->second;
			iip->PrintSomething();
			quant_data_map.erase(iter);
		}
	}
	cout<<"+++++++++++++++++++++++"<<endl;
	
	/*vector<QSharePtr<Base> >::iterator it;
	Derive* d;
	vector<QSharePtr<Base> > vec = func();
	it = vec.begin();
	cout<<"--------------------------------"<<endl;
	for(;it != vec.end();++it)
	{
		d = dynamic_cast<Derive*>((*it).get_pointer());
		(*it).get_pointer()->print();
		cout<<"n :"<<d->n<<" x :"<<d->x<<endl;
		d->print();
	}*/
	
	getchar();
	return 0;
	/*vector<Base* >::iterator it;
	Derive* d;
	vector<Base* > vec = func1();
	it = vec.begin();
	cout<<"--------------------------------"<<endl;
	for(;it != vec.end();++it)
	{
		d = dynamic_cast<Derive*>((*it));
		(*it)->print();
		cout<<"n :"<<d->n<<" x :"<<d->x<<endl;
		d->print();
	}*/
}

