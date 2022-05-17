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


int main() {
    std::vector<int> test = { 5, 4, 12, 6, 2, 7, 18 };
    std::vector<int> test2 = { 5, 4, 12, 6, 2, 7, 18 };
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
    return 0;
}