#include <QString>
#include <QImage>
#include <iostream>

using namespace std;

int main()
{

    QImage image("1.jpg");
    int w = image.width();
    int h = image.height();
    string red[256];
    string green[256];
    string blue[256];
    int i, j;

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            QRgb rgb = image.pixel(i, j);
            red[i][j] = qRed(rgb);
            green[i][j] = qGreen(rgb);
            blue[i][j] = qBlue(rgb);
        }
    }
    cout << red;
    return 0;
}