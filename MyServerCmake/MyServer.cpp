#include "MyServer.h"
#include "ui_MyServer.h"
#include <QFile>
#include <QTextStream>
MyServer::MyServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyServer)
{
    ui->setupUi(this);
}

MyServer::~MyServer()
{
    delete ui;
    delete this->m_ptcpServer;
}
MyServer::MyServer(int nPort, QWidget* pwgt):QWidget(pwgt)
                                            , m_nNextBlockSize(0)
{
    m_ptcpServer=new QTcpServer(this);
    if(!m_ptcpServer->listen(QHostAddress::Any,nPort)){
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              +m_ptcpServer->errorString()
                              );
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer,SIGNAL(newConnection()),
            this,           SLOT(slotNewConnection()));
    m_ptxt=new QTextEdit;
    m_ptxt->setReadOnly(true);
    QVBoxLayout* pvbxLayout= new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}
void MyServer::slotNewConnection(){
    QTcpSocket* pClientSocket=m_ptcpServer->nextPendingConnection();

    mMapTimeWorkSockets[pClientSocket->localAddress().toString()]="NULL";

    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
            );
    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
            );
    sendToClient(pClientSocket, "Server Response: Connected!");
}
void MyServer::slotReadClient(){
    QTcpSocket* pClientSocket =(QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    for(;;){
        if(!m_nNextBlockSize){
            if(pClientSocket->bytesAvailable()<sizeof(quint16)){
                break;
            }
            in>>m_nNextBlockSize;
        }
        if(pClientSocket->bytesAvailable()<m_nNextBlockSize){
            break;
        }
        QTime time;
        QTime timestart;
        QString str;
        in>>time>>str;
        QString key=pClientSocket->localAddress().toString();
        QString a="";
        if(mMapTimeWorkSockets[key]!="NULL"){

           time=QTime::currentTime();
           timestart=QTime::fromString(mMapTimeWorkSockets[key]);
           int totalseconds=time.hour()*3600+time.minute()*60+time.second()
                   -timestart.hour()*3600-timestart.minute()*60-timestart.second();
           QString tothours=QString::number(totalseconds%(24*3600)/3600);
           QString totminutes=QString::number(totalseconds%3600/60);
           QString totseconds=QString::number(totalseconds%60);
           a=(tothours.size()==1?"0"+tothours:tothours)+":"+
             (totminutes.size()==1?"0"+totminutes:totminutes)+":"+
             (totseconds.size()==1?"0"+totseconds:totseconds);

        }
        else{

            mMapTimeWorkSockets[key]=QTime::currentTime().toString();
            a="00:00:00";
        }
        QString strMessage=
                a+" "+"Calculator has send: "+str;
        QFile outfile("CalculatorAnswers.txt");
        if(outfile.open(QIODevice::Append)){
        QTextStream stream(&outfile);
        stream<<strMessage<<Qt::endl;
        }
        outfile.close();
        m_ptxt->append(strMessage);
        m_nNextBlockSize=0;
        sendToClient(pClientSocket,
                     "Server Response: Received \"" +str+"\""
                     );
    }
}
void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str){
    QByteArray arrBlock;
    QDataStream out(&arrBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out<<quint16(0)<<QTime::currentTime()<<str;
    out.device()->seek(0);
    out<<quint16(arrBlock.size()-sizeof(quint16));
    pSocket->write(arrBlock);
}


