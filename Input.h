#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sstream>//them



char *NhapTu(int n,int xi,int yi)
{
	int pix = xi;
	gotoxy(xi,yi);
	
	char c;
	char *S = new char{NULL};
	int i=0;
	while((c=getch())!=13 || S[0] == NULL)//van con phai nhap khi chua nhan phim enter va mang S chua co ptu nao
	{
		if(i < n)
		{
			if( (c >= 97 && c <= 122))
			{
				S[i]=c;cout<<c;i++;xi++;//de dua con tro di toi 1 don vi chieu ngang
			}
			
			else if(int(c)==8 && i > 0)
			{
				cout<<"\b \b";i--;xi--;
			}
			if(i==0)
			{
				S[i]=NULL;
			}
		}

		
		else if(int(c)==8 && i > 0)
		{
			cout<<"\b \b";i--;xi--;
		}
		if(i==0)
		{
			S[i]=NULL;
		}
		if(int(c) == 13 && i == n-1)break;
	}
	S[i]='\0';
	return S;
}


char *NhapLuaChon(int n,int xi,int yi)
{
	int pix = xi;
	gotoxy(xi,yi);
	
	char c;
	char *esc = new char{NULL};//de nhan nut ESC khi dang nhap lieu
	char *S = new char{NULL};
	int i=0;
	while((c=getch())!=13 || S[0] == NULL)//van con phai nhap khi chua nhan phim enter va mang S chua co ptu nao
	{
		if(i < n)
		{
			if( (c >= 49 && c <= 51))
			{
				S[i]=c;cout<<c;i++;xi++;//de dua con tro di toi 1 don vi chieu ngang
			}
			
			else if(int(c)==8 && i > 0)
			{
				cout<<"\b \b";i--;xi--;
			}
			if(i==0)
			{
				S[i]=NULL;
			}
		}

		
		else if(int(c)==8 && i > 0)
		{
			cout<<"\b \b";i--;xi--;
		}
		if(i==0)
		{
			S[i]=NULL;
		}
		
		/////TAI DAY DE TRA VE NUT ESC//////
		if(int(c)==27 && c!=13)
		{
			esc[0] = 'e';
			return esc;
		}//////////////////////////////////
		
		if(int(c) == 13 && i == n-1)break;
	}
	S[i]='\0';
	return S;
}


char *NhapSo(int n,int xi,int yi)
{
	int pix = xi;
	gotoxy(xi,yi);
	
	char c;
	char *esc = new char{NULL};//de nhan nut ESC khi dang nhap lieu
	char *S = new char{NULL};
	int i=0;
	while((c=getch())!=13 || S[0] == NULL)//van con phai nhap khi chua nhan phim enter va mang S chua co ptu nao
	{
		if(i < n)
		{
			if( (c >= 48 && c <= 52))
			{
				S[i]=c;cout<<c;i++;xi++;//de dua con tro di toi 1 don vi chieu ngang
			}
			
			else if(int(c)==8 && i > 0)
			{
				cout<<"\b \b";i--;xi--;
			}
			if(i==0)
			{
				S[i]=NULL;
			}
		}

		
		else if(int(c)==8 && i > 0)
		{
			cout<<"\b \b";i--;xi--;
		}
		if(i==0)
		{
			S[i]=NULL;
		}
		
		/////TAI DAY DE TRA VE NUT ESC//////
//		if(int(c)==27 && c!=13)
//		{
//			esc[0] = 'e';
//			return esc;
//		}//////////////////////////////////
//		
		if(int(c) == 13 && i == n-1)break;
	}
	S[i]='\0';
	return S;
}
