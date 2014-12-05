#pragma once

template<class T>
class Vect
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;

	Vect(){ create(); }
	explicit Vect(size_type n, const T& val = T()){create(n,val)}
	Vect(const Vect& v){ create(v.begin(), v.end()); }
	~Vect{ (uncreate(); }

	Vect& operator=(const Vect&);
	size_type size()const{ return limit - data; }
	T& operator[](size_type i){ return data[i]; }
	const T& operator[](size_type i)const { return data[i]; }
	iterator begin(){ return data; }
	const_iterator begin()const { return data; }
	iterator end(){ return limit; }
	const_iterator end() const { return limit; }

	void push_back(const T& val)
	{
		if (avail == limit)
			grow()
			unchecked_append(avl);
	}
public:

private:
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);
	void uncreate();
	void grow();
	void unchecked_append(const T&);
	allocator<T> alloc;


	iterator data;	//first element
	iterator avail;
	iterator limit;	//last element
};

template<class T>
Vect<T>& Vect<T>::operator=(const Vect& r)
{
	//assign self?
	if (&r != this)
	{
		//delete left object element
		uncreate();
		//copy to left
		create(r.begin(), r.end());
	}
	return *this;
}

template<class T>
void Vect<T>::create()
{
	data = avail = limit = 0;
}

template<class T>
void Vect<T>::create(size_type n, const T& val)
{
	data = alloc.allocate(n);
	limit = avail = data + n;
	uninitialized_fill(data, limit, val);
}

template<class T>
Vect<T>::create(const_iterator i, const_iterator j)
{
	data = alloc.allocate(j - i);
	limit = avail = uninitialized_copy(i, j, data);
}

template<class T>
void Vect<T>::uncreate()
{
	if (data)
	{
		iterator it = avail;
		while (it != data)
		{
			alloc.destory(--i);
		}
			alloc.deallocate(data, limit - data);
		
	}
	data = limit = avail = 0;
}

template<class T>
void Vect<T>::grow()
{
	size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = uninitialized_copy(data, avail, new_data);
	uncreate();
	data = new_data;
	avail = new_avail;
	limit = data + new_size;

}

template<class T>
void Vect<T>::uncreate_append(const T& val)
{
	alloc.construct(avail++, val);
}




















