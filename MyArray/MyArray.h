#pragma once
#include <iostream>

template <typename T>
class MyArray
{
private:
	T* _arr;
	size_t _capacity = 1;
	size_t _size;
public:
	MyArray()
	{
		_size = 0;
		_capacity = 1;
		_arr = 0;
	}
	MyArray(int capacity) : _capacity(capacity) , _size(0)
	{
		if (_capacity >= 0)
			_arr = new T[_capacity]{};
		else
			throw std::exception("Wrong capacity");
	}
	MyArray(const MyArray& arr)
	{
		reallocate(arr.capacity());
		for (size_t i = 0; i != arr.size(); ++i)
		{
			_arr[i] = arr._arr[i];
			++_size;
		}
	}
	MyArray(MyArray&& arr) noexcept : _size(arr._size), _capacity(arr._capacity), _arr(arr._arr)
	{
		arr._capacity = 0;
		arr._size = 0;
		arr._arr = nullptr;
	}
	MyArray& operator=(const MyArray& data)
	{
		if (&data == this)
			return *this;
		resize(data.capacity());
		return *this;
	}
	MyArray& operator=(MyArray&& data) noexcept
	{
		delete[] _arr;
		_arr = data._arr;
		_size = data._size;
		_capacity = data._capacity;
		data._capacity = 0;
		data._size = 0;
		data._arr = nullptr;
		return *this;
	}
	void erase()
	{
		delete[] _arr;
		_arr = nullptr;
		_size = 0;
		_capacity = 1;
	}
	T operator[](size_t index) const
	{
		if (index >= 0 && index < _size)
		{
			return _arr[index];
		}
		else
			throw std::exception("Wrong index");
	}
	void reallocate(size_t newCapacity)
	{
		erase();
		if (newCapacity <= 1)
			return;
		_arr = new T[newCapacity];
		_capacity = newCapacity;
	}
	void resize(size_t newCapacity)
	{
		if (newCapacity == _capacity)
			return;
		if (newCapacity <= 0)
		{
			erase();
			return;
		}
		T* data = new T[newCapacity];
		if (_size > 0)
		{
			if (_size > newCapacity)
			{
				_size = newCapacity;
				for (size_t i = 0; i != _size; ++i)
					data[i] = _arr[i];
			}
			if (_size <= newCapacity)
			{
				for (size_t i = 0; i != _size; ++i)
					data[i] = _arr[i];
			}
		}
		delete[] _arr;
		_arr = data;
		_capacity = newCapacity;
	}
	void push_back(const T& value)
	{
		if (_size == _capacity)
			resize(_size * 2);
		_arr[_size] = value;
		++_size;
	}
	void insertBefore(size_t value, size_t index)
	{
		if (index <= 0 && index > _size)
			throw std::exception("Wrong index");
		T* data = new T[_size + 1];
		std::copy_n(_arr, index, data);
		data[index] = value;
		std::copy_n(_arr + index, _size - index, data + index + 1);
		delete[] _arr;
		_arr = data;
		++_capacity;
		++_size;
	}
	void pop_index(size_t index)
	{
		if (index < 0 && index < _size)
			throw std::exception("Wrong index");
		if (_size == 1)
		{
			erase();
			return;
		}
		T* data = new T[_size - 1];
		std::copy_n(_arr, index, data);
		std::copy_n(_arr + index + 1, _size - index - 1, data + index);
		delete[] _arr;
		_arr = data;
		--_capacity;
		--_size;
	}
	bool empty() { return _size == 0; }
	void insertAtBeginning(size_t value) { insertBefore(value, 0); }
	void pop_back() { pop_index(_size - 1); }
	void pop_front() { pop_index(0); }
	int size() const { return _size; }
	int capacity() const { return _capacity; }
	const T* cbegin() const { return _arr; }
	const T* cend() const { return _arr + _size; }
	T* begin() { return _arr; }
	T* end() { return _arr + _size; }
	~MyArray() { delete[] _arr; }
};