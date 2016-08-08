#ifndef __Pre
#define __Pre

#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#include <fstream>
#include<cmath>
#include<map>
#include<vector>
#include<utility>

using namespace std;
typedef unsigned char byte;
struct Instruct{
	int Kind;
	int Rdest, Rsrc1, Rsrc2, Number, Offset;
	bool unsign;
	string lable;
	Instruct(int kind){
		Kind = kind;
		Rdest = Rsrc1 = Rsrc2 = -1;
		Number = Offset = 0;
		unsign = false;
		lable = "";
	}
};
vector <Instruct> InstructionLine;
map <string, int> Register;
map <string, int> TextLabel;
map <string, int> DataLabel;
map <int, byte> Memory;
map <string, int> Instruction;
char code[10000];
int NewAddress = 1;
vector<string> LabelArray[2];

void Prepare_Register(){
	Register["zero"] = 0; Register["at"] = 1;
	Register["v0"] = 2; Register["v1"] = 3;
	Register["a0"] = 4; Register["a1"] = 5; Register["a2"] = 6; Register["a3"] = 7;
	Register["t0"] = 8; Register["t1"] = 9; Register["t2"] = 10; Register["t3"] = 11;
	Register["t4"] = 12; Register["t5"] = 13; Register["t6"] = 14; Register["t7"] = 15;
	Register["s0"] = 16; Register["s1"] = 17; Register["s2"] = 18; Register["s3"] = 19;
	Register["s4"] = 20; Register["s5"] = 21; Register["s6"] = 22; Register["s7"] = 23 ;
	Register["t8"] = 24; Register["t9"] = 25;
	Register["k0"] = 26; Register["k1"] = 27; Register["gp"] = 28; Register["sp"] = 29;
	Register["fp"] = 30; Register["s8"] = 30; Register["ra"] = 31;
}
void Prepare_Instruction(){
	Instruction["abs"] = 1;
	Instruction["add"] = 2;
	Instruction["addi"] = 2;
	Instruction["addu"] = 2;
	Instruction["addiu"] = 2;
	Instruction["and"] = 3;
	Instruction["andi"] = 3;
	Instruction["div"] = 4;
	Instruction["divu"] = 4;
	Instruction["mul"] = 5;
	Instruction["mulo"] = 5;
	Instruction["mulou"] = 5;
	Instruction["mult"] = 5;
	Instruction["multu"] = 5;
	Instruction["neg"] = 6;
	Instruction["negu"] = 6;
	Instruction["nor"] = 7;
	Instruction["not"] = 8;
	Instruction["or"] = 9;
	Instruction["ori"] = 9;
	Instruction["rem"] = 10;
	Instruction["remu"] = 10;
	Instruction["rol"] = 11;
	Instruction["ror"] = 12;
	Instruction["sll"] = 13;
	Instruction["sllv"] = 13;
	Instruction["sra"] = 14;
	Instruction["srav"] = 14;
	Instruction["srl"] = 15;
	Instruction["srlv"] = 15;
	Instruction["sub"] = 16;
	Instruction["subu"] = 16;
	Instruction["xor"] = 17;
	Instruction["xori"] = 17;
	Instruction["li"] = 18;
	Instruction["lui"] = 18;
	Instruction["seq"] = 19;
	Instruction["sge"] = 20;
	Instruction["sgeu"] = 20;
	Instruction["sgt"] = 21;
	Instruction["sgtu"] = 21;
	Instruction["sle"] = 22;
	Instruction["sleu"] = 22;
	Instruction["slt"] = 23;
	Instruction["slti"] = 23;
	Instruction["sltu"] = 23;
	Instruction["sltiu"] = 23;
	Instruction["sne"] = 24;
	Instruction["b"] = 25;
	Instruction["beq"] = 26;
	Instruction["beqz"] = 27;
	Instruction["bge"] = 28;
	Instruction["bgeu"] = 28;
	Instruction["bgez"] = 29;
	Instruction["bgezal"] = 30;
	Instruction["bgt"] = 31;
	Instruction["bgtu"] = 31;
	Instruction["bgtz"] = 32;
	Instruction["ble"] = 33;
	Instruction["bleu"] = 33;
	Instruction["blez"] = 34;
	Instruction["bgezal"] = 35;
	Instruction["bltzal"] = 36;
	Instruction["blt"] = 37;
	Instruction["bltu"] = 37;
	Instruction["bltz"] = 38;
	Instruction["bne"] = 39;
	Instruction["bnez"] = 40;
	Instruction["j"] = 41;
	Instruction["jal"] = 42;
	Instruction["jalr"] = 43;
	Instruction["jr"] = 44;
	Instruction["la"] = 45;
	Instruction["lb"] = 46;
	Instruction["lbu"] = 46;
	Instruction["ld"] = 47;
	Instruction["lh"] = 48;
	Instruction["lhu"] = 48;
	Instruction["lw"] = 49;
	Instruction["sb"] = 50;
	Instruction["sd"] = 51;
	Instruction["sh"] = 52;
	Instruction["sw"] = 53;
	Instruction["move"] = 54;
	Instruction["mfhi"] = 55;
	Instruction["mflo"] = 56;
	Instruction["nop"] = 57;
	Instruction["syscall"] = 58;
}

bool visible(char c){
	return !(c == 9 || c == 32);
}
void store_to_memory(int x, int len){
	for (int i = len - 1; i >= 0; --i){
		Memory[NewAddress + i] = x & 0x00ff;
		x >>= 8;
	}
	NewAddress += len;
}

int get_Rdest(int number, int now){
	int len = strlen(code);
	while (!visible(code[now])) now++;
	if (code[now] != '$') return now;
	else now++;
	string str = "";
	while (visible(code[now]) && code[now] != ',' && now < len) str += code[now++];
	if (code[now] == ',') now++;
	bool flag = true;
	for (int i = 0; i < str.length(); ++i)
		if (!(str[i] >= '0' && str[i] <= '9')) {flag = false; break;}
	int res = 0;
	if (flag)
		for (int i = 0; i < str.length(); ++i) res = res * 10 + str[i] - '0';
	else res = Register[str];
	InstructionLine[number].Rdest = res;
	return now;
}

int get_Rsrc1(int number, int now){
	int len = strlen(code);
	while (!visible(code[now])) now++;
	if (code[now] != '$') return now;
	else now++;
	string str = "";
	while (visible(code[now]) && code[now] != ',' && now < len) str += code[now++];
	if (code[now] == ',') now++;
	bool flag = true;
	for (int i = 0; i < str.length(); ++i)
		if (!(str[i] >= '0' && str[i] <= '9')) {flag = false; break;}
	int res = 0;
	if (flag)
		for (int i = 0; i < str.length(); ++i) res = res * 10 + str[i] - '0';
	else res = Register[str];
	InstructionLine[number].Rsrc1 = res;
	return now;
}

int get_Src2(int number, int now){
	int len = strlen(code);
	while (!visible(code[now])) now++;
	int res = 0;
	if (code[now] != '$'){
		int tmp = 1;
		if (code[now] == '-'){tmp = -1; now++;}
		while (visible(code[now]) && code[now] != ',' && now < len) res = res * 10 + (code[now++] - '0');
		if (code[now] == ',') now++;
		InstructionLine[number].Number = tmp * res;
	}
	else{
		now++;
		string str = "";
		while (visible(code[now]) && code[now] != ',' && now < len) str += code[now++];
		if (code[now] == ',') now++;
		bool flag = true;
		for (int i = 0; i < str.length(); ++i)
			if (!(str[i] >= '0' && str[i] <= '9')) {flag = false; break;}
		if (flag)
			for (int i = 0; i < str.length(); ++i) res = res * 10 + str[i] - '0';
		else res = Register[str];
		InstructionLine[number].Rsrc2 = res;
	}
	return now;
}

int get_Imm(int number, int now){
	int len = strlen(code);
	while (!visible(code[now])) now++;
	int tmp = 1;
	if (code[now] == '-') {tmp = -1; now++;}
	int res = 0;
	while (visible(code[now]) && code[now] != ',' && now < len) res = res * 10 + (code[now++] - '0');
	if (code[now] == ',') now++;
	InstructionLine[number].Number = tmp * res;
	return now;
}

int get_label(int number, int now){
	int len = strlen(code);
	while (!visible(code[now])) now++;
	while (visible(code[now]) && now < len) InstructionLine[number].lable += code[now++];
	return now;
}

int get_address(int number, int now){
	int len = strlen(code);
	while (!visible(code[now])) now++;
	string str = "";
	while (visible(code[now]) && now < len) str += code[now++];
	bool flag = true;
	int x; 
	for (int i = 0; i < str.length(); ++i)
		if (str[i] == '$') {flag = false; x = i; break;}
	if (flag){
		InstructionLine[number].lable = str;
	}
	else{
		int tmp = 1, st = 0;
		if (str[0] == '-') {tmp = -1; st = 1;}
		InstructionLine[number].Offset = 0;
		for (int i = st; i < x - 1; ++i)
			InstructionLine[number].Offset = InstructionLine[number].Offset * 10 + str[i] - '0';
		InstructionLine[number].Offset *= tmp;
		string s1 = "";
		for (int i = x + 1; i < str.length() - 1; ++i) s1 += str[i];
		flag = true;
		for (int i = 0; i < s1.length(); ++i)
			if (!(s1[i] >= '0' && s1[i] <= '9')) {flag = false; break;}
		int res = 0;
		if (flag) for (int i = 0; i < s1.length(); ++i) res = res * 10 + s1[i] - '0';
		else res = Register[s1];
		InstructionLine[number].Rsrc1 = res;
	}
	return now;
}

void read(const char *name){
	ifstream in(name);
	bool KIND;
	int size[2];
	size[1] = size[2] = 0;
	while (!in.eof()) {
		in.getline(code, 10000);
		int len = strlen(code);
		int now = 0, x = -1;
		while (!visible(code[now])) now++;
		string lab = "";
		for (int i = now; i < len; ++i){
			if (code[i] == ':') x = i;
			if (code[i] == '"') break;
		}
		while (now <= x){
			string lab = "";
			while (code[now] != ':') lab += code[now++];
			LabelArray[KIND].push_back(lab);
			now++;
			while (!visible(code[now])) now++;
		}
		if (now >= len) continue;
		if (code[now] == '.'){
			string inst = "";
			now++;
			while (visible(code[now]) && now < len) inst += code[now++];
			if (inst == "data") {KIND = true; continue;}
			if (inst == "text") {KIND = false; continue;}
			for (int i = LabelArray[KIND].size() - 1; i >= 0; --i){
				if (DataLabel[LabelArray[KIND][i]] == 0) DataLabel[LabelArray[KIND][i]] = NewAddress;
				else break;
			}
			if (inst == "align"){
				int n = 0;
				while (!visible(code[now])) now++;
				while (now < len && code[now] != ',' && code[now] != ' ' && visible(code[now])) n = n * 10 + (code[now++] - '0');
				n = 1 << n;
				n = n - ((NewAddress - 1) % n);
				for (int i = 1; i <= n; ++i) store_to_memory(0, 1);
			}else if (inst == "ascii"){
				while (!visible(code[now])) now++;
				while (code[now] == '"') now++;
				while (now < len && code[now] != '"'){
					if (code[now] == '\\' && code[now + 1] == 'n'){store_to_memory('\n', 1); now += 2;}
					else  store_to_memory(code[now++], 1);
				}
			}else if (inst == "asciiz"){
				while (!visible(code[now])) now++;
				while (code[now] == '"') now++;
				while (now < len && code[now] != '"'){
					if (code[now] == '\\' && code[now + 1] == 'n'){store_to_memory('\n', 1); now += 2;}
					else store_to_memory(code[now++], 1);
				}
				store_to_memory('\0', 1);
			}else if (inst == "byte"){
				while (!visible(code[now])) now++;
				while(now < len){
					int n = 0;
					while (now < len && code[now] != ',' && code[now] != ' ' && visible(code[now])) n = n * 10 + (code[now++] - '0');
					store_to_memory(n, 1);
					if (now > len) break;
					while (!visible(code[now])) now++;
				}
			}else if (inst == "half"){
				while (!visible(code[now])) now++;
				while(now < len){
					int n = 0;
					while (now < len && code[now] != ',' && code[now] != ' ' && visible(code[now])) n = n * 10 + (code[now++] - '0');
					store_to_memory(n, 2);
					if (now > len) break;
					while (!visible(code[now])) now++;
				}
			}else if (inst == "word"){
				while (!visible(code[now])) now++;
				while(now < len){
					int n = 0;
					while (now < len && code[now] != ',' && code[now] != ' ' && visible(code[now])) n = n * 10 + (code[now++] - '0');
					store_to_memory(n, 4);
					if (now > len) break;
					while (!visible(code[now])) now++;
				}
			}else if (inst == "space"){
				int n = 0;
				while (!visible(code[now])) now++;
				while (now < len && visible(code[now])) n = n * 10 + (code[now++] - '0');
				for (int i = 1; i <= n; ++i) store_to_memory(0, 1);
			}
		}
		else{
			string inst = "";
			while (visible(code[now]) && now < len) inst += code[now++];
			int kind = Instruction[inst], number = InstructionLine.size();
			InstructionLine.push_back(Instruct(kind));
			for (int i = LabelArray[KIND].size() - 1; i >= 0; --i){
				if (TextLabel[LabelArray[KIND][i]] == 0) TextLabel[LabelArray[KIND][i]] = number;
				else break;
			}
			switch (kind){
				case 1:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					break;
				}
				case 2:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 3:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 4:{
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					while (!visible(code[now])) now++;
					if (now < len){
						InstructionLine[number].Rdest = InstructionLine[number].Rsrc1;
						InstructionLine[number].Rsrc1 = InstructionLine[number].Rsrc2;
						while (!visible(code[now])) now++;
						InstructionLine[number].Rsrc2 = -1;
						now = get_Src2(number, now);
					}
					if (inst == "divu") InstructionLine[number].unsign = true;
					break;
				}
				case 5:{
					if (!(inst == "mult" || inst == "multu")) now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 6:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					break; 
				}
				case 7:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 8:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					break;
				}
				case 9:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 10:{
					if (inst == "remu") InstructionLine[number].unsign = true;
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 11:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 12:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 13:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 14:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 15:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 16:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 17:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 18:{
					if (inst == "lui") InstructionLine[number].unsign = true;
					now = get_Rdest(number, now);
					now = get_Imm(number, now);
					break;
				}
				case 19:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 20:{
					if (inst == "sgeu") InstructionLine[number].unsign = true;
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 21:{
					if (inst == "sgtu") InstructionLine[number].unsign = true;
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 22:{
					if (inst == "sleu") InstructionLine[number].unsign = true;
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 23:{
					if (inst == "sltu" || inst == "sltiu") InstructionLine[number].unsign = true;
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 24:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					break;
				}
				case 25:{
					now = get_label(number, now);
					break;
				}
				case 26:{
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					now = get_label(number, now);
					break;
				}
				case 27:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 28:{
					if (inst == "bgeu") InstructionLine[number].unsign = true;
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					now = get_label(number, now);
					break;
				}
				case 29:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 30:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 31:{
					if (inst == "bgtu") InstructionLine[number].unsign = true;
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					now = get_label(number, now);
					break;
				}
				case 32:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 33:{
					if (inst == "bleu") InstructionLine[number].unsign = true;
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					now = get_label(number, now);
					break;
				}
				case 34:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 35:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 36:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 37:{
					if (inst == "bltu") InstructionLine[number].unsign = true;
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					now = get_label(number, now);
					break;
				}
				case 38:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 39:{
					now = get_Rsrc1(number, now);
					now = get_Src2(number, now);
					now = get_label(number, now);
					break;
				}
				case 40:{
					now = get_Rsrc1(number, now);
					now = get_label(number, now);
					break;
				}
				case 41:{
					now = get_label(number, now);
					break;
				}
				case 42:{
					now = get_label(number, now);
					break;
				}
				case 43:{
					now = get_Rsrc1(number, now);
					break;
				}
				case 44:{
					now = get_Rsrc1(number, now);
					break;
				}
				case 45:{
					now = get_Rdest(number, now);
					now = get_address(number, now);
					break;
				}
				case 46:{
					if (inst == "lbu") InstructionLine[number].unsign = true;
					now = get_Rdest(number, now);
					now = get_address(number, now);
					break;
				}
				case 47:{
					now = get_Rdest(number, now);
					now = get_address(number, now);
					break;
				}
				case 48:{
					if (inst == "lhu") InstructionLine[number].unsign = true;
					now = get_Rdest(number, now);
					now = get_address(number, now);
					break;
				}
				case 49:{
					now = get_Rdest(number, now);
					now = get_address(number, now);
					break;
				}
				case 50:{
					now = get_Src2(number, now);
					now = get_address(number, now);
					break;
				}
				case 51:{
					now = get_Src2(number, now);
					now = get_address(number, now);
					break;
				}
				case 52:{
					now = get_Src2(number, now);
					now = get_address(number, now);
					break;
				}
				case 53:{
					now = get_Src2(number, now);
					now = get_address(number, now);
					break;
				}
				case 54:{
					now = get_Rdest(number, now);
					now = get_Rsrc1(number, now);
					break;
				}
				case 55:{
					now = get_Rdest(number, now);
					break;
				}
				case 56:{
					now = get_Rdest(number, now);
					break;
				}
				case 57:{
					break;
				}
				case 58:{
					break;
				}
			}
		}
	}
}
#endif
