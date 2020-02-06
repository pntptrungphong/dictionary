#define boxx 12 //Vi tri x bat dau cua box
#define boxy 8 //Vi tri y bat dau cua box
#define boxs 54 //Box size
#define boxw 8 //So tu hien thi trong khung ket qua tim kiem
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}


void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void normal()
{
	SetColor(63); //mau chu
}

void hightline()
{
	SetColor(4); // mau chu cua vi tri con tro hien tai
}

/*----------------OF DIC4.0------------*/



void dicbox() 
{ 
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) {
		cout << char(205);
	}
	cout << char(187);
	for(int i = boxy + 1; i < boxy + 1 + boxw; i++) {
		gotoxy(boxx, i);
		cout << char(186);
		gotoxy(boxx + boxs + 1, i);
		cout << char(186);
	}
	gotoxy(boxx, boxy + boxw + 1); cout << char(200);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188);
}




void menu1() 
{
	gotoxy(18,2);
	SetColor(63);
	cout << "Tab: Them tu moi";
	gotoxy(18,3);
	cout << "Esc: Ket thuc chuong trinh";
	SetColor(63);
}

void menu2() 
{
	gotoxy(0,10);
	SetColor(63);
	cout << "Backspace: Chinh sua tu nay";
	gotoxy(0,11);
	cout << "Space: Xoa tu nay";
	gotoxy(0,12);
	cout << "Esc: Quay lai khung tim kiem";
	SetColor(63);
}

/*-----------------------------------------------*/


