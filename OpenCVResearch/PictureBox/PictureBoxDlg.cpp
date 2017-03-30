
// PictureBoxDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "PictureBox.h"
#include "PictureBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPictureBoxDlg �_�C�A���O



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
    //[E-0806] �^��@�\�̎��̃r�f�I�t�@�C�����ŁA���O��t���ĕۑ��_�C�A���O�̃t�@�C������ύX���Ă��L���ɂȂ�Ȃ��s��̑Ή�  2007.05.15  H.Yoshimori
    //UpdateData(FALSE);
    UpdateData();
    static TCHAR BASED_CODE szFilter[] = _T("BMP/JPEG/PNG File(*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png||");


    // [E-0671] �t�B���^�[���X�g������s��Ή� 2007.04.02 H.Yoshimori
    //CFileDialog dlg(FALSE,"avi",m_strFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.avi",this);
    CFileDialog fileDlg(TRUE, NULL, pathImage, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
    if (fileDlg.DoModal() == IDOK)
    {
        pathImage = fileDlg.GetPathName();
        //[E-0806] �^��@�\�̎��̃r�f�I�t�@�C�����ŁA���O��t���ĕۑ��_�C�A���O�̃t�@�C������ύX���Ă��L���ɂȂ�Ȃ��s��̑Ή�  2007.05.15  H.Yoshimori
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

// CPictureBoxDlg ���b�Z�[�W �n���h���[

BOOL CPictureBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
    //m_picture = (CStatic *)GetDlgItem(IDC_PICTURE_CONTROL);
	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CPictureBoxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CPictureBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

