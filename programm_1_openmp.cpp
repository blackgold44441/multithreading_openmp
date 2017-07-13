#define _CRT_SECURE_NO_WARNINGS 
#include <iostream> 
#include <vector> 
#include <time.h> 
#include <algorithm> 
#include <omp.h> 

using namespace std;

int thread_count = 5;
const int array_size = 1e8;
const long long module_product = 1e9 + 1743;

vector<int> my_array(array_size, 1);

int rand_element()
{
	int l = rand();

	while ((l == 0) || (l % 10 == 0))
	{
		l = rand();
	}

	return l;
}

int main()
{
	setlocale(0, "");
	freopen("outputMP1.txt", "w", stdout);

	srand(time(nullptr));
	generate(my_array.begin(), my_array.end(), rand_element);

	long long product, i;

	int thread_count = 1;

	for (int j = 1; j <= 10; j++)
	{
		cout << "Число потоков: " << thread_count << " - ";
		auto start = omp_get_wtime();
		product = 1;

#pragma omp parallel num_threads(thread_count) 
		{
#pragma omp for reduction(* : product) 
			for (i = 0; i < array_size; i++)
			{
				product *= my_array[i];
				product %= module_product;
			}

#pragma omp single 
			{
				product %= module_product;
			}
		}

		auto end = omp_get_wtime();
		cout << fixed << (end - start) << " с - ";
		thread_count++;

		cout << "Результат: " << product << endl;
	}
}
