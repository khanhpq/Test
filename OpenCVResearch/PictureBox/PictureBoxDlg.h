
// PictureBoxDlg.h : ヘッダー ファイル
//

#pragma once
#include "XOpenCV.h"


// CPictureBoxDlg ダイアログ
class CPictureBoxDlg : public CDialogEx
{
// コンストラクション
public:
	CPictureBoxDlg(CWnd* pParent = NULL);	// 標準コンストラクター
    CString pathImage;
    CStatic  m_picture;    // pointer to a picture control
    float alpha, beta;

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICTUREBOX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDir();
	DECLARE_MESSAGE_MAP()
};
