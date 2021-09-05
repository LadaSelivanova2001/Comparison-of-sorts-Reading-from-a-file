#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
//Описание класса
class Abitur {
public:
	char* FIO;
	char* Faculty;
	char* Spec;
	int Sum;
	Abitur();
	bool operator>(Abitur& left);
	bool operator<(Abitur& left);
	bool operator>=(Abitur& left);
	bool operator<=(Abitur& left);
	friend ostream& operator<<(ostream& out, const Abitur& left);
};
//Конструктор
Abitur::Abitur() {
	this->FIO = new char[50];
	this->Faculty = new char[50];
	this->Spec = new char[50];
}
//Перегрузка 4 операторов сравнения для сравнения элементов класса
bool Abitur::operator>(Abitur& left) {
	bool k = false;
	if (Sum < left.Sum) {//сравниваем сумму баллов (по убыванию)
		k = true;
	}
	else if (Sum == left.Sum) {
		if (strcmp(FIO, left.FIO) > 0) //сравниваем ФИО
		{
			k = true;
		}
	}
	return k;
}
bool Abitur::operator<(Abitur& left) {
	bool k = false;
	if (Sum > left.Sum) {
		k = true;
	}
	else if (Sum == left.Sum) {
		if (strcmp(FIO, left.FIO) < 0)
		{
			k = true;
		}
	}
	return k;
}
bool Abitur::operator>=(Abitur& left) {
	bool k = false;
	if (Sum >= left.Sum) {
		k = true;
	}
	return k;
}
bool Abitur::operator<=(Abitur& left) {
	bool k = false;
	if (Sum <= left.Sum) {
		k = true;
	}
	return k;
}
//Перегрузка оператора вывода для вывода элементов класса
ostream& operator<<(ostream& out, const Abitur& left) {
	out << left.FIO << "|" << left.Faculty << "|" << left.Spec << "|" << left.Sum << "|" << "\n"; 
	return out;
}
void heapify(Abitur arr[], int n, int i)
{
	int largest = i;
	// Инициализируем наибольший элемент как корень
	int l = 2 * i + 1; // левый = 2*i + 1
	int r = 2 * i + 2; // правый = 2*i + 2

	// Если левый дочерний элемент больше корня
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// Если самый большой элемент не корень
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(arr, n, largest);
	}
}



// Основная функция, выполняющая пирамидальную сортировку
void heapSort(Abitur arr[], int n)
{
	// Построение кучи (перегруппируем массив)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// Один за другим извлекаем элементы из кучи
	for (int i = n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(arr[0], arr[i]);

		// вызываем процедуру heapify на уменьшенной куче
		heapify(arr, i, 0);
	}
}
void selectionsort(Abitur a[], int size) //сортировка выбором
{
	int j = 0;
	Abitur tmp;
	for (int i = 0; i < size; i++) {
		j = i;
		for (int k = i; k < size; k++) {
			if (a[j] > a[k]) {
				j = k;
			}
		}
		tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	const int size = 800;
	Abitur a[size], b[size]; //необходимо для двух сортировок
	cout << "Start" << endl;
	char* str = new char[200];
	ifstream file("800.txt");
	int Sum;
	//Получение данных из файла в два массива
	for (int i = 0; i < size; i++) {
		char* FIO = new char[50], * Faculty = new char[50], * Spec = new char[50];
		file.getline(str, 200, '\n');
		FIO = strtok(str, ";");
		Faculty = strtok(NULL, ";");
		Spec = strtok(NULL, ";"); 
		Sum = atoi(strtok(NULL, ";"));//преобразовываем в число
		strcpy(a[i].FIO, FIO); //перемещаем в массив а[] (для сортировки выбором)
		strcpy(a[i].Faculty, Faculty);
		strcpy(a[i].Spec, Spec);
		a[i].Sum = Sum;
		strcpy(b[i].FIO, FIO);//перемещаем в массив b[](для пирамилальной сортировки)
		strcpy(b[i].Faculty, Faculty);
		strcpy(b[i].Spec, Spec);
		b[i].Sum = Sum;
	}
	for (int i = 0; i < size; i++) {
		//cout << a[i];
	}
	cout << endl;

	//Первая сортировка(Сортировка выбором)
	time_t time1 = clock(); //засекаем время
	selectionsort(a, size);
	time1 = clock()-time1; 


	for (int i = 0; i < size; i++) {
		//cout << a[i];
	}


	time_t time2 = clock();//засекаем время
	int v = sizeof(b)/sizeof(b[0]);
	heapSort(b, v);
	time2 = clock() - time2;


	cout << "------------------\n";
	for (int i = 0; i < size; i++) {
		//cout << b[i];
	}
	cout << endl;


	
	cout <<"Время первой сортировки: " << (double)time1 / CLOCKS_PER_SEC << "\n" << "Время второй сортировки: " << (double)time2 / CLOCKS_PER_SEC << "\n" << "Размер массива: "<<size << endl;
	file.close();
	cout << "Finish" << endl;
	return 0;
}
