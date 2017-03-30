
// PictureBox.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CPictureBoxApp:
// このクラスの実装については、PictureBox.cpp を参照してください。
//

class CPictureBoxApp : public CWinApp
{
public:
	CPictureBoxApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CPictureBoxApp theApp;