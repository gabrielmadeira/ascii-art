#include "asciiartmenu.h"
#include "ui_asciiartmenu.h"

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat img;
string imgTitle = "Image";
Mat originalImg;

ASCIIArtMenu::ASCIIArtMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ASCIIArtMenu)
{
    ui->setupUi(this);
}

ASCIIArtMenu::~ASCIIArtMenu()
{
    delete ui;
}

//string curDir = QDir::toNativeSeparators(QDir::currentPath()).toStdString();
//string curDir = QCoreApplication::applicationDirPath().toStdString();

long int templateMatching(Mat glyph, Mat segment) {
    long int dif = 0;
    for (int row = 0; row < glyph.rows-1; row++)
        for (int col = 0; col < glyph.cols-1; col++)
            dif += abs(glyph.at<uint8_t>(row, col)-segment.at<uint8_t>(row, col));

    return dif;
}

void ASCIIArtMenu::generateStructureBasedASCIIArt(Mat img) {

    vector<char> chars = {'$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*', 'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm', 'Z' ,'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X', 'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't', '/', '\\', '|', '(', ')', '1', '{', '}', '[', ']', '?', '-', '+', '~', '<', '>', 'i', '!', 'l', 'I', ';', ':', ',', '\'', '^', '`', '"', '.', ' '};
    vector<string> charsFileName = {"dl", "at", "B", "perc", "8", "and", "W", "M", "hash", "ast", "o", "a", "h", "k", "b", "d", "p", "q", "w", "m", "Z" ,"O", "0", "Q", "L", "C", "J", "U", "Y", "X", "z", "c", "v", "u", "n", "x", "r", "j", "f", "t", "sla", "csla", "pip", "par", "cpar", "1", "cbra", "ccbra", "sbra", "csbra", "quest", "dash", "plus", "til", "less", "great", "i", "ex", "l", "I", "semc", "col", "comm", "singc", "car", "bco", "quot", "dot", "space"};

    unordered_map<char, Mat> charsImg;
    for(int i=0; i<chars.size(); i++)
        charsImg[chars[i]] = imread("glyphs1\\"+charsFileName[i]+".png",IMREAD_GRAYSCALE);

    string output = "";
    bool space = ui->checkSpace->isChecked();

    int charsImageSize = 8;
    int nRows = img.rows-charsImageSize;
    int nCols = img.cols-charsImageSize;
    for (int row = 0; row < nRows; row += charsImageSize) {
        for (int col = 0; col < nCols; col += charsImageSize) {
            Rect crop(col, row, charsImageSize-1, charsImageSize-1);
            Mat segment = img(crop);

            int minDiff = INT_MAX;
            char minDiffChar = NULL;
            for(auto c : charsImg) {
                int diff = templateMatching(c.second, segment);
                if(diff < minDiff) {
                    minDiff = diff;
                    minDiffChar = c.first;
                }
            }
            output += minDiffChar;
            if(space)
                output += ' ';
        }
        output += "\n";
    }
    output += "Lines: " + to_string(nRows/charsImageSize) + "\n";
    ui->textResult->setPlainText(QString::fromStdString(output));
}

char calculate_symbol(Mat image, int posX, int posY)
{
    string density = "@W$9876543210?!abc;:+-,._ ";
    int pixel_value = image.at<uint8_t>(posX, posY); // Talvez ,mudar x e y
    float difference = 0.0;
    int tam_of_desnsity = density.length();
    float intervalo = 256.0 / tam_of_desnsity;
    vector<float> values;

    for(int i = 0; i < tam_of_desnsity; i++)
    {
        difference = fabs(pixel_value - (intervalo * i));
        values.push_back(difference);
    }

    int index = 0;
    float minus = values[0];
    for(int j = 0; j < tam_of_desnsity; j++)
    {
        if(values[j] < minus)
        {
            minus = values[j];
            index = j;
        }
    }

    return density[index];
}

void ASCIIArtMenu::generateToneBasedASCIIArt(Mat img) {

    double resizeFactor = 0.15;
    cv::resize(img, img, Size(), resizeFactor, resizeFactor);

    string output = "";
    bool space = ui->checkSpace->isChecked();

    for(int i = 0; i < img.size().height; i++)
    {
        for(int j = 0; j < img.size().width; j++)
        {
            output += calculate_symbol(img, i, j);
            if(space)
                output += ' ';
        }
        output += "\n";
    }
    output += "Lines: " + to_string(img.size().height) + "\n";
    ui->textResult->setPlainText(QString::fromStdString(output));
}

void ASCIIArtMenu::on_btnChooseImage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.jpg *.jpeg *.bmp *.png)"));
    if (QString::compare(filename, QString()) != 0)
    {
        img = imread(filename.toStdString(),IMREAD_GRAYSCALE);
        originalImg = img.clone();
        imshow(imgTitle,img);

    }
}


void ASCIIArtMenu::on_btnGenerateASCII_clicked()
{
    if(ui->radioStructure->isChecked())
        generateStructureBasedASCIIArt(img);
    else
        generateToneBasedASCIIArt(img);
}



void ASCIIArtMenu::on_btnReset_clicked()
{
    img = originalImg.clone();
    imshow(imgTitle,img);
}


void ASCIIArtMenu::on_btnResize_clicked()
{
    double resizeFactor = ui->spinSizeRatio->value();
    cv::resize(img, img, Size(), resizeFactor, resizeFactor);
    imshow(imgTitle,img);
}


void ASCIIArtMenu::on_btnThresh_clicked()
{
    double threshValue = ui->spinThreshValue->value();
    threshold(img, img,threshValue,255,THRESH_BINARY);
    imshow(imgTitle,img);
}


void ASCIIArtMenu::on_btnEdge_clicked()
{
    int cannyThreshold = ui->spinEdgeValue->value();
    Canny(img, img,10*(cannyThreshold+1/10),cannyThreshold*3);
    bitwise_not(img, img);
    imshow(imgTitle,img);
}


void ASCIIArtMenu::on_btnBlur_clicked()
{
    double blurValue = ui->spinBlurValue->value();
    GaussianBlur(img, img, Size(5,5), blurValue, blurValue);
    imshow(imgTitle,img);
}


void ASCIIArtMenu::on_btnBright_clicked()
{
    int brightValue = ui->spinBrightValue->value();
    img.convertTo(img, -1, 1, brightValue);
    imshow(imgTitle,img);
}


void ASCIIArtMenu::on_btnContrast_clicked()
{
    double contrastValue = ui->spinContrastValue->value();
    img.convertTo(img, -1, contrastValue, 0);
    imshow(imgTitle,img);
}


void ASCIIArtMenu::on_btnIncFont_clicked()
{
    QFont f = ui->textResult->font();
    f.setPointSize(f.pointSize()+1);
    ui->textResult->setFont(f);
}


void ASCIIArtMenu::on_btnDecFont_clicked()
{
    QFont f = ui->textResult->font();
    f.setPointSize(f.pointSize()-1);
    ui->textResult->setFont(f);
}

