#include"struct.h"
#include"sawon.h"
#include "ex.h"

int peopleno = 0;
HWND hTree;
HWND hList;
sawoninfo *data;
sawoninfo *sw;
Manager *menu;
Jik *menu1;
Joggyo *menu2;
HWND hWndMain;
cfm *menu3;
Dsw *menu4;

void InsertChild(HTREEITEM pNode, int pid) {
	TVINSERTSTRUCT TI;
	HTREEITEM Node;
	int i = 0;
	Manager *t;
	t = menu;
	while (t->link != NULL) {
		if (t->iParent == pid) {
			TI.hParent = pNode;
			TI.hInsertAfter = TVI_LAST;
			TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
			TI.item.pszText = t->menu;
			TI.item.lParam = i;
			Node = TreeView_InsertItem(hTree, &TI);
			InsertChild(Node, i);
		}
		i++;
		t = t->link;
	}
	if (t->iParent == pid) {
		TI.hParent = pNode;
		TI.hInsertAfter = TVI_LAST;
		TI.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
		TI.item.pszText = t->menu;
		TI.item.lParam = i;
		Node = TreeView_InsertItem(hTree, &TI);
		InsertChild(Node, i);
	}
	return;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK bsProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Manager");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	g_hInst = hInstance;
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);


	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	Manager *t, *p;
	Jik *t1, *p1;
	Joggyo *t2, *p2;
	csw *cs;
	cfm *cf,*cf2;
	cfm *cf1;
	Dsw *ds;
	cDsw *ds1;
	char *res;
	int r,i,j;
	char tmp[1000] = "";
	FILE *rp, *sp;
	static HWND hBs;
	LVCOLUMN COL;
	LVITEM LI;
	TCHAR test[300];
	TCHAR ch[30];
	TCHAR Cap[30];
	tag_Param *pParam;
	static HWND hCommbo;
	static TCHAR STR[100];


	switch (iMessage) {
	case WM_CREATE:
		data = create1();
		data->tmp = create();
		menu = createM();
		menu->iParent = -1;
		lstrcpy(menu->menu, TEXT("부서"));
		menu1 = createJ();
		menu2 = createJO();
		menu3 = createcf();
		menu4 = createds();
		t = menu;
		fopen_s(&rp, "bslist.txt", "r");
		if (rp == NULL) {
			MessageBox(hWnd, TEXT("파일없음"), TEXT("알림"), MB_OK);
		}
		else {
			while (1) {
				res = fgets(tmp, sizeof(tmp), rp);
				if (res == NULL)break;
				tmp[strlen(tmp) - 1] = '\0';
				wsprintf(test, TEXT("%s"), tmp);
				p = createM();
				lstrcpy(p->menu, test);
				t->link = p;
				t = t->link;
			}
		}
		fclose(rp);

		t1 = menu1;
		fopen_s(&rp, "jiklist.txt", "r");
		if (rp == NULL) {
			MessageBox(hWnd, TEXT("파일없음"), TEXT("알림"), MB_OK);
		}
		else {
			while (1) {
				res = fgets(tmp, sizeof(tmp), rp);
				if (res == NULL)break;
				tmp[strlen(tmp) - 1] = '\0';
				wsprintf(test, TEXT("%s"), tmp);
				p1 = createJ();
				lstrcpy(p1->menu, test);
				t1->link = p1;
				t1 = t1->link;
			}
		}
		fclose(rp);

		t2 = menu2;
		fopen_s(&rp, "jglist.txt", "r");
		if (rp == NULL) {
			MessageBox(hWnd, TEXT("파일없음"), TEXT("알림"), MB_OK);
		}
		else {
			while (1) {
				res = fgets(tmp, sizeof(tmp), rp);
				if (res == NULL)break;
				tmp[strlen(tmp) - 1] = '\0';
				wsprintf(test, TEXT("%s"), tmp);
				p2 = createJO();
				lstrcpy(p2->menu, test);
				t2->link = p2;
				t2 = t2->link;
			}
		}
		fclose(rp);



		InitCommonControls();
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
		CreateWindow(TEXT("button"), TEXT("전체조회"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 350, 6, 100, 25, hWnd, (HMENU)10, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 600, 6, 100, 25, hWnd, (HMENU)12, g_hInst, NULL);
		hCommbo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 500, 6, 100, 25, hWnd, (HMENU)11, g_hInst, NULL);
		t1 = menu1;
		do {
			t1 = t1->link;
			SendMessage(hCommbo, CB_ADDSTRING, 0, (LPARAM)t1->menu);
		} while (t1->link != NULL);
		hTree = CreateWindow(WC_TREEVIEW, TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES | TVS_SHOWSELALWAYS,
			10, 30, 300, 600, hWnd, NULL, g_hInst, NULL);
		InsertChild((HTREEITEM)0, -1);
		hList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT, 350, 30, 1000, 600, hWnd, NULL, g_hInst, NULL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 168;
		COL.pszText = TEXT("사원번호");
		COL.iSubItem = 0;
		ListView_InsertColumn(hList, 0, &COL);

		COL.pszText = TEXT("성명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hList, 1, &COL);

		COL.pszText = TEXT("부서");
		COL.iSubItem = 2;
		ListView_InsertColumn(hList, 2, &COL);

		COL.pszText = TEXT("직위");
		COL.iSubItem = 3;
		ListView_InsertColumn(hList, 3, &COL);

		COL.pszText = TEXT("입사년도");
		COL.iSubItem = 4;
		ListView_InsertColumn(hList, 4, &COL);

		COL.pszText = TEXT("생년월일");
		COL.iSubItem = 5;
		ListView_InsertColumn(hList, 5, &COL);
		sw = data;
		fopen_s(&sp, "swlist.txt", "r");
		if (sp == NULL) {
			MessageBox(hWnd, TEXT("파일없음"), TEXT("알림"), MB_OK);
		}
		else {
			while (1) {
				cs = createcsw();
				r = fscanf_s(sp, "%s%s%s%s%s%s%s%s%s%s%s%s%s%d%d%d%d",
					cs->sno, sizeof(cs->sno), cs->jik, sizeof(cs->jik), cs->bs, sizeof(cs->bs), cs->tmp->name, sizeof(cs->tmp->name),
					cs->tmp->address, sizeof(cs->tmp->address), cs->tmp->email, sizeof(cs->tmp->email), cs->tmp->Pnum, sizeof(cs->tmp->Pnum),
					cs->tmp->k, sizeof(cs->tmp->k), cs->tmp->kg, sizeof(cs->tmp->kg), cs->tmp->bl, sizeof(cs->tmp->bl), cs->tmp->eye[0], sizeof(cs->tmp->eye[0]),
					cs->tmp->eye[1], sizeof(cs->tmp->eye[1]), cs->tmp->religian, sizeof(cs->tmp->religian), &cs->tmp->birth, &cs->tmp->ps, &cs->tmp->marry, &cs->tmp->inyear);
				if (r == EOF)break;
				sw->link = CtoT(cs);
				sw = sw->link;
				peopleno++;
			}
		}
		fclose(sp);
		sw = data;
		cf = menu3;
		fopen_s(&sp, "flist.txt", "r");
		if (sp == NULL) {
			MessageBox(hWnd, TEXT("파일없음"), TEXT("알림"), MB_OK);
		}
		else {
			while (1) {
				cf1 = createcf();
				r = fscanf_s(sp, "%s%s%s%s%s%d", cf1->sno,sizeof(cf1->sno), cf1->gan,sizeof(cf1->gan),
					cf1->name,sizeof(cf1->name), cf1->br,sizeof(cf1->br), cf1->job,sizeof(cf1->job), &cf1->c);
				if (r == EOF)break;
				cf->link = cf1;
				cf = cf->link;
			}
			cf2 = menu3;
			if (cf2->link != NULL) {
				cf2 = cf2->link;
				do {
					if (sw->link == NULL)break;
					sw = sw->link;
					wsprintf(ch, TEXT("%s"), cf2->sno);
					if (lstrcmp(sw->sno, ch) == 0) {
						sw->f = ctot(cf);
						if (cf2->link != NULL) {
							cf2 = cf2->link;
						}
						else { break; }
					}
				} while (sw->link != NULL);
			}
		}
		fclose(sp);
		ds = menu4;
		fopen_s(&sp, "deletesw.txt", "r");
		if (sp == NULL) {
			MessageBox(hWnd, TEXT("파일없음"), TEXT("알림"), MB_OK);
		}
		else {
			while (1) {
				ds1 = createcds();
				r = fscanf_s(sp, "%s%s%s%s%s%s%s", ds1->sno, sizeof(ds1->sno), ds1->bs, sizeof(ds1->bs),ds1->jik,sizeof(ds1->jik), ds1->name, sizeof(ds1->name),
					ds1->re, sizeof(ds1->re), ds1->pnum, sizeof(ds1->pnum), ds1->day, sizeof(ds1->day));
				if (r == EOF)break;
				ds->link = ctot1(ds1);
				ds = ds->link;
				peopleno++;
			}
		}
		fclose(sp);
		return 0;

	case WM_NOTIFY:
		HTREEITEM hNow;
		TVITEMEX tv;
		LPNMHDR hdr;
		LPNMTREEVIEW ntv;
		TCHAR re[20];
		hdr = (LPNMHDR)lParam;
		ntv = (LPNMTREEVIEW)lParam;
		i = 0;
		if (hdr->hwndFrom == hTree) {
			switch (hdr->code) {
			case TVN_SELCHANGED:
				SendMessage(hList, LVM_DELETEALLITEMS, 0, 0);
				tv.mask = TVIF_PARAM|TVIF_TEXT;
				tv.hItem = ntv->itemNew.hItem;
				tv.pszText = Cap;
				tv.cchTextMax = 30;
				TreeView_GetItem(hTree, &tv);
				sw = data;
				do {
					sw = sw->link;
					if (lstrcmp(Cap, sw->bs) == 0) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = sw->sno;
						ListView_InsertItem(hList, &LI);
						ListView_SetItemText(hList, i, 1, sw->tmp->name);
						ListView_SetItemText(hList, i, 3, sw->jik);
						wsprintf(re, TEXT("%d"), sw->tmp->inyear);
						ListView_SetItemText(hList, i, 4, re);
						wsprintf(re, TEXT("%d"), sw->tmp->birth);
						ListView_SetItemText(hList, i, 5, re);
					}
				} while (sw->link != NULL);
				return 0;
			}
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 10:
			SendMessage(hList, LVM_DELETEALLITEMS, 0, 0);
			sw = data;
			i = 0;
			do {
				sw = sw->link;
				
				LI.mask = LVIF_TEXT;
				LI.iItem = i;
				LI.iSubItem = 0;
				LI.pszText = sw->sno;
				ListView_InsertItem(hList, &LI);
				ListView_SetItemText(hList, i, 1, sw->tmp->name);
				ListView_SetItemText(hList, i, 2, sw->bs);
				ListView_SetItemText(hList, i, 3, sw->jik);
				wsprintf(re, TEXT("%d"), sw->tmp->inyear);
				ListView_SetItemText(hList, i, 4, re);
				wsprintf(re, TEXT("%d"), sw->tmp->birth);
				ListView_SetItemText(hList, i, 5, re);
			} while (sw->link != NULL);
			break;
		case 11:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				j = SendMessage(hCommbo, CB_GETCURSEL, 0, 0);
				SendMessage(hCommbo, CB_GETLBTEXT, j, (LPARAM)STR);
				break;
			}
			break;
		case 12:
			SendMessage(hList, LVM_DELETEALLITEMS, 0, 0);
			sw = data;
			i = 0;
			do {
				sw = sw->link;
				if (lstrcmp(STR, sw->jik) == 0) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = sw->sno;
					ListView_InsertItem(hList, &LI);
					ListView_SetItemText(hList, i, 1, sw->tmp->name);
					ListView_SetItemText(hList, i, 2, sw->bs);
					wsprintf(re, TEXT("%d"), sw->tmp->inyear);
					ListView_SetItemText(hList, i, 4, re);
					wsprintf(re, TEXT("%d"), sw->tmp->birth);
					ListView_SetItemText(hList, i, 5, re);
				}
			} while (sw->link != NULL);
			break;
		case ID_40003://사원등록
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DlgProc);
			break;
		case ID_40006: //부서등록
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, DlgProc1);
			SendMessage(hTree, TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
			InsertChild((HTREEITEM)0, -1);
			break;
		case ID_40007://직위등록
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, DlgProc2);
			break;
		case ID_40008://종교등록
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG5), hWnd, DlgProc3);
			break;
		case ID_40009://사원수정
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, DlgProc4);
			break;
		case ID_40010://사원정보검색
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG7), hWnd, DlgProc5);
			break;
		case ID_40011://사원정보삭제
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG8), hWnd, DlgProc6);
			break;
		case ID_40012://가족사항등록
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG9), hWnd, DlgProc7);
			break;
		case ID_40013://x퇴직자등록
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG10), hWnd, DlgProc8);
			break;
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
