#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QImage>
#include <QTimer>

namespace Ui {
class PlayerWidget;
}

class QUdpSocket;

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();

private slots:
    void readBytes();
    void handleImage(QImage image);
    void printFrameRate();

    void on_bindButton_clicked();

signals:
    void newFrame(QImage image);


private:
    Ui::PlayerWidget *ui;

    QUdpSocket *client;
    QTimer timer;
    int fps;

    bool receivingImage;
    QString fileName;
    int imageSize;
    QByteArray imageDatagram;
};

#endif // PLAYERWIDGET_H
