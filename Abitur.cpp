#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
//�������� ������
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
//�����������
Abitur::Abitur() {
	this->FIO = new char[50];
	this->Faculty = new char[50];
	this->Spec = new char[50];
}

//���������� 4 ���������� ��������� ��� ��������� ��������� ������
bool Abitur::operator>(Abitur& left) {
	bool k = false;
	if (Sum < left.Sum) {//���������� ����� ������ (�� ��������)
		k = true;
	}
	else if (Sum == left.Sum) {
		if (strcmp(FIO, left.FIO) > 0) //���������� ���
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
//���������� ��������� ������ ��� ������ ��������� ������
ostream& operator<<(ostream& out, const Abitur& left) {
	out << left.FIO << "|" << left.Faculty << "|" << left.Spec << "|" << left.Sum << "|" << "\n"; 
	return out;
}
void heapify(Abitur arr[], int n, int i)
{
	int largest = i;
	// �������������� ���������� ������� ��� ������
	int l = 2 * i + 1; // ����� = 2*i + 1
	int r = 2 * i + 2; // ������ = 2*i + 2

	// ���� ����� �������� ������� ������ �����
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// ���� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// ���� ����� ������� ������� �� ������
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// ���������� ����������� � �������� ���� ���������� ���������
		heapify(arr, n, largest);
	}
}



// �������� �������, ����������� ������������� ����������
void heapSort(Abitur arr[], int n)
{
	// ���������� ���� (�������������� ������)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// ���� �� ������ ��������� �������� �� ����
	for (int i = n - 1; i >= 0; i--)
	{
		// ���������� ������� ������ � �����
		swap(arr[0], arr[i]);

		// �������� ��������� heapify �� ����������� ����
		heapify(arr, i, 0);
	}
}
void selectionsort(Abitur a[], int size) //���������� �������
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
	Abitur a[size], b[size]; //���������� ��� ���� ����������
	cout << "Start" << endl;
	char* str = new char[200];
	ifstream file("800.txt");
	int Sum;
	//��������� ������ �� ����� � ��� �������
	for (int i = 0; i < size; i++) {
		char* FIO = new char[50], * Faculty = new char[50], * Spec = new char[50];
		file.getline(str, 200, '\n');
		FIO = strtok(str, ";");
		Faculty = strtok(NULL, ";");
		Spec = strtok(NULL, ";"); 
		Sum = atoi(strtok(NULL, ";"));//��������������� � �����
		strcpy(a[i].FIO, FIO); //���������� � ������ �[] (��� ���������� �������)
		strcpy(a[i].Faculty, Faculty);
		strcpy(a[i].Spec, Spec);
		a[i].Sum = Sum;
		strcpy(b[i].FIO, FIO);//���������� � ������ b[](��� ������������� ����������)
		strcpy(b[i].Faculty, Faculty);
		strcpy(b[i].Spec, Spec);
		b[i].Sum = Sum;
	}
	for (int i = 0; i < size; i++) {
		//cout << a[i];
	}
	cout << endl;

	//������ ����������(���������� �������)
	time_t time1 = clock(); //�������� �����
	selectionsort(a, size);
	time1 = clock()-time1; 


	for (int i = 0; i < size; i++) {
		//cout << a[i];
	}


	time_t time2 = clock();//�������� �����
	int v = sizeof(b)/sizeof(b[0]);
	heapSort(b, v);
	time2 = clock() - time2;


	cout << "------------------\n";
	for (int i = 0; i < size; i++) {
		//cout << b[i];
	}
	cout << endl;


	
	cout <<"����� ������ ����������: " << (double)time1 / CLOCKS_PER_SEC << "\n" << "����� ������ ����������: " << (double)time2 / CLOCKS_PER_SEC << "\n" << "������ �������: "<<size << endl;
	file.close();
	cout << "Finish" << endl;
	return 0;
}
