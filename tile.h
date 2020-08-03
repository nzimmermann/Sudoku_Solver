#ifndef TILE_H
#define TILE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QStyle>
#include <QRect>
#include <QPointF>
#include <QDebug>

#include <vector>

#define CELL 40
#define INDENT 30


class Tile : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Tile(int x, int y, int digit);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item,
               QWidget *widget) override;

    void changeDigit(int digit);

    void set_given() { given_digit_ = true; }
    bool is_given() { return given_digit_; }

    int get_digit() { return digit_; }

    QPointF get_pos() { return QPointF(pos_x,pos_y); }

    bool operator == (Tile const &t);

    void select() { selected_ = true; }
    void unselect() { selected_ = false; }


    //int get_first_available();// { return int(available_.size()); }

    //void highlight_selected() { shade_ = 100; }
    //void unhighlight() { shade_ = 0; }





signals:
    void tileClicked(Tile &);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


private:
    int pos_x;
    int pos_y;
    const int width_ = CELL;
    const int height_ = CELL;


    int digit_;
    int shade_;

    bool given_digit_;  // is the tile given at the start of the game
    bool selected_; // highlight if matched
    bool softshade_;


    std::vector<int> available_; // set of available digits



    QRadialGradient background_;

};


#endif // TILE_H



