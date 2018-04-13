// TJP04.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int load(string name, Bill** bill) {
	ifstream in(name);
	string jb10, jb9, jb8;
	int i = 0;
	int j = 0;
	do {
		in >> jb10 >> jb9 >> jb8;
		if (jb10 == "Confirmation" && jb9 == "#") {
			(*bill)[i].signedHash = atoi(jb8.c_str());
			in >> jb10 >> jb9 >> jb8;
			(*bill)[i].custID = jb8;
			i += 1;
			j = 0;
		}
		else {
			(*bill)[i].tj[j].name = jb10;
			(*bill)[i].tj[j].quantity = jb9;
			(*bill)[i].tj[j].cost = jb8;
		}
	} while (!in.fail());
	return i;
}

void creditCardCompany(string input, string output) {

}

int main(){
	Bill** tj;
	(*tj) = new Bill[20];
	int i;
	i = load("test_04_data.txt", tj);
	cout << i << endl;
    return 0;
}

