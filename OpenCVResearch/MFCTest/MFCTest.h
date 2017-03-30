
// MFCTest.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMFCTestApp:
// このクラスの実装については、MFCTest.cpp を参照してください。
//

class CMFCTestApp : public CWinApp
{
public:
	CMFCTestApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMFCTestApp theApp;