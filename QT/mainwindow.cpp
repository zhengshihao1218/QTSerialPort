#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_serialPort = new QSerialPort(this);

    m_serialPort->setPortName("COM7");
    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serialPort->open(QIODevice::ReadWrite)) {
        connect(m_serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
        ui->textEdit->append("串口已打开！");
    } else {
        ui->textEdit->append("串口打开失败！");
    }
}

MainWindow::~MainWindow()
{
    m_serialPort->close();
    delete ui;
}

void MainWindow::readData()
{
    data += m_serialPort->readAll();
    if(data.contains('\n') | data.contains('\r')) {
        ui->textEdit->append("单片机回复：" + QString::fromUtf8(data));
        data.clear();
    }

}


void MainWindow::on_pushButton_clicked()
{
    m_serialPort->write("ON\n");
}

void MainWindow::on_pushButton_2_clicked()
{
    m_serialPort->write("OFF\n");
}
