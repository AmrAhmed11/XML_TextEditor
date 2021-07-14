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
QString hashFile;
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
    ui->Correctbtn->hide();
    ui->Prettifybtn->hide();
    ui->minifybtn->hide();
    ui->Compressbtn->hide();
    ui->Decompressbtn->hide();
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
        ui->plainTextEdit->setPlainText(text);
        ui->save->show();
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
    QFile file("C:/Users/Amr/Desktop/ASU 1/min.txt");
    if(!file.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream out(&file);
    ui->plainTextEdit->setPlainText(str);
    out<<str;
    file.flush();
    file.close();
}


void MainWindow::on_Prettifybtn_clicked()
{
    QString str = QString::fromStdString(tree.prettify());
    QFile file("C:/Users/Amr/Desktop/ASU 1/prt.txt");
    if(!file.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream out(&file);
    ui->plainTextEdit->setPlainText(str);
    out<<str;
    file.flush();
    file.close();
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

    QFile f("C:/Users/Amr/Desktop/ASU 1/hashed.txt");
    hashFile ="C:/Users/Amr/Desktop/ASU 1/hashed.txt";
    if(!f.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream out(&f);
    ui->plainTextEdit->setPlainText(str);
    out<<str;
    f.flush();
    f.close();
    ui->Decompressbtn->show();

}


void MainWindow::on_Decompressbtn_clicked()
{
    QFile file("C:/Users/Amr/Desktop/ASU 1/dehashed.txt");
    if(!file.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    string str = decompress(hashFile.toStdString());
    QTextStream out(&file);
    ui->plainTextEdit->setPlainText(QString::fromStdString(str));
    out<<QString::fromStdString(str);
    file.flush();
    file.close();
}

