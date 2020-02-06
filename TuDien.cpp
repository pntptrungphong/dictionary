#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <sstream>//them
#define M 26//26 ki tu



#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESC 27
#define SPACE 32
#define BACKSPACE 8
#define TAB 9
#define INSERT 82
#define END 79
#include "mylib.h"
#include "khaibao.h"
#include "Input.h"
#include "dohoa.h"
using namespace std;
void findfirstword(HashTable *dictionary, NODE *&Current_Word) { //truyen len dictionary va tu hien tai len  va thay doi gia tri cua no
	for(int i = 0; i < 26; i++) {
		if(dictionary[i].Head != NULL) {
			Current_Word = dictionary[i].Head;
			break;
		}
	}
}
bool SearchWord(HashTable *dictionary,string word)
{
	int key = HashFunc(word[0]);
	for(NODE *p = dictionary[key].Head ; p != NULL ; p = p->pNext)
	{
		if(word==p->data.tu)
		{
			return true;
		}
	}
		return false;
}

void inputdetail(WORDS &x)//de nhap thong tin chi tiet cua tu
{
	for(int i = 0 ; i < 4; i++)
	{
		cout<<i<<":"<< LoaiTu[i]<<" ";
	}
	cout<<"nhap loai tu: ";
	char *so = NhapSo(1,54,2);
	x.loaitu= atoi(so);
	
	///NHAP NGHIA
//	fflush(stdin);
//	cout<<"nhap nghia:"<<endl;
	cout<<endl;
	for(int i = 0; i < MAXNGHIA ; i++)
	{
		
		fflush(stdin);
		cout<<"NHAP NGHIA THU "<<i+1<<" :"<<endl;
		getline(cin,x.listnghiaviet.node_nghia[i].nghia);
	}
	
	///////////NHAP VI DU/////////
	InitVidu(x.listvidu);
	VIDU y;
	fflush(stdin);
	cout<<"nhap vi du:";
	getline(cin,y.vidu);
	NODEVIDU *p = Getnode_Vidu(y); 
	AddTail_Vidu(x, p); 
}


void Input_Again(WORDS &a)//de nhap thong tin chi tiet cua tu
{
//	fflush(stdin);
//	cout<<"nhap tu:";
//	char *tumoi = NhapTu(30,8,0);
//	a.tu = tumoi;
	inputdetail(a);
}
void DeleteHead(HashTable *&dictionary, int key)
{
	NODE *temp = dictionary[key].Head;
	dictionary[key].Head = dictionary[key].Head->pNext;
	dictionary[key].Head->pPre = NULL;
	delete temp;
}
void DeleteTail(HashTable *&dictionary, int key)
{
	NODE *temp = dictionary[key].Tail;
	dictionary[key].Tail = temp->pPre;
	temp->pPre->pNext = NULL;
	delete temp;
}


void DeleteWord(HashTable *&dictionary, string check)
{
	if(dictionary[HashFunc(check[0])].Head->data.tu==check && dictionary[HashFunc(check[0])].Tail->data.tu==check)
	{
		dictionary[HashFunc(check[0])].Head = dictionary[HashFunc(check[0])].Tail = NULL;
		return;
	}
	else if(dictionary[HashFunc(check[0])].Head->data.tu==check)
	{
		DeleteHead(dictionary, HashFunc(check[0]));
		return;
	}
	
	else if(dictionary[HashFunc(check[0])].Tail->data.tu==check)
	{
		DeleteTail(dictionary,HashFunc(check[0]));
		return;
	}
	
	else
	{
		for(NODE *p = dictionary[HashFunc(check[0])].Head; p != NULL ; p = p->pNext)
		{
			if(check==p->data.tu)
			{
				NODE *temp=p;
				temp->pPre->pNext = temp->pNext;
				temp->pNext->pPre = temp->pPre;
				delete temp;
				break;			
			}
		}
	}
}


void Add(NODE *&Head , NODE *&Tail, NODE *q) 
{
	NODE *run = Head;
	if(Head == NULL) 
	{
		Head = Tail = q;
	}
	else 
	{
		while(run != NULL) 
		{
			if(run->data.tu < q->data.tu) 
			{
				if(run->pNext == NULL) 
				{
					run->pNext = q;
					q->pPre = run;
					Tail = q;
					break;
				}
				else 
				{
					run = run->pNext;
				}		
			}
			else 
			{
				if(run == Head) 
				{
					Head = q;
					Head->pNext = run;
					run->pPre = Head;
					break;
				}
				else 
				{
					NODE *tmp = run->pPre;
					tmp->pNext = q;
					q->pPre = tmp;
					q->pNext = run;
					run->pPre = q;
					break;
				}
			}
		}
	}
}

void writef(HashTable *dictionary) { //Ghi file       
	ofstream fo("tudien.txt");
	if(fo.is_open()) {
		for(int i = 0; i < 26; i++) {
			NODE *head = dictionary[i].Head;
			while(head != NULL) {
				fo << head->data.tu
					<< "|" << head->data.loaitu
					<< "|" <<head->data.listnghiaviet.node_nghia[0].nghia
					<< "|" <<head->data.listnghiaviet.node_nghia[1].nghia
					<< "|" <<head->data.listnghiaviet.node_nghia[2].nghia
					<< "|" <<head->data.listnghiaviet.node_nghia[3].nghia
					<< "|" <<head->data.listnghiaviet.node_nghia[4].nghia
					<< "|" <<head->data.listvidu.pHead->data.vidu << "|" << "\n";
					head = head->pNext;
			}
		}
		fo.close();
	}
}        


void InPutWord(HashTable *&dictionary, NODE *&Current_Word)
{	tt:
	cout<<" Nhap tu moi: ";
	char check[30];
	char *tumoi;
	tumoi = NhapTu(30,14,0);//tai sao k dungg string
	cout<<endl;
	strcpy(check,tumoi);
	
	if(SearchWord(dictionary,check)==false)//tu them vao chua co trong tu dien
	{
		WORDS x;
		x.tu=check;
		cout<<"Tu: "<<tumoi<<endl;
		inputdetail(x);
		NODE *q = Getnode_Word(x);
		Add(dictionary[HashFunc(x.tu[0])].Head , dictionary[HashFunc(x.tu[0])].Tail ,q);
		findfirstword(dictionary,Current_Word);
		cout<<"Them Vao Tu Dien Thanh Cong"<<endl;
		system("pause");
		writef(dictionary);
		return;
	}
	
	else
	{
		system("cls");
		char *c;
		cout<<"Tu Ban Nhap Trung Voi 1 Tu Trong Tu Dien"<<endl<<" Ban Co Muon Xoa Tu Nay Va Nhap Lai Khong ?"<<endl;
		cout<<"1 Xoa Va Thay Doi"<<endl;
		cout<<"2 De Nhap Tu Khac"<<endl;
		cout<<"Nhap So Khac De Thoat"<<endl;
		cout<<"Enter Choice: ";
		c = NhapLuaChon(1,13,5);
		int number = atoi(c);
		cout<<endl;
		switch(number)
		{
			
			
			case 1:{
				system("cls");
				/*------XOA TU DANG NHAP-----------*/
				WORDS y;
				fflush(stdin);
				cout<<"nhap tu:";
				char *tumoi = NhapTu(30,8,0);
				y.tu = tumoi;
				if(SearchWord(dictionary,tumoi)==true)
				{
					system("cls");
					cout<<"Ban Nhap Lai Tu Van Trung"<<endl;system("pause>NULL");
					findfirstword(dictionary,Current_Word);// cap nhat lai tu hien tai
					system("cls");
					break;
				}
				else
				{
					DeleteWord(dictionary,check);
					cout<<endl;
					cout<<"Tu: "<<tumoi<<endl;
					Input_Again(y);
					NODE *q = Getnode_Word(y);
					Add(dictionary[HashFunc(y.tu[0])].Head , dictionary[HashFunc(y.tu[0])].Tail ,q);
					findfirstword(dictionary,Current_Word);
					writef(dictionary);
					return;	
				}
				
			}
			
			case 2:{
				/*---bat dau nhap lai tu moi--*/
				system("cls");
				WORDS z;
				fflush(stdin);
				cout<<"nhap tu:";
				char *tumoi = NhapTu(30,8,0);
				z.tu = tumoi;

				if(SearchWord(dictionary,z.tu)==true)
				{
					cout<<"Ban Nhap Lai Tu Van Trung"<<endl;system("pause>NULL");
					findfirstword(dictionary,Current_Word);
					system("cls");
					break;
				}
				else
				{
					cout<<endl;
					cout<<"Tu: "<<tumoi<<endl;
					Input_Again(z);
					NODE *q = Getnode_Word(z);
					Add(dictionary[HashFunc(z.tu[0])].Head , dictionary[HashFunc(z.tu[0])].Tail ,q);
					cout<<"Them tu moi thanh cong"<<endl;system("pause>NULL");
					findfirstword(dictionary,Current_Word);
					writef(dictionary);
					return;
				}
			}
			
			case 3:
			{
				findfirstword(dictionary,Current_Word);break;
			}	
		}
	}
}




NODE *Up_Word(HashTable *dictionary, NODE *current) { //Tim tu phia truoc cua tu //current=tu hien tai
	if(current != NULL) {
		NODE *up = current->pPre;
		if(up != NULL) {
			return up;
		}
		else {
			int x = HashFunc(current->data.tu[0]);
			if(x > 0) {
				while(x > 0) 
				{
					if(dictionary[x - 1].Tail != NULL)
					{
						return dictionary[x - 1].Tail;
					}
					x--;
				}
				return NULL;
			}
			else {
				return NULL;
			}
		}
	}
	else return NULL;
}



NODE *Down_Word(HashTable *dictionary, NODE *current) { //Tim tu phia sau cua tu
	if(current != NULL) 
	{
		NODE *Down = current->pNext;
		if(Down != NULL) 
		{
			return Down;
		}
		else {
			int x = HashFunc(current->data.tu[0]);
			if(x < 25) 
			{
				while(x != 26) 
				{
					if(dictionary[x + 1].Head != NULL)
					{
						return dictionary[x + 1].Head;
					}
					x++;
				}
				return NULL;
			}
			else 
			{
				return NULL;
			}
		}
	}
	else return NULL;
}



char menu_TUDIEN[5][100] =   {  "1.  TRA TU         ",
   								"2.  THEM TU MOI    ",
							 };





int Select()
{
	system("cls");
	
	int select = 0;  
	int i = 0;
	char c;

	gotoxy(2,3); cout<<"UP: len";
	gotoxy(2,4); cout<<"DOWN: xuong";
	gotoxy(2,5); cout<<"ENTER: chon ";
	gotoxy(30,3);cout<<"CHUC NANG CUA TU DIEN";
	
	gotoxy(30,2); normal();
	for(int i = 0;i<2;i++)
	{
		gotoxy(30,5+i*2);
		cout<<menu_TUDIEN[i];
	}
	hightline();
	gotoxy(30,5); cout<<menu_TUDIEN[0];

	while(true)
	{
		c = _getch();
		normal();	
		gotoxy(30,(5+select*2)); cout << menu_TUDIEN[select];
		
		switch(c)
		{
			case UP:{
				select -= 1; 
				if(select < 0) 
				{ 
					select = 1; 
				}
				break;
			}
			case DOWN:
			{
				select += 1; 
				if(select > 1)
				{
				 	select = 0; 
				}
				
				break;
			}
			case ENTER:
			{
			 	return select + 1;
				break;
			}
			default:
			{
				break;
			}
		}
		hightline();
	    gotoxy(30,(5+select*2)); cout << menu_TUDIEN[select];
	}
	gotoxy(70,70);
}






void printscreen(NODE *tmp) { //In 1 tu ra man hinh tim kiem
	if(tmp != NULL) 
	{
		cout << tmp->data.tu;
	}
}


void displaycurrent(NODE *tmp) { //Hien thi tu dau tren trong khung ket qua tim kiem
	if(tmp != NULL) 
	{
		cout << " " << tmp->data.tu;
		for(int i = tmp->data.tu.length(); i < boxs-1 ; i++) cout << " ";// tao thanh sang cho tu 
	}
}




void displayword(HashTable *dictionary, NODE *hientai)
{ 
		for(int i = 1; i < boxw; i++)
		{ //Xoa sach khung hien thi ket qua tim kiem
			gotoxy(boxx + 2, boxy + 1 + i);
			for(int j = 1; j < boxs - 1; j++) cout << " ";
		}
		//in lai cac ket qua tim kiem tuong ung
		for(int i = 0; i < boxw; i++) 
		{
			if(i == 0){
				gotoxy(boxx+1, boxy+1+i); 
				SetColor(12);
				displaycurrent(hientai);
			}
			else {
				gotoxy(boxx+2, boxy+1+i);
				SetColor(1);
				printscreen(hientai);
			}
			hientai = Down_Word(dictionary, hientai);
		}
}
                     
           

                    
                    
void output(HashTable *&dictionary, NODE *&Current_Word)
{
	system("cls");
	int keyhit = 0;
	cout<<"tu:"<<Current_Word->data.tu<<endl;
	cout<<"loai tu:"<<LoaiTu[Current_Word->data.loaitu]<<endl;
	for(int i = 0 ; i < MAXNGHIA ; i++)
	{
		cout<<"NGHIA "<<i+1 <<": "<<Current_Word->data.listnghiaviet.node_nghia[i].nghia<<endl;
	}
	for(NODEVIDU *k = Current_Word->data.listvidu.pHead ; k != NULL ; k = k->pNext)
	{
		cout<<"Vi Du:"<<k->data.vidu<<endl;
	}
	menu2();
	int dem = 0;//
	for(int i = 0 ; i < 26; i++)
	{
		for(NODE *q = dictionary[i].Head ; q != NULL ; q = q->pNext)
		{
			if(q!= NULL)
			{
				dem++;
			}
		}
	}
	
	if(dem > 1)
	{
		keyhit = getch();
		if(keyhit == SPACE)
		{
			DeleteWord(dictionary,Current_Word->data.tu);
			for(int i = 0 ; i < 26 ; i++)
			{
				for(NODE *q = dictionary[i].Head; q != NULL ; q = q->pNext)
				{
					if(q!=NULL)
					Current_Word = q;
					break;
				}
			}
			writef(dictionary);
			cout<<endl;
	  		cout<<"Xoa Thanh cong";system("pause>NULL");
	  		return;
		}
	}
	
	else
	{	cout<<"\n";
		cout<<"Khong duoc xoa tu cuoi cung trong tu dien"<<endl;system("pause>NULL");
		return;
	}
	keyhit = getch();
	if(keyhit==BACKSPACE)
	{
		system("cls");
		cout<<" Nhap tu moi: ";
		char check[30];
		char *tumoi;
		tumoi = NhapTu(30,14,0);
		cout<<endl;
		strcpy(check,tumoi);
		DeleteWord(dictionary,Current_Word->data.tu);
		if(SearchWord(dictionary,check)==false)
		{
			WORDS x;
			x.tu=check;
			cout<<"Tu: "<<tumoi<<endl;
			inputdetail(x);
			NODE *q = Getnode_Word(x);
			Add(dictionary[HashFunc(x.tu[0])].Head , dictionary[HashFunc(x.tu[0])].Tail ,q);
			
			for(int i = 0 ; i < 26 ; i++)
			{
				for(NODE *q = dictionary[i].Head; q != NULL ; q = q->pNext)
				{
					if(q!=NULL)
					Current_Word = q;
					break;
				}
		
				findfirstword(dictionary,Current_Word);
				cout<<"Chinh Sua Thanh Cong"<<endl;
				system("pause>NULL");
				writef(dictionary);
				return;
			}
		}
		else
		{
			system("cls");
			cout<<"Tu Ban Chinh Sua Dang Trung Voi Tu Da Co Trong Tu Dien";
			system("pause>NULL");
			return;	
		}
	}
}


         
                    
                   
void SearchBox(HashTable *&dictionary, NODE *&Current_Word)
{ 
	Nocursortype();
	SetColor(63);
	bool changed = false;
	int keyhit = 0;
	while(keyhit != ESC)
	{
		menu1();
		dicbox();
		while(keyhit != ENTER || Current_Word == NULL)
		{
			displayword(dictionary, Current_Word); //Hien thi ket qua tim kiem			
			keyhit = getch();
			
			if(keyhit == 224)
			{
				keyhit = getch();
				if(keyhit == UP) {//len
					if(Up_Word(dictionary, Current_Word) != NULL)//tim tu ben trai
					{
						Current_Word = Up_Word(dictionary, Current_Word);
					}
				}
				else if(keyhit == DOWN) 
				{
					if(Down_Word(dictionary, Current_Word) != NULL)//tim tu ben trai
					{
						Current_Word = Down_Word(dictionary, Current_Word);
					}
				}
				changed = false;
			}
			
			
			else if(keyhit == ESC) break;
			else if(keyhit == TAB) break;
	    }
	    if(keyhit == ENTER)
		{
	   	 	output(dictionary,Current_Word);
	   	 	break;
			//system("cls");
		}
		
		else if(keyhit == TAB)
		{
			system("cls");
			InPutWord(dictionary,Current_Word);
			//writef(dictionary);
			break;
		}
		
		else
		{
			system("cls");
			gotoxy(boxx, boxy); cout << "Nhan Esc mot lan nua de thoat chuong trinh";
			gotoxy(boxx, boxy + 1); cout << "Nhan bat ky phim nao khac de quay lai chuong trinh";
			keyhit = getch();
			if(keyhit != ESC)
			{
				if(keyhit == 224) keyhit = getch();
				keyhit = 0;
			}
			system("cls");
		}
		
    }
}




void Menu(HashTable *&dictionary ,NODE *&Current_Word)
{
	int choice;
	while(true)
	{
		
		choice = Select();
			switch(choice){
				
				case 1:{
					//writef(dictionary);
					system("cls");
					
					SearchBox(dictionary,Current_Word);
					system("pause>NULL");
					break;
				}
				
				case 2:
				{
					system("cls");
	       			InPutWord(dictionary,Current_Word);
					system("pause>nul");
					break;
				}
			
	}
}
}




void addlast(NODE *&head, NODE *&tail, NODE *&newword)// them vao cuoi khi importfile tudien
{
	if(head == NULL)
	{
		head = tail = newword;
	}
	else
	{
		tail->pNext = newword;
		newword->pPre = tail;
		tail = newword;
	}
}








void tachchuoi(string line, NODE *&newword)
{
	int  i = 0;
	string tach = "";
	
	int n = 0;
	
	/*--------------tu--------------*/
	while(line[i] != '|')
	{	
		tach += line[i];
		i++;
	}
	i++;
	newword->data.tu = tach;
	/*-------------tu---------------*/
	
	
	tach = "";
	/*-------------loai tu---------------*/
	while(line[i] != '|')
	{
		tach += line[i];
		i++;
	}
	i++;
	const char* loaitu = (tach.c_str());
	newword->data.loaitu = atoi(loaitu);
	/*-------------lao tu---------------*/


	tach = "";
	/*--------------nghia 1--------------*/
	while(line[i] != '|') {
		tach += line[i];
		i++;
	}
	i++;
	newword->data.listnghiaviet.node_nghia[n].nghia = tach;
	n++;
	/*--------------nghia 1--------------*/
	
	
	
	tach = "";
	/*--------------nghia 2--------------*/
	while(line[i] != '|') {
		tach += line[i];
		i++;
	}
	i++;
		newword->data.listnghiaviet.node_nghia[n].nghia = tach;
	n++;
	/*--------------nghia 2--------------*/
	
	
	tach = "";
	/*--------------nghia 3--------------*/
	while(line[i] != '|') {
		tach += line[i];
		i++;
	}
	i++;
	newword->data.listnghiaviet.node_nghia[n].nghia = tach;
	n++;
	/*--------------nghia 3--------------*/
	
	
	
	tach = "";
	/*--------------nghia 4--------------*/
	while(line[i] != '|') {
		tach += line[i];
		i++;
	}
	i++;
		newword->data.listnghiaviet.node_nghia[n].nghia = tach;
	n++;
	/*--------------nghia 4--------------*/
	
	
	tach = "";
	/*--------------nghia 5--------------*/
	while(line[i] != '|') {
		tach += line[i];
		i++;
	}
	i++;
	newword->data.listnghiaviet.node_nghia[n].nghia = tach;
	/*--------------nghia 5--------------*/
	
	
	
	tach = "";
	InitVidu(newword->data.listvidu);
	/*--------------vidu--------------*/
	while(line[i] != '|') {
		tach += line[i];
		i++;
	}
	VIDU x;
	x.vidu=tach;
	NODEVIDU *example = Getnode_Vidu(x);
	AddTail_Vidu(newword->data,example);
	i++;
	/*--------------vidu--------------*/
	
}



void importword(HashTable *&dictionary, string line) {
	for(int i = 97; i < 124; i++){
		if(line[0] == char(i)) { 
			NODE *newword = new NODE;
			tachchuoi(line, newword);
			newword->pNext = NULL;
			newword->pPre = NULL;
			addlast(dictionary[i - 97].Head, dictionary[i - 97].Tail, newword);
			break;
		}
	}
}



void ReadFile(HashTable *&dictionary, NODE *&Current_Word) { 
	ifstream fi("tudien.txt");
	string line;
	if(fi.is_open())
	{
		while(getline(fi, line)) 
		{
			importword(dictionary, line);
		}
		fi.close();
	}
	findfirstword(dictionary, Current_Word);
}




int main()
{
	SetBGColor(0);
	resizeConsole(840,720);
	HashTable *dictionary = new HashTable[26];
	/*-----khoi tao HashTable-----*/
	for(int i = 0; i < 26; i++)
	{
		dictionary[i].Head = NULL;
    	dictionary[i].Tail = NULL;
	}
	/*-----khoi tao HashTable-----*/
	
	NODE *Current_Word = NULL;
	ReadFile(dictionary, Current_Word);
	
	
	////////////////////////////
	Menu(dictionary,Current_Word);
	
	return 0;
}


