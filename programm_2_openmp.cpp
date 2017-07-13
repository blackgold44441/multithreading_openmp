#define _CRT_SECURE_NO_WARNINGS 
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <omp.h> 

using namespace std;

const int first_matrix_str = 100;
const int first_matrix_stl = 100;
const int second_matrix_str = 100;
const int second_matrix_stl = 100;

vector<vector<int>> first_matrix;
vector<vector<int>> second_matrix;
vector<vector<int>> result_matrix;

long long module_product = 1e9 + 15634;

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
	freopen("outputMP2.txt", "w", stdout);

	int i, j, k;

	first_matrix.resize(first_matrix_str, vector<int>(first_matrix_stl, 0));
	second_matrix.resize(second_matrix_str, vector<int>(second_matrix_stl, 0));
	result_matrix.resize(first_matrix_str, vector<int>(second_matrix_stl, 0));

	for (int i = 0; i < first_matrix_str; i++)
	{
		generate(first_matrix[i].begin(), first_matrix[i].end(), rand_element);
	}

	for (int i = 0; i < second_matrix_str; i++)
	{
		generate(second_matrix[i].begin(), second_matrix[i].end(), rand_element);
	}

	int thread_count = 1;

	for (int l = 1; l <= 10; l++)
	{
		cout << endl << "Число потоков: " << thread_count << " - ";
		auto start = omp_get_wtime();

#pragma omp parallel num_threads(thread_count) 
		{
#pragma omp for schedule(static, 2) 
			for (i = 0; i < first_matrix_str; i++)
			{
				for (j = 0; j < second_matrix_stl; j++)
				{
					result_matrix[i][j] = 0;

					for (k = 0; k < first_matrix_stl; k++)
					{
						result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j];
						result_matrix[i][j] %= module_product;
					}
				}
			}
		}

		auto end = omp_get_wtime();
		cout << fixed << (end - start) << " с - " << " Результат - ";
		for (int i = 0; i < result_matrix.size(); ++i)
			for (int j = 0; j < result_matrix.size(); ++j)
			{
				{
					cout << result_matrix[i][j] << " ";
				}
			}
		cout << endl;
		thread_count++;
	}

	return 0;
}
