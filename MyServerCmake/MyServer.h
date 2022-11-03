#ifndef MYSERVER_H
#define MYSERVER_H
#pragma once
#include <QWidget>
#include <QIODevice>
#include <QTcpServer>
#include <QTextEdit>
#include <QTcpSocket>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QString>
#include <QByteArray>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MyServer; }
QT_END_NAMESPACE

class MyServer : public QWidget
{
    Q_OBJECT

public:
    MyServer(QWidget *parent = nullptr);
    ~MyServer();

private:
    QTcpServer* m_ptcpServer;
    QTextEdit* m_ptxt;
    quint16 m_nNextBlockSize;
    Ui::MyServer *ui;
private:
    void sendToClient(QTcpSocket* pSocket,const QString& str);
    QMap<QString,QString> mMapTimeWorkSockets;

public:
    MyServer(int nPort,QWidget* pwgt=0);
public slots:
    virtual void slotNewConnection();
    void slotReadClient();
};
#endif // MYSERVER_H
