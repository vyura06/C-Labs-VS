Михаил Мороз, [31.03.20 13:11]
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

static const string LAST_NAME_OF_THE_WORKER = "Enter the last name of the worker:\n";
static const string NAME_OF_THE_WORKSHOP = "Enter the name of the workshop:\n";
static const string NUMBERS_OF_PRODUCTS_A = "Enter how many products A the worker made:\n";
static const string NUMBER_OF_PRODUCTS_B = "Enter how many products B the worker made:\n";
static const string NUMBER_OF_PRODUCTS_C = "Enter how many products C the worker made:\n";

struct Day {
	int lessonNumber;
	string className;
};

struct Teacher {
	string teacherSurname;
	Day days[6];
};

vector<Teacher> teachers;

static bool isDigit(const string& str) {
	bool isCorrect = false;
	int number = 0;
	stringstream string_stream;
	string_stream << str;
	if (string_stream >> number) {
		isCorrect = true;
	}
	return isCorrect;
}

static bool isExit(bool isNotCorrect) {
	string check;
	if (isNotCorrect) {
		cout << "Record not found!\nIf you want to exit - enter \"STOP\"\n"
			"If not - enter something\n";
		cin >> check;
		if (check == "STOP") {
			isNotCorrect = false;
		}
	}
	else {
		cout << "Record found!\n";
	}
	return isNotCorrect;
}

static int enterNumber() {
	int number_of_items;
	while (!(cin >> number_of_items) || number_of_items < 1) {
		cout << "ERROR! TRY AGAIN!\n";
		cin.clear();
		cin.sync();
	}
	return number_of_items;
}

static string enterSurname() {
	string last_name;
	do {
		cin >> last_name;
		if (last_name.empty()) {
			cout << "Error!\n";
		}
	} while (last_name.empty());
	return last_name;
}

static void enterDay(Teacher& teacher) {
	for (int i = 0; i < 6; i++) {
		teacher.days[i].lessonNumber = enterNumber();
		cin >> teacher.days[i].className;
	}
}

static void fillTeachers(Teacher& teacher) {
	cout << "Enter teacher:\n";
	cout << LAST_NAME_OF_THE_WORKER;
	teacher.teacherSurname = enterSurname();
	cout << NAME_OF_THE_WORKSHOP;
	enterDay(teacher);
}

int parseInt(const string& array) {
	int number;
	stringstream string_stream;
	string_stream << array;
	string_stream >> number;
	string_stream.clear();
	string_stream.sync();
	return number;
}

static void fillRecordFromFile(string array[]) {
	stringstream string_stream;
	Teacher teacher;
	teacher.teacherSurname = array[0];
	teacher.days[0].lessonNumber = parseInt(array[1]);
	teacher.days[0].className = array[2];

	teacher.days[1].lessonNumber = parseInt(array[3]);
	teacher.days[1].className = array[4];

	teacher.days[2].lessonNumber = parseInt(array[5]);
	teacher.days[2].className = array[6];

	teacher.days[3].lessonNumber = parseInt(array[7]);
	teacher.days[3].className = array[8];

	teacher.days[4].lessonNumber = parseInt(array[9]);
	teacher.days[4].className = array[10];

	teacher.days[5].lessonNumber = parseInt(array[11]);
	teacher.days[5].className = array[12];
	teachers.push_back(teacher);
}

static void readFile(const string& pathname) {
	stringstream string_stream;
	string array[5];
	string line;
	ifstream in(pathname);
	while (getline(in, line)) {
		string_stream << line;
		int i = 0;
		while (i < 5) {
			string_stream >> array[i];
			i++;
		}
		if (isDigit(array[2]) && isDigit(array[3]) && isDigit(array[4])) {
			fillRecordFromFile(array);
		}
		string_stream.clear();
		string_stream.sync();
	}
}

Михаил Мороз, [31.03.20 13:11]
static void inputFile() {
	string pathname;
	bool isNotCorrect = true;
	do {
		cout << "Enter path to the file (input):\n";
		cin >> pathname;
		ifstream in(pathname);
		if (in) {
			cout << "File Found!\n";
			readFile(pathname);
			if (teachers.empty()) {
				cout << "File is not correct!\n";
			}
			else {
				isNotCorrect = false;
			}
		}
		else {
			cout << "File not found\n";
		}
	} while (isNotCorrect);
}

static void inputConsole() {
	string check;
	do {
		Teacher worker = Teacher();
		fillTeachers(worker);
		teachers.push_back(worker);
		cout << "Do you want to continue to enter data? (\"yes\" or \"no\")\n";
		cin >> check;
	} while (check != "no");
}

static void writeInFile(const string& pathname) {
	fstream both(pathname);
	both << "Sorted array: ";
	for (int i = 0; i < teachers.size(); i++) {
		both << teachers.at(i).teacherSurname << "\n";
		for (int j = 0; j < 6; j++) {
			both << teachers.at(i).days[j].lessonNumber <<
				" " << teachers.at(i).days[j].className << "\n";
		}
	}
	both.close();
}

static void outputFile() {
	bool isNotCorrect = true;
	string pathname;
	do {
		cout << "Enter path to the file (output):\n";
		cin >> pathname;
		ifstream in(pathname);
		if (in) {
			cout << "File Found!\n";
			isNotCorrect = false;
		}
		else {
			cout << "File not found\n";
		}
		in.close();
	} while (isNotCorrect);
	writeInFile(pathname);
}

static void consoleOutput() {
	for (int i = 0; i < teachers.size(); i++) {
		cout << teachers.at(i).teacherSurname << "\n";
		for (int j = 0; j < 6; j++) {
			cout << teachers.at(i).days[j].lessonNumber <<
				" " << teachers.at(i).days[j].className << "\n";
		}
	}
}

static void output() {
	string number_output;
	string message = "OUTPUT\nHow do you want to print the records?\n"
		"1. Output to the console\n2. Writing data to a file\n";
	bool isNotCorrect = true;
	do {
		cout << message;
		cin >> number_output;
		if (number_output == "1") {
			consoleOutput();
			isNotCorrect = false;
		}
		if (number_output == "2") {
			outputFile();
			isNotCorrect = false;
		}
	} while (isNotCorrect);
}

static void addRecords() {
	string number_add;
	string message = "ADD\nHow do you want to add the record?\n"
		"1. Keyboard\n2. File\n0. Exit\n";
	bool isNotCorrect = true;
	do {
		cout << message;
		cin >> number_add;
		if (number_add == "1") {
			inputConsole();
		}
		if (number_add == "2") {
			inputFile();
		}
		if (number_add == "0") {
			isNotCorrect = false;
		}
	} while (isNotCorrect);
}

static void changeValue(int index) {
	string number_change;
	string message = "CHANGE\nWhat do you want to change?\n"
		"1. Last name\n2. Workshop name\n"
		"3. Numbers of items A\n4. Numbers of items B\n"
		"5. Numbers of items C\n6. All fields\n"
		"7. All fields from file\n0. Exit\n";
	bool isNotCorrect = true;
	do {
		cout << message;
		cin >> number_change;
		if (number_change == "1") {
			cout << LAST_NAME_OF_THE_WORKER;
			teachers.at(index).teacherSurname = enterSurname();
		}
		if (number_change == "2") {
			cout << NAME_OF_THE_WORKSHOP;
			enterDay(teachers.at(index));
		}
		if (number_change == "3") {
			cout << NUMBERS_OF_PRODUCTS_A;
			fillTeachers(teachers.at(index));
		}
		if (number_change == "0") {
			isNotCorrect = false;
		}
	} while (isNotCorrect);
}

Михаил Мороз, [31.03.20 13:11]
static void input() {
	string number_input;
	string message = "INPUT\nHow do you want to enter the records?\n"
		"1. Keyboard input\n"  "2. Reading data from a file\n";
	bool isNotCorrect = true;
	do {
		cout << message;
		cin >> number_input;
		if (number_input == "1") {
			inputConsole();
			isNotCorrect = false;
		}
		if (number_input == "2") {
			inputFile();
			isNotCorrect = false;
		}
	} while (isNotCorrect);
}

int main() {
	input();
	process();
	output();
	return 0;
}

Михаил Мороз, [31.03.20 13:11]
static int searchIndexBySurname() {
	int indexOfRecord = 0;
	bool isNotCorrect = true;
	string surname;
	do {
		cout << "Enter the last name for which you want to search the record:\n";
		cin >> surname;
		for (int i = 0; i < teachers.size(); i++) {
			if (teachers.at(i).teacherSurname == surname) {
				indexOfRecord = i;
				isNotCorrect = false;
			}
		}
		isNotCorrect = isExit(isNotCorrect);
	} while (isNotCorrect);
	return indexOfRecord;
}

static void changeRecords() {
	string number_change;
	string message = "CHANGE\nHow do you want to search the record?\n"
		"1. By last name\n2. By workshop name\n0. Exit\n";
	bool isNotCorrect = true;
	int indexOfRecord;
	do {
		cout << message;
		cin >> number_change;
		if (number_change == "1") {
			indexOfRecord = searchIndexBySurname();
			changeValue(indexOfRecord);
		}
		if (number_change == "0") {
			isNotCorrect = false;
		}
	} while (isNotCorrect);
}

static void removeRecordLikeInFile(string arr[]) {
	for (int j = 0; j < teachers.size(); j++) {
		if (teachers.at(j).teacherSurname == (arr[0])) {
			teachers.erase(teachers.begin() + j);
		}
	}
}

static void readFileRemove(const string& pathname) {
	string line;
	string array[5];
	stringstream string_stream;
	ifstream in(pathname);
	while (getline(in, line)) {
		string_stream << line;
		int i = 0;
		while (i < 5) {
			string_stream >> array[i];
			i++;
		}
		removeRecordLikeInFile(array);
		string_stream.clear();
		string_stream.sync();
	}
}

static void deleteByRecordsInFile() {
	string pathname;
	bool isNotCorrect = true;
	do {
		cout << "Enter path to the file:\n";
		cin >> pathname;
		ifstream in(pathname);
		if (in) {
			cout << "File Found!\n";
			readFileRemove(pathname);
			isNotCorrect = false;
		}
		else {
			cout << "File not found\n";
		}
		isNotCorrect = isExit(isNotCorrect);
	} while (isNotCorrect);
}

static void deleteBySurname() {
	bool isNotCorrect = true;
	string surname;
	do {
		cout << "Enter the last name for which you want to delete the record:\n";
		cin >> surname;
		for (int i = 0; i < teachers.size(); i++) {
			if (teachers.at(i).teacherSurname == surname) {
				teachers.erase(teachers.begin() + i);
				isNotCorrect = false;
			}
		}
		isNotCorrect = isExit(isNotCorrect);
	} while (isNotCorrect);
}

static void deleteRecords() {
	string number_delete;
	string message = "DELETE\nHow do you want to delete the record?\n"
		"1. By last name\n2. By workshop name\n"
		"3. By records that are in the file\n0. Exit\n";
	bool isNotCorrect = true;
	do {
		cout << message;
		cin >> number_delete;
		if (number_delete == "1") {
			deleteBySurname();
		}
		if (number_delete == "2") {
			deleteByRecordsInFile();
		}
		if (number_delete == "0") {
			isNotCorrect = false;
		}
	} while (isNotCorrect);
}

static void process() {
	string number_process;
	string message = "PROCESSING\n1. Delete selected records\n"
		"2. Change selected records\n3. Add records\n0. Exit\n";
	bool isNotCorrect = true;
	do {
		cout << message;
		cin >> number_process;
		if (number_process == "1") {
			deleteRecords();
		}
		if (number_process == "2") {
			changeRecords();
		}
		if (number_process == "3") {
			addRecords();
		}
		if (number_process == "0") {
			isNotCorrect = false;
		}
	} while (isNotCorrect);
}