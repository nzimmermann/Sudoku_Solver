#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QStyle>
#include <QRect>
#include <QPointF>

////////////
// BUTTON //
////////////

class Button : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Button(QPoint,QSize,QString,bool);

    QRectF boundingRect() const override;
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *item,
                       QWidget *widget) override;

    QPoint get_pos() { return pos_; }
    QSize get_size() { return size_; }
    QString get_label() { return label_; }


    void set_inactive() { this->active_ = false; update(); }
    void set_active() { this->active_ = true; update(); }
    bool is_active() { return active_; }

signals:
    void startButtonClicked(Button&);

    //void verifyButtonClicked(Button&);
    //void hintButtonClicked(Button&);
    void autoCompleteClicked(Button&);



protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


private:
    QString label_;  // String displayed on button
    QPoint  pos_;    // Position of button
    QSize   size_;   // Size of button's rectangle

    bool    active_; // Is button clickable?
    int pen_highlight_;




};


// PENCIL //


class Pencil : public Button
{
    Q_OBJECT

public:
    Pencil(int,int,int,int,int);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    int get_id() { return id_; }
    void highlight(){ highlight_ = 100; update(); }
    void unhighlight(){ highlight_ = 0; update(); }


signals:
    void pencilButtonClicked(Pencil&);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int id_,    highlight_;
    int xpos_,  ypos_;
    int width_, height_;

};



// DIFFICULTY //

class Difficulty : public Button
{
    Q_OBJECT

public:
    Difficulty(QPoint,QString,int);


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    int get_lvl() const { return level_; }

    void highlight() { highlight_ = 100; update();}
    void unhighlight() { highlight_ = 0; update();}

signals:
    void difficultyButtonClicked(Difficulty&);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int level_;
    int highlight_;

    bool selected_;

};


// AUTO-COMPLETE

class AutoComplete : public Button
{
    Q_OBJECT

public:
    AutoComplete(QPoint,QSize);

signals:
    void autoButtonClicked(AutoComplete&);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:

};



// Verify

class Verify : public Button
{
    Q_OBJECT

public:
    Verify(QPoint,QSize);

signals:
    void verifyButtonClicked(Verify&);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:

};


// Hint

class Hint : public Button
{
    Q_OBJECT

public:
    Hint(QPoint,QSize);

signals:
    void hintButtonClicked(Hint&);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:

};


#endif // BUTTON_H
