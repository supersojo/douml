// PropertiesDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PropertiesDialog.h"
#include "afxdialogex.h"
#include "resource.h"

// PropertiesDialog �Ի���

IMPLEMENT_DYNAMIC(PropertiesDialog, CDialogEx)

PropertiesDialog::PropertiesDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

PropertiesDialog::~PropertiesDialog()
{
}

void PropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PropertiesDialog, CDialogEx)
END_MESSAGE_MAP()


// PropertiesDialog ��Ϣ�������
