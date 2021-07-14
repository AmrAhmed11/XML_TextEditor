#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

bool flag =0;
Node* currentNode;
QString openFile = "-1";
string functionUsed;
Tree tree;
//BasicXMLSyntaxHighlighter* highlighter;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //highlighter = new BasicXMLSyntaxHighlighter(ui->plainTextEdit);
    ui->openbtn->show();
    ui->save->hide();
    ui->Convertbtn->hide();
    ui->Compressbtn->hide();
    ui->SaveAsbtn->hide();
    ui->Prettifybtn->hide();
    ui->minifybtn->hide();
    ui->Compressbtn->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openbtn_clicked()
{
    openFile = QFileDialog::getOpenFileName(this,"Open a file","C://");
    QFile file(openFile);
    if(!file.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    else{
        Node* n = new Node("XML");
        currentNode = n;
        tree.setRoot(n);
        n->setType(3);
        QTextStream out(&file);
        QString text = out.readAll();
        stringManipulate(text.toStdString());
        //ui->plainTextEdit->setPlainText(text);
        ui->textBrowser->setText(text);
        ui->save->show();
        ui->SaveAsbtn->show();
        ui->minifybtn->show();
        ui->Prettifybtn->show();
        ui->minifybtn->show();
        ui->Prettifybtn->show();
        ui->Compressbtn->show();
    }
}




void MainWindow::on_actionOpen_triggered()
{
    openFile = QFileDialog::getOpenFileName(this,"Open a file","C://");
    QFile file(openFile);
    if(!file.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    else{
        Node* n = new Node("XML");
        currentNode = n;
        tree.setRoot(n);
        n->setType(3);
        QTextStream out(&file);
        QString text = out.readAll();
        stringManipulate(text.toStdString());
        ui->plainTextEdit->setPlainText(text);
        ui->save->show();
        ui->minifybtn->show();
        ui->Prettifybtn->show();
        ui->Compressbtn->show();
    }
}


void MainWindow::on_actionSave_triggered()
{
    QFile file(openFile);
    if(!file.open(QFile::WriteOnly | QFile::Text)){

    }
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}


void MainWindow::on_save_clicked()
{
    QFile file(openFile);
    if(!file.open(QFile::WriteOnly | QFile::Text)){

    }
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}



void MainWindow::on_minifybtn_clicked()
{
    QString str = QString::fromStdString(tree.minify());
    ui->plainTextEdit->setPlainText(str);
    functionUsed = "/minifiedVersion.xml";
    ui->minifybtn->setDisabled(1);
    ui->Prettifybtn->setEnabled(1);
}


void MainWindow::on_Prettifybtn_clicked()
{
    QString str = QString::fromStdString(tree.prettify());
    ui->plainTextEdit->setPlainText(str);
    ui->Prettifybtn->setDisabled(1);
    ui->minifybtn->setEnabled(1);
    functionUsed = "/prettifiedVersion.xml";
}


void MainWindow::on_Compressbtn_clicked()
{
    QFile file(openFile);
    if(!file.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    vector<int> hash = compress(text.toStdString());

    QString str;
    for(int i=0;i<hash.size();i++){
        str += QString::number(hash[i]) + " ";
    }
    string location = QFileDialog::getExistingDirectory(this,"Save As","C://").toStdString();
    location+="/compressed";
    QFile f(QString::fromStdString(location));
    if(!f.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream out(&f);
    out<<str;
    f.flush();
    f.close();
}


void MainWindow::on_Decompressbtn_clicked()
{
    string fileToDecompress =QFileDialog::getOpenFileName(this,"Open file to decompress","C://").toStdString();
    string str = decompress(fileToDecompress);
    string locationToSaveFile = QFileDialog::getExistingDirectory(this,"Select save location","C://").toStdString();
    locationToSaveFile+="/DecompressedVersion.xml";
    QFile f(QString::fromStdString(locationToSaveFile));
    if(!f.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream out(&f);
    out<<QString::fromStdString(str);
    f.flush();
    f.close();
    ui->plainTextEdit->setPlainText(QString::fromStdString(str));
}


void MainWindow::on_SaveAsbtn_clicked()
{
        string location = QFileDialog::getExistingDirectory(this,"Save As","C://").toStdString();
        location +=functionUsed;
        QFile file(QString::fromStdString(location));
        if(!file.open(QFile::ReadWrite | QFile::Text)){
            QMessageBox::warning(this,"title","file not open");
        }
        QTextStream out(&file);
        out<<ui->plainTextEdit->toPlainText();
        file.flush();
        file.close();
}



