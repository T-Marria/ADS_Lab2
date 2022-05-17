#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


void Print(vector<int> v)
{
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << ' ';
    std::cout << std::endl;
}

stats inserts_sort(std::vector<int>& data) {
	stats tmp;
	for (size_t i = 1; i < data.size(); i++) {
		for (size_t j = i; j > 0; j--) {
			tmp.comparison_count++;
			if (data[j - 1] > data[j]) {
				int temp = data[j - 1];
				data[j - 1] = data[j];
				data[j] = temp;
				tmp.copy_count++;
			}
		}
	}
	return tmp;
}

stats Shaker(std::vector<int>& data) //n^2
{
    stats shaker;
    int beyond = data.size() - 1;
    int left = 0;
    int right = data.size() - 1;
    do {
        for (int i = left; i < right; i++)
        {
            shaker.comparison_count++;
            if (data[i] > data[i + 1])
            {
                swap(data[i], data[i + 1]);
                beyond = i;
                shaker.copy_count++;
            }
        }
        right = beyond;
        for (int i = right; i > left; i--)
        {
            shaker.comparison_count++;
            if (data[i] < data[i - 1])
            {
                swap(data[i], data[i - 1]);
                beyond = i;
                shaker.copy_count++;
            }
        }
        left = beyond;
        shaker.comparison_count++;
    } while (left < right);
    Print(data);
    return shaker;
}

void Heap_Sort(std::vector<int>& data, size_t root, size_t size, stats& heap)
{
    size_t largest = root;
    size_t l = 2 * root + 1;
    size_t r = 2 * root + 2;
    heap.comparison_count++;
    if ((l < size) && (data[l] > data[largest]))
    {
        largest = l;
        heap.copy_count++;
    }
    heap.comparison_count++;
    if ((r < size) && (data[r] > data[largest]))
    {
        largest = r;
        heap.copy_count++;
    }
    heap.comparison_count++;
    if (largest != root)
    {
        swap(data[root], data[largest]);
        heap.copy_count++;
        Heap_Sort(data, largest, size, heap);
    }
}

stats Heap(std::vector<int>& data) //n*log(n)
{
    stats heap;
    int size = int(data.size());
    for (int i = size / 2 - 1; i >= 0; --i)
        Heap_Sort(data, i, size, heap);
    for (int i = size - 1; i > 0; i--)
    {
        swap(data[i], data[0]);
        heap.copy_count++;
        Heap_Sort(data, 0, i, heap);
    }
    Print(data);
    return heap;
}


int main() {
    std::vector<int> test = { 5, 4, 12, 6, 2, 7, 18 };
    std::vector<int> test2 = { 5, 4, 12, 6, 2, 7, 18 };
    std::vector<int> test3 = { 5, 4, 12, 6, 2, 7, 18 };
    stats result1 = inserts_sort(test);
    std::cout << result1.comparison_count << std::endl;
    std::cout << result1.copy_count << std::endl;
    for (auto i = test.begin(); i != test.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    stats result2 = Shaker(test2);
    std::cout << result2.comparison_count << std::endl;
    std::cout << result2.copy_count << std::endl;
    for (auto i = test.begin(); i != test.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    stats result3 = Heap(test2);
    std::cout << result2.comparison_count << std::endl;
    std::cout << result2.copy_count << std::endl;
    for (auto i = test.begin(); i != test.end(); ++i) {
        std::cout << *i << " ";
    }
    return 0;
}