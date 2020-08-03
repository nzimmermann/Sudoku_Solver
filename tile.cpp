#include <math.h>
#include "tile.h"



 // indent of tiles from the top-left corner


Tile::Tile(int row, int col, int digit)
{
    this->pos_x = col; // * width_ + INDENT;
    this->pos_y = row; // * height_ + INDENT;

    if(digit != 0){
        given_digit_ = true;
    }

    this->digit_ = digit;    
    this->shade_ = 100;

    selected_ = false;
    softshade_ = false;
    given_digit_ = false;


    available_ = {1,2,3,4,5,6,7,8,9};


}








void Tile::changeDigit(int digit){
    if(!given_digit_)
        digit_ = digit;

    update();
}


bool Tile::operator==(const Tile &t){
    return( digit_ == t.digit_ );
}


//
// UI METHODS
//

QRectF Tile::boundingRect() const{
    return QRectF(QPoint(pos_x,pos_y), QSize(width_,height_));
}



void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){

    Q_UNUSED(item)
    Q_UNUSED(widget)

    QRect tileSquare(QPoint(pos_x,pos_y), QSize(width_,height_));
    QBrush b = painter->brush();
    QRadialGradient highlight(get_pos(), 50);

    painter->save();

    // Determine tile color
    if(selected_){
        highlight.setColorAt(1, QColor(155,230,255));
    } else {
        if(given_digit_){
            if(softshade_){
                highlight.setColorAt(1, QColor(210,210,160));
            } else {
                highlight.setColorAt(1, QColor(175,175,175));
            }
        } else {
            if(softshade_){
                highlight.setColorAt(1, QColor(255,255,153));
            } else {
                highlight.setColorAt(1, QColor(255,255,255));
            }
        }
    }

    // Draw Tile
    //painter->setPen(Qt::SolidLine);

    painter->setBrush(highlight);

    painter->drawRect(tileSquare);

    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);

    if(digit_ != 0)
        painter->drawText(tileSquare, Qt::AlignCenter, QString::number(digit_), &tileSquare);
    else
        painter->drawText(tileSquare, Qt::AlignCenter, QString(QChar(' ')), &tileSquare);

    painter->restore();
}


void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    emit(tileClicked(*this));
    //qDebug() << "Tile clicked: 1" << endl;
}



