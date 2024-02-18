#include <iostream>
#include "MyArray.h"

int main()
{
	try
	{
		MyArray<int> array(10);
		for (int i = 0; i < 10; ++i)
			array.push_back(i);
		array.resize(8);
		array.insertBefore(20, 5);
		array.pop_index(3);
		array.insertAtBeginning(40);
		array.push_back(30);
		{
			MyArray<int> b(array);
			b = array;
			b = b;
			array = array;
		}
		for (const auto& it : array)
		{
			std::cout << it << ' ';
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}
}