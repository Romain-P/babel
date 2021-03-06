#include <iostream>
#include <regex>
#include <memory>
#include <thread>
#include <QMessageBox>
#include <QPixmap>
#include <QtCore/QCoreApplication>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "livewindow.h"
#include "../Exception.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	_child(nullptr)
{
	ui->setupUi(this);
	QPixmap pix(":/resources/logobabel.png");
	int w = ui->label_pic->width();
	int h = ui->label_pic->height();
	ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
	QIcon icon(":/resources/icon.png");
	this->setWindowIcon(icon);
    ui->lblInfos->setStyleSheet("QLabel { color : red; }");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QWidget *newWindow = nullptr;

    newWindow = new LiveWindow(this
            , std::string(ui->username->text().toUtf8().constData())
            , ui->serverAdress->text().toUtf8().constData()
            , std::atoi(ui->serverPort->text().toUtf8().constData()));
    if (!newWindow)
        throw Exception("mainwindow: impossible to open new window");
    newWindow->move(geometry().center() - newWindow->geometry().center());
    newWindow->show();
    this->hide();
}

void MainWindow::on_username_textChanged(const QString &arg1)
{
    std::regex r_username("^[a-zA-Z0-9-]+$");
	std::string	tmp = arg1.toUtf8().constData();

    if (!std::regex_match(tmp, r_username))
        ui->username->setText(ui->username->text().remove(ui->username->text().size() - 1, 1));
    ui->lblInfos->setText("Only alphanumeric allowed with minimum 3 to 84 characters");
    textChanged();
}

void MainWindow::on_serverAdress_textChanged(const QString &arg1)
{
    std::regex r_adress("^[0-9.]+$");

    if (!std::regex_match(arg1.toUtf8().constData(), r_adress))
        ui->serverAdress->setText(ui->serverAdress->text().remove(ui->serverAdress->text().size() - 1, 1));
    ui->lblInfos->setText("Only IP format allowed");
    textChanged();
}

void MainWindow::on_serverPort_textChanged(const QString &arg1)
{

    std::regex r_port("^[0-9]+$");

    if (!std::regex_match(arg1.toUtf8().constData(), r_port))
        ui->serverPort->setText(ui->serverPort->text().remove(ui->serverPort->text().size() - 1, 1));
    ui->lblInfos->setText("Only numeric allowed minimum 1 to 6 caharcters");
    textChanged();
}

void MainWindow::textChanged()
{
    std::regex r_username("[a-zA-Z0-9-]{3,84}");
    std::regex r_adress("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    std::regex r_port("[0-9]{1,6}");

    if (std::regex_match(ui->username->text().toUtf8().constData(), r_username)
    && std::regex_match(ui->serverAdress->text().toUtf8().constData(), r_adress)
    &&  std::regex_match(ui->serverPort->text().toUtf8().constData(), r_port)) {
        ui->lblInfos->setText("");
        ui->lblInfos->setStyleSheet("QLabel { color : green; }");
        if (!ui->pushButton_Login->isEnabled())
            ui->pushButton_Login->setEnabled(true);
    } else {
        if (ui->pushButton_Login->isEnabled())
            ui->pushButton_Login->setEnabled(false);
        ui->lblInfos->setStyleSheet("QLabel { color : red; }");
    }
}

void MainWindow::returnPressed()
{
	if (ui->pushButton_Login->isEnabled())
		on_pushButton_Login_clicked();
}

void MainWindow::on_username_returnPressed()
{
	returnPressed();
}

void MainWindow::on_serverAdress_returnPressed()
{
	returnPressed();
}

void MainWindow::on_serverPort_returnPressed()
{
	returnPressed();
}
