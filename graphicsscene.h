#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GraphicsScene(QObject *parent = 0);

signals:
    void mouseCoordinates(QString);

protected:
    //void mousePressEvent();
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // GRAPHICSSCENE_H
