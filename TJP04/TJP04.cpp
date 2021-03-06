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

bool Good(Bill** zzk,int nu) {
	string it="";
	string temp2;
	int n2 =((*zzk)[nu]).num;
	int *op = new int;
	int *og = new int;
	//cerr << n2;
	for (int i = 0; i < n2; i++) {
		if (!AllisNum((*((*zzk)[nu]).tj[i].quantity))) {
			continue;
		}
		string temp3 = (*((*zzk)[nu]).tj[i].quantity);
		if (temp3 == "") continue;
		int ab = stoi(temp3);
		string temp4 = *((*zzk)[nu]).tj[i].cost;
		double cd = stod(temp4);
		double ef = ab * cd;
		stringstream ss;
		ss << ef;
		string t;
		t=ss.str();
		ss.clear();
		//cerr << ef << endl;
		it = it + (*((*zzk)[nu]).tj[i].name)+ t;
	}
	temp2 = (*zzk)[nu].custID;
	if (it == "") {
		return false;
	}
	
	//std::transform(it.begin(), it.end(), it.begin(), ::tolower);
	cerr << it << endl;
	string hash = sha256(it);
	cerr << "this is: " << sign(hash, temp2) << std::endl;
	cerr << "this id: " << atoi((((*zzk)[nu]).signedHash).c_str()) << endl;
	if (sign(sha256(it), temp2) == atoi((((*zzk)[nu]).signedHash).c_str())) {
		return true;
		//std::cerr << endl << "true" << endl;
	}
	return false;
}

void load(string name,Bill*& bill, int &n, int *n2) {
	ifstream in(name);
	string jb10, jb9, jb8;
	int i = 0;
	int k = 0;
	int l = 10;
	int &j = k;
	while(!in.fail()) {
		in >> jb10 >> jb9 >> jb8;
		if (jb10 == "Confirmation" && jb9 == "#") {
			(bill)[n].signedHash = (jb8);
			//cerr << jb10 << jb9 << (((bill)[i].signedHash)) << endl;//remov
			in >> jb10 >> jb8;

			(bill)[n].custID = jb8;
			//cerr << jb10 << jb9 << (bill)[i].custID << endl;//remove
			(bill)[n].num = k;
			//std::cerr << endl <<"j="<< k << endl;
			i += 1;
			n += 1;
			if (n >= ((*n2)-1)) {
				(*n2) += 10;
				Bill* jbjun10=new Bill[*n2];
				memcpy(jbjun10, bill, sizeof(Bill)*n);
				//delete(bill);
				bill = new Bill[l];
				for (int to = n; to< l; to++) {
					bill[to].tj = new Item[10];
				}
				bill = jbjun10;
			}
			//std::cerr << endl << "n=" << n << endl;
			j = 0;
		}
		else if (!AllisNum(jb9)) {
			if (n >= ((*n2) - 1)) {
				(*n2) += 10;
				Bill* jbjun10 = new Bill[*n2];
				memcpy(jbjun10, bill, sizeof(Bill)*n);
				//delete(bill);
				bill = new Bill[l];
				for (int t = 0; t <(n); t++) {
					bill[t].tj = new Item[jbjun10[n].num];
				}
				for (int to = n; to< l; to++) {
					bill[to].tj = new Item[10];
				}
				memcpy(bill, jbjun10, sizeof(Bill)*(*n2));
			}
			if (j >= l-1 || j==0) {
				if (j == 0) {
					bill[n].tj = new Item[10];
				}
				l += 10;
				Bill jbjun;
				jbjun.tj = new Item[l];
				memcpy(jbjun.tj, bill[n].tj, sizeof(Item)*j);
				//delete(bill[n].tj);
				bill[n].tj = new Item[l];
				memcpy( bill[n].tj, jbjun.tj, sizeof(Item)*l);
			}
			jb10 = jb10 + jb9;
			in >> jb9;
			(bill)[n].tj[k].name = new string;
			*((bill)[n].tj[k].name)=jb10;
			//cerr << (bill)[i].tj[j].name << '\t'; // remove
			(bill)[n].tj[k].quantity = new string;
			(*(bill)[n].tj[k].quantity) = jb8;
			//cerr << (bill)[i].tj[j].quantity << '\t';//remove
			(bill)[n].tj[k].cost = new string;
			*((bill)[n].tj[k].cost) = jb9;
			//cerr << (bill)[i].tj[j].cost << '\n';//remove
			j = j + 1;

		}
		else {
			if (n >= ((*n2) - 1)) {
				(*n2) += 10;
				Bill* jbjun10 = new Bill[*n2];
				memcpy(jbjun10, bill, sizeof(Bill)*n);
				//delete(bill);
				bill = new Bill[l];
				for (int t = 0; t <(n); t++) {
					bill[t].tj = new Item[jbjun10[n].num];
				}
				for (int to = n; to< l; to++) {
					bill[to].tj = new Item[10];
				}
				memcpy(bill,jbjun10, sizeof(Bill)*(*n2));
			}
			if (j >= l-1 || j==0) {
				l += 10;
				Bill jbjun;
				jbjun.tj = new Item[l];
				//cerr << l << endl;
				memcpy(jbjun.tj, bill[n].tj, (j) * sizeof(Item));
				//delete(bill[n].tj);
				bill[n].tj = new Item[l];
				memcpy(bill[n].tj, jbjun.tj, (l) * sizeof(Item));
			}
			(bill)[n].tj[j].name = new string;
			(*(bill)[n].tj[j].name)=jb10;
			//cerr << (bill)[i].tj[j].name << '\t';//remov
			(bill)[n].tj[j].quantity = new string;
			(*bill[n].tj[j].quantity) = jb9;
			//cerr << (bill)[i].tj[j].quantity << '\t';//remove
			(bill)[n].tj[j].cost = new string;
			(*(bill)[n].tj[j].cost) = jb8;
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
	zzk.tj = new Item[10];
	string jb10;
	string jb9;
	string jb8;
	int i = 0;
	int l = 10;
	int k = 0;
	int &j = k;
	while (!in.fail()) {
		in >> jb10 >> jb9 >> jb8;
		if (jb10 == "Confirmation" && jb9 == "#") {
			zzk.signedHash = to_string(atoi(jb8.c_str()));
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
			if (j >= l-1 || j == 0) {
				l += 10;
				Bill jbjun;
				jbjun.tj = new Item[l];
				memcpy(jbjun.tj,zzk.tj,(l-10)*sizeof(Item));
				//delete(zzk.tj);
				zzk.tj = new Item[l];
				memcpy(zzk.tj, jbjun.tj, (l) * sizeof(Item));
			}
			jb10 = jb10 + jb9;
			in >> jb9;
			zzk.tj[k].name = new string;
			(*(zzk.tj[k].name)) = jb10;
			out <<'\t'<< *(zzk.tj[j].name) << '\t'; // remove
			zzk.tj[k].quantity = new string;
			(*(zzk.tj[k].quantity)) = jb8;
			out <<'\t' <<*(zzk.tj[j].quantity) << '\t';//remove
			zzk.tj[k].cost = new string;
			*(zzk.tj[k].cost) = jb9;
			out << '\t'<<jb9 << '\n';//remove
			j = j + 1;
			
		}
		else {
			if (j >= l-1 || j == 0) {
				l += 10;
				Bill jbjun;
				jbjun.tj = new Item[l];
				memcpy(jbjun.tj, zzk.tj, (l-10)*sizeof(Item));
				//delete(zzk.tj);
				zzk.tj = new Item[l];
				memcpy(zzk.tj, jbjun.tj,  (l) * sizeof(Item));
			}
			zzk.tj[k].name = new string;
			*(zzk.tj[k].name) = jb10;
			out << '\t'<<*(zzk.tj[k].name) << '\t';//remove
			zzk.tj[k].quantity = new string;
			(*(zzk.tj[k].quantity)) = jb9;
			out << '\t'<<*(zzk.tj[k].quantity) << '\t';//remove
			zzk.tj[k].cost = new string;
			(*(zzk.tj[k].cost)) = jb8;
			out << '\t'<< *(zzk.tj[k].cost) << '\n';//remove
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

void show(ifstream &in, ofstream &out, Bill*& bill, int &n) {

	string jb10="";
	string jb9="";
	string jb8 = "";
	string jbtemp;
	char x;
	int j = 0;
	in >> jb10;
	in.get(x);
	in.seekg(-1, ios_base::cur);
	out << " "<<  jb10;
	const char* temp = jb10.c_str();
	Bill** jb100 = new Bill*;
	(*jb100) = bill;

	if (jb10=="bad" && x!=' ') {
		bool o = 0;
		out << endl;
		for (int i = 0; i < n-1; i++) {
			if (not(Good(jb100,i))) {
				if (bill[i].custID=="" || bill[i].signedHash=="") continue;
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
		bool o = 0;
		out << endl;
		for (int i = 0; i < n-1; i++) {
			if (Good(jb100,i)) {
				j += 1;
				out << '#' << j << endl;
				out << '\t' << bill[i].custID << endl;
				out << '\t' << bill[i].signedHash << endl;
				out << '\t' << "Total Items: " << bill[i].num << endl;
			}
		}
		if (o) {
			out << "No good bills to show." << endl;
		}
	}
	else if (jb10=="good" && x==' '/*“好”和数字*/) {
		in >> jb8;
		out <<" "<< jb8 << endl;
		int k = atoi(jb8.c_str());
		for (int i = 0; i < n-1; i++) {
			if (Good(jb100,i)) {
				j += 1;
				if (j == k) {
					for (int l = 0; l < bill[i].num; i++) {
						out << '\t' << (*bill[i].tj[l].name) << '\t'<<(*bill[i].tj[l].quantity) <<'\t' <<*(bill[i].tj[l].cost) << endl;
					}
					out <<"\t" <<  "Confirmation # " << (bill[i].signedHash) << endl;
					out << "\t" << "Cust ID: " << (bill[i].custID) << endl;
					return;
				}
			}
		}
		out << '\t' << "Sorry bill #" << k << " not gound." << endl;

	}else if (jb10=="bad" && x==' '/*“坏”和数字*/) {
		in >> jb8;
		out <<" "<< jb8 << endl;
		int k = atoi(jb8.c_str());
		for (int i = 0; i < n-1; i++) {
			if (!Good(jb100,i)) {
				j += 1;
				if (j == k) {
					for (int l = 0; l < bill[i].num; i++) {
						out << '\t' << (*bill[i].tj[l].name) << '\t' << (*bill[i].tj[l].quantity) << '\t' << (*bill[i].tj[l].cost) << endl;
						
					}
					out << '\t' << "Confirmation # ";
					//cerr << "this is" << bill[i].signedHash << endl;
					jb8 = ((bill[i].signedHash));//这里卡住了，出不出来，但是如果把*去掉的话好像是正常的 是不是我的指针退出一个函数就被删掉了的问题
					out << (bill[i].signedHash) << endl;
					out << '\t' << "Cust ID: " << ((bill[i].custID)) << endl;
					return;
				}
			}
		}
		out << '\t' << "Sorry bill #" << k << " not gound." << endl;

	}
	return;
}

void achieve(ifstream &in, ofstream &out, Bill*& bill, int &n) {//n写的是bill array里面有几个元素
	string jb10;
	int jb9;//bad之后跟的数字
	int j = 0;
	const char* arr;
	Bill** jb100 = new Bill*;
	(*jb100) = bill;
	getline(in, jb10);
	if (jb10.size() == 6/*condition bad*/) {
		arr = jb10.c_str();
		arr += 5;
		jb9=atoi(arr);
		for (int i = 0; i < n; i++) {
			if (!Good(jb100,i)) {
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
			if (Good(jb100,i)) {
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

void save(ifstream &in, ofstream &out, Bill*& bill, int n) {
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
	Bill* UCSB = new Bill[10];
	for (int i = 0; i < 10; i++) {
		UCSB[i].tj = new Item[10];
	}
	int *n = new int;
	int *n2 = new int;
	*n = 0;
	*n2 = 10;
	string command;
	string jb0;
	while (!in.fail()) {
		in >> command;
		out << "Command: " << command;
		if (command == "load") {
			int jb00 = *n;
			in >> jb0;
			out << ' ' << jb0 << endl;
			load(jb0,UCSB, *n,n2);
			out << '\t'<< "Loaded: " << ((*n)-jb00) << endl;
		}
		else if (command == "add") {
			if (*n >= ((*n2) - 1)) {
				(*n2) += 10;
				Bill* jbjun9 = new Bill[*n2];
				memcpy(jbjun9, UCSB, sizeof(Bill)*(*n));
				UCSB = new Bill[*n2];
				memcpy(UCSB,jbjun9 , sizeof(Bill)*(*n));
			}
			Bill* tu = new Bill;
			*tu = add(in, out, (*n));
			*(UCSB +(*n)) = *tu;
			
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


void main(){
	creditCardCompany("test_08_input.txt", "test_08_output.txt");
    return;
}