#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BasicXMLSyntaxHighlighter.h"
#include "../XMLparser/string_manipulate.h"
#include "../compression.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openbtn_clicked();



    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_save_clicked();


    void on_minifybtn_clicked();

    void on_Prettifybtn_clicked();

    void on_Compressbtn_clicked();

    void on_Decompressbtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
