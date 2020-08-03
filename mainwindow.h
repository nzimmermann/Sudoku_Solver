#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <vector>
#include <QGraphicsSimpleTextItem>
#include <unistd.h>
#include <sys/types.h>
#include <cmath>
#include <stdlib.h>

#include "tile.h"
#include "button.h"
//#include "game.h"

#define DIFFICULTIES 3





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int get_selected_digit() { return selected_digit_->get_id(); }
    void set_selected_digit(Pencil&);

    int get_difficulty() { return dif_lvl_; }
    void highlight_difficulty(Difficulty&);

    void SetBoard(int*);
    void activate_buttons();


    int Solver(Tile&, std::vector<Tile*>);

    bool verify_board();
    
    int** grid_attempt(int g[9][9]);



    bool check_row(int r, int d);   // check row r for digit d
    bool check_col(int c, int d);   // check col c for digit d
    bool check_block(int b, int d); // check block b 4 digit d
    

private slots:
    void tileClickedSlot(Tile&);
    void pencilButtonClickedSlot(Pencil&);
    void difficultyButtonClickedSlot(Difficulty&);


    void startButtonClickedSlot(Button&);
    void verifyButtonClickedSlot(Verify&);
    void hintButtonClickedSlot(Hint&);

    void autoCompleteClickedSlot(AutoComplete&);
    //Tile* tracking_step(Tile &);

    void update_available(Tile &);


private:
    QGraphicsScene * scene;
    Ui::MainWindow *ui;

    Tile *grid_[9][9];
    Pencil *options_[10];
    Pencil *selected_digit_;

    Difficulty *difficulty_[3];     // Easy, Med, Hard
    int dif_lvl_;                   // Last selected difficulty

    Button *start_button_;          // Starts the game

    Verify *verify_button_;
    Hint *hint_button_;
    AutoComplete *auto_button_;

    std::vector<Tile *> attempt_stack_;



    int clicked_num_ = 0;

    bool game_started_;




};
#endif // MAINWINDOW_H


/*

*/

