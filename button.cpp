#include "button.h"


///////////////////////////
// BUTTON : PARENT CLASS //
///////////////////////////


Button::Button(QPoint pos, QSize size, QString label, bool active){
    pos_ = pos;
    size_ = size;
    label_ = label;

    active_ = active;
}


void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(item)
    Q_UNUSED(widget)

    QRect buttonRect(pos_, size_);
    QBrush b = painter->brush();
    //QRadialGradient highlight(get_pos(), 50);
    //painter->setBrush(b);

    painter->save();

    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);

    if(this->is_active()){
        painter->setPen(QColor(0,0,0,255));
    } else {
        painter->setPen(QColor(0,0,0,127));
    }

    painter->drawRect(buttonRect);  //drawRect(buttonRect);
    painter->drawText(buttonRect, Qt::AlignCenter, label_, &buttonRect);

    painter->restore();
}



void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->source();
    qDebug() << "got to the button!!" << endl;
    emit(startButtonClicked(*this));
}





//////////////////////////////
// PENCIL : BUTTON SUBCLASS //
//////////////////////////////


Pencil::Pencil(int xpos, int ypos, int width, int height, int id)
    : Button(QPoint(xpos,ypos), QSize(width,height), QString(QChar(id)), true)
{

    id_ = id;
    xpos_ = xpos;
    ypos_ = ypos;
    width_ = width;
    height_ = height;
    highlight_ = 0;

}



QRectF Button::boundingRect() const{
    return QRectF(pos_,size_);  //(xpos_, ypos_, width_, height_);
}


void Pencil::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item)
    Q_UNUSED(widget)

    QBrush b = painter->brush();
    painter->save();

    // make buttons highlightable

    if(is_active()){
        painter->setPen(QColor(0,0,0,255));
    } else {
        painter->setPen(QColor(0,0,0,127));
    }


    QRadialGradient highlight(get_pos(), 50);
    highlight.setColorAt(1, QColor(0,128,255, highlight_));
    //highlight.setColorAt(0, QColor(255,255,255, highlight_));

    painter->setBrush(highlight);

    QRect buttonRect(QPoint(xpos_,ypos_), QSize(width_,height_));
    painter->drawRect(buttonRect);  //drawRect(buttonRect);


    QFont font = painter->font();
    font.setPixelSize(25);
    painter->setFont(font);

    if(id_ == 0)
        painter->drawText(buttonRect, Qt::AlignCenter, QString("Erase"), &buttonRect);
    else
        painter->drawText(buttonRect, Qt::AlignCenter, QString::number(id_), &buttonRect);

    painter->restore();
}


void Pencil::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->source();
    if(is_active()){
        emit(pencilButtonClicked(*this));
    }
}



////////////////
// DIFFICULTY //
////////////////

Difficulty::Difficulty(QPoint p, QString s, int lvl) : Button(p, QSize(60,40), s, true)
{
    level_ = lvl;
    highlight_ = 0;
}



void Difficulty::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item)
    Q_UNUSED(widget)

    QRect buttonRect(Button::get_pos(), Button::get_size());
    QBrush b = painter->brush();
    //QRadialGradient highlight(get_pos(), 50);


    //painter->setBrush(b);

    painter->save();

    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);

    QRadialGradient highlight(get_pos(), 50);

    switch(get_lvl()){
    case 1:
        highlight.setColorAt(1, QColor(51,255,51, highlight_));
        break;

    case 2:
        highlight.setColorAt(1, QColor(255,255,51, highlight_));
        break;

    case 3:
        highlight.setColorAt(1, QColor(255,51,51, highlight_));
        break;


    }

    painter->setBrush(highlight);


    if(this->is_active()){
        painter->setPen(QColor(0,0,0,255));
        painter->setBrush(highlight);
    } else {
        painter->setPen(QColor(0,0,0,127));
        painter->setBrush(highlight);
    }


    painter->drawRect(buttonRect);
    painter->drawText(buttonRect, Qt::AlignCenter, Button::get_label(), &buttonRect);

    painter->restore();

}

void Difficulty::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->source();
    if(is_active()){
        emit(difficultyButtonClicked(*this));
    }
    update();
}


///////////////////
// AUTO-COMPLETE //
///////////////////


AutoComplete::AutoComplete(QPoint pos, QSize size) : Button(pos,size, QString("Auto-Complete"), true){
    qDebug() << "AutoComplete constructor success" << endl;
}


void AutoComplete::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->source();
    emit(autoButtonClicked(*this));
}


////////////
// VERIFY //
////////////


Verify::Verify(QPoint p, QSize s) : Button(p,s,QString("Verify"), true) {

}

void Verify::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->source();
    emit(verifyButtonClicked(*this));
}


//////////////
// GET HINT //
//////////////

Hint::Hint(QPoint p, QSize s) : Button(p,s,QString("Get Hint"), true){

}

void Hint::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->source();
    emit(hintButtonClicked(*this));
}


