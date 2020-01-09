#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

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

    void on_pushButton_Start_clicked();

    void on_pushButton_Export_clicked();

    void on_lineEdit_Browse_editingFinished();

private:
    Ui::MainWindow *ui;
    cv::Mat result;
    QString file_path_open;
    QString file_path_save;
    QString file_path_filter = "JPEG Files (*.jpg)";
};
#endif // MAINWINDOW_H
