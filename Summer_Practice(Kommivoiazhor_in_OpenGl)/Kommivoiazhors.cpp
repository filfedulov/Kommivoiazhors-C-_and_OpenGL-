#include "Kommivoiazhors.h"


Kommivoiazhors::Kommivoiazhors()
{
	std::vector<int> tmp_v(5, 0); //везде, где создаю временный вектор, потому-что нельзя проинициализировать вектор являющейся атрибутом класса(поэтому просто копиривать)
	vector_vertex = tmp_v;

	std::vector<std::vector<int>> tmp_adjm(vector_vertex.size(), std::vector<int>(vector_vertex.size()));
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			tmp_adjm[i][j] = 0;
		}
	}
	adj_matrix = tmp_adjm;
	vec_ways = tmp_adjm;
	copy_adjmatrix = tmp_adjm;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (i == j) adj_matrix[i][j] = 999; //под 999 подразумивается бесконечность, просто с 999 проще производить вывод матрицы

			else if (i == 0 && j == 1) adj_matrix[i][j] = 5;
			else if (i == 0 && j == 2) adj_matrix[i][j] = 11;
			else if (i == 0 && j == 3) adj_matrix[i][j] = 9;
			else if (i == 0 && j == 4) adj_matrix[i][j] = 1;

			else if (i == 1 && j == 0) adj_matrix[i][j] = 10;
			else if (i == 1 && j == 2) adj_matrix[i][j] = 8;
			else if (i == 1 && j == 3) adj_matrix[i][j] = 7;
			else  if (i == 1 && j == 4) adj_matrix[i][j] = 2;

			else if (i == 2 && j == 0) adj_matrix[i][j] = 7;
			else if (i == 2 && j == 1) adj_matrix[i][j] = 14;
			else if (i == 2 && j == 3) adj_matrix[i][j] = 8;
			else if (i == 2 && j == 4) adj_matrix[i][j] = 3;

			else if (i == 3 && j == 0) adj_matrix[i][j] = 12;
			else if (i == 3 && j == 1) adj_matrix[i][j] = 6;
			else if (i == 3 && j == 2) adj_matrix[i][j] = 15;
			else if (i == 3 && j == 4) adj_matrix[i][j] = 4;

			else if (i == 4 && j == 0) adj_matrix[i][j] = 3;
			else if (i == 4 && j == 1) adj_matrix[i][j] = 1;
			else if (i == 4 && j == 2) adj_matrix[i][j] = 11;
			else if (i == 4 && j == 3) adj_matrix[i][j] = 20;
		}
	}
	copy_adjmatrix = adj_matrix;
}

Kommivoiazhors::Kommivoiazhors(int amount_punkts)
{
	if (amount_punkts <= max_amount)
	{
		std::vector<int> tmp_v(amount_punkts, 0);
		vector_vertex = tmp_v;

		std::vector<std::vector<int>> tmp_adjm(amount_punkts, std::vector<int>(amount_punkts));
		for (size_t i = 0; i < tmp_adjm.size(); i++)
		{
			for (size_t j = 0; j < tmp_adjm.size(); j++)
			{
				tmp_adjm[i][j] = 0;
			}
		}
		adj_matrix = tmp_adjm;
		vec_ways = tmp_adjm;
		copy_adjmatrix = tmp_adjm;
	}

	else
	{
		std::cout << "Введенное значение превышает максимально-заданное количество городов!\n";
	}

}

Kommivoiazhors& Kommivoiazhors::operator=(const Kommivoiazhors& other)
{
	this->vector_vertex = other.vector_vertex;
	this->adj_matrix = other.adj_matrix;
	this->vec_ways = other.vec_ways;
	this->copy_adjmatrix = other.copy_adjmatrix;

	return* this;
}

//СОЗДАНИЕ КАРТЫ ГОРОДОВ
void Kommivoiazhors::create_road_map()
{
		int count_punkts = 1;
		int count_punkts_ = 1;
		std::cout << "Заполните пути между пунктами:\n";
		for (size_t i = 0; i < vector_vertex.size(); i++)
		{
			count_punkts = i + 1;
			std::cout << "Путь из пункта " << count_punkts;
			for (size_t j = 0; j < vector_vertex.size(); j++)
			{
				if (i == j)
				{
					adj_matrix[i][j] = 999;
				}
				else
				{
					count_punkts_ = j + 1;
					std::cout << " в пункт " << count_punkts_ << " = ";
					std::cin >> way;
					adj_matrix[i][j] = way;
				}
			}
			std::cout << std::endl;
		}

		copy_adjmatrix = adj_matrix;
}

//ЗАПОЛНЕНИЕ СТЭКА AMOUTN_OF_ITERATIONS
void Kommivoiazhors::fill_amountofiterations()
{
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		amount_of_iterations.emplace(i);
	}
}

//1.ВЫВОД КАРТЫ ГОРОДОВ
void Kommivoiazhors::print_road_map()
{
	std::cout << "1.Карта дорог готова(матрица смежности)\n";
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		if (i == 0)
			std::cout << std::setw(5) << i + 1;

		else
			std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		std::cout << i + 1;
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			std::cout << std::setw(4) << adj_matrix[i][j];

		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//2.НАХОЖДЕНИЕ МНИМУМОВ ПОСТРОКАМ
void Kommivoiazhors::finding_minimums_by_STR()
{
	int min = 0;
	std::vector<int> tmp_di(vector_vertex.size(), 0);
	di = tmp_di;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		min = INT_MAX;
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (adj_matrix[i][j] != 999)
			{
				if (adj_matrix[i][j] < min)
					min = adj_matrix[i][j];
			}

		}
		if (min != INT_MAX)
		{
			if (min != 999)
			{
				if (min < 0)
				di[i] = 0;

				else
				di[i] = min;
			}
		}
	}

	std::cout << "2.Карта дорог(матрица) с учетом минимумов по строкам:\n";
	for (size_t i = 0; i < vector_vertex.size() + 1; i++)
	{
		if (i == 0)
			std::cout << std::setw(5) << i + 1;

		else if (i == vector_vertex.size())
			std::cout << std::setw(3) << char(ch_di) << char(ch_di_);

		else
			std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		std::cout << i + 1;
		for (size_t j = 0; j < vector_vertex.size() + 1; j++)
		{
			if (j == vector_vertex.size())
				std::cout << std::setw(4) << di[i];

			else
				std::cout << std::setw(4) << adj_matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//3.РЕДУКЦИЯ СТРОК
void Kommivoiazhors::reduction_of_STR()
{
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (adj_matrix[i][j] != 999)
				adj_matrix[i][j] -= di[i];

		}
	}

	std::cout << "3.Матрица, после редукции строк:\n";
	for (size_t i = 0; i < vector_vertex.size() + 1; i++)
	{
		if (i == 0)
			std::cout << std::setw(5) << i + 1;

		else if (i == vector_vertex.size())
			std::cout << std::setw(3) << char(ch_di) << char(ch_di_);

		else
			std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		std::cout << i + 1;
		for (size_t j = 0; j < vector_vertex.size() + 1; j++)
		{
			if (j == vector_vertex.size())
				std::cout << std::setw(4) << di[i];

			else
				std::cout << std::setw(4) << adj_matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//4.НАХОЖДЕНИЕ МИНИМУМОВ ПО СТОЛБЦАМ
void Kommivoiazhors::finding_minimums_by_STL()
{
	int min = 0;
	std::vector<int> tmp_dj(vector_vertex.size(), 0);
	dj = tmp_dj;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		min = INT_MAX;
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (adj_matrix[i][j] != 999)
			{
				if (adj_matrix[j][i] < min)
					min = adj_matrix[j][i];
			}

		}
		if (min != INT_MAX)
		{
			if (min != 999)
			{
				if (min < 0)
				dj[i] = 0;

				else
				dj[i] = min;
			}
		}
	}

	std::cout << "4.Карта дорог(матрица) с учетом минимумов по столбцам:\n";
	for (size_t i = 0; i < vector_vertex.size() + 1; i++)
	{
		if (i == 0)
			std::cout << std::setw(5) << i + 1;

		else if (i == vector_vertex.size())
			std::cout << std::setw(3) << char(ch_di) << char(ch_di_);

		else
			std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		std::cout << i + 1;
		for (size_t j = 0; j < vector_vertex.size() + 1; j++)
		{
			if (j == vector_vertex.size())
				std::cout << std::setw(4) << di[i];

			else
				std::cout << std::setw(4) << adj_matrix[i][j];
		}
		std::cout << std::endl;
	}

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		if (i == 0)
			std::cout << char(ch_di) << char(ch_dj__) << std::setw(3) << dj[i];

		else
			std::cout << std::setw(4) << dj[i];
	}
	std::cout << std::endl << std::endl;
}

//5.РЕДУКЦИЯ СТОЛБЦОВ
void Kommivoiazhors::reduction_of_STL()
{
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (adj_matrix[j][i] != 999)
				adj_matrix[j][i] -= dj[i];

		}
	}

	std::cout << "5.Матрица, после редукции столбцов:\n";
	for (size_t i = 0; i < vector_vertex.size() + 1; i++)
	{
		if (i == 0)
			std::cout << std::setw(5) << i + 1;

		else if (i == vector_vertex.size())
			std::cout << std::setw(3) << char(ch_di) << char(ch_di_);

		else
			std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		std::cout << i + 1;
		for (size_t j = 0; j < vector_vertex.size() + 1; j++)
		{
			if (j == vector_vertex.size())
				std::cout << std::setw(4) << di[i];

			else
				std::cout << std::setw(4) << adj_matrix[i][j];
		}
		std::cout << std::endl;
	}

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		if (i == 0)
			std::cout << char(ch_di) << char(ch_dj__) << std::setw(3) << dj[i];

		else
			std::cout << std::setw(4) << dj[i];
	}
	std::cout << std::endl << std::endl;
}

//6.ВЫЧИСЛЕНИЕ ОЦЕНОК НУЛЕВЫХ КЛЕТОК
void Kommivoiazhors::zero_cells()
{
	memory_zero = adj_matrix;
	
	int minSTR = 0;
	int minSTL = 0;
	int summ_STL_STR = 0;
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (adj_matrix[i][j] == 0)
			{
				for (size_t x = i; x < i + 1; x++)
				{
					minSTR = INT_MAX;
					for (size_t y = 0; y < vector_vertex.size(); y++)
					{
						if (adj_matrix[x][y] != 999)
						{
							if (adj_matrix[x][y] < minSTR && y != j)
								minSTR = adj_matrix[x][y];
						}
					}
				}

				for (size_t z = j; z < j + 1; z++)
				{
					minSTL = INT_MAX;
					for (size_t w = 0; w < vector_vertex.size(); w++)
					{
						if (adj_matrix[w][z] != 999)
						{
							if (adj_matrix[w][z] < minSTL && w != i)
								minSTL = adj_matrix[w][z];
						}

					}
				}

				if (minSTR != INT_MAX && minSTL != INT_MAX)
				{
					summ_STL_STR = minSTR + minSTL;
					memory_zero[i][j] = summ_STL_STR;
				}
			}
		}
	}

	std::cout << "6.Матрица, после оценки нулевых значений:\n";
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		if (i == 0)
			std::cout << std::setw(5) << i + 1;

		else
			std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		std::cout << i + 1;
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (i == j)
				std::cout << std::setw(4) << memory_zero[i][j];

			else if (adj_matrix[i][j] == 0)
				std::cout << std::setw(3) << char(40) << memory_zero[i][j];

			else
				std::cout << std::setw(4) << memory_zero[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}

//7.РЕДУКЦИЯ МАТРИЦЫ
void Kommivoiazhors::reduction_of_a_matrix()
{
	int max_value = 0;
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (adj_matrix[i][j] == 0)
			{
				if (memory_zero[i][j] > max_value)
					max_value = memory_zero[i][j];
			}
		}
	}

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (memory_zero[i][j] == max_value && adj_matrix[i][j] == 0)
			{
				adj_matrix[j][i] = 999;
				vec_ways[i][j] = max_value;

				for (size_t x = i; x < i + 1; x++)
				{
					for (size_t y = 0; y < vector_vertex.size(); y++)
					{
						adj_matrix[x][y] = 999;
					}
				}

				for (size_t z = j; z < j + 1; z++)
				{
					for (size_t w = 0; w < vector_vertex.size(); w++)
					{
						adj_matrix[w][z] = 999;
					}
				}
			}
		}
	}

	std::cout << "7.Редукция матрицы:\n";
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		if (i == 0)
			std::cout << std::setw(5) << i + 1;

		else
			std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		std::cout << i + 1;
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			std::cout << std::setw(4) << adj_matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}

//ВЫВОД МАТРИЦЫ ИТОГОВЫХ ПУТЕЙ
void Kommivoiazhors::result()
{
	std::cout << "Итог(предварительный)\n";
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		if (i == 0)
			std::cout << std::setw(5) << i + 1;

		else
			std::cout << std::setw(4) << i + 1;
	}
	std::cout << std::endl;

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		std::cout << i + 1;
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			std::cout << std::setw(4) << vec_ways[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//ВЫВОД И СЧЕТ МИНИМАЛЬНОГО МАРШРУТА
void Kommivoiazhors::print_min_ways_and_counting()
{
	int home = 0; //чтобы не посчитать несколько раз последний пункт он же и первый
	int last_punkt = 0; //чтобы запомнить с какого пункта начался кратчайший путь(для вывода)
	std::vector<int> summ; //запомнить пути и посчитать дистанцию
	std::vector<int> store_repeat; //чтобы пути не повторялись при выводе
	bool odd = false;

	std::cout << "КРАТЧАЙШИЙ ПУТЬ НА ДАННОЙ КАРТЕ ДОРОГ: ";
	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (vec_ways[i][j] != 0)
			{
				store_repeat.push_back(i + 1);
				store_repeat.push_back(j + 1);
				if (home == 0)
				{
					last_punkt = i;
					home++;
				}
					summ.push_back(i);
					summ.push_back(j);
					counter_for_summ += 2;
			}
		}
	}

	for (size_t i = 0; i < vector_vertex.size(); i++)
	{
		for (size_t j = 0; j < vector_vertex.size(); j++)
		{
			if (i == j)
			copy_adjmatrix[i][j] = 0;
		}
	}

	for (size_t i = 0; i < store_repeat.size() - 1; i++)
	{
		if (store_repeat[i] != store_repeat[i + 1])
		{
				if (vector_vertex.size() % 2 != 0 || store_repeat.size() % 2 != 0)
				{
					if (i == 0)
						std::cout << store_repeat[i] << "->" << store_repeat[i + 1] << "->";

					else if(i==store_repeat.size()-2)
					std::cout << last_punkt + 1 << " = ";

					else
						std::cout << store_repeat[i + 1] << "->";
				}

				else
				{
					if (i == 0)
						std::cout << store_repeat[i] << "->" << store_repeat[i + 1] << "->";

					else
						std::cout << store_repeat[i + 1] << "->";
				}
        }
	}
	if(vector_vertex.size() % 2 == 0 && store_repeat.size() % 2 == 0)
	std::cout << last_punkt + 1 << " = ";

	summ.push_back(last_punkt);

	for (int i = 0; i < counter_for_summ; i++)
	{
		distance += copy_adjmatrix[summ[i]][summ[i + 1]];
	}
	std::cout << distance << "." << std::endl;
}

//НАХОЖДЕНИЯ КРАТЧАЙШЕГО ПУТИ МЕТОДОМ "ВЕТВЕЙ И ГРАНИЦ"
int Kommivoiazhors::MAIN_finding_the_shortest_way(Kommivoiazhors* k)
{
	fill_amountofiterations();

	while (!amount_of_iterations.empty())
	{
		/*1.*/k->print_road_map();

		/*2.*/k->finding_minimums_by_STR();

		/*3.*/k->reduction_of_STR();

		/*4.*/k->finding_minimums_by_STL();

		/*5.*/k->reduction_of_STL();

		/*6.*/k->zero_cells();

		/*7.*/k->reduction_of_a_matrix();

		result();

		amount_of_iterations.pop();
	}

	print_min_ways_and_counting();

	return 0;
}

Kommivoiazhors::~Kommivoiazhors()
{
}



