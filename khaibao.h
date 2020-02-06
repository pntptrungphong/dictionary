#include <iostream>

#define MAXNGHIA 5
using namespace std;


///////////////NGHIA////////////////
typedef struct NghiaViet
{
	string nghia;
};

typedef struct LISTNGHIAVIET
{
	int n = 0;
	NghiaViet node_nghia[MAXNGHIA];
};
///////////////////////////////


/////////////////VIDU/////////////
 struct VIDU
{
	string vidu;
};
struct nodevidu
{
	VIDU data;
	struct nodevidu *pNext;
};
typedef struct nodevidu NODEVIDU;

typedef struct LISTVIDU
 {
	NODEVIDU *pHead;
	NODEVIDU *pTail;
};
/////////////////////////////////


char LoaiTu[4][20] = {"DANH TU", "TINH TU", "DONG TU", "TRANG TU"};
/////////////////////////////////
struct word//moi tu la moi node trong DSLK kep
{
	string tu;
	int loaitu;
	LISTNGHIAVIET listnghiaviet;
	LISTVIDU listvidu;
	
};
typedef struct word WORDS;


struct node
{
	WORDS data;
	struct node *pNext,*pPre;
};
typedef struct node NODE;


///////////////////////////////
void InitVidu(LISTVIDU &l)
{
	l.pHead = l.pTail = NULL;	
}


//////////////////////////////////////END KHAI BAO////////////////////////////////////////



/////////////////////////////////////////////////
// cap phat 1 node cho dslk don (Vidu)
NODEVIDU* Getnode_Vidu(VIDU x)
{
	NODEVIDU *p= new NODEVIDU;
	if(p==NULL)
	{
		return NULL;
	}
	else
	{
		p->data=x;
		p->pNext=NULL;
		return p;
	}
}

void AddTail_Vidu(WORDS &x, NODEVIDU *p)
{
   if (x.listvidu.pHead == NULL)
      x.listvidu.pHead = x.listvidu.pTail = p;
   else
   {
   		x.listvidu.pTail->pNext = p;
   		x.listvidu.pTail = p;
   }
}
///////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////
// cap phat 1 node cho dslk kep
NODE* Getnode_Word(WORDS x)//theo dslk kep
{
	NODE *p= new NODE;
	if(p==NULL)
	{
		return NULL;
	}
	else
	{
		p->data=x;
		p->pNext=p->pPre=NULL;
		return p;
	}
}

/////////////////////// bang bam/////////////////////


struct HashTable
{
	NODE *Head;
	NODE *Tail;
};

//ham bam
int HashFunc(char c)
{
    if (c>=97) c=c-32;
    return (c%65);
} 
///////////////////////////end bang bam////////////////




