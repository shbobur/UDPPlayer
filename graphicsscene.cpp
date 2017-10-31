#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{

}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QString x = "x: " + QString::number(mouseEvent->scenePos().x());
    QString y = " y: " + QString::number(mouseEvent->scenePos().y());
    emit mouseCoordinates(x + y);
}
