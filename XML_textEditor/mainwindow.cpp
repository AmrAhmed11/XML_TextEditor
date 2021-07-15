#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QSyntaxHighlighter>

bool flag =0;
Node* currentNode;
QString openFile = "-1";
string functionUsed = "-1";
Tree tree;
string bigFile;

int currentPage=0;
int pagesNo;
vector<int> pages;

BasicXMLSyntaxHighlighter* highlighter;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    highlighter = new BasicXMLSyntaxHighlighter(ui->textEdit);
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
    ui->Correctionbtn->hide();
    ui->textEdit_2->hide();

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
        vector<Error> e = stringManipulate(text.toStdString());
        vector<Error> balance = balanced();
        e.insert(e.end(),balance.begin(),balance.end());
        Display(alert(e,text));
        ui->save->show();
        ui->SaveAsbtn->show();
        if(e.size()>0){
            ui->Convertbtn->hide();
            ui->Correctionbtn->show();
            ui->minifybtn->hide();
            ui->Prettifybtn->hide();
        }
        else{
            ui->Convertbtn->show();
            ui->minifybtn->show();
            ui->Prettifybtn->show();
            ui->Correctionbtn->hide();
        }
        ui->Compressbtn->show();
    }
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
    Display(str);
    functionUsed = "/minifiedVersion.xml";
}

void MainWindow::on_Prettifybtn_clicked()
{
    QString str = QString::fromStdString(tree.prettify());
    Display(str);
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
    Display(QString::fromStdString(str));
}

void MainWindow::on_SaveAsbtn_clicked()
{
        string location = QFileDialog::getExistingDirectory(this,"Save As","C://").toStdString();
        if(functionUsed=="-1"){
            functionUsed = "/SaveAs.xml";
        }
        location +=functionUsed;
        QFile file(QString::fromStdString(location));
        if(!file.open(QFile::ReadWrite | QFile::Text)){
            QMessageBox::warning(this,"title","file not open");
        }
        QTextStream out(&file);
        out<<QString::fromStdString(bigFile);
        file.flush();
        file.close();
}

void MainWindow::on_Nextbtn_clicked()
{
    currentPage++;
    string toDisplay = bigFile.substr (pages[currentPage], pages[currentPage+1]-pages[currentPage]);
    ui->textEdit->setText(QString::fromStdString(toDisplay));
    ui->Previousbtn->setEnabled(1);
    string text2str = to_string(currentPage)+" Out of "+to_string(pagesNo);
    ui->textEdit_2->setText(QString::fromStdString(text2str));
    if(currentPage == pagesNo){
        ui->Nextbtn->setDisabled(1);
    }
}

void MainWindow::on_Previousbtn_clicked()
{
    currentPage--;
    string toDisplay = bigFile.substr (pages[currentPage], pages[currentPage+1]-pages[currentPage]);
    ui->textEdit->setText(QString::fromStdString(toDisplay));
    ui->Nextbtn->setEnabled(1);
    string text2str = to_string(currentPage)+"Out of "+to_string(pagesNo);
    ui->textEdit_2->setText(QString::fromStdString(text2str));
    if(currentPage==0){
        ui->Previousbtn->setDisabled(1);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    on_openbtn_clicked();
}


void MainWindow::on_actionSave_triggered()
{
    on_save_clicked();
}


void MainWindow::on_actionSave_As_triggered()
{
    on_SaveAsbtn_clicked();
}


void MainWindow::on_actionCompress_triggered()
{
    on_Compressbtn_clicked();
}


void MainWindow::on_actionDecompress_triggered()
{
    on_Decompressbtn_clicked();
}

void MainWindow::Display(QString str){
    pages.clear();
    if(str.size()<100000){
        bigFile = str.toStdString();
        ui->textEdit->setText(str);
        ui->Previousbtn->setDisabled(1);
        ui->Nextbtn->setDisabled(1);
    }
    else{
        ui->textEdit_2->show();
        bigFile = str.toStdString();
        currentPage=0;
        pages.push_back(0);
        ui->Previousbtn->setDisabled(1);
        ui->Nextbtn->setEnabled(1);
        for(int i=100000;i<bigFile.size();i++){
            if(i == bigFile.size()-1){
                pages.push_back(bigFile.size());
                break;
            }
            if(bigFile[i]=='>'){
                pages.push_back(i+1);
                if(i+100000<bigFile.size()){
                    i+=100000;
                }
                else{
                    pages.push_back(bigFile.size());
                    break;
                }
            }
        }
        pagesNo = pages.size()-2;
        string text2str = to_string(currentPage)+" Out of "+to_string(pagesNo);
        ui->textEdit_2->setText(QString::fromStdString(text2str));
        string toDisplay = bigFile.substr (pages[currentPage], pages[currentPage+1]-pages[currentPage]);
        ui->textEdit->setText(QString::fromStdString(toDisplay));
        ui->Previousbtn->show();
        ui->Nextbtn->show();
    }
}

QString MainWindow::alert(vector<Error> e,QString s){
    if(e.size()==0){
        return s;
    }
    string rtn = "";
    int start=0;

    vector<int> sortedPoints;
    for(int i=0;i<e.size();i++){
        if(e[i].type==1){
            sortedPoints.push_back(e[i].openPosition);
        }
        else if(e[i].type==2){
            sortedPoints.push_back(e[i].openPosition);
            sortedPoints.push_back(e[i].closePosition+2);
        }
        else if(e[i].type ==3){
            sortedPoints.push_back(e[i].closePosition+2);
        }
    }

    sort(sortedPoints.begin(),sortedPoints.end());

    for(int i=0;i<sortedPoints.size();i++){
        rtn+= s.toStdString().substr(start,sortedPoints[i]-start)+"!!";
        start = sortedPoints[i];
    }
    rtn+=s.toStdString().substr(start,s.size()-start);
    return QString::fromStdString(rtn);
}

void MainWindow::on_Correctionbtn_clicked()
{
    QString str = QString::fromStdString(tree.prettify());
    Display(str);
    functionUsed = "/CorrectVersion.xml";
    ui->Correctionbtn->hide();
    ui->Prettifybtn->show();
    ui->minifybtn->show();
    ui->Convertbtn->show();
}


void MainWindow::on_Convertbtn_clicked()
{
    QString str = QString::fromStdString(tree.jsonify());
    string locationToSaveFile = QFileDialog::getExistingDirectory(this,"Select save location","C://").toStdString();
    locationToSaveFile+="/JSONVersion.json";
    QFile f(QString::fromStdString(locationToSaveFile));
    if(!f.open(QFile::ReadWrite | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream out(&f);
    out<<str;
    f.flush();
    f.close();

}

