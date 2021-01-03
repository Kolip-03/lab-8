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
	cout << "Ваш Баланс " << this->balance << endl;
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
	cout << "\t\t\t\t\tВаш банковский счёт ";
	if (!fl)
		cout <<"до начала транзакции " << endl;
	else
		cout << "После выполнения транзакции: " << endl;

	if (prev)
		cout << "\t до операции: " << prev->get() << endl;
	else
		cout << "\t До операции: данные отсутствуют " << endl;
	cout << "\t Текущий баланс  " << that->get() << endl;
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
	cout << "1 - Пополнить баланс" << endl;
	cout << "2 - Снять со счёта" << endl;
	cout << "3 - Показать баланс" << endl;
	cout << "4 - Откатить последнюю операцию" << endl;
	cout << "5 - История ваших операций" << endl;
	cout << "6 - Вывести вашу транзакцию" << endl;
	cout << "0 - Закончить работу с денежками" << endl;
	
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
	cout << "Банк Тинькофф" << endl;
	do {
		showMenu();
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			cout << "\tВведите сумму для пополнения: ";
			cin >> sum;
			if (tr.Begin()) {
				tr->replenish(sum);
				log += "\nПополнение: " + to_string(sum);
			}
			else {
				cout << "Ошибка в создании транзакции!";
				log += "\nПополнение: Ошибка в создании транзакции!";
			}
			break;
		case 2:
			cout << "\tВведите сумму для снятия: ";
			cin >> sum;
			if (tr.Begin()) {
				tr->withdraw(sum);
				log += "\nСнятие: " + to_string(sum);
			}
			else {
				cout << "Ошибка в создании транзакции!";
				log += "\nCнятие: Ошибка в создании транзакции!";
			}

			if (tr->get() < 0) {
				cout << "\tОбнаружен отрицательный баланс(недостаточно средств для снятия), проводится откат операци..." << endl;
				log += "\nCнятие: отрицательный баланс - откат назад";
				tr.Back();
			}

			break;
		case 3:
			cout << "\t\t";
			tr->show();
			break;
		case 4:
			tr.Back();
			log += " - откат назад";
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