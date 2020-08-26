#include"Kommivoiazhors.h"


Kommivoiazhors one;
Kommivoiazhors two;
int amount_v = 0;
int menu_one = 0;
int WinW = 1280;
int WinH = 720;
float  R = 0.0;
const int maxSize = 20;

//структура координат вершин
struct vertC   
{
	int x, y;

};
vertC vC[20];

//круг в заданных координатах
void drawCircle(float x, float y, float R) 
{
	glColor3f(0.9f, 0.9f, 0.9f);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (size_t i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

//вес ребра между вершинами
void drawText(int nom, int x1, int y1)	
{
	
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	std::string s = std::to_string(nom);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (size_t j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

//линии(пути)
void drawLine_(int text, int x0, int y0, float x1, float y1)
{
	 x1 = x0 + (x1 - x0) / 2;
     y1 = y0 + (y1 - y0) / 2;

	glColor3i(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(GLint(x1), GLint(y1));
	glEnd();
	drawText(text, int((x0+x1) / 2 + 10), int((y0+y1) / 2 + 10));
	
	float vx = float(x0 - x1);
	float vy = float(y0 - y1);
	float s = 1.0f / sqrt(vx * vx + vy * vy);
	vx *= s;
	vy *= s;
	
	glColor3i(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(GLfloat(x1), GLfloat(y1));
	glVertex2f(GLfloat(x1) + GLfloat(10) * GLfloat(vx + vy), GLfloat(y1) + GLfloat(10) * GLfloat(vy - vx));
	glVertex2f(GLfloat(x1) + GLfloat(10) * GLfloat(vx - vy), GLfloat(y1) + GLfloat(10) * GLfloat(vy + vx));
	glEnd();
}

//пронумерованные вершины
void drawVertex(int n)	
{
	for (size_t i = 0; i < size_t(n); i++)
	{
		drawCircle(float(vC[i].x), float(vC[i].y), float(R));
		drawText(i + 1, vC[i].x, vC[i].y);
	}
}

//установка координат вершины в завис. от размеров окна
void setCoords(int i, float n) 
{
	float R_ = 0.0;
	float x0 = float(WinW) / float(2.0);
	float y0 = float(WinH) / float(2.0);
	if (WinW > WinH)
	{
		R = float(5.0) * (float(WinH) / float(13.0)) / n;
		R_ = float(WinH) / float(2.0) - R - float(10.0);
	}
	else
	{
		R = float(5.0) * (float(WinW) / float(13.0)) / n;
		R_ = float(WinW) / float(2.0) - R - float(10.0);
	}
	float theta = 2.0f * 3.1415926f * float(i) / n;
	float y1 = R_ * cos(theta) + y0;
	float x1 = R_ * sin(theta) + x0;

	
	vC[i].x = int(x1);
	vC[i].y = int(y1);
}

//отрисовка графа
void Kommivoiazhors::drawGraph()
{
	size_t n = vector_vertex.size();
	for (size_t i = 0; i < n; i++)
	{
		setCoords(i, float(n));	
	}
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0 ; j < n; j++)
		{
			int a = adj_matrix[i][j];
			if (a != 0)
			{
				drawLine_(a, vC[i].x, vC[i].y, float(vC[j].x), float(vC[j].y)); 
			}
		}
	}
	drawVertex(n);		
}

//установка новых размеров окна в зависимости от количества вершин 
void reshape(int w, int h)	
{
	WinW = w;
	WinH = h;

	glViewport(GLint(0.0), GLint(0.0), WinW, WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WinW, 0.0, WinH);
	glutPostRedisplay();
}

void menu()
{
	std::cout << "\t\t\tПрограмма ""НАХОЖДЕНИЕ КРАТЧАЙШЕГО ПУТИ С ПОСЕЩЕНИЕМ ВСЕХ ПУНКТОВ НА КАРТЕ ДОРОГ""\n";
	std::cout << "\t\t\t(!Данный задача решена методом ""ВЕТВЕЙ И ГРАНИЦ"")\n\n";
	int choice = 0;
	int amount_v = 0;

	while (true)
	{
		std::cout << "Выберите действие:\n";
		std::cout << "1.Воспользоваться картой дорог по-умолчанию для демонстрации алгоритма\n"
			<< "2.Разработать собственную карту дорог и найти кратчайший путь (максимальное количество пунктов 15)\n"
			<< "3.Выход.\n";

		std::cin >> choice; std::cout << std::endl;
		if (choice == 1)
		{
			menu_one = 1;
			Kommivoiazhors one1;
			one1.MAIN_finding_the_shortest_way(&one1);

			break;
		}

		else if (choice == 2)
		{
			menu_one = 2;
			std::cout << "Введите количество пунктов:";
			std::cin >> amount_v;
			Kommivoiazhors two1(amount_v);
			two1.create_road_map();
			two = two1;
			two1.MAIN_finding_the_shortest_way(&two1);

			break;
		}

		else if (choice == 3)
		{
			menu_one = 3;
			std::cout << "УДАЧИ ВАМ!!!" << std::endl;

			break;
		}

		else
		{
			menu_one = 4;
			throw std::exception("ВЫ ВВЕЛИ СИМВОЛ ВМЕСТО ЧИСЛА, ЛИБО НЕТ ДЕЙСТВИЙ ПОД ДАННЫМ ИНДЕКСОМ, ВНИМАТЕЛЬНЕЙ!");
		}
	}
}

//вывод графа на экран
void display()
{
	glMatrixMode(GL_PROJECTION);	//установка новой сис. координат
	glLoadIdentity();
	gluOrtho2D(0.0, WinW, 0.0, WinH);
	glViewport(GLint(0.0), GLint(0.0), WinW, WinH);
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (menu_one == 1)
	one.drawGraph();

	else if (menu_one == 2)
	two.drawGraph();

	else if (menu_one == 3)
	return;

	else
	return;
	
	glutSwapBuffers();
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");


	glutInit(&argc, argv);

	try
	{
		menu();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);//указываем каким образом будут выводиться объекты на экран
	glutInitWindowSize(WinW, WinH);
	glutCreateWindow("НАХОЖДЕНИЕ КРАТЧАЙШЕГО ПУТИ НА КАРТЕ ДОРОГ");
	glutDisplayFunc(display);//регистрируем дисплейную функцию обратного вызова
	glutReshapeFunc(reshape);//отвечает за масштабируемость изображения

	glutMainLoop();

	return 0;
}