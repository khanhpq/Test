
// PictureBoxDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "XOpenCV.h"


// CPictureBoxDlg �_�C�A���O
class CPictureBoxDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	CPictureBoxDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[
    CString pathImage;
    CStatic  m_picture;    // pointer to a picture control
    float alpha, beta;

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICTUREBOX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDir();
	DECLARE_MESSAGE_MAP()
};
