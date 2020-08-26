#pragma once
#include <glut.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include<stack>
#include<string>


class Kommivoiazhors
{
public:
	Kommivoiazhors();
	Kommivoiazhors(int amount_punkts);
	Kommivoiazhors& operator = (const Kommivoiazhors& other);
	
	void create_road_map(); //создание карты городов
	void fill_amountofiterations(); //заполнение стэка amount_of_iterations
	void print_road_map(); //1.вывод карты городов (изначальной)
	void finding_minimums_by_STR(); //2.Нахождение минимумов по строкам
	void reduction_of_STR(); //3.Редукция строк(вычитание минимуму из каждого элемента строки, ну кроме бесконечности)
	void finding_minimums_by_STL(); //4.Нахождение мнимумов по столбцам
	void reduction_of_STL(); //5.Редукция столбцов
	void zero_cells(); //6.Вычисление оценок нулевых клеток
	void reduction_of_a_matrix(); //7.Редукция матрицы
	void result(); //вывод матрицы итоговых путей
	void print_min_ways_and_counting(); //вывод и счет минимального маршрута
	int MAIN_finding_the_shortest_way(Kommivoiazhors* k); //НАХОЖДЕНИЯ КРАТЧАЙШЕГО ПУТИ МЕТОДОМ "ВЕТВЕЙ И ГРАНИЦ"
	void drawGraph();
	~Kommivoiazhors();

private:
	//bool amount_punkts_yes_or_no = false; //переменная на те случаи когда количество пунктов уже известно или нет (нужно при создании карты)
	const int max_amount = 15;
	int amount_vertex = 0;
	int way = 0;
	const int ch_di = 100; //'d'
	const int ch_di_ = 105; //'i'
	const int ch_dj__ = 106; //'j'
	int memory_i = 0; int memory_j = 0; //переменные, чтобы больше не рассматривать строки и столбцы удаленны, после действий метода "ветвей и границ"
	int circle_algotihm = 0; //сколько кругов метода уже пройдено, чтобы применять memory_i и j
	int distance = 0; //итоговое расстояние
	int counter_for_summ = 0; 
	std::vector<int> di, dj; //в методе(2. и 4.) в одном из которых будут хранится минимумы из каждой строки, а в другом из столбца
	std::vector<int> vector_vertex; //вектор вершин(пунктов)
	std::vector<std::vector<int>> adj_matrix; //вектор для хранения карты путей
	std::vector<std::vector<int>> copy_adjmatrix; //копия карты путей, пригодиться для вывода расстояния, потому-что матрица(карта) будет меняться, псоле редукци
	std::vector<std::vector<int>> memory_zero; //для вычисления оценок нулевых клеток и для последующей перезаписи их в матрицу
	std::vector<std::vector<int>> vec_ways; //накапливать в него данные о минимальных путях
	std::stack<int> amount_of_iterations; //чтобы знать сколько раз проделывать полный комплекс действий метода "ветвей и границ"

};




