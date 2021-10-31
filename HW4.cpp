#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#pragma region Task1

class ArrayInt
{
	int m_length;
	int* m_data;

public:
	ArrayInt()
		: m_length(0),
		m_data(nullptr)
	{

	}
	ArrayInt(int length)
		: m_length(length)
	{
		assert(length >= 0);
		if (length > 0)
			m_data = new int[length];
		else
			m_data = nullptr;
	}

	~ArrayInt()
	{
		delete[] m_data;
	}

	void erase()
	{
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
	}

	int getLength() const
	{
		return m_length;
	}

	int& operator[] (int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	void resize(int newLength)
	{
		if (m_length == newLength)
			return;
		if (newLength <= 0)
		{
			erase();
			return;
		}

		int* data = new int[newLength];
		if (m_length > 0)
		{
			int elementsToCopy = newLength > m_length ? m_length : newLength;
			for (int i = 0; i < elementsToCopy; i++)
			{
				data[i] = m_data[i];
			}
		}
		delete[] m_data;
		m_data = data;
		m_length = newLength;
	}

	void insertBefore(int value, int index)
	{
		assert(index >= 0 && index <= m_length);
		int* data = new int[m_length + 1];
		for (int i = 0; i < index; ++i)
		{
			data[i] = m_data[i];
		}
		data[index] = value;
		for (int i = index; i < m_length; ++i)
		{
			data[i + 1] = m_data[i];
		}
		delete[] m_data;
		m_data = data;
		++m_length;
	}

	void push_back(int value)
	{
		insertBefore(value, m_length);
	}

	void deleteBefore(int index)
	{
		assert(index >= 0 && index < m_length);
		if (m_length == 1)
		{
			erase();
			return;
		}

		int* data = new int[m_length - 1];
		for (int i = 0; i < index; ++i)
		{
			data[i] = m_data[i];
		}

		for (int i = index + 1; i < m_length; ++i)
		{
			data[i - 1] = m_data[i];
		}
		delete[] m_data;
		m_data = data;
		--m_length;
	}

	void pop_back()
	{
		deleteBefore(m_length - 1);
	}

	void pop_front()
	{
		deleteBefore(0);
	}

	void print()
	{
		cout << "array : ";
		for (int i = 0; i < m_length; i++)
		{
			cout << m_data[i] << " ";
		}
		cout << endl;
	}

	void sort()
	{
		for (int j = 0; j < m_length - 1; j++)
		{
			for (int i = 0; i < m_length - 1 - j; i++)
			{
				if (m_data[i] > m_data[i + 1])
				{
					swap(m_data[i], m_data[i + 1]);
				}
			}
		}
	}
};
#pragma endregion
#pragma region Task2

int unValues(std::vector<int> a)
{
	auto last = unique(a.begin(), a.end());
	a.erase(last, a.end());
	sort(a.begin(), a.end());
	last = unique(a.begin(), a.end());
	a.erase(last, a.end());
	return a.size();
};
#pragma endregion

int main()
{
	setlocale(LC_ALL, "Russian");

	ArrayInt array(8);
	for (int i = 0; i < array.getLength(); i++)
	{
		array[i] = rand() % 100 + 1;
	}
	array.print();

	array.insertBefore(19, 2);
	array.print();

	array.deleteBefore(2);
	array.print();

	array.pop_back();
	array.print();

	array.pop_front();
	array.print();

	array.sort();
	array.print();

	cout << endl;

	vector<int> a = {14,2,45,32,5,7,3,23,31,2,7,14,99,3,6 };
	cout << "Вектор имеет  " << unValues(a) << " различных чисел." << endl;
	for (size_t i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
}