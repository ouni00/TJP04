// TJP04.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

bool AllisNum(string str){
	for (int i = 0; i < str.size(); i++){
		int tmp = (int)str[i];
		if (tmp >= 48 && tmp <= 57){
			continue;
		}
		else{
			return false;
		}
	}
	return true;
}

bool Good(Bill zzk) {
	string it="";
	for (int i = 0; i < zzk.num; i++) {
		it+=zzk.tj[i].name;
		it += zzk.tj[i].quantity;
		it += zzk.tj[i].cost;
	}
	if (sign(it, zzk.custID) == zzk.signedHash) {
		return true;
	}
	return false;
}

Bill* load(string name, int &n) {
	struct Bill* bill = new Bill[20];
	ifstream in(name);
	string jb10, jb9, jb8;
	int i = 0;
	int j = 0;
	while(!in.fail()) {
		in >> jb10 >> jb9 >> jb8;
		if (jb10 == "Confirmation" && jb9 == "#") {
			(bill)[i].signedHash = atoi(jb8.c_str());
			cerr << jb10 << jb9 << (bill)[i].signedHash << endl;//remove
			in >> jb10 >> jb9 >> jb8;
			(bill)[i].custID = jb8;
			cerr << jb10 << jb9 << (bill)[i].custID << endl;//remove
			(bill)[i].num = j + 1;
			i += 1;
			n += 1;
			j = 0;
		}
		else if (!AllisNum(jb9)) {
			jb10 = jb10 + jb9;
			in >> jb9;
			(bill)[i].tj[j].name = jb10;
			cerr << (bill)[i].tj[j].name << '\t'; // remove
			(bill)[i].tj[j].quantity = jb8;
			cerr << (bill)[i].tj[j].quantity << '\t';//remove
			(bill)[i].tj[j].cost = jb9;
			cerr << (bill)[i].tj[j].cost << '\n';//remove
		}
		else {
			(bill)[i].tj[j].name = jb10;
			cerr << (bill)[i].tj[j].name << '\t';//remove
			(bill)[i].tj[j].quantity = jb9;
			cerr << (bill)[i].tj[j].quantity << '\t';//remove
			(bill)[i].tj[j].cost = jb8;
			cerr << (bill)[i].tj[j].cost << '\n';//remove
		}
		in.get();//获取之后一个字符
		if (in.peek() == EOF) {
			break;
		}
	}
	return bill;
}

Bill add(ifstream &in,int &n) {
	Bill zzk;
	string jb10;
	string jb9;
	string jb8;
	int j = 0;
	while (!in.fail()) {
		in >> jb10 >> jb9 >> jb8;
		if (jb10 == "Confirmation" && jb9 == "#") {
			zzk.signedHash = atoi(jb8.c_str());
			cerr << jb10 << jb9 << zzk.signedHash << endl;//remove
			in >> jb10 >> jb9 >> jb8;
			zzk.custID = jb8;
			cerr << jb10 << jb9 << zzk.custID << endl;//remove
			zzk.num = j + 1;
			cerr << endl << "ZZKAANGYOU: " << zzk.num << endl;
			j = 0;
			n += 1;
			return zzk;
		}
		else if (!AllisNum(jb9)) {
			jb10 = jb10 + jb9;
			in >> jb9;
			zzk.tj[j].name = jb10;
			cerr << zzk.tj[j].name << '\t'; // remove
			zzk.tj[j].quantity = jb8;
			cerr << zzk.tj[j].quantity << '\t';//remove
			zzk.tj[j].cost = jb9;
			cerr << zzk.tj[j].cost << '\n';//remove
		}
		else {
			zzk.tj[j].name = jb10;
			cerr << zzk.tj[j].name << '\t';//remove
			zzk.tj[j].quantity = jb9;
			cerr << zzk.tj[j].quantity << '\t';//remove
			zzk.tj[j].cost = jb8;
			cerr << zzk.tj[j].cost << '\n';//remove
		}
		in.get();//获取之后一个字符
		if (in.peek() == EOF) {
			break;
		}
	}
	return zzk;
}

void show(ifstream &in, ofstream &out, Bill* bill, int n) {
	string jb10;
	string jb9;
	for (int i = 0; i < n; i++) {
		getline(in, jb10);
		cerr << jb10;// remove
		if (jb10.size() == 4/*case bad it's 4because space*/) {
			for (i = 0; i < n; i++) {

			}
		}
	}
}


void creditCardCompany(string input, string output) {
	struct Bill tj;
	int i;
	int n=0;
	string jb10;
	string jb9;
	ifstream in("test_10_input.txt");
	while (!in.eof()) {
		in >> jb10;
		if (jb10 == "show") {
			getline(in, jb9);
			cerr << jb9 << endl;
		}
	}
}

int main(){
	creditCardCompany("ss", "s");
    return 0;
}

