#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_Browse_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Andrei_clicked();

    void on_pushButton_Florin_clicked();

    void on_lineEdit_Browse_editingFinished();

private:
    Ui::MainWindow *ui;
    QString file_path;
    QString file_path_filter;
};
#endif // MAINWINDOW_H
