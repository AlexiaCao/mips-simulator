#ifndef __Work
#define __Work

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
#include "Pre.hpp"

using namespace std;
typedef unsigned char byte;
int Registers[34];
int PresentLine;
void ABS(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1]; 
	Registers[InstructionLine[now].Rdest] = abs(a);
}
void ADD(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = b + c;
	Registers[InstructionLine[now].Rdest] = a;
}
void AND(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = b & c;
	Registers[InstructionLine[now].Rdest] = a;
}

void DIV(int now, int level){
	if (InstructionLine[now].unsign){
		unsigned int a = (unsigned int)Registers[InstructionLine[now].Rsrc1];
		unsigned int b;
		if (InstructionLine[now].Rsrc2 == -1) b = (unsigned int)InstructionLine[now].Number;
		else b = (unsigned int)Registers[InstructionLine[now].Rsrc2];	
		Registers[32] = a / b;
		Registers[33] = a % b;
	}
	else{
		int a = Registers[InstructionLine[now].Rsrc1];
		int b;
		if (InstructionLine[now].Rsrc2 == -1) b = InstructionLine[now].Number;
		else b = Registers[InstructionLine[now].Rsrc2];
		Registers[32] = a / b;
		Registers[33] = a % b;
	}
	if (InstructionLine[now].Rdest != -1) Registers[InstructionLine[now].Rdest] = Registers[32];
}

void MUL(int now, int level){
	if (InstructionLine[now].unsign){
		unsigned int b = (unsigned int)Registers[InstructionLine[now].Rsrc1], c;
		if (InstructionLine[now].Rsrc2 == -1) c = (unsigned int)InstructionLine[now].Number;
		else c = (unsigned int)Registers[InstructionLine[now].Rsrc2];		
		unsigned long long a = (unsigned long long)b * c;
		Registers[32] = ((unsigned int)(a >> 32));
		Registers[33] = (unsigned int)(a - ((a >> 32) << 32));
		unsigned int tmp = (unsigned int)a;
		if (InstructionLine[now].Rdest != -1) Registers[InstructionLine[now].Rdest] = tmp;
	}
	else{
		int b = Registers[InstructionLine[now].Rsrc1], c;
		if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
		else c = Registers[InstructionLine[now].Rsrc2];
		long long a = (long long)b * c;
		Registers[32] = (int)(((unsigned long long)a) >> 32);
		Registers[33] = (int)(a - ((((unsigned long long)a) >> 32) << 32));
		int tmp = (int)a;
		if (InstructionLine[now].Rdest != -1) Registers[InstructionLine[now].Rdest] = tmp;
	}
}

void NEG(int now, int level){
	int a;
	a = Registers[InstructionLine[now].Rsrc1];
	Registers[InstructionLine[now].Rdest] = -a;
}

void NOR(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = ~(b | c);
	Registers[InstructionLine[now].Rdest] = a;
}
void NOT(int now, int level){
	int a;
	a = Registers[InstructionLine[now].Rsrc1];
	Registers[InstructionLine[now].Rdest] = ~a;
}

void OR(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = b | c;
	Registers[InstructionLine[now].Rdest] = a;
}
void REM(int now, int level){
	if (InstructionLine[now].unsign){
		unsigned int a = (unsigned int)Registers[InstructionLine[now].Rsrc1], b;
		if (InstructionLine[now].Rsrc2 == -1) b = (unsigned int)InstructionLine[now].Number;
		else b = (unsigned int)Registers[InstructionLine[now].Rsrc2];
		Registers[InstructionLine[now].Rdest] = (int)((unsigned int)(a % b));
	}
	else{
		int a = Registers[InstructionLine[now].Rsrc1], b;
		if (InstructionLine[now].Rsrc2 == -1) b = InstructionLine[now].Number;
		else b = Registers[InstructionLine[now].Rsrc2];
		Registers[InstructionLine[now].Rdest] = a % b;
	}
}
void ROL(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = (b << c) | ((unsigned)b >> (32 - c));
	Registers[InstructionLine[now].Rdest] = a;
}
void ROR(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = ((unsigned)b >> c) | (b << (32 - c));
	Registers[InstructionLine[now].Rdest] = a;
}
void SLL(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2] % 32;
	a = b << (c % 32);
	Registers[InstructionLine[now].Rdest] = a;
}
void SRA(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2] % 32;
	a = b << (c % 32);
	Registers[InstructionLine[now].Rdest] = a;
}
void SRL(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2] % 32; 
	a = (unsigned) b >> (c % 32);
	Registers[InstructionLine[now].Rdest] = a;
}
void SUB(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = b - c;
	Registers[InstructionLine[now].Rdest] = a;
}
void XOR(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = b ^ c;
	Registers[InstructionLine[now].Rdest] = a;
}
void LI(int now, int level){
	int a = InstructionLine[now].Number;
	if (InstructionLine[now].unsign) Registers[InstructionLine[now].Rdest] = (a & 0xffff) << 16;
	else Registers[InstructionLine[now].Rdest] = a;
	
}
void SEQ(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = (b == c);
	Registers[InstructionLine[now].Rdest] = a;
}
void SGE(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign) a = ((unsigned int)b >= (unsigned int)c);
	else a = (b >= c);
	Registers[InstructionLine[now].Rdest] = a;
}
void SGT(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign) a = ((unsigned int)b > (unsigned int)c);
	else a = (b > c);
	Registers[InstructionLine[now].Rdest] = a;
}
void SLE(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign) a = ((unsigned int)b <= (unsigned int)c);
	else a = (b <= c);
	Registers[InstructionLine[now].Rdest] = a;
}
void SLT(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign) a = ((unsigned int)b < (unsigned int)c);
	else a = (b < c);
	Registers[InstructionLine[now].Rdest] = a;
}
void SNE(int now, int level){
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	a = (b != c);
	Registers[InstructionLine[now].Rdest] = a;
}
void B(int now, int level){
	PresentLine = TextLabel[InstructionLine[now].lable];
}
void BEQ(int now, int level){
	int a, b;
	a = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) b = InstructionLine[now].Number;
	else b = Registers[InstructionLine[now].Rsrc2];
	if (a == b) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BEQZ(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a == 0) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BGE(int now, int level){
	int a, b;
	a = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) b = InstructionLine[now].Number;
	else b = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign){
		if ((unsigned int)a >= (unsigned int)b) PresentLine = TextLabel[InstructionLine[now].lable];
	}
	else if (a >= b) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BGEZ(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a >= 0)	PresentLine = TextLabel[InstructionLine[now].lable];
}
void BGEZAL(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a >= 0){
		Registers[31] = now + 1;
		PresentLine = TextLabel[InstructionLine[now].lable];
	}
}
void BGT(int now, int level){
	int a, b;
	a = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) b = InstructionLine[now].Number;
	else b = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign){
		if ((unsigned int)a > (unsigned int)b) PresentLine = TextLabel[InstructionLine[now].lable];
	}
	else if (a > b) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BGTZ(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a > 0)	PresentLine = TextLabel[InstructionLine[now].lable];
}
void BLE(int now, int level){
	int a, b;
	a = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) b = InstructionLine[now].Number;
	else b = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign){
		if ((unsigned int)a <= (unsigned int)b) PresentLine = TextLabel[InstructionLine[now].lable];
	}
	else if (a <= b) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BLEZ(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a <= 0)	PresentLine = TextLabel[InstructionLine[now].lable];
}
void BGZAL(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a >= 0){
		Registers[31] = now + 1; 
		PresentLine = TextLabel[InstructionLine[now].lable];
	}
}
void BLTZAL(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a >= 0){
		Registers[31] = now + 1; 
		PresentLine = TextLabel[InstructionLine[now].lable];
	}
}
void BLT(int now, int level){
	int a, b;
	a = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) b = InstructionLine[now].Number;
	else b = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign){
		if ((unsigned int)a < (unsigned int)b) PresentLine = TextLabel[InstructionLine[now].lable];
	}
	else if (a < b) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BLTZ(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a < 0)	PresentLine = TextLabel[InstructionLine[now].lable];
}
void BNE(int now, int level){
	int a, b;
	a = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) b = InstructionLine[now].Number;
	else b = Registers[InstructionLine[now].Rsrc2];
	if (a != b) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BNEZ(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a != 0)	PresentLine = TextLabel[InstructionLine[now].lable];
}
void J(int now, int level){
	PresentLine = TextLabel[InstructionLine[now].lable];
}
void JAL(int now, int level){
	Registers[31] = PresentLine + 1; 
	PresentLine = TextLabel[InstructionLine[now].lable];
}
void JALR(int now, int level){
	int address =  Registers[InstructionLine[now].Rsrc1];
	Registers[31] = PresentLine + 1; 
	PresentLine = address;
}
void JR(int now, int level){
	int address =  Registers[InstructionLine[now].Rsrc1];
	PresentLine = address;
}
void LA(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	Registers[InstructionLine[now].Rdest] = address;
}
void LB(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	int a = Memory[address];
	if (InstructionLine[now].unsign) Registers[InstructionLine[now].Rdest] = ((a >> 7) ? -1 : 1) * (a & ((1 << 7) - 1));
	else Registers[InstructionLine[now].Rdest] = a;
}
void LD(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	unsigned long long a = 0llu;
	for (int i = 0; i < 8; ++i) a = (a << 8) + Memory[address + i];
	Registers[InstructionLine[now].Rdest] = (int)((unsigned long long)(a >> 32));
	Registers[InstructionLine[now].Rdest + 1] = (int)((unsigned long long)(a - ((a >> 32) << 32)));
}
void LH(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	int a = (Memory[address] << 8) | Memory[address + 1];
	if (InstructionLine[now].unsign) Registers[InstructionLine[now].Rdest] = (unsigned int)a;
	else Registers[InstructionLine[now].Rdest] = a;
}
void LW(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	int a = 0, i;
	for (i = 0; i < 4; ++i)	a = (a << 8) | Memory[address + i];
	Registers[InstructionLine[now].Rdest] = (unsigned int)a;
}
void SB(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	unsigned int a = Registers[InstructionLine[now].Rsrc2];
	Memory[address] = (unsigned char)a;
}
void SD(int now, int level){
	int address, i;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	unsigned int a = Registers[InstructionLine[now].Rsrc2];
	unsigned int b = Registers[InstructionLine[now].Rsrc2 + 1];
	unsigned long long c = (unsigned long long)((unsigned long long)a << 32) + b;
	for (int i = 7; i >= 0; --i) {
		Memory[address + i] = (unsigned char)(c - ((c >> 8) << 8));
		c >>= 8;
	}
}
void SH(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	unsigned int a = Registers[InstructionLine[now].Rsrc2];
	Memory[address + 1] = (unsigned char)(a >> 8);
	Memory[address] = (unsigned char)(a - ((a >> 8) << 8));
}
void SW(int now, int level){
	int address, i;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	unsigned int a = Registers[InstructionLine[now].Rsrc2];
	for (int i = 3; i >= 0; --i) {
		Memory[address + i] = (unsigned char)(a - ((a >> 8) << 8));
		a >>= 8;
	}
}
void MOVE(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	Registers[InstructionLine[now].Rdest] = a;
}
void MFHI(int now, int level){
	Registers[InstructionLine[now].Rdest] = Registers[33];
}
void MFLO(int now, int level){
	Registers[InstructionLine[now].Rdest] = Registers[32];
}
void NOP(int now, int level){
}
void SYSCALL(int now, int level){
	int a = Registers[2];
	switch (a){
		case 1:{
			cout << Registers[4];
			break;
		}
		case 4:{
			int address = Registers[4];
			while (Memory[address] != 0) cout << Memory[address++];
			break;
		}
		case 5:{
			cin >> Registers[2];
			break;
		}
		case 8:{
			int address = Registers[4], len = Registers[5];
			string StringData;
			cin >> StringData;
			for (int i = 0; i < len; ++i) Memory[address + i] = StringData[i];
			break;
		}
		case 9:{
			int len = Registers[4];
			while ((NewAddress - 1) % 4 != 0) NewAddress++;
			Registers[2] = NewAddress;
			for (int i = 0; i < len; ++i) Memory[NewAddress++] = 0;
			break;
		}
		case 10:{
			exit(0);
			break;
		}
		case 17:{
			exit(Registers[4]);
			break;
		}
	}
}
void (*func[59])(int, int) = {NULL, ABS, ADD, AND, DIV, MUL, NEG, NOR, NOT, OR,
	REM, ROL, ROR, SLL, SRA, SRL, SUB, XOR, LI, SEQ, SGE, SGT, SLE, SLT, SNE, B, BEQ,
	BEQZ, BGE, BGEZ, BGEZAL, BGT, BGTZ, BLE, BLEZ, BGZAL, BLTZAL, BLT, BLTZ, BNE, BNEZ,
	J, JAL, JALR, JR, LA, LB, LD, LH, LW, SB, SD, SH, SW, MOVE, MFHI, MFLO, NOP, SYSCALL};
	
void work(int StartLine, int SumLine){
	PresentLine = StartLine;
	while (PresentLine < SumLine && PresentLine){
		/*printf("Now: %d\n", PresentLine);
		for (int i = 0; i <= 33; ++i){
			if (i && i % 5 == 0) printf("\n");
			printf("$%2d = %6d ", i, Registers[i]);
		}
		printf("\n");*/
		//cerr << "Now:" << PresentLine << " ";
		//cerr << "Kind:" << InstructionLine[PresentLine].Kind << endl;
		//cerr << "$ra = " << Registers[31] << endl;*/
		int tmp = PresentLine;
		func[InstructionLine[PresentLine].Kind](PresentLine, 1);
		if (PresentLine == tmp) PresentLine++;
	}
}
#endif
