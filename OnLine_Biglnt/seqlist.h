#pragma once
#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_

#include"common.h"

template<class Type>
class SeqList
{
public:
	typedef Type& reference;
	typedef const Type& const_reference;
public:
	SeqList(int sz = SEQLIST_DEFAULT_SIZE);
	SeqList(const SeqList<Type> &st);
	SeqList& operator=(const SeqList<Type> &st);
	~SeqList();
public:
	bool isfull()const;
	bool isempty()const;
public:
	void push_back(const Type &x);
	void push_front(const Type &x);
	void pop_back();
	void pop_front();
	reference front();
	reference back();
	const_reference back()const;
	const_reference front()const;
	size_t size()const;
	void reverse();
	void clear();
	void sort();
	int find(const Type &key);
	void erase(const Type &key);
public:
	reference operator[](unsigned int pos);
	const_reference operator[](unsigned int pos)const;
public:
	Symbol GetSymbol()const;
	void SetSymbol(Symbol sym);
protected:
	bool _Inc();
private:
	enum { SEQLIST_DEFAULT_SIZE = 20};
private:
	Type * base;
	size_t capacity;
	size_t len;
};

//////////////////////////////////////////////////////////////////////////////////
//实现顺序表的内容

template<class Type>
Symbol SeqList<Type>::GetSymbol()const
{	return big[0];}

template<class Type>
void SeqList<Type>::SetSymbol(Symbol sym)
{	big[0] = (Type)sym;}

template<class Type>
bool SeqList<Type>::_Inc()
{
	Type *new_base;
	try
	{
		new_base = new Type[capacity * 2 + 1];
	}
	catch (bad_alloc &e)
	{
		cout << "Out Of Memory." << endl;
		return false;
	}

	memset(new_base, 0, sizeof(Type)*(capacity * 2 + 1));
	memcpy(new_base, base, sizeof(Type)*(capacity + 1));
	capacity *= 2;

	delete[]base;
	base = new_base;

	return true;
}

template<class Type>//判满
bool SeqList<Type>::isfull()const
{	return len >= capacity;}

template<class Type>//判空
bool SeqList<Type>::isempty()const
{	return len == 0;}

template<class Type>//构造顺序表
SeqList<Type>::SeqList(int sz)
{
	capacity = sz > SEQLIST_DEFAULT_SIZE ? sz : SEQLIST_DEFAULT_SIZE;
	base = new Type[capacity+1];
	memset(base, 0, sizeof(Type)*(capacity + 1));
	len = 0;
}

template<class Type>//析构
SeqList<Type>::~SeqList()
{
	delete[]base;
	base = NULL;
	capacity = len = 0;
}

template<class Type>//拷贝构造
SeqList<Type>::SeqList(const SeqList<Type> &st)
{
	capacity = st.capacity;
	base = new Type[sizeof(Type)*(capacity + 1)];
	memset(base, 0, sizeof(Type)*(capacity + 1));
	memcpy(base, st.base, sizeof(Type)*(st.len + 1));
	len = st.len;
}

template<class Type>//赋值运算符重载
SeqList<Type>&::SeqList<Type>::operator=(const SeqList<Type> &st)
{
	if (this != &st)
	{
		if (capacity < st.len)
		{
			Type *new_base = new Type[st.capacity + 1];
			delete[]base;
			base = new_base;
			capacity = st.capacity;
		}
		memcpy(base, st.base, sizeof(Type)*(st.len + 1));
		len = st.len;
	}
	return *this;
}


template<class Type>//尾插
void SeqList<Type>::push_back(const Type &x)
{
	if (isfull()&&!_Inc())
		ERR_EXIT("push_back");
	base[++len] = x;

}
template<class Type>//头插
void SeqList<Type>::push_front(const Type &x)
{
	if(isfull() && !_Inc())
		ERR_EXIT("push_front");
	for (size_t i = len; i >= 1; --i)
		base[i + 1] = base[i];
	base[1] = x;
	len++;
}

template<class Type>//求长度
size_t SeqList<Type>::size()const
{return len;}

template<class Type>//尾删
void  SeqList<Type>::pop_back()
{
	if(isempty())
		ERR_EXIT("pop_back");
	len--;
}

template<class Type>//头删
void  SeqList<Type>::pop_front()
{
	if(isempty())
		ERR_EXIT("pop_front");
	for (size_t i = 1; i < len; ++i)
	{
		base[i] = base[i + 1];
	}
	len--;
}

template<class Type>//取头元素
typename SeqList<Type>::reference SeqList<Type>::front()
{
	if(isempty())
		ERR_EXIT("front");
	return base[1];
}

template<class Type>//取尾元素
typename SeqList<Type>::reference SeqList<Type>::back()
{
	if (isempty())
		ERR_EXIT("back");
	return base[len];
}

template<class Type>
typename SeqList<Type>::const_reference SeqList<Type>::front()const
{
	if (isempty())
		ERR_EXIT("front");
	return base[1];
}

template<class Type>
typename SeqList<Type>::const_reference SeqList<Type>::back()const
{
	if (isempty())
		ERR_EXIT("back");
	return base[len];
}


template<class Type>//重载[]
typename SeqList<Type>::reference SeqList<Type>::operator[](unsigned int pos)
{
	assert(pos >= 1 && pos <= len);
	return base[pos];
}

template<class Type>//重载[]
typename SeqList<Type>::const_reference SeqList<Type>::operator[](unsigned int pos)const
{
	assert(pos >= 1 && pos <= len);
	return base[pos];
}

template<class Type>//逆置顺序表
void SeqList<Type>::reverse()
{
	if (size() <= 1)
		return;
	size_t start = 1, end = len;
	while (start<end)
	{
		Type tmp = base[end];
		base[end] = base[start];
		base[start] = tmp;
		start++;
		end--;
	}
}

template<class Type>//清除
void SeqList<Type>::clear()
{	len = 0;}

template<class Type>//排序
void SeqList<Type>::sort()
{
	if (size() <= 1)
		return;
	for (size_t i = 0; i < len; ++i)
	{
		for (size_t j = 1; j <=len - i - 1; ++j)
			if (base[j] > base[j + 1])
				Swap(base[j], base[j + 1]);
	}
}

template<class Type>//顺序查找
int SeqList<Type>::find(const Type &key)
{
	if (size() <= 1)
		return -1;
	for (size_t i = 1; i <= len; ++i)
		if (base[i] == key)
			return i;
	return -1;
}

template<class Type>//按值删除
void SeqList<Type>::erase(const Type &key)
{
	int pos = find(key);
	if (pos == -1)
		return;
	for (size_t i = pos; i <= len; ++i)
		Swap(base[i], base[i + 1]);
	pop_back();
}
#endif/*_SEQ_LIST_H_*/