#ifndef __STRUCT_H__
#define __STRUCT_H__
#include<windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include"resource.h"
#include<commctrl.h>
typedef struct csw {
	char sno[15];
	char jik[30];
	char bs[30];
	struct cin *tmp;
	struct csw *link;
}csw;
typedef struct cin {
	char name[100];
	int birth;
	char address[500];
	char email[500];
	char Pnum[20];
	int ps;
	char k[10];
	char kg[10];
	char bl[10];
	char eye[2][10];
	int marry;
	char religian[10];
	int inyear;
}cin;

typedef struct sawoninfo {
	TCHAR sno[15];
	TCHAR jik[30];
	TCHAR bs[30];
	struct information *tmp;
	struct sawoninfo *link;
	struct fm *f;
}sawoninfo;

typedef struct information {
	TCHAR name[100];
	int birth;
	TCHAR address[500];
	TCHAR email[500];
	TCHAR Pnum[20];
	int ps;
	TCHAR k[10];
	TCHAR kg[10];
	TCHAR bl[10];
	TCHAR eye[2][10];
	int marry;
	TCHAR religian[10];
	int inyear;
}information;

typedef struct fm {
	int c;
	TCHAR sno[30];
	TCHAR gan[30];
	TCHAR name[30];
	TCHAR br[30];
	TCHAR job[30];
}fm;
typedef struct cfm {
	int c;
	char sno[30];
	char gan[30];
	char name[30];
	char br[30];
	char job[30];
	struct cfm *link;
}cfm;

typedef struct manager {
	int iParent;
	TCHAR menu[100];
	struct manager *link;
}Manager;

typedef struct jik {
	TCHAR menu[100];
	struct jik *link;
}Jik;

typedef struct joggyo {
	TCHAR menu[100];
	struct joggyo *link;
}Joggyo;

typedef struct swdel {
	TCHAR sno[30];
	TCHAR bs[30];
	TCHAR jik[30];
	TCHAR delday[30];
	TCHAR name[30];
	TCHAR su[30];
	TCHAR num[30];
	struct swdel *link;
}swdel;
typedef struct cdsw {
	char sno[30];
	char bs[30];
	char jik[30];
	char name[30];
	char re[30];
	char pnum[30];
	char day[30];
}cDsw;
typedef struct dsw {
	TCHAR sno[30];
	TCHAR bs[30];
	TCHAR jik[30];
	TCHAR name[30];
	TCHAR re[30];
	TCHAR pnum[30];
	TCHAR day[30];
	struct dsw *link;
}Dsw;
typedef struct tag_Param {
	TCHAR str[100];
}tag_Param;
#endif