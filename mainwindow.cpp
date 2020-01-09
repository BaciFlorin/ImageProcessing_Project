#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_segmentation.h"
#include "image_2D_to_3D.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Browse_clicked()
{
    file_path_open = QFileDialog::getOpenFileName(this, tr("Select an image"), QDir::homePath(), file_path_filter);
    ui->lineEdit_Browse->setText(file_path_open);
    ui->pushButton_Export->setEnabled(false);
}

void MainWindow::on_pushButton_Exit_clicked()
{
    QCoreApplication::quit();
}

bool checkExtension(const std::string& filename)
{
    size_t pos = filename.rfind('.');
    if (pos == std::string::npos)
        return false;

    std::string ext = filename.substr(pos+1);

    if (ext == "jpg" || ext == "jpeg")
        return true;

    return false;
}

void MainWindow::on_pushButton_Start_clicked()
{
    std::string file_path_open_std = file_path_open.toStdString();
    if(checkExtension(file_path_open_std))
    {
        /// THE IMAGE
        Mat img = imread(file_path_open_std);

        /// IMAGE SEGMENTATION
        Mat image_seg =  regionGrowing(img);

        /// IMAGE 3D TRANSFORMATION
        Mat rimage = changeDirection(img, image_seg);
        result = transformation_3D(img, rimage);

        /// ENABLE EXPORTING
        ui->pushButton_Export->setEnabled(true);

        /// RESULT
        cv::imshow("Result", result);
    }
    else
    {
        QMessageBox::warning(this, "Picture error", "The picture must have a JPEG format! Please recheck your path.");
    }
}

void MainWindow::on_pushButton_Export_clicked()
{
    QString file_path_save = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), file_path_filter);
    std::string file_path_save_std = file_path_save.toStdString();
    if(checkExtension(file_path_save_std))
    {
        cv::imwrite( file_path_save_std, result);
    }
    else
    {
        QMessageBox::warning(this, "Picture error", "The picture must have a JPEG format and end in .jpg!");
    }
}

void MainWindow::on_lineEdit_Browse_editingFinished()
{
    file_path_open = ui->lineEdit_Browse->text();
}
