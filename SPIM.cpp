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

bool used[100];

int main(int argc, char *argv[]){
	//fin.open(argv[1]);
	Prepare_Register();
	Prepare_Instruction();
	Registers[29] = Registers[30] = 299999;
	InstructionLine.push_back(Instruct(0));
	read(argv[1]);
/*	for (int i = 0; i < LabelArray[0].size(); ++i){
		cout << LabelArray[0][i] << " " << TextLabel[LabelArray[0][i]] << endl;
	}*/
	/*for (int i = 0; i < LabelArray[1].size(); ++i){
		cerr << LabelArray[1][i] << " " << DataLabel[LabelArray[1][i]] << endl;
	}
	printf("\n");
	for (int i = 1; i <= NewAddress; ++i){
		printf("%d\n", Memory[i]);
	}
	for (int i = 1; i <= NewAddress; ++i){
		printf("%c\n", Memory[i]);
	}*/
	int n = InstructionLine.size();
/*	memset(used, false, sizeof(used));
	for (int i = 1; i <= n; ++i)
		used[InstructionLine[i].Kind] = true;
	for (int i = 1; i <= 59; ++i)
		if (used[i] == true) printf("%d\n", i);*/
/*	for (int i = 1; i < n; ++i){
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

