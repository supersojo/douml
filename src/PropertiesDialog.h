#pragma once


// PropertiesDialog �Ի���

class PropertiesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PropertiesDialog)

public:
	PropertiesDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PropertiesDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
