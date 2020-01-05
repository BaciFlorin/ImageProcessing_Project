#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_2D_to_3D.h"
#include "image_segmentation.h"
#include <opencv2/opencv.hpp>
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
	file_path_filter = "JPEG Files (*.jpg)";
	file_path = QFileDialog::getOpenFileName(this, "Select an image", QDir::homePath(), file_path_filter);
	ui->lineEdit_Browse->setText(file_path);
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

	std::string ext = filename.substr(pos + 1);

	if (ext == "jpg" || ext == "jpeg")
		return true;

	return false;
}

void MainWindow::on_pushButton_Andrei_clicked()
{
	std::string file_path_std = file_path.toStdString();
	if (checkExtension(file_path_std))
	{
		////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////
		// COD ANDREI
		Mat result, image_seg, rimage;
		Mat img = imread(file_path_std);
		image_seg = regionGrowing(img);
		rimage = changeDirection(img, image_seg, 20);
		result = transformation_3D(img, rimage);
		imshow("Result", result);
		waitKey(0);
		////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////
	}
	else
	{
		QMessageBox::warning(this, "Picture error", "The picture must have a JPEG format! Please recheck your path.");
	}
}

void MainWindow::on_pushButton_Florin_clicked()
{
	std::string file_path_std = file_path.toStdString();
	if (checkExtension(file_path_std))
	{
		////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////
		// COD FLORIN
		////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////
	}
	else
	{
		QMessageBox::warning(this, "Picture error", "The picture must have a JPEG format! Please recheck your path.");
	}
}

void MainWindow::on_lineEdit_Browse_editingFinished()
{
	file_path = ui->lineEdit_Browse->text();
}
