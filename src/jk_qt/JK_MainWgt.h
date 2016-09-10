/****************************************
//  @ File Name : JK_MainWgt.h
//  @ Date : 2016/9/10
****************************************/


#if !defined(_JK_MAINWGT_H)
#define _JK_MAINWGT_H

#include <QMainWindow>

class JK_MainWgt : public QMainWindow
{
	Q_OBJECT
public:
	JK_MainWgt(QWidget* parent = nullptr);
	~JK_MainWgt();
};

#endif  //_JK_MAINWGT_H
