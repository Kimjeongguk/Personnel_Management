#pragma warning(disable:4996) 
#include "sawon.h"
#include "struct.h"
#include "ex.h"

extern sawoninfo *data;
extern Manager *menu;
extern Jik *menu1;
extern Joggyo *menu2;
extern int peopleno;
extern sawoninfo *sw;
extern Dsw *menu4;

int check;
TCHAR sno[30];
static TCHAR fstr[30];

BOOL CALLBACK DlgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	TCHAR str[128];
	TCHAR A[4];
	TCHAR tm[4];
	TCHAR str2[] = TEXT("0000");
	FILE *of;
	sawoninfo *p, *temp;
	//	int i;
	switch (iMessage) {
	case WM_INITDIALOG:
		Manager *t;
		Jik *t1;
		Joggyo *t2;

		t = menu;
		t1 = menu1;
		t2 = menu2;

		while (t2->link != NULL) {
			t2 = t2->link;
			SendDlgItemMessage(hWnd, IDC_COMBO3, CB_ADDSTRING, 0, (LPARAM)t2->menu);
		}
		while (t->link != NULL) {
			t = t->link;
			SendDlgItemMessage(hWnd, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)t->menu);
		}
		while (t1->link != NULL) {
			t1 = t1->link;
			SendDlgItemMessage(hWnd, IDC_COMBO2, CB_ADDSTRING, 0, (LPARAM)t1->menu);
		}
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK1:
			p = create1();

			GetDlgItemText(hWnd, IDC_EDIT3, p->tmp->name, 100);
			p->tmp->birth = GetDlgItemInt(hWnd, IDC_EDIT4, NULL, FALSE);
			GetDlgItemText(hWnd, IDC_EDIT5, p->tmp->address, 500);
			GetDlgItemText(hWnd, IDC_EDIT6, p->tmp->email, 500);
			GetDlgItemText(hWnd, IDC_EDIT7, p->tmp->Pnum, 20);
			if (IsDlgButtonChecked(hWnd, IDC_RADIO1) == BST_CHECKED)p->tmp->ps = 1;//1=남
			else p->tmp->ps = 2;													//여
			GetDlgItemText(hWnd, IDC_EDIT8, p->tmp->k, 10);
			GetDlgItemText(hWnd, IDC_EDIT9, p->tmp->kg, 10);
			GetDlgItemText(hWnd, IDC_EDIT10, p->tmp->bl, 10);
			GetDlgItemText(hWnd, IDC_EDIT11, p->tmp->eye[0], 10);
			GetDlgItemText(hWnd, IDC_EDIT12, p->tmp->eye[1], 10);
			if (IsDlgButtonChecked(hWnd, IDC_RADIO3) == BST_CHECKED)p->tmp->marry = 1;//미혼
			else p->tmp->marry = 2;													//기혼
			p->tmp->inyear = GetDlgItemInt(hWnd, IDC_EDIT1, NULL, FALSE);
			GetDlgItemText(hWnd, IDC_COMBO3, p->tmp->religian, 10);
			GetDlgItemText(hWnd, IDC_COMBO1, p->bs, 30);
			GetDlgItemText(hWnd, IDC_COMBO2, p->jik, 30);

			_itoa(p->tmp->inyear, str, 10);
			peopleno++;
			lstrcpy(p->sno, str);
			A[0] = p->bs[0];
			A[1] = p->bs[1];
			if (p->tmp->ps == 1) A[2] = '1';
			else A[2] = '2';
			A[3] = '\0';
			lstrcat(p->sno, A);
			_itoa(peopleno, tm, 10);
			if (peopleno > 999) {
				lstrcpy(str2, tm);
			}
			else if (peopleno > 99) {
				str2[1] = tm[0];
				str2[2] = tm[1];
				str2[3] = tm[2];
			}
			else if (peopleno > 9) {
				str2[2] = tm[0];
				str2[3] = tm[1];
			}
			else { str2[3] = tm[0]; }
			lstrcat(p->sno, str2);

			sw->link = p;
			sw = sw->link;
			temp = data;

			fopen_s(&of, "swlist.txt", "w");
			if (of == NULL)MessageBox(hWnd, TEXT("파일이없습니다."), TEXT("알림"), MB_OK);
			do {
				temp = temp->link;
				fprintf(of, "%s %s %s %s %s %s %s %s %s %s %s %s %s %d %d %d %d \n"//7
					, temp->sno, temp->jik, temp->bs, temp->tmp->name, temp->tmp->address, temp->tmp->email
					, temp->tmp->Pnum, temp->tmp->k, temp->tmp->kg, temp->tmp->bl, temp->tmp->eye[0], temp->tmp->eye[1], temp->tmp->religian,
					temp->tmp->birth, temp->tmp->ps, temp->tmp->marry, temp->tmp->inyear);//17
			} while (temp->link != NULL);
			fclose(of);

			EndDialog(hWnd, IDOK1);
			return TRUE;

		case IDCANCEL:
			EndDialog(hWnd, IDCANCEL);
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CALLBACK DlgProc4(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	TCHAR str[100];
	TCHAR A[4];
	TCHAR tm[4];
	TCHAR str2[] = TEXT("0000");
	sawoninfo *swa, *temp;
	FILE *of;

	swa = data;

	switch (iMessage) {
	case WM_INITDIALOG:
		check = 0;
		Manager *t;
		Jik *t1;
		Joggyo *t2;

		t = menu;
		t1 = menu1;
		t2 = menu2;

		while (t2->link != NULL) {
			t2 = t2->link;
			SendDlgItemMessage(hWnd, IDC_RCOMBO3, CB_ADDSTRING, 0, (LPARAM)t2->menu);
		}
		while (t->link != NULL) {
			t = t->link;
			SendDlgItemMessage(hWnd, IDC_RCOMBO1, CB_ADDSTRING, 0, (LPARAM)t->menu);
		}
		while (t1->link != NULL) {
			t1 = t1->link;
			SendDlgItemMessage(hWnd, IDC_RCOMBO2, CB_ADDSTRING, 0, (LPARAM)t1->menu);
		}
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RBUTTON1:
			GetDlgItemText(hWnd, IDC_REDIT1, sno, 100);
			do {
				swa = swa->link;
				if (lstrcmp(swa->sno, sno) == 0) {
					check = 1;
					SetDlgItemText(hWnd, IDC_REDIT3, swa->tmp->name);
					SetDlgItemInt(hWnd, IDC_REDIT4, swa->tmp->birth, FALSE);
					SetDlgItemText(hWnd, IDC_REDIT5, swa->tmp->address);
					SetDlgItemText(hWnd, IDC_REDIT6, swa->tmp->email);
					SetDlgItemText(hWnd, IDC_REDIT7, swa->tmp->Pnum);
					SetDlgItemText(hWnd, IDC_REDIT8, swa->tmp->k);
					SetDlgItemText(hWnd, IDC_REDIT9, swa->tmp->kg);
					SetDlgItemText(hWnd, IDC_REDIT10, swa->tmp->bl);
					SetDlgItemText(hWnd, IDC_REDIT11, swa->tmp->eye[0]);
					SetDlgItemText(hWnd, IDC_REDIT12, swa->tmp->eye[1]);
					SetDlgItemInt(hWnd, IDC_REDIT2, swa->tmp->inyear, FALSE);
					SetDlgItemText(hWnd, IDC_RCOMBO3, swa->tmp->religian);
					SetDlgItemText(hWnd, IDC_RCOMBO1, swa->bs);
					SetDlgItemText(hWnd, IDC_RCOMBO2, swa->jik);
					if (swa->tmp->ps == 1) {
						SendMessage(GetDlgItem(hWnd, IDC_RRADIO1), BM_SETCHECK, iMessage, 0);
					}
					else {
						SendMessage(GetDlgItem(hWnd, IDC_RRADIO2), BM_SETCHECK, iMessage, 0);
					}
					if (swa->tmp->marry == 1) {
						SendMessage(GetDlgItem(hWnd, IDC_RRADIO3), BM_SETCHECK, iMessage, 0);
					}
					else {
						SendMessage(GetDlgItem(hWnd, IDC_RRADIO4), BM_SETCHECK, iMessage, 0);
					}
					return TRUE;
				}
			} while (swa->link != NULL);
			MessageBox(hWnd, TEXT("일치하는 사원번호가 없습니다."), TEXT("알림"), MB_OK);
			return TRUE;
		case RIDOK:
			if (check != 1) {
				MessageBox(hWnd, TEXT("검색먼서하세요."), TEXT("알림"), MB_OK);
				return TRUE;
			}
			swa = data;
			do {
				swa = swa->link;
				if (lstrcmp(swa->sno, sno) == 0) {
					GetDlgItemText(hWnd, IDC_REDIT3, swa->tmp->name, 100);
					MessageBox(hWnd, swa->tmp->name, TEXT("알림"), MB_OK);
					swa->tmp->birth = GetDlgItemInt(hWnd, IDC_REDIT4, NULL, FALSE);
					GetDlgItemText(hWnd, IDC_REDIT5, swa->tmp->address, 500);
					GetDlgItemText(hWnd, IDC_REDIT6, swa->tmp->email, 500);
					GetDlgItemText(hWnd, IDC_REDIT7, swa->tmp->Pnum, 20);
					if (IsDlgButtonChecked(hWnd, IDC_RRADIO1) == BST_CHECKED)swa->tmp->ps = 1;//1=남
					else swa->tmp->ps = 2;													//여
					GetDlgItemText(hWnd, IDC_REDIT8, swa->tmp->k, 10);
					GetDlgItemText(hWnd, IDC_REDIT9, swa->tmp->kg, 10);
					GetDlgItemText(hWnd, IDC_REDIT10, swa->tmp->bl, 10);
					GetDlgItemText(hWnd, IDC_REDIT11, swa->tmp->eye[0], 10);
					GetDlgItemText(hWnd, IDC_REDIT12, swa->tmp->eye[1], 10);
					if (IsDlgButtonChecked(hWnd, IDC_RRADIO3) == BST_CHECKED)swa->tmp->marry = 1;//미혼
					else swa->tmp->marry = 2;													//기혼
					swa->tmp->inyear = GetDlgItemInt(hWnd, IDC_REDIT2, NULL, FALSE);
					GetDlgItemText(hWnd, IDC_RCOMBO3, swa->tmp->religian, 10);
					GetDlgItemText(hWnd, IDC_RCOMBO1, swa->bs, 30);
					GetDlgItemText(hWnd, IDC_RCOMBO2, swa->jik, 30);

					_itoa(swa->tmp->inyear, str, 10);
					peopleno++;
					lstrcpy(swa->sno, str);
					A[0] = swa->bs[0];
					A[1] = swa->bs[1];
					if (swa->tmp->ps == 1) A[2] = '1';
					else A[2] = '2';
					A[3] = '\0';
					lstrcat(swa->sno, A);
					_itoa(peopleno, tm, 10);
					if (peopleno > 999) {
						lstrcpy(str2, tm);
					}
					else if (peopleno > 99) {
						str2[1] = tm[0];
						str2[2] = tm[1];
						str2[3] = tm[2];
					}
					else if (peopleno > 9) {
						str2[2] = tm[0];
						str2[3] = tm[1];
					}
					else { str2[3] = tm[0]; }
					lstrcat(swa->sno, str2);
					break;
				}
			} while (swa->link != NULL);

			temp = data;
			fopen_s(&of, "swlist.txt", "w");
			if (of == NULL)MessageBox(hWnd, TEXT("파일이없습니다."), TEXT("알림"), MB_OK);
			do {
				temp = temp->link;
				fprintf(of, "%s %s %s %s %s %s %s %s %s %s %s %s %s %d %d %d %d \n"//7
					, temp->sno, temp->jik, temp->bs, temp->tmp->name, temp->tmp->address, temp->tmp->email
					, temp->tmp->Pnum, temp->tmp->k, temp->tmp->kg, temp->tmp->bl, temp->tmp->eye[0], temp->tmp->eye[1], temp->tmp->religian,
					temp->tmp->birth, temp->tmp->ps, temp->tmp->marry, temp->tmp->inyear);//17
			} while (temp->link != NULL);
			check = 0;
			fclose(of);
			EndDialog(hWnd, RIDOK);
			return TRUE;
		case RIDCANCEL:
			EndDialog(hWnd, RIDCANCEL);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
BOOL CALLBACK DlgProc5(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	sawoninfo *t;
	char str[300];
	TCHAR str1[300];
	TCHAR str2[30];
	int year;
	switch (iMessage) {
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_SBUTTON1:
			SendDlgItemMessage(hWnd, IDC_SLIST1, LB_RESETCONTENT, 0, 0);
			GetDlgItemText(hWnd, IDC_SEDIT1, str2, 30);
			t = data;
			do {
				t = t->link;
				if (lstrcmp(str2, t->tmp->name) == 0) {
					sprintf_s(str, sizeof(str), "%s %s %s %s %s %s %s %s %s %s %s %s %s %d %d %d %d",
						t->sno, t->jik, t->bs, t->tmp->name, t->tmp->address, t->tmp->email, t->tmp->Pnum,
						t->tmp->k, t->tmp->kg, t->tmp->bl, t->tmp->eye[0], t->tmp->eye[1], t->tmp->religian, t->tmp->birth, t->tmp->ps, t->tmp->marry, t->tmp->inyear);
					wsprintf(str1, TEXT("%s"), str);
					SendDlgItemMessage(hWnd, IDC_SLIST1, LB_ADDSTRING, 0, (LPARAM)str1);
				}
			} while (t->link != NULL);
			return TRUE;
		case IDC_SBUTTON2:
			SendDlgItemMessage(hWnd, IDC_SLIST1, LB_RESETCONTENT, 0, 0);
			year = GetDlgItemInt(hWnd, IDC_SEDIT2, NULL, FALSE);
			t = data;
			do {
				t = t->link;
				if (t->tmp->inyear == year) {
					sprintf_s(str, sizeof(str), "%s %s %s %s %s %s %s %s %s %s %s %s %s %d %d %d %d",
						t->sno, t->jik, t->bs, t->tmp->name, t->tmp->address, t->tmp->email, t->tmp->Pnum,
						t->tmp->k, t->tmp->kg, t->tmp->bl, t->tmp->eye[0], t->tmp->eye[1], t->tmp->religian, t->tmp->birth, t->tmp->ps, t->tmp->marry, t->tmp->inyear);
					wsprintf(str1, TEXT("%s"), str);
					SendDlgItemMessage(hWnd, IDC_SLIST1, LB_ADDSTRING, 0, (LPARAM)str1);
				}
			} while (t->link != NULL);
			return TRUE;
		case IDC_SBUTTON3:
			SendDlgItemMessage(hWnd, IDC_SLIST1, LB_RESETCONTENT, 0, 0);
			GetDlgItemText(hWnd, IDC_SEDIT3, str2, 30);
			t = data;
			do {
				t = t->link;
				if (lstrcmp(str2, t->sno) == 0) {
					sprintf_s(str, sizeof(str), "%s %s %s %s %s %s %s %s %s %s %s %s %s %d %d %d %d",
						t->sno, t->jik, t->bs, t->tmp->name, t->tmp->address, t->tmp->email, t->tmp->Pnum,
						t->tmp->k, t->tmp->kg, t->tmp->bl, t->tmp->eye[0], t->tmp->eye[1], t->tmp->religian, t->tmp->birth, t->tmp->ps, t->tmp->marry, t->tmp->inyear);
					wsprintf(str1, TEXT("%s"), str);
					SendDlgItemMessage(hWnd, IDC_SLIST1, LB_ADDSTRING, 0, (LPARAM)str1);
				}
			} while (t->link != NULL);
			return TRUE;
		case IDC_SBUTTON4:
			SendDlgItemMessage(hWnd, IDC_SLIST1, LB_RESETCONTENT, 0, 0);
			t = data;
			do {
				t = t->link;
				sprintf_s(str, sizeof(str), "%s %s %s %s %s %s %s %s %s %s %s %s %s %d %d %d %d",
					t->sno, t->jik, t->bs, t->tmp->name, t->tmp->address, t->tmp->email, t->tmp->Pnum,
					t->tmp->k, t->tmp->kg, t->tmp->bl, t->tmp->eye[0], t->tmp->eye[1], t->tmp->religian, t->tmp->birth, t->tmp->ps, t->tmp->marry, t->tmp->inyear);
				wsprintf(str1, TEXT("%s"), str);
				SendDlgItemMessage(hWnd, IDC_SLIST1, LB_ADDSTRING, 0, (LPARAM)str1);

			} while (t->link != NULL);
			return TRUE;
		case SIDOK:
			EndDialog(hWnd, SIDOK);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
BOOL CALLBACK DlgProc6(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	sawoninfo *t;
	char str[300];
	TCHAR str1[300];
	TCHAR str2[30];
	Dsw *ds, *test;
	FILE *of;
	ds = menu4;
	do {
		if (ds->link == NULL) { break; }
		ds = ds->link;
	} while (ds->link != NULL);
	switch (iMessage) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_DBUTTON2:
			GetDlgItemText(hWnd, IDC_DEDIT1, str2, 30);
			SendDlgItemMessage(hWnd, IDC_DLIST1, LB_RESETCONTENT, 0, 0);
			t = data;
			do {
				t = t->link;
				if (lstrcmp(str2, t->sno) == 0) {
					check = 1;
					sprintf_s(str, sizeof(str), "%s %s %s %s %s %s %s %s %s %s %s %s %s %d %d %d %d",
						t->sno, t->jik, t->bs, t->tmp->name, t->tmp->address, t->tmp->email, t->tmp->Pnum,
						t->tmp->k, t->tmp->kg, t->tmp->bl, t->tmp->eye[0], t->tmp->eye[1], t->tmp->religian, t->tmp->birth, t->tmp->ps, t->tmp->marry, t->tmp->inyear);
					wsprintf(str1, TEXT("%s"), str);
					SendDlgItemMessage(hWnd, IDC_DLIST1, LB_ADDSTRING, 0, (LPARAM)str1);
				}
			} while (t->link != NULL);
			return TRUE;
		case IDC_DBUTTON1:
			if (check == 1) {
				t = data;
				GetDlgItemText(hWnd, IDC_DEDIT1, str2, 30);
				do {
					if (lstrcmp(str2, t->link->sno) == 0) {
						if (t->link->link == NULL) {
							ds->link = in(t->link);
							ds = ds->link;
							t->link = NULL;
							SendDlgItemMessage(hWnd, IDC_DLIST1, LB_RESETCONTENT, 0, 0);
							MessageBox(hWnd, TEXT("삭제완료!"), TEXT("알림"), MB_OK);
							test = menu4;
							fopen_s(&of, "deletesw.txt", "w");
							if (of == NULL)MessageBox(hWnd, TEXT("파일이없습니다."), TEXT("알림"), MB_OK);
							do {
								test = test->link;
								fprintf(of, "%s %s %s %s %s %s %s \n",test->sno, test->bs, test->jik, test->name, test->re, test->pnum, test->day);
							} while (test->link != NULL);
							fclose(of);
							break;
						}
						ds->link = in(t->link);
						ds = ds->link;
						t->link = t->link->link;
						SendDlgItemMessage(hWnd, IDC_DLIST1, LB_RESETCONTENT, 0, 0);
						MessageBox(hWnd, TEXT("삭제완료!"), TEXT("알림"), MB_OK);
						test = menu4;
						fopen_s(&of, "deletesw.txt", "w");
						if (of == NULL)MessageBox(hWnd, TEXT("파일이없습니다."), TEXT("알림"), MB_OK);
						do {
							test = test->link;
							fprintf(of, "%s %s %s %s %s %s %s \n",test->sno, test->bs, test->jik, test->name, test->re, test->pnum, test->day);
						} while (test->link != NULL);
						fclose(of);
						break;
					}
					t = t->link;
				} while (t->link != NULL);
				check = 0;
			}
			else {
				MessageBox(hWnd, TEXT("사원번호를 먼저입력하세요."), TEXT("알림"), MB_OK);
			}
			return TRUE;
		case DIDOK:
			EndDialog(hWnd, DIDOK);
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CALLBACK DlgProc7(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	sawoninfo *t;
	char str[300];
	TCHAR str1[300];
	FILE *of;
	switch (iMessage) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_FBUTTON4://검색
			GetDlgItemText(hWnd, IDC_FEDIT6, fstr, 30);
			SendDlgItemMessage(hWnd, IDC_FLIST1, LB_RESETCONTENT, 0, 0);
			t = data;
			do {
				t = t->link;
				if (lstrcmp(fstr, t->sno) == 0) {
					check = 1;
					if (t->f->c == 1) {
						sprintf_s(str, sizeof(str), "%s %s %s %s %s",
							t->sno, t->f->gan, t->f->name, t->f->br, t->f->job);
						wsprintf(str1, TEXT("%s"), str);
						SendDlgItemMessage(hWnd, IDC_FLIST1, LB_ADDSTRING, 0, (LPARAM)str1);
						return TRUE;
					}
					MessageBox(hWnd, TEXT("가족사항을 등록해주세요."), TEXT("알림"), MB_OK);
					return TRUE;
				}
			} while (t->link != NULL);
			MessageBox(hWnd, TEXT("일치하는 사원번호가 없습니다."), TEXT("알림"), MB_OK);
			return TRUE;
		case IDC_FBUTTON1://전제조회
			SendDlgItemMessage(hWnd, IDC_FLIST1, LB_RESETCONTENT, 0, 0);
			t = data;
			do {
				t = t->link;
				if (t->f->c == 1) {
					sprintf_s(str, sizeof(str), "%s %s %s %s %s",
						t->sno, t->f->gan, t->f->name, t->f->br, t->f->job);
					wsprintf(str1, TEXT("%s"), str);
					SendDlgItemMessage(hWnd, IDC_FLIST1, LB_ADDSTRING, 0, (LPARAM)str1);
				}
			} while (t->link != NULL);
			return TRUE;
		case IDC_FBUTTON5://삭제

			if (check == 1) {
				t = data;
				do {
					t = t->link;
					if (lstrcmp(t->sno, fstr) == 0) {
						t->f = createf();
						check = 0;
						SendDlgItemMessage(hWnd, IDC_FLIST1, LB_RESETCONTENT, 0, 0);
						MessageBox(hWnd, TEXT("삭제가 완료되었습니다."), TEXT("알림"), MB_OK);
						return TRUE;
					}
				} while (t->link != NULL);
			}
			MessageBox(hWnd, TEXT("사원번호를 먼저 입력해주세요."), TEXT("알림"), MB_OK);
			return TRUE;
		case IDC_FBUTTON3://수정
		case IDC_FBUTTON2://등록
			if (check == 1) {
				t = data;
				do {
					t = t->link;
					if (lstrcmp(t->sno, fstr) == 0) {
						t->f->c = 1;
						GetDlgItemText(hWnd, IDC_FEDIT6, t->f->sno, 30);
						GetDlgItemText(hWnd, IDC_FEDIT1, t->f->gan, 30);
						GetDlgItemText(hWnd, IDC_FEDIT2, t->f->name, 30);
						GetDlgItemText(hWnd, IDC_FEDIT3, t->f->br, 30);
						GetDlgItemText(hWnd, IDC_FEDIT4, t->f->job, 30);
						MessageBox(hWnd, TEXT("등록 완료!"), TEXT("알림"), MB_OK);
						check = 0;
						return TRUE;
					}
				} while (t->link != NULL);
				MessageBox(hWnd, TEXT("사원번호를 먼저 입력해주세요."), TEXT("알림"), MB_OK);
			}
			return TRUE;
		case FIDOK://확인
			sawoninfo *tt;
			fopen_s(&of, "flist.txt", "w");
			if (of == NULL)MessageBox(hWnd, TEXT("파일이없습니다."), TEXT("알림"), MB_OK);
			tt = data;
			do {
				tt = tt->link;
				if (tt->f->c == 1) {
					fprintf(of, "%s %s %s %s %s %d\n",
						tt->f->sno, tt->f->gan, tt->f->name, tt->f->br, tt->f->job, tt->f->c);
				}
			} while (tt->link!=NULL);
			fclose(of);
			EndDialog(hWnd, FIDOK);
			return TRUE;
		case FIDCANCEL:
			EndDialog(hWnd, FIDCANCEL);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
BOOL CALLBACK DlgProc8(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	Dsw *t;
	FILE *of;
	char str[300];
	static TCHAR dstr[30];
	static int check;
	TCHAR str1[300];
	TCHAR d1[50],d2[50];
	switch (iMessage) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_dsBUTTON1://전채검색
			SendDlgItemMessage(hWnd, IDC_dsLIST1, LB_RESETCONTENT, 0, 0);
			t = menu4;
			if (t->link != NULL) {
				do {
					t = t->link;
					sprintf_s(str, sizeof(str), "%s %s %s %s %s %s %s",
						t->sno, t->bs, t->jik, t->name, t->re, t->pnum, t->day);
					wsprintf(str1, TEXT("%s"), str);
					SendDlgItemMessage(hWnd, IDC_dsLIST1, LB_ADDSTRING, 0, (LPARAM)str1);
				} while (t->link != NULL);
			}
			return TRUE;
		case IDC_dsBUTTON2://사원번호검색
			SendDlgItemMessage(hWnd, IDC_dsLIST1, LB_RESETCONTENT, 0, 0);
			GetDlgItemText(hWnd, IDC_dsEDIT1, dstr, 30);
			t = menu4;
			if (t->link != NULL) {
				do {
					t = t->link;
					if (lstrcmp(dstr, t->sno) == 0) {
						check = 1;
						sprintf_s(str, sizeof(str), "%s %s %s %s %s %s %s",
							t->sno, t->bs, t->jik, t->name, t->re, t->pnum, t->day);
						wsprintf(str1, TEXT("%s"), str);
						SendDlgItemMessage(hWnd, IDC_dsLIST1, LB_ADDSTRING, 0, (LPARAM)str1);
						return TRUE;
					}
				} while (t->link != NULL);
			}
			MessageBox(hWnd, TEXT("일치하는 사원번호가 없습니다."), TEXT("알림"), MB_OK);			
			return TRUE;
		case IDC_dsBUTTON3://수정
			if (check == 1) {
				SendDlgItemMessage(hWnd, IDC_dsLIST1, LB_RESETCONTENT, 0, 0);
				GetDlgItemText(hWnd, IDC_dsEDIT2, d1, 50);
				GetDlgItemText(hWnd, IDC_dsEDIT3, d2, 50);
				t = menu4;
				do {
					t = t->link;
					if (lstrcmp(dstr, t->sno) == 0) {
						lstrcpy(t->day, d1);
						lstrcpy(t->re, d2);
						MessageBox(hWnd, TEXT("수정완료!"), TEXT(""), MB_OK);
						break;
					}
				} while (t->link != NULL);
				t = menu4;
			}
			else { MessageBox(hWnd, TEXT("사원번호를 먼저 입력하세요."), TEXT("알림"), MB_OK); }
			return TRUE;
		case dsIDOK:
			t = menu4;
			fopen_s(&of, "deletesw.txt", "w");
			if (of == NULL)MessageBox(hWnd, TEXT("파일이없습니다."), TEXT("알림"), MB_OK);
			if (t->link != NULL) {
				do {
					t = t->link;
					fprintf(of, "%s %s %s %s %s %s %s \n",t->sno, t->bs, t->jik, t->name, t->re, t->pnum, t->day);
				} while (t->link != NULL);
			}
			fclose(of);
			EndDialog(hWnd, dsIDOK);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}