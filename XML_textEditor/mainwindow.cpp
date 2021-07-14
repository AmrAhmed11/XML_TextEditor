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
string bigFile;

int currentPage=0;
int pagesNo;
vector<int> pages;

//BasicXMLSyntaxHighlighter* highlighter;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //highlighter = new BasicXMLSyntaxHighlighter(ui->textEdit);
    ui->openbtn->show();
    ui->save->hide();
    ui->Convertbtn->hide();
    ui->Compressbtn->hide();
    ui->SaveAsbtn->hide();
    ui->Prettifybtn->hide();
    ui->minifybtn->hide();
    ui->Compressbtn->hide();
    ui->Previousbtn->hide();
    ui->Nextbtn->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openbtn_clicked()
{
    openFile = QFileDialog::getOpenFileName(this,"Open a file","C://");
    QFile file(openFile);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
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
//        if(text.size()<100000){
            ui->textEdit->setText(text);
//        }
//        else{
//            pagesNo = ceil(text.size()/100000);
//            bigFile = text.toStdString();
//            currentPage=0;
//            pages.push_back(0);
//            ui->Previousbtn->setDisabled(1);
//            for(int i=100000;i<bigFile.size();i++){
//                if(bigFile[i] == '>'){
//                    pages.push_back(i+1);
//                    i+=100000;
//                }
//            }
//            string toDisplay = bigFile.substr (pages[currentPage], pages[currentPage+1]);
//            ui->textEdit->setText(QString::fromStdString(toDisplay));
//            ui->textEdit->setText(QString::fromStdString(bigFile));
//        }
        ui->save->show();
        ui->SaveAsbtn->show();
        ui->minifybtn->show();
        ui->Prettifybtn->show();
        ui->minifybtn->show();
        ui->Prettifybtn->show();
        ui->Compressbtn->show();
//        ui->Previousbtn->show();
//        ui->Nextbtn->show();
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
        ui->textEdit->setText(text);
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
    QString text = ui->textEdit->toPlainText();
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
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}



void MainWindow::on_minifybtn_clicked()
{
    QString str = QString::fromStdString(tree.minify());
    ui->textEdit->setText(str);
    functionUsed = "/minifiedVersion.xml";
}


void MainWindow::on_Prettifybtn_clicked()
{
    QString str = QString::fromStdString(tree.prettify());
    ui->textEdit->setText(str);
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
    ui->textEdit->setPlainText(QString::fromStdString(str));
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
        out<<ui->textEdit->toPlainText();
        file.flush();
        file.close();
}




//void MainWindow::on_Nextbtn_clicked()
//{
//currentPage++;
//string toDisplay = bigFile.substr (pages[currentPage], pages[currentPage+1]);
//ui->textEdit->setText(QString::fromStdString(toDisplay));
//ui->Previousbtn->setEnabled(1);
//if(currentPage == pagesNo){
//ui->Nextbtn->setDisabled(1);
//}
//}


//void MainWindow::on_Previousbtn_clicked()
//{
//currentPage--;
//string toDisplay = bigFile.substr (pages[currentPage], pages[currentPage+1]);
//ui->textEdit->setText(QString::fromStdString(toDisplay));
//ui->Nextbtn->setEnabled(1);
//if(currentPage==0){
//ui->Previousbtn->setDisabled(1);
//}
//}

