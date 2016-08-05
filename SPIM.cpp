#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include <fstream>
#include<cmath>
#include<map>
#include<utility>
#include "Work.hpp"
#include "Pre.hpp"
typedef unsigned char byte;

using namespace std;

int main(int argc, char *argv[]){
	//freopen("Code.txt", "w", stdout);
	//fin.open(argv[1]);
	Prepare_Register();
	Prepare_Instruction();
	//read(argv[1]);
	Registers[29] = Registers[30] = 299999;
	InstructionLine.push_back(Instruct(0));
	read("array_test1-mahaojun.s");
	
/*	for (int i = 0; i < LabelArray[0].size(); ++i){
		cout << LabelArray[0][i] << " " << TextLabel[LabelArray[0][i]] << endl;
	}
	for (int i = 0; i < LabelArray[1].size(); ++i){
		cout << LabelArray[1][i] << " " << DataLabel[LabelArray[1][i]] << endl;
	}
	printf("\n");*/
	int n = InstructionLine.size();
	/*for (int i = 1; i < n; ++i){
		printf("Line:%d ", i);
		printf("Kind:%d ", InstructionLine[i].Kind);
		printf("Rdest:%d ", InstructionLine[i].Rdest);
		printf("Rsrc1:%d ", InstructionLine[i].Rsrc1);
		printf("Rsrc2:%d ", InstructionLine[i].Rsrc2);
		printf("Offset:%d ", InstructionLine[i].Offset);
		printf("Number:%d ", InstructionLine[i].Number);
		cout << "label:" << InstructionLine[i].lable;
		printf("\n");
	}*/
	work(TextLabel["main"], n);
	//fin.close();
}

