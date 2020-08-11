#define _CRT_SECURE_NO_WARNINGS 1
#include"seqlist.h"
#include"bigint.h"

int main()
{
	BigInt bt1(199);
	BigInt bt2(10);
	BigInt bt(0);
	//bt1.LoadData(4);

	cout << "bt1 = ";
	bt1.ShowData();

	//Sleep(1000);
	//bt2.LoadData(4);
	cout << "bt2 = ";
	bt2.ShowData();
	clock_t start = clock();
	//BigInt::Add(bt, bt1, bt2);
	//BigInt::Sub(bt, bt1, bt2);
	//BigInt::Mul(bt, bt1, bt2);
	//BigInt::Div(bt, bt1, bt2);
	//BigInt::Mod(bt, bt1, bt2);
	BigInt::Square(bt, bt1);
	//BigInt::Pow(bt, bt1, bt2);
	clock_t end = clock();
	//bt = bt1 + bt2;
	//bt = bt1 - bt2;
	//bt = bt1 * bt2;
	//bt = bt1 / bt2;
	//bt1 += bt2;


	cout << "bt  = ";
	bt.ShowData();
	cout << "time:" << end - start<<endl;
	system("pause");
	return 0;
}

/*void Test_SeqList()
{
	SeqList<unsigned int>list;
	for (int i = 1; i <= 10; ++i)
		list.push_back(i);
	for (unsigned int i = 1; i <= 10; ++i)
		cout << list[i] << " ";
	cout << endl;

		list.push_front(10);
	for (unsigned int i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;

	    list.pop_back();
	for (unsigned int i = 1; i <= list.size(); ++i)
	    cout << list[i] << " ";
	cout << endl;

	    list.pop_front();
	for (unsigned int i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;

	cout << "back=" << list.back()<<endl;
	cout << "front=" << list.front()<<endl;

	list.reverse();
	for (unsigned int i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;

	list.sort();
	for (unsigned int i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;

	cout << list.find(5)<< endl;

	list.erase(5);
	for (unsigned int i = 1; i <= list.size(); ++i)
		cout << list[i] << " ";
	cout << endl;
}
int main()
{
	Test_SeqList();
	system("pause"); 
}*/