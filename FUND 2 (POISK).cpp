#include <iostream> 
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <set>
#include <chrono>
using namespace std;
int const n = 100;
int const Ner = 10;


int getRandomNumber()
{
	return rand() % ::Ner;
}        // количество имен в массиве
const char* names[::Ner] = { "Jhon", "Alex", "Georg", "Sidny", "Angelina",
								"Kollin", "Mary", "Sun", "Robert", "Garry" 
};
const char* snames[::Ner] = { "Abram", "Dauny", "Jhukof", "Jolly", "Umbrella",
								"Mishel", "Ackles", "Potter", "North", "Sikker"
};

struct str {
	string type;
	string name;
	int day;
	int mou;
	int year;
	int per;
	string numb;
};


str wow[n];
str WithB[n + 1];

set <string> typN{ "Single", "Double", "Triple", "Extra", "Presidential" };
void In() { //создаю файл на 11111 записей
	std::ofstream out;          // поток для записи
	out.open("C:\\T.txt"); // окрываем файл для записи
	if (out.is_open())
	{
		for (int i = 0; i < n; ++i) {
			switch (i % 5) {
			case 0:
				out << names[getRandomNumber()] << ' ' << snames[getRandomNumber()];
				out << ' ';
				out << "Single ";
				break;
			case 1:
				out << names[getRandomNumber()] << ' ' << snames[getRandomNumber()];
				out << ' ';
				out << "Double ";
				break;
			case 2:
				out << names[getRandomNumber()] << ' ' << snames[getRandomNumber()];
				out << ' ';
				out << "Triple ";
				break;
			case 3:
				out << names[getRandomNumber()] << ' ' << snames[getRandomNumber()];
				out << ' ';
				out << "Extra ";
				break;
			case 4:
				out << names[getRandomNumber()] << ' ' << snames[getRandomNumber()];
				out << ' ';
				out << "Presidential ";
				break;
			}
			if (i == n - 1) {
				out << rand() % 3 << rand() % 9 + 1 << '.' << rand() % 1 << rand() % 9 + 1 << '.' << rand() % 5000 << ' ' << rand() % 10000 << " +" << rand() % 1000000;
			}
			else {
				out << rand() % 3 << rand() % 9 + 1 << '.' << rand() % 1 << rand() % 9 + 1 << '.' << rand() % 5000 << ' ' << rand() % 10000 << " +" << rand() % 1000000 << endl;
			}
		}
		out.close();
	}
}


int Ten(int a) {
	int b = 1;
	for (int i = a; i != 0; i--) {
		b *= 10;
	}
	return(b);
}


void Print(str* a) {
	for (int i = 0; i < n; i++) {
		cout << a[i].name << ' ';
		cout << a[i].type << ' ';
		if (a[i].day < 10) cout << '0' << a[i].day << '.';
		else cout << a[i].day << '.';
		if (a[i].mou < 10) cout << '0' << a[i].mou;
		else cout << a[i].mou;
		cout << '.' << a[i].year << ' ' << a[i].per << ' ' << a[i].numb << endl;
	}
}


set <char> ss{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };  //для проверки циферок


void Read() {
	In(); //создаю файл на 11111 записей
	int g;  //темповая переменная для свапа массива
	char w = ' '; //темповая переменная чтобы файл читать
	int i = 0;
	int j = 0;
	ifstream s("C:\\T.txt");
	string r;
	int d[4];
	//getline(s, r);
	while (!s.eof()) {  //читаю файл, формирую массив для сортировки
		int fio = 0; //читаю фио (2 words, first and second name)	
		s.get(w);
		wow[j].name = w;
		while (fio <= 1) {
			s.get(w);
			if (w == ' ') {
				fio++;
				if (fio == 1) {
					wow[j].name += w;
				}
			}
			else wow[j].name += w;
		}
		fio = 0;
		i = 0;			//читаю тип номера
		s.get(w);
		while (w != ' ') {
			wow[j].type += w;
			s.get(w);
			i++;
		}
		while (!ss.count(w)) {        //читаю дату
			s.get(w);
		}
		wow[j].day = (w - '0') * 10;
		s.get(w);
		wow[j].day += w - '0';
		s.get(w); s.get(w);
		wow[j].mou = (w - '0') * 10;
		s.get(w);
		wow[j].mou = (w - '0');
		s.get(w); s.get(w);
		wow[j].year = (w - '0') * 1000;
		s.get(w);
		wow[j].year += (w - '0') * 100;
		s.get(w);
		wow[j].year += (w - '0') * 10;
		s.get(w);
		wow[j].year += (w - '0');
		s.get(w);
		while (!ss.count(w)) {
			s.get(w);
		}
		i = 0;
		d[i] = w - '0';
		while (ss.count(w)) {  //доп массив для кол-ва дней
			s.get(w);
			if (!ss.count(w)) break;
			i++;
			d[i] = w - '0';
		}
		if (i == 3) {  //читаю дни
			g = d[0];
			d[0] = d[3];
			d[3] = g;
			g = d[1];
			d[1] = d[2];
			d[2] = g;
		}
		else if (i == 2) {
			g = d[0];
			d[0] = d[2];
			d[2] = g;
		}
		else if (i == 1) {
			g = d[0];
			d[0] = d[1];
			d[1] = g;
		}
		wow[j].per = 0;
		while (i != -1) {  //сколько дней 
			if (i == 0)  wow[j].per += d[i];
			else wow[j].per += d[i] * Ten(i);
			i--;
		}
		while (w != '+') {
			s.get(w);
		}
		wow[j].numb = w;  //в этом блоке номер телефона
		getline(s, r);
		wow[j].numb += r;
		j++;
	}
}


void Sort(int start) {
	switch (start) {
	case 1:
		for (int i = 1; i < n; i++)
		{
			int j = i - 1;
			while (j >= 0 && wow[j].name > wow[j + 1].name)
			{
				swap(wow[j], wow[j + 1]);
				j--;
			}
		}
		break;
	case 2:
		for (int i = 1; i < n; i++)
		{
			int j = i - 1;
			while (j >= 0 && wow[j].year >= wow[j + 1].year)
			{
				swap(wow[j], wow[j + 1]);
				j--;
			}
		}
		break;
	case 3:
		for (int i = 1; i < n; i++)
		{
			int j = i - 1;
			while (j >= 0 && wow[j].type > wow[j + 1].type)
			{
				swap(wow[j], wow[j + 1]);
				j--;
			}
		}
		break;
	case 4:
		for (int i = 1; i < n; i++)
		{
			int j = i - 1;
			while (j >= 0 && wow[j].per > wow[j + 1].per)
			{
				swap(wow[j], wow[j + 1]);
				j--;
			}
		}
		break;
	case 5:
		for (int i = 1; i < n; i++)
		{
			int j = i - 1;
			while (j >= 0 && wow[j].numb > wow[j + 1].numb)
			{
				swap(wow[j], wow[j + 1]);
				j--;
			}
		}
		break;
	}
}

void ForBar() {
	for (int i = 0; i < n; i++) {
		WithB[i] = wow[i];
	}
}


void FindWithBar(int start) {
	string fname, fhelp, roomT, numbPS, numbP;
	int d1, m1, y1, perR;
	switch (start) {
	case 1:{ 
		cout << "Enter name\n";
		cin >> fname;
		getline(cin, fhelp);
		fname += fhelp;
		WithB[n].name = fname;
		int i = 1;
		while (WithB[i].name != fname) {
			i += 1;
		}
		if (i == n) {
			cout << "\nNot found\n";
		}
		else cout << "\nKey in line " << i << "\nNumber of steps to find " << i;
	}
		  break;
	case 2:{ 
		cout << "Enter date\nDay ";
		cin >> d1;
		cout << "\nMonth ";
		cin >> m1;
		cout << "\nYear ";
		cin >> y1;
		WithB[n].day = d1; 
		WithB[n].mou = m1;
		WithB[n].year = y1;
		int i = 1;
		while (WithB[i].day != d1 or WithB[i].mou != m1 or WithB[i].year != y1) {
			i += 1;
		}
		if (i == n) {
			cout << "\nNot found\n";
		}
		else cout << "\nKey in line " << i << "\nNumber of steps to find " << i;
	}
		  break;
	case 3:{
		cout << "\nEnter room type ";
		cin >> roomT;
		WithB[n].type = roomT;
		int i = 1;
		while (WithB[i].type != roomT) {
			i += 1;
		}
		if (i == n) {
			cout << "\nNot found\n";
		}
		else cout << "\nKey in line " << i << "\nNumber of steps to find " << i;
	}
		  break;
	case 4:{
		cout << "\nEnter period of residence ";
		cin >> perR;
		WithB[n].per = perR;
		int i = 1;
		while (WithB[i].per != perR) {
			i += 1;
		}
		if (i == n) {
			cout << "\nNot found\n";
		}
		else cout << "\nKey in line " << i << "\nNumber of steps to find " << i;
	}
		  break;
	case 5:{
		cout << "\nEnter number of phone ";
		cin >> numbP;
		numbPS = "+" + numbP;
		WithB[n].numb = numbPS;
		int i = 1;
		while (WithB[i].numb != numbPS) {
			i += 1;
		}
		if (i == n) {
			cout << "\nNot found\n";
		}
		else cout << "\nKey in line " << i << "\nNumber of steps to find " << i;
	}
		  break;
	}
	
}
int strVint(string r) {
	int a = r.length();
	int sum = 0;
	for (int i = 0; i < a; i++) {
		sum += r[i];
	}
	return sum;
}

int  FindInter(int start) { //Как искать не в интовых полях?
	string fname, fhelp, roomT;
	int d1, m1, y1, perR, numbP, mid, low = 0, high = n - 1, step = 0;
	switch (start) {
	case 1:{
		/*cout << "Enter name\n";
		cin >> fname;
		getline(cin, fhelp);
		fname += fhelp;
		while (wow[low].name < fname && wow[high].name > fname) {
			if (wow[high].name == wow[low].name) break;
			mid = low + ((strVint(fname) - strVint(wow[low].name)) * (high - low) / (strVint(wow[high].name) - strVint(wow[low].name)));
			if (strVint(wow[mid].name) < strVint(fname)) {
				low = mid + 1;
			}
			else if (strVint(wow[mid].name) > strVint(fname)) {
				high = mid - 1;
			}
			else return mid;
		}
		if (strVint(wow[low].name) == strVint(fname)) {
			return low;
		}
		if (strVint(wow[high].name) == strVint(fname)) {
			return high;
		}*/
		return -2;
	}
		  break;
	case 2:{
		cout << "Enter date\nDay ";
		cin >> d1;
		cout << "\nMonth ";
		cin >> m1;
		cout << "\nYear ";
		cin >> y1;
		while (wow[low].year < y1 && wow[high].year > y1) {
			if (wow[high].name == wow[low].name) break;
			mid = low + ((y1 - wow[low].year) * (high - low) / (wow[high].year - (wow[low].year)));
			if (wow[mid].year < y1) {
				low = mid + 1;
			}
			else if (wow[mid].year > y1) {
				high = mid - 1;
			}
			else return mid;
		}
		if (wow[low].year == y1) {
			return low;
		}
		if (wow[high].year == y1) {
			return high;
		}
		return -1;
	}
		  break;
	case 3:{
		/*cout << "\nEnter room type ";
		cin >> roomT;*/
		return -2;
	}
		  break;
	case 4:{
		cout << "\nEnter period of residence ";
		cin >> perR;
		while (wow[low].per < perR && wow[high].per > perR) {
			step++;
			if (wow[high].per == wow[low].per) break;
			mid = low + ((perR - wow[low].per) * (high - low) / (wow[high].per - (wow[low].per)));
			if (wow[mid].per < perR) {
				low = mid + 1;
			}
			else if (wow[mid].per > perR) {
				high = mid - 1;
			}

			else { 
				cout << "\nNumber of stepts to find " << step;
			    return mid;
			}
		}
		if (wow[low].per == perR) {
			step++;
			cout << "\nNumber of stepts to find " << step;
			return low;
		}
		if (wow[high].per == perR) {
			step++;
			cout << "\nNumber of stepts to find " << step;
			return high;
		}
		return -1;
	}
		  break;
	case 5:{
		/*cout << "\nEnter number of phone ";
		cin >> numbP;*/
	}
		  return -2;
		  break;
	}
}

int main() {
	Read();
	int start;
	cout << "\nWhat field are we looking for?\n";
	cout << "1 - Full name\n2 - date\n3 - room type\n4 - period of residence\n5 - phone number\n";
	cin >> start;
	Sort(start);
	//Print(wow);
	ForBar();
	//FindWithBar(start);
	int k = (FindInter(start));
	if (k == -2) cout << "\nImbossible to find in this field";
	if (k == -1) cout << "\nNot found\n";
	else cout << "\nkey in line: " << k;
}
