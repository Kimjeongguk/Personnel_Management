#include "sawon.h"
#include "struct.h"
#include "ex.h"

#define IDC_LIST1 1041
#define IDC_LIST2 1048
#define IDC_LIST3 1049
extern HINSTANCE g_hInst;
extern Manager *menu;
extern Jik *menu1;
extern Joggyo *menu2;
HWND hEdit, hEdit2, hEdit3;

BOOL CALLBACK DlgProc1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	int idx;
	TCHAR str[100];
	TCHAR str1[100];
	FILE *wp;
	Manager *t, *in;
	int i = 0;
	switch (iMessage) {
	case WM_INITDIALOG:
		hEdit = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_SORT | LBS_NOTIFY
			, 230, 10, 200, 250, hWnd, (HMENU)IDC_LIST1, g_hInst, NULL);
		t = menu;
		while (t->link != NULL) {
			t = t->link;
			SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)t->menu);
		}
		return TRUE;

	case WM_COMMAND:
		GetWindowText(GetDlgItem(hWnd, IDC_bsname), str, 100);
		idx = SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
		switch (LOWORD(wParam)) {
		case IDC_LIST1:
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK:
				idx = SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
				SendMessage(hEdit, LB_GETTEXT, idx, (LPARAM)str);
				SetDlgItemText(hWnd, IDC_bsname, str);
				break;
			}
			break;
		case IDC_ADD:
			SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)str);
			t = menu;
			in = createM();
			lstrcpy(in->menu, str);
			while (t->link != NULL) {
				t = t->link;
			}
			t->link = in;
			//	free(in);

			return TRUE;
		case IDC_DEL:
			idx = SendDlgItemMessage(hWnd, IDC_LIST1, LB_FINDSTRING, idx, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_LIST1, LB_DELETESTRING, idx, 0);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오."), TEXT("알림"), MB_OK);
			}

			else {
				t = menu;
				while (t->link != NULL) {
					if (lstrcmp(t->link->menu, str) == 0) {
						if (t->link == NULL) {
							t = NULL;
							break;
						}
						t->link = t->link->link;
						break;
					}
					t = t->link;
				}
			}
			return TRUE;
		case IDC_RE1:
			idx = SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETCURSEL, idx, (LPARAM)str);
			SendMessage(hEdit, LB_GETTEXT, idx, (LPARAM)str1);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오."), TEXT("알림"), MB_OK);
			}
			else {
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_DELETESTRING, idx, 0);
				t = menu;
				while (t->link != NULL) {
					if (lstrcmp(t->link->menu, str1) == 0) {
						if (t->link == NULL) {
							t = NULL;
							break;
						}
						t->link = t->link->link;
						break;
					}
					t = t->link;
				}
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, idx, (LPARAM)str);
				t = menu;
				in = createM();
				lstrcpy(in->menu, str);
				while (t->link != NULL) {
					t = t->link;
				}
				t->link = in;
			}
			return TRUE;
		case IDC_FIND:
			idx = SendDlgItemMessage(hWnd, IDC_LIST1, LB_FINDSTRING, idx, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_LIST1, LB_SETCURSEL, idx, 0);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("지정한 이름의 항목은 없습니다."), TEXT("알림"), MB_OK);
			}
			return TRUE;
		case IDC_END:
			t = menu;

			fopen_s(&wp, "bslist.txt", "w");

			while (t->link != NULL) {
				t = t->link;
				fprintf(wp, "%s\n", t->menu);
			}
			fclose(wp);
			EndDialog(hWnd, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK DlgProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {//사원등록
	int idx;
	TCHAR str[100];
	TCHAR str1[100];
	FILE *wp;
	Jik *t, *in;
	int i = 0;
	switch (iMessage) {
	case WM_INITDIALOG:
		hEdit2 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_SORT | LBS_NOTIFY
			, 230, 10, 200, 250, hWnd, (HMENU)IDC_LIST2, g_hInst, NULL);
		t = menu1;
		while (t->link != NULL) {
			t = t->link;
			SendDlgItemMessage(hWnd, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)t->menu);
		}
		return TRUE;

	case WM_COMMAND:
		GetWindowText(GetDlgItem(hWnd, IDC_jikname), str, 100);
		idx = SendDlgItemMessage(hWnd, IDC_LIST2, LB_GETCURSEL, 0, 0);
		switch (LOWORD(wParam)) {
		case IDC_LIST2:
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK:
				idx = SendDlgItemMessage(hWnd, IDC_LIST2, LB_GETCURSEL, 0, 0);
				SendMessage(hEdit2, LB_GETTEXT, idx, (LPARAM)str);
				SetDlgItemText(hWnd, IDC_jikname, str);
				break;
			}
			break;
		case IDC_JADD:
			SendDlgItemMessage(hWnd, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)str);
			t = menu1;
			in = createJ();
			lstrcpy(in->menu, str);
			while (t->link != NULL) {
				t = t->link;
			}
			t->link = in;

			return TRUE;
		case IDC_JDEL:
			idx = SendDlgItemMessage(hWnd, IDC_LIST2, LB_FINDSTRING, idx, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_LIST2, LB_DELETESTRING, idx, 0);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오."), TEXT("알림"), MB_OK);
			}

			else {
				t = menu1;
				while (t->link != NULL) {
					if (lstrcmp(t->link->menu, str) == 0) {
						if (t->link == NULL) {
							t = NULL;
							break;
						}
						t->link = t->link->link;
						break;
					}
					t = t->link;
				}
			}
			return TRUE;
		case IDC_JRE:
			idx = SendDlgItemMessage(hWnd, IDC_LIST2, LB_GETCURSEL, idx, (LPARAM)str);
			SendMessage(hEdit2, LB_GETTEXT, idx, (LPARAM)str1);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오."), TEXT("알림"), MB_OK);
			}
			else {
				SendDlgItemMessage(hWnd, IDC_LIST2, LB_DELETESTRING, idx, 0);
				t = menu1;
				while (t->link != NULL) {
					if (lstrcmp(t->link->menu, str1) == 0) {
						if (t->link == NULL) {
							t = NULL;
							break;
						}
						t->link = t->link->link;
						break;
					}
					t = t->link;
				}
				SendDlgItemMessage(hWnd, IDC_LIST2, LB_ADDSTRING, idx, (LPARAM)str);
				t = menu1;
				in = createJ();
				lstrcpy(in->menu, str);
				while (t->link != NULL) {
					t = t->link;
				}
				t->link = in;
			}
			return TRUE;
		case IDC_JFIND:
			idx = SendDlgItemMessage(hWnd, IDC_LIST2, LB_FINDSTRING, idx, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_LIST2, LB_SETCURSEL, idx, 0);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("지정한 이름의 항목은 없습니다."), TEXT("알림"), MB_OK);
			}
			return TRUE;
		case JIDOK:
			t = menu1;

			fopen_s(&wp, "jiklist.txt", "w");

			while (t->link != NULL) {
				t = t->link;
				fprintf(wp, "%s\n", t->menu);
			}
			fclose(wp);
			EndDialog(hWnd, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK DlgProc3(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	int idx;
	TCHAR str[100];
	TCHAR str1[100];
	FILE *wp;
	Joggyo *t, *in;
	int i = 0;
	switch (iMessage) {
	case WM_INITDIALOG:
		hEdit3 = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | LBS_SORT | LBS_NOTIFY
			, 230, 10, 200, 250, hWnd, (HMENU)IDC_LIST3, g_hInst, NULL);
		t = menu2;
		while (t->link != NULL) {
			t = t->link;
			SendDlgItemMessage(hWnd, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)t->menu);
		}
		return TRUE;

	case WM_COMMAND:
		GetWindowText(GetDlgItem(hWnd, IDC_jgname), str, 100);
		idx = SendDlgItemMessage(hWnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
		switch (LOWORD(wParam)) {
		case IDC_LIST3:
			switch (HIWORD(wParam)) {
			case LBN_DBLCLK:
				idx = SendDlgItemMessage(hWnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
				SendMessage(hEdit3, LB_GETTEXT, idx, (LPARAM)str);
				SetDlgItemText(hWnd, IDC_jgname, str);
				break;
			}
			break;
		case IDC_JGADD:
			SendDlgItemMessage(hWnd, IDC_LIST3, LB_ADDSTRING, 0, (LPARAM)str);
			t = menu2;
			in = createJO();
			lstrcpy(in->menu, str);
			while (t->link != NULL) {
				t = t->link;
			}
			t->link = in;

			return TRUE;
		case IDC_JGDEL:
			idx = SendDlgItemMessage(hWnd, IDC_LIST3, LB_FINDSTRING, idx, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_LIST3, LB_DELETESTRING, idx, 0);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오."), TEXT("알림"), MB_OK);
			}

			else {
				t = menu2;
				while (t->link != NULL) {
					if (lstrcmp(t->link->menu, str) == 0) {
						if (t->link == NULL) {
							t = NULL;
							break;
						}
						t->link = t->link->link;
						break;
					}
					t = t->link;
				}
			}
			return TRUE;
		case IDC_JGRE:
			idx = SendDlgItemMessage(hWnd, IDC_LIST3, LB_GETCURSEL, idx, (LPARAM)str);
			SendMessage(hEdit3, LB_GETTEXT, idx, (LPARAM)str1);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오."), TEXT("알림"), MB_OK);
			}
			else {
				SendDlgItemMessage(hWnd, IDC_LIST3, LB_DELETESTRING, idx, 0);
				t = menu2;
				while (t->link != NULL) {
					if (lstrcmp(t->link->menu, str1) == 0) {
						if (t->link == NULL) {
							t = NULL;
							break;
						}
						t->link = t->link->link;
						break;
					}
					t = t->link;
				}
				SendDlgItemMessage(hWnd, IDC_LIST3, LB_ADDSTRING, idx, (LPARAM)str);
				t = menu2;
				in = createJO();
				lstrcpy(in->menu, str);
				while (t->link != NULL) {
					t = t->link;
				}
				t->link = in;
			}
			return TRUE;
		case IDC_JGFIND:
			idx = SendDlgItemMessage(hWnd, IDC_LIST3, LB_FINDSTRING, idx, (LPARAM)str);
			SendDlgItemMessage(hWnd, IDC_LIST3, LB_SETCURSEL, idx, 0);
			if (idx == -1) {
				MessageBox(hWnd, TEXT("지정한 이름의 항목은 없습니다."), TEXT("알림"), MB_OK);
			}
			return TRUE;
		case JGIDOK:
			t = menu2;

			fopen_s(&wp, "jglist.txt", "w");

			while (t->link != NULL) {
				t = t->link;
				fprintf(wp, "%s\n", t->menu);
			}
			fclose(wp);
			EndDialog(hWnd, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}//
