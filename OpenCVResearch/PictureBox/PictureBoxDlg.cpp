
// PictureBoxDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PictureBox.h"
#include "PictureBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPictureBoxDlg ダイアログ



CPictureBoxDlg::CPictureBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PICTUREBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    pathImage = _T("");
    alpha = -1.0;
    beta = 0.0;
}

void CPictureBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PICTURE_CONTROL, m_picture);
}

BEGIN_MESSAGE_MAP(CPictureBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, OnDir)
END_MESSAGE_MAP()

void CPictureBoxDlg::OnDir()
{
    //[E-0806] 録画機能の時のビデオファイル名で、名前を付けて保存ダイアログのファイル名を変更しても有効にならない不具合の対応  2007.05.15  H.Yoshimori
    //UpdateData(FALSE);
    UpdateData();
    static TCHAR BASED_CODE szFilter[] = _T("BMP/JPEG/PNG File(*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png||");


    // [E-0671] フィルターリストが壊れる不具合対応 2007.04.02 H.Yoshimori
    //CFileDialog dlg(FALSE,"avi",m_strFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.avi",this);
    CFileDialog fileDlg(TRUE, NULL, pathImage, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
    if (fileDlg.DoModal() == IDOK)
    {
        pathImage = fileDlg.GetPathName();
        //[E-0806] 録画機能の時のビデオファイル名で、名前を付けて保存ダイアログのファイル名を変更しても有効にならない不具合の対応  2007.05.15  H.Yoshimori
        //UpdateData();
        //Bind hbitmap to picturebox
        Xopencv *xopencv = new Xopencv(CT2A((LPCTSTR)pathImage));
        HBITMAP hbitmap;
        hbitmap = xopencv->CVMatToHBITMAP();
        m_picture.ModifyStyle(0xF, SS_BITMAP, SWP_NOSIZE);
        m_picture.SetBitmap(hbitmap);


        UpdateData(FALSE);
    }
    //EndDialog(0);
}

// CPictureBoxDlg メッセージ ハンドラー

BOOL CPictureBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
    //m_picture = (CStatic *)GetDlgItem(IDC_PICTURE_CONTROL);
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CPictureBoxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CPictureBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

