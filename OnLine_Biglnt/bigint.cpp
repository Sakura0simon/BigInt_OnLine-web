#define _CRT_SECURE_NO_WARNINGS 1
#include"bigint.h"

ostream& operator<<(ostream &out, const BigInt &bt)//重载<<
{
	for (u_long i = bt.size(); i >= 1; --i)
		out << (int)bt[i];
	return out;
}

BigInt::BigInt(u_long value) //构造
{
	if (value == 0)
		push_back(0);
	while (value)
	{
		push_back(value % 10);
		value /= 10;
	}
}
///////////////////////////////////////////////////////////////
//装载数据
void BigInt::LoadData(int sz)
{
	clear();
	srand((int)time(0));
	for (int i = 0; i < sz; ++i)
	{
		u_char val = rand() % 10;
		while (i == sz - 1 && val == 0)   //解决头部出现0的情况
		{
			val = rand() % 10;
		}
		push_back(val);
	}
	clear_head_zero(*this);
}

void BigInt::clear_head_zero(BigInt &bt)//表头清零
{
	if (bt == 0)
		return;
	while (bt.back() == 0)
	{
		bt.pop_back();
		if(bt == 0)
			return;
	}
}

void BigInt::ShowData()const//打印数据
{
	for (size_t i = size(); i > 0; --i)
		cout << (int)big[i];
	cout << endl;
}

//////////////////////////////////////////////////////////
//插入删除
u_char BigInt::back()const//取尾元素
{	return big.back();}

void BigInt::push_back(u_char x)//尾插
{	 big.push_back(x);}

void BigInt::push_front(u_char x)//头插
{	big.push_front(x);}

void BigInt::pop_back()//尾删
{	big.pop_back();}

size_t BigInt::size()const//计算表长
{	return big.size();}

void BigInt::clear()//清除
{	big.clear();}

u_char BigInt::operator[](size_t pos)const//重载[]
{
	assert(pos >= 1 && pos <= size());
	return big[pos];
}

u_char& BigInt::operator[](size_t pos)
{
	assert(pos >= 1 && pos <= size());
	return big[pos];
}

/////////////////////////////////////////////////////////////////////////
//加法
u_char BigInt::AddItem(u_char a, u_char b, u_char &sign)
{
	u_char sum = 0;
	sum = a + b + sign;
	if (sum >= 10)
	{
		sign = 1;
		sum -= 10;
	}
	else
		sign = 0;
	return sum;
}

void BigInt::Add(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	u_long i, j;
	i = j = 1;
	u_char sum = 0, sign = 0;
	while (i <= bt1.size() && j <= bt2.size())
	{
		sum = AddItem(bt1[i], bt2[j], sign);
			bt.push_back(sum);
			i++;
			j++;
	}
	while (i <= bt1.size())
	{
		sum = AddItem(bt1[i], 0, sign);
		bt.push_back(sum);
		i++;
	}
	while (j <= bt2.size())
	{
		sum = AddItem(0, bt2[i], sign);
		bt.push_back(sum);
		j++;
	}
	if (sign > 0)
		bt.push_back(sign);
}

/////////////////////////////////////////////////////////////////////////////////////
//减法
u_char BigInt::SubItem(u_char a, u_char b, u_char &sign)
{
	u_char sub = 0;
	if (a >= b + sign)
	{
		sub = a - b;
		sign = 0;
	}
	else 
	{
		sub = (a + 10) - (b + sign);
		sign = 1;
	}
	return sub;
}

void BigInt::Sub(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	if (bt1 < bt2)
		return;
	else if (bt1 == bt2)
		bt = 0;
	bt.clear();

	u_long i, j;
	i = j = 1;
	u_char sub, sign = 0;

	while (i <= bt1.size() && j <= bt2.size())
	{
		sub = SubItem(bt1[i], bt2[j], sign);
		bt.push_back(sub);
		i++;
		j++;
	}
	while (i <= bt1.size())
	{
		sub = SubItem(bt1[i], 0, sign);
		bt.push_back(sub);
		i++;
	}
}

/////////////////////////////////////////////////////////////////////
//乘法
void BigInt::MulItem(BigInt &bt, const BigInt &bt1, u_char x)
{
	u_long i = 1;
	u_char res, sign = 0;
	while (i <= bt1.size())
	{
		res = bt1[i] * x+sign;
		sign = res / 10;
		res %= 10;
		bt.push_back(res);
		i++;
	}
	if (sign > 0)
		bt.push_back(sign);
}

void BigInt::MoveAdd(BigInt &bt, const BigInt &bt1, u_long offset)
{
	u_long i = offset;
	u_char sign = 0;
	u_long j = 1;
	while (i <= bt.size() && j <= bt1.size())//从偏移位置与当前操作数最低位开始相加
	{
		bt[i] = AddItem(bt[i], bt1[j], sign);
		i++;
		j++;
	}
	while (sign > 0 && i <= bt.size())//bt未加完，bt1加完
	{
		bt[i] = AddItem(bt[i], 0, sign);
		i++;
	}
	while (j <= bt1.size())//bt加完，bt1未加完
	{
		u_char sum = AddItem(0, bt1[j], sign);
		bt.push_back(sum);
		j++;
	}
	if (sign > 0)
		bt.push_back(sign);
}

void BigInt::Mul(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	BigInt tmp;
	tmp.clear();
	for (u_long i = 1; i <= bt2.size(); ++i)
	{
		MulItem(tmp, bt1, bt2[i]);
		MoveAdd(bt, tmp, i);
		tmp.clear();
	}
}

/////////////////////////////////////////////////////////////////////
//除法
void BigInt::Div(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	bt.clear();
	if (bt1 < bt2)
		bt = 0;
	else if (bt1 == bt2)
		bt = 1;
	else
	{
		u_long bt1_len = bt1.size();
		u_long bt2_len = bt2.size();
		int k = bt1_len - bt2_len;

		BigInt tmp;
		tmp.clear();
		for (u_long i = 1; i <= bt2.size(); ++i)
			tmp.push_back(bt1[i + k]);//取与被除数相同的位数

		while (k >= 0)
		{
			u_char div = 0;//记录商的值
			while (tmp >= bt2)
			{
				tmp -= bt2;
				div++;
				clear_head_zero(tmp);
			}
			bt.push_front(div);
			if (k > 0)
			{
				tmp.push_back(bt1[k]);//补一位继续除
				clear_head_zero(tmp);
			}
			--k;
		}
		clear_head_zero(bt);
		cout << "remainder =" << tmp<<endl;
	}
}

///////////////////////////////////////////////////////////////////////
//取模
void BigInt::Mod(BigInt &bt, const BigInt &bt1, const BigInt &bt2)
{
	bt.clear();
	if (bt1 < bt2)
		bt = bt1;
	else if (bt1 == bt2)
		bt = 0;
	else
	{
		u_long bt1_len = bt1.size();
		u_long bt2_len = bt2.size();
		int k = bt1_len - bt2_len;

		BigInt tmp;
		tmp.clear();
		for (u_long i = 1; i <= bt2.size(); ++i)
			tmp.push_back(bt1[i + k]);
		while (k >= 0)
		{
			while (tmp >= bt2)
			{
				tmp -= bt2;
				clear_head_zero(tmp);
			}
			if (k > 0)
			{
				tmp.push_front(bt1[k]);
				clear_head_zero(tmp);
			}
			--k;
		}
		bt = tmp;
		clear_head_zero(bt);
	}
}

//求平方
void BigInt::Square(BigInt &bt, const BigInt &bt1)
{
	BigInt::Mul(bt, bt1, bt1);
}

//幂的快速求解法
void BigInt::Pow(BigInt &bt, const BigInt &bt1, const BigInt &bt2) 
{
	bt = 1;
	for (BigInt i = 0; i < bt2; ++i)
		bt *= bt1;
}

//////////////////////////////////////////////////
//重载方法
BigInt& BigInt::operator++()
{
	u_long i = 1;
	u_char sign = 1;
	while (sign > 0 && i <= size())
	{
		(*this)[i] = AddItem((*this)[i], 0, sign);
		i++;
	}
	if (sign > 0)
		push_back(sign);
	return *this;
}

BigInt  BigInt::operator++(int)
{
	BigInt tmp = *this;
	++*this;
	return tmp;
}

BigInt& BigInt::operator--()
{
	u_long i = 1;
	u_char sign = 1;
	while (sign > 0 && i <= size())
	{
		(*this)[i] = SubItem((*this)[i], 0, sign);
		i++;
	}
	clear_head_zero(*this);
	return *this;
}
BigInt  BigInt::operator--(int)
{
	BigInt tmp = *this;
	--*this;
	return tmp;
}

BigInt& BigInt::operator+=(const BigInt &bt)
{
	u_long i, j;
	i = j = 1;
	u_char sign = 0;
	while (i <= size() && j <= bt.size())
	{
		(*this)[i] = AddItem((*this)[i], bt[j], sign);
		i++;
		j++;
	}
	while (sign > 0 && i <= size())
	{
		(*this)[i] = AddItem((*this)[i], 0, sign);
		i++;
	}
	while (j <= bt.size())
	{
		u_char sum = AddItem(0, bt[j], sign);
		push_back(sum);
		j++;
	}
	if (sign > 0)
		push_back(sign);

	return *this;
}

BigInt& BigInt::operator-=(const BigInt &bt)
{
	u_long i, j;
	i = j = 1;
	u_char sign = 0;
	while (i <= size() && j <= bt.size())
	{
		(*this)[i] = SubItem((*this)[i], bt[j], sign);
		i++;
		j++;
	}
	while (sign > 0)
	{
		(*this)[i] = SubItem((*this)[i], 0, sign);
		i++;
	}
	return *this;
}

BigInt& BigInt::operator*=(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Mul(tmp, *this, bt);
	*this = tmp;
	return *this;
}
BigInt& BigInt::operator/=(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Div(tmp, *this, bt);
	*this = tmp;
	return *this;
}
BigInt& BigInt::operator%=(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Mod(tmp, *this, bt);
	*this = tmp;
	return *this;
}

BigInt BigInt::operator+(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Add(tmp, *this, bt);
	return tmp;
}
BigInt BigInt::operator-(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Sub(tmp, *this, bt);
	return tmp;
}
BigInt BigInt::operator*(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Mul(tmp, *this, bt);
	return tmp;
}
BigInt BigInt::operator/(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Div(tmp, *this, bt);
	return tmp;
}
BigInt BigInt::operator%(const BigInt &bt)
{
	BigInt tmp;
	BigInt::Mod(tmp, *this, bt);
	return tmp;
}

/////////////////////////////////////////////////////////////
//比较运算符重载
bool BigInt::operator<(const BigInt &bt)const
{
	if (size() < bt.size())
		return true;
	else if (size() > bt.size())
		return false;

	for (u_long i = bt.size(); i >= 1; --i)
	{
		if ((*this)[i] > bt[i])
			return false;
		else if (big[i] < bt[i])
			return true;
	}
	return false;
}

bool BigInt::operator>=(const BigInt &bt)const
{
	return !(*this < bt);
}

bool BigInt::operator>(const BigInt &bt)const
{
	if (size() > bt.size())
		return true;
	else if (size() < bt.size())
		return false;

	for (u_long i = bt.size(); i >= 1; --i)
	{
		if ((*this)[i] > bt[i])
			return true;
		else if (big[i] < bt[i])
			return false;
	}
	return false;
}

bool BigInt::operator<=(const BigInt &bt)const
{
	return !(*this > bt);
}

bool BigInt::operator==(const BigInt &bt)const
{
	if (size() != bt.size())
		return false;

	for (u_long i = 1; i <= bt.size(); ++i)
	{
		if ((*this)[i] != bt[i])
			return false;
	}
	return true;
}

bool BigInt::operator!=(const BigInt &bt)const
{
	return !(*this == bt);
}