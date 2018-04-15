// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
//#include<string>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include"sha256.h"
using namespace std;



// TODO: 在此处引用程序需要的其他头文件
struct Item {
	string* name;
	string* quantity;
	string* cost;
};

struct Bill {
	int num;
	string signedHash;
	string custID;
	Item* tj;
};