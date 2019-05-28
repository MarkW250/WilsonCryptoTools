#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "symbolanalysisform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_symbAnalButton_clicked()
{
    SymbolAnalysisForm* symbForm = new SymbolAnalysisForm();
    symbForm->show();
}
