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
	int n2 = zzk.num;
	//cerr << n2;
	for (int i = 0; i < n2; i++) {
		it=it+zzk.tj[i].name+ zzk.tj[i].quantity+ zzk.tj[i].cost;
	}
	cerr << sign(it, zzk.custID) << endl;
	cerr << zzk.custID << endl;
	cerr << zzk.signedHash << endl << endl;
	if (sign(sha256(it), zzk.custID) == zzk.signedHash) {
		return true;
		//std::cerr << endl << "true" << endl;
	}
	return false;
}

void load(string name,Bill* bill, int &n) {
	ifstream in(name);
	string jb10, jb9, jb8;
	int i = 0;
	int k = 0;
	int &j = k;
	while(!in.fail()) {
		in >> jb10 >> jb9 >> jb8;
		if (jb10 == "Confirmation" && jb9 == "#") {
			(bill)[n].signedHash = atoi(jb8.c_str());
			//cerr << jb10 << jb9 << (bill)[i].signedHash << endl;//remove
			in >> jb10 >> jb9 >> jb8;
			(bill)[n].custID = jb8;
			//cerr << jb10 << jb9 << (bill)[i].custID << endl;//remove
			(bill)[n].num = k;
			//std::cerr << endl <<"j="<< k << endl;
			i += 1;
			n += 1;
			//std::cerr << endl << "n=" << n << endl;
			j = 0;
		}
		else if (!AllisNum(jb9)) {
			jb10 = jb10 + jb9;
			in >> jb9;
			(bill)[n].tj[j].name = jb10;
			//cerr << (bill)[i].tj[j].name << '\t'; // remove
			(bill)[n].tj[j].quantity = jb8;
			//cerr << (bill)[i].tj[j].quantity << '\t';//remove
			(bill)[n].tj[j].cost = jb9;
			//cerr << (bill)[i].tj[j].cost << '\n';//remove
			j = j + 1;
		}
		else {
			(bill)[n].tj[j].name = jb10;
			//cerr << (bill)[i].tj[j].name << '\t';//remove
			(bill)[n].tj[j].quantity = jb9;
			//cerr << (bill)[i].tj[j].quantity << '\t';//remove
			(bill)[n].tj[j].cost = jb8;
			//cerr << (bill)[i].tj[j].cost << '\n';//remove
			j = j + 1;
		}
		in.get();//获取之后一个字符
		if (in.peek() == EOF) {
			break;
		}
	}
	return;
}

Bill add(ifstream &in, ofstream &out,int &n) {
	out << '\n';
	Bill zzk;
	zzk.tj = new Item[1000];
	string jb10;
	string jb9;
	string jb8;
	int i = 0;
	int k = 0;
	int &j = k;
	while (!in.fail()) {
		in >> jb10 >> jb9 >> jb8;
		if (jb10 == "Confirmation" && jb9 == "#") {
			zzk.signedHash = atoi(jb8.c_str());
			out <<'\t'<< jb10 << jb9 << zzk.signedHash << endl;
			in >> jb10 >> jb9 >> jb8;
			zzk.custID = jb8;
			out <<'\t'<< jb10 << jb9 << zzk.custID << endl;//remove
			zzk.num = k;
			//std::cerr << endl << "j=" << k << endl;
			i += 1;
			n += 1;
			//std::cerr << endl << "n=" << n << endl;
			return zzk;
		}
		else if (!AllisNum(jb9)) {
			jb10 = jb10 + jb9;
			in >> jb9;
			zzk.tj[k].name = jb10;
			out <<'\t'<< zzk.tj[j].name << '\t'; // remove
			zzk.tj[k].quantity = jb8;
			out <<'\t' <<zzk.tj[j].quantity << '\t';//remove
			zzk.tj[k].cost = jb9;
			out << '\t'<<zzk.tj[j].cost << '\n';//remove
			j = j + 1;
		}
		else {
			zzk.tj[k].name = jb10;
			out << '\t'<<zzk.tj[j].name << '\t';//remove
			zzk.tj[k].quantity = jb9;
			out << '\t'<<zzk.tj[j].quantity << '\t';//remove
			zzk.tj[k].cost = jb8;
			out << '\t'<<zzk.tj[j].cost << '\n';//remove
			j = j + 1;
		}
		in.get();//获取之后一个字符
		if (in.peek() == EOF) {
			break;
		}
		else {
			in.seekg(-1, ios_base::cur);
		}
	}
	return zzk;
}

void show(ifstream &in, ofstream &out, Bill* bill, int &n) {

	string jb10="";
	string jb9="";
	string jbtemp;
	char x;
	int j = 0;
	in >> jb10;
	x=in.get();
	in.seekg(-1, ios_base::cur);
	out << " "<<  jb10 << endl;
	const char* temp = jb10.c_str();

	if (jb10=="bad" && x!=' ') {	
		bool o = 0;
		for (int i = 0; i < n; i++) {
			if (not(Good(bill[i]))) {
				j += 1;
				out << '#' << j << endl;
				out << '\t' << bill[i].custID << endl;
				out << '\t' << bill[i].signedHash << endl;
				out << '\t' << "Total Items: " << bill[i].num << endl;
				o += 1;
			}
			
		}
		if (!o) {
			out << "No bad bills to show." << endl;
		}
	}else if (jb10 == "good" && x!=' ') {
		for (int i = 0; i < n; i++) {
			if (Good(bill[i])) {
				j += 1;
				out << '#' << j << endl;
				out << '\t' << bill[i].custID << endl;
				out << '\t' << bill[i].signedHash << endl;
				out << '\t' << "Total Items: " << bill[i].num << endl;
			}
		}
	}
	else if (jb10=="good" && x==' '/*“好”和数字*/) {
		int k = atoi(temp+6);
		for (int i = 0; i < n; i++) {
			if (Good(bill[i])) {
				j += 1;
				if (j == k) {
					for (int l = 0; l < bill[i].num; i++) {
						out << '\t' << bill[i].tj[l].name << '\t'<<bill[i].tj[l].quantity <<'\t' <<bill[i].tj[l].cost << endl;
						out << "Confirmation # " << bill[i].signedHash << endl;
						out << "Cust ID: " << bill[i].custID << endl;
						return;
					}
				}
			}
		}
		out << '\t' << "Sorry bill #" << k << " not gound." << endl;

	}else if (jb10=="bad" && x==' '/*“坏”和数字*/) {
		int k = atoi(temp+4);
		for (int i = 0; i < n; i++) {
			if (!Good(bill[i])) {
				j += 1;
				if (j == k) {
					for (int l = 0; l < bill[i].num; i++) {
						out << '\t' << bill[i].tj[l].name << '\t' << bill[i].tj[l].quantity << '\t' << bill[i].tj[l].cost << endl;
						out << "Confirmation # " << bill[i].signedHash << endl;
						out << "Cust ID: " << bill[i].custID << endl;
						return;
					}

				}
			}
		}
		out << '\t' << "Sorry bill #" << k << " not gound." << endl;

	}
	return;
}

void achieve(ifstream &in, ofstream &out, Bill* bill, int &n) {//n写的是bill array里面有几个元素
	string jb10;
	int jb9;//bad之后跟的数字
	int j = 0;
	const char* arr;
	getline(in, jb10);
	if (jb10.size() == 6/*condition bad*/) {
		arr = jb10.c_str();
		arr += 5;
		jb9=atoi(arr);
		for (int i = 0; i < n; i++) {
			if (!Good(bill[i])) {
				j += 1;
				if (j == jb9) {
					for (int k = i; k < n-1; k++) {//从i开始到最后
						bill[k] = bill[k + 1];
						n -= 1;
						out << '\t' << "Bill #" << jb9 << " achieved.\n";
						return;
					}

				}
			}
		}
		out << '\t' << "Sorry bill #" << jb9 << " not found.\n";
		return;
	}else if (jb10.size() == 7/*condition good*/) {
		arr = jb10.c_str();
		arr += 6;
		jb9 = atoi(arr);
		for (int i = 0; i < n; i++) {
			if (Good(bill[i])) {
				j += 1;
				if (j == jb9) {
					for (int k = i; k < n - 1; k++) {//从i开始到最后
						bill[k] = bill[k + 1];
						n -= 1;
						out << '\t' << "Bill #" << jb9 << " achieved.\n";
						return;
					}

				}
			}
		}
		out << '\t' << "Sorry bill #" << jb9 << " not found.\n";
		return;
	}
	return;
}

void save(ifstream &in, ofstream &out, Bill* bill, int n) {
	string jb10;
	in >> jb10;
	out << jb10 << endl;
	ofstream ofs(jb10);
	for (int i = 0; i < n; i++) {
		int justin = bill[i].num;
		for (int j = 0; j < justin; j++) {
			ofs <<'\t' << bill[i].tj[j].name << '\t' << bill[i].tj[j].quantity << '\t' << bill[i].tj[j].cost << endl;
		}
		ofs <<'\t' <<  "Confirmation # " << bill[i].signedHash << endl;
		ofs << '\t'<< "Cust ID: " << bill[i].custID << endl;

	}
}

void creditCardCompany(string input, string output) {
	ifstream in(input);
	ofstream out(output);
	Bill* UCSB = new Bill[100];
	for (int i = 0; i < 100; i++) {
		UCSB[i].tj = new Item[100];
	}
	int *n = new int;
	*n = 0;
	string command;
	string jb0;
	while (!in.fail()) {
		in >> command;
		out << "Command: " << command;
		if (command == "load") {
			in >> jb0;
			out << ' ' << jb0 << endl;
			load(jb0,UCSB, *n);
			out << '\t'<< "Loaded: " << n << endl;
		}
		else if (command == "add") {
			UCSB[*n-1] = add(in,out,*n);
		}
		else if (command == "show") {
			show(in, out, UCSB, *n);
		}
		else if (command == "achieve") {
			achieve(in, out, UCSB, *n);
		}
		else if (command == "save") {
			save(in, out, UCSB, *n);
		}
		in.get();//获取之后一个字符
		if (in.peek() == EOF) {
			break;
		}
		else {
			in.seekg(-1, ios_base::cur);
		}
	}
	return;
	
}


int main(){
	creditCardCompany("test_09_input.txt", "test_09_output.txt");
    return 0;
}

