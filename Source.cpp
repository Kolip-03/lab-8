#include <iostream> 
#include <locale.h> 
#include <string>
#include <string>
#include <conio.h>

using namespace std;


class BankAccount {
private:
	double balance;
public:
	BankAccount() {
		balance = 0;
	}

	BankAccount(double balance) {
		this->balance = balance;
	}

	void show();
	void withdraw(double sum); 
	void replenish(double sum); 
	double get();
	void set(double balance);
};

void  BankAccount::show() {
	cout << "��� ������ " << this->balance << endl;
}

double  BankAccount::get()
{
	return this->balance;
}

void  BankAccount::set(double balance) {
	this->balance = balance;
}

void   BankAccount::withdraw(double sum) {
	balance -= sum;
}

void  BankAccount::replenish(double sum) {
	balance += sum;
}

template <class T>
class Tran
{
	T* that;
	T* prev;
public:
	Tran() :prev(NULL), that(new T) {}
	Tran(const Tran& obj) :
		that(new T(*(obj.that))), prev(NULL) {}
	~Tran() { delete that;  delete prev; }
	Tran& operator=(const Tran& obj);
	void Show(int);

	bool Begin();
	void Commit();
	void Back();
	T* operator->();
};

template <class T>
Tran<T>& Tran<T>::operator=(const Tran<T>& obj)
{
	if (this != &obj)
	{
		delete that;
		that = new T(*(obj.that));
	}
	return *this;
}

template <class T>
T* Tran<T>::operator->()
{
	return that;
}

template <class T>
void Tran<T>::Show(int fl)
{
	cout << "\t\t\t\t\t��� ���������� ���� ";
	if (!fl)
		cout <<"�� ������ ���������� " << endl;
	else
		cout << "����� ���������� ����������: " << endl;

	if (prev)
		cout << "\t �� ��������: " << prev->get() << endl;
	else
		cout << "\t �� ��������: ������ ����������� " << endl;
	cout << "\t ������� ������  " << that->get() << endl;
}



template <class T>
bool Tran<T>::Begin()
{
	delete prev;
	prev = that;
	that = new T(*prev);
	if (!that)
		return false;
	return true;
}

template <class T>
void Tran<T>::Commit()
{
	delete prev;
	prev = NULL;
}

template <class T>
void Tran<T>::Back()
{
	if (prev != NULL)
	{
		delete that;
		that = prev;
		prev = NULL;
	}
}

void showMenu() {
	cout << "1 - ��������� ������" << endl;
	cout << "2 - ����� �� �����" << endl;
	cout << "3 - �������� ������" << endl;
	cout << "4 - �������� ��������� ��������" << endl;
	cout << "5 - ������� ����� ��������" << endl;
	cout << "6 - ������� ���� ����������" << endl;
	cout << "0 - ��������� ������ � ���������" << endl;
	
}


int main()
{
	string log = "";
	Tran<BankAccount> tr;
	setlocale(LC_ALL, "Russian");
	int choice = 0;
	double sum;
	tr.Show(false);
	cout << endl;
	cout << "���� ��������" << endl;
	do {
		showMenu();
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			cout << "\t������� ����� ��� ����������: ";
			cin >> sum;
			if (tr.Begin()) {
				tr->replenish(sum);
				log += "\n����������: " + to_string(sum);
			}
			else {
				cout << "������ � �������� ����������!";
				log += "\n����������: ������ � �������� ����������!";
			}
			break;
		case 2:
			cout << "\t������� ����� ��� ������: ";
			cin >> sum;
			if (tr.Begin()) {
				tr->withdraw(sum);
				log += "\n������: " + to_string(sum);
			}
			else {
				cout << "������ � �������� ����������!";
				log += "\nC�����: ������ � �������� ����������!";
			}

			if (tr->get() < 0) {
				cout << "\t��������� ������������� ������(������������ ������� ��� ������), ���������� ����� �������..." << endl;
				log += "\nC�����: ������������� ������ - ����� �����";
				tr.Back();
			}

			break;
		case 3:
			cout << "\t\t";
			tr->show();
			break;
		case 4:
			tr.Back();
			log += " - ����� �����";
			break;
		case 5:
			cout << endl << log << endl << endl;
			break;
		case 6:
			tr.Show(true);
			break;
		default:
			break;
		}
	} while (choice != 0);

	tr.Show(true);
	return 0;

}
string writeWord()
{
	string slovo;
	while (true) {
		int Knopka;
		char sumbol;
		Knopka = _getch();
		if (Knopka == 224) {
			Knopka = _getch();
		}
		else
			if (Knopka == 8) {
				if (slovo.length() != 0) {
					cout << '\b' << " " << '\b';
					slovo.erase(slovo.length() - 1);
				}
			}
			else
				if (Knopka == 13) {
					break;
				}
				else {
					sumbol = (char)Knopka;
					if ((sumbol >= 'a' && sumbol <= 'z') || (sumbol >= 'A' && sumbol <= 'Z')) {
						slovo = slovo + sumbol;
						cout << sumbol;
					}
				}
	}
	return slovo;
}