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
	int a, b;
	a = Registers[InstructionLine[now].Rsrc1];
	b = Registers[InstructionLine[now].Rsrc2];
	if (b == 0) throw("Error!");
	if (InstructionLine[now].unsign){
		Registers[32] = (unsigned int)a / (unsigned int)b;
		Registers[33] = (unsigned int)a % (unsigned int)b;
	}
	else{
		Registers[32] = a / b;
		Registers[33] = a % b;
	}
	if (InstructionLine[now].Rdest != -1) Registers[InstructionLine[now].Rdest] = Registers[32];
}

void MUL(int now, int level){
	int b, c;
	long long a;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign) a = (unsigned int)b * (unsigned int)c; 
	else a = b * c; 
	printf("%d * %d\n", b, c);
	Registers[32] = a & 0xffffffff;
	Registers[33] = a >> 32;
	if (InstructionLine[now].Rdest != -1) Registers[InstructionLine[now].Rdest] = Registers[32];
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
	int a, b, c;
	b = Registers[InstructionLine[now].Rsrc1];
	if (InstructionLine[now].Rsrc2 == -1) c = InstructionLine[now].Number;
	else c = Registers[InstructionLine[now].Rsrc2];
	if (InstructionLine[now].unsign) a = ((unsigned int)b % (unsigned int)c);
	else a = b % c;
	Registers[InstructionLine[now].Rdest] = a;
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
	int a = Registers[InstructionLine[now].Rsrc1];
	int b = Registers[InstructionLine[now].Rsrc2];
	if (a == b) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BEQZ(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	if (a == 0) PresentLine = TextLabel[InstructionLine[now].lable];
}
void BGE(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	int b = Registers[InstructionLine[now].Rsrc2];
	cerr << "$" << InstructionLine[now].Rsrc1 << " = "  << a << " ";
	cerr << "$" << InstructionLine[now].Rsrc2 << " = "  << b << endl;
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
	int a = Registers[InstructionLine[now].Rsrc1];
	int b = Registers[InstructionLine[now].Rsrc2];
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
	int a = Registers[InstructionLine[now].Rsrc1];
	int b = Registers[InstructionLine[now].Rsrc2];
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
	int a = Registers[InstructionLine[now].Rsrc1];
	int b = Registers[InstructionLine[now].Rsrc2];
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
	int a = Registers[InstructionLine[now].Rsrc1];
	int b = Registers[InstructionLine[now].Rsrc2];
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
	if (InstructionLine[now].unsign) Registers[InstructionLine[now].Rdest] = (unsigned int)Memory[address];
	else Registers[InstructionLine[now].Rdest] = Memory[address];
}
void LD(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	int a = 0, b = 0, i;
	for (i = 0; i < 4; ++i)	a = (a << 8) | Memory[address + i];
	Registers[InstructionLine[now].Rdest] = a;
	for (i = 4; i < 8; ++i) b = (b << 8) | Memory[address + i];
	Registers[InstructionLine[now].Rdest + 1] = b;
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
	Registers[InstructionLine[now].Rdest] = a;
}
void SB(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	Memory[address] = Registers[InstructionLine[now].Rsrc2] & 0x00ff;
}
void SD(int now, int level){
	int address, i;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	int a = Registers[InstructionLine[now].Rsrc2];
	for (i = 3; i >= 0; --i) {
		Memory[address + i] = a & 0x00ff;
		a >>= 8;
	}
	a = Registers[InstructionLine[now].Rsrc2 + 1];
	for (i = 7; i >= 4; --i) {
		Memory[address + i] = a & 0x00ff;
		a >>= 8;
	}
}
void SH(int now, int level){
	int address;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	int a = Registers[InstructionLine[now].Rsrc2] & 0xffff;
	Memory[address + 1] = a & 0x00ff;
	Memory[address] = a >> 8;
}
void SW(int now, int level){
	int address, i;
	if (InstructionLine[now].Rsrc1 == -1) address = DataLabel[InstructionLine[now].lable];
	else address = Registers[InstructionLine[now].Rsrc1] + InstructionLine[now].Offset;
	int a = Registers[InstructionLine[now].Rsrc2];
	for (i = 3; i >= 0; --i) {
		Memory[address + i] = a & 0x00ff;
		a >>= 8;
	}
}
void MOVE(int now, int level){
	int a = Registers[InstructionLine[now].Rsrc1];
	Registers[InstructionLine[now].Rdest] = a;
}
void MFHI(int now, int level){
	Registers[InstructionLine[now].Rdest] = Registers[32];
}
void MFLO(int now, int level){
	Registers[InstructionLine[now].Rdest] = Registers[33];
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
			while (NewAddress % 4 != 0) NewAddress++;
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
		printf("Now: %d\n", PresentLine);
		for (int i = 0; i <= 33; ++i){
			if (i && i % 5 == 0) printf("\n");
			printf("$%2d = %6d ", i, Registers[i]);
		}
		printf("\n");
		//cerr << "Now:" << PresentLine << " ";
		//cerr << "Kind:" << InstructionLine[PresentLine].Kind << endl;
		//cerr << "$ra = " << Registers[31] << endl;
		int tmp = PresentLine;
		func[InstructionLine[PresentLine].Kind](PresentLine, 1);
		if (PresentLine == tmp) PresentLine++;
	}
}
#endif
