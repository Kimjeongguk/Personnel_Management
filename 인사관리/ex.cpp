#include "ex.h"


extern sawoninfo *data;
extern Manager *menu;
extern Jik *menu1;
extern Joggyo *menu2;
extern int peopleno;
extern sawoninfo *sw;
extern Dsw *menu4;

cDsw *createcds() {
	cDsw *t;
	t = (cDsw*)calloc(1, sizeof(cDsw));
	return t;
}
Dsw *createds() {
	Dsw* t;
	t = (Dsw*)calloc(1, sizeof(Dsw));
	t->link = NULL;
	return t;
}
csw *createcsw() {
	csw *t;
	t = (csw*)calloc(1, sizeof(csw));
	t->tmp = createcin();
	return t;
}
cin *createcin() {
	cin*t;
	t = (cin*)calloc(1, sizeof(cin));
	return t;
}
sawoninfo *create1() {
	sawoninfo *temp;

	temp = (sawoninfo*)calloc(1, sizeof(sawoninfo));
	temp->tmp = create();
	temp->link = NULL;
	temp->f = createf();
	return temp;
}
information *create() {
	information *tmp;

	tmp = (information*)calloc(1, sizeof(information));

	return tmp;
}
fm *createf() {
	fm *t;
	t = (fm*)calloc(1, sizeof(fm));
	t->c = 0;
	return t;
}
Manager *createM() {
	Manager *t;
	t = (Manager*)malloc(sizeof(Manager));

	t->iParent = 0;
	lstrcpy(t->menu, TEXT(""));
	t->link = NULL;

	return t;
}

Jik *createJ() {
	Jik *t;
	t = (Jik*)malloc(sizeof(Jik));
	lstrcpy(t->menu, TEXT(""));
	t->link = NULL;

	return t;
}

Joggyo * createJO() {
	Joggyo *t;
	t = (Joggyo*)malloc(sizeof(Joggyo));
	lstrcpy(t->menu, TEXT(""));
	t->link = NULL;

	return t;
}

cfm * createcf() {
	cfm *t;
	t = (cfm*)calloc(1, sizeof(cfm));
	t->link = NULL;
	return t;
}


sawoninfo *CtoT(csw* str) {
	TCHAR ct[20];
	sawoninfo*a;
	a = create1();
	wsprintf(ct, TEXT("%s"), str->sno);
	lstrcpy(a->sno, ct);
	wsprintf(ct, TEXT("%s"), str->jik);
	lstrcpy(a->jik, ct);
	wsprintf(ct, TEXT("%s"), str->bs);
	lstrcpy(a->bs, ct);
	wsprintf(ct, TEXT("%s"), str->tmp->name);
	lstrcpy(a->tmp->name, ct);
	wsprintf(ct, TEXT("%s"), str->tmp->address);
	lstrcpy(a->tmp->address, ct);
	wsprintf(ct, TEXT("%s"), str->tmp->email);
	lstrcpy(a->tmp->email, ct);
	wsprintf(ct, TEXT("%s"), str->tmp->Pnum);
	lstrcpy(a->tmp->Pnum, ct);
	wsprintf(ct, TEXT("%s"), str->tmp->k);
	lstrcpy(a->tmp->k, ct);
	wsprintf(ct, TEXT("%s"), str->tmp->kg);
	lstrcpy(a->tmp->kg, ct);
	wsprintf(ct, TEXT("%s"), str->tmp->bl);
	lstrcpy(a->tmp->bl, ct);
	wsprintf(ct, TEXT("%s"), str->tmp->eye[0]);
	lstrcpy(a->tmp->eye[0], ct);
	wsprintf(ct, TEXT("%s"), str->tmp->eye[1]);
	lstrcpy(a->tmp->eye[1], ct);
	wsprintf(ct, TEXT("%s"), str->tmp->religian);
	lstrcpy(a->tmp->religian, ct);
	a->tmp->birth = str->tmp->birth;
	a->tmp->ps = str->tmp->ps;
	a->tmp->marry = str->tmp->marry;
	a->tmp->inyear = str->tmp->inyear;
	return a;
}
fm *ctot(cfm*str) {
	TCHAR ch[20];
	fm *t;
	t = createf();

	wsprintf(ch, TEXT("%s"), str->sno);
	lstrcpy(t->sno, ch);
	wsprintf(ch, TEXT("%s"), str->gan);
	lstrcpy(t->gan, ch);
	wsprintf(ch, TEXT("%s"), str->name);
	lstrcpy(t->name, ch);
	wsprintf(ch, TEXT("%s"), str->br);
	lstrcpy(t->br, ch);
	wsprintf(ch, TEXT("%s"), str->job);
	lstrcpy(t->job, ch);
	t->c = str->c;

	return t;
}
Dsw *ctot1(cDsw*str) {
	TCHAR ch[30];
	Dsw *t;
	t = createds();

	wsprintf(ch, TEXT("%s"), str->sno);
	lstrcpy(t->sno, ch);
	wsprintf(ch, TEXT("%s"), str->bs);
	lstrcpy(t->bs, ch);
	wsprintf(ch, TEXT("%s"), str->jik);
	lstrcpy(t->jik, ch);
	wsprintf(ch, TEXT("%s"), str->name);
	lstrcpy(t->name, ch);
	wsprintf(ch, TEXT("%s"), str->re);
	lstrcpy(t->re, ch);
	wsprintf(ch, TEXT("%s"), str->pnum);
	lstrcpy(t->pnum, ch);
	wsprintf(ch, TEXT("%s"), str->day);
	lstrcpy(t->day, ch);

	return t;
}

Dsw *in(sawoninfo*str) {
	Dsw *t;
	t = createds();
	lstrcpy(t->sno, str->sno);
	lstrcpy(t->bs, str->bs);
	lstrcpy(t->jik, str->jik);
	lstrcpy(t->name, str->tmp->name);
	lstrcpy(t->re, "0");
	lstrcpy(t->pnum, str->tmp->Pnum);
	lstrcpy(t->day, "0");

	return t;
}