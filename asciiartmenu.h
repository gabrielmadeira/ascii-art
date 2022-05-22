#ifndef ASCIIARTMENU_H
#define ASCIIARTMENU_H

#include <QMainWindow>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class ASCIIArtMenu; }
QT_END_NAMESPACE

class ASCIIArtMenu : public QMainWindow
{
    Q_OBJECT

public:
    ASCIIArtMenu(QWidget *parent = nullptr);
    ~ASCIIArtMenu();

private slots:

    void generateStructureBasedASCIIArt(cv::Mat img);

    void generateToneBasedASCIIArt(cv::Mat img);

    void on_btnChooseImage_clicked();

    void on_btnGenerateASCII_clicked();

    void on_btnReset_clicked();

    void on_btnResize_clicked();

    void on_btnThresh_clicked();

    void on_btnEdge_clicked();

    void on_btnBlur_clicked();

    void on_btnBright_clicked();

    void on_btnContrast_clicked();

    void on_btnIncFont_clicked();

    void on_btnDecFont_clicked();

private:
    Ui::ASCIIArtMenu *ui;
};
#endif // ASCIIARTMENU_H
