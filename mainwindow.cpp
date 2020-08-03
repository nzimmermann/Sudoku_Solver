#include "mainwindow.h"
#include "ui_mainwindow.h"


int easy[81] = {
    0, 0, 0,  9, 5, 0,  6, 0, 0,
    0, 5, 0,  0, 0, 4,  3, 0, 2,
    0, 6, 7,  0, 0, 1,  0, 0, 4,

    0, 1, 6,  2, 0, 8,  0, 7, 3,
    0, 2, 4,  0, 0, 0,  8, 5, 0,
    3, 9, 0,  7, 0, 5,  2, 6, 0,

    8, 0, 0,  5, 0, 0,  1, 4, 0,
    9, 0, 1,  8, 0, 0,  0, 3, 0,
    0, 0, 5,  0, 1, 7,  0, 0, 0
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsView * view = ui->graphicsView;

    scene = new QGraphicsScene;

    view->setScene(scene);
    view->setSceneRect(0,0,view->frameSize().width(), view->frameSize().height());

    dif_lvl_ = 0;
    //
    // Set up individual tiles
    //




    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            grid_[row][col] = new Tile(row*CELL + INDENT , col*CELL + INDENT, 0);
            scene->addItem(grid_[row][col]);
            connect(grid_[row][col], &Tile::tileClicked, this, &MainWindow::tileClickedSlot);
        }
    }




     QPen p;

    //
    // Draw bolder Lines for border and blocks
    //

    p.setWidth(5);
    scene->addLine(INDENT,INDENT,INDENT+CELL*9,INDENT, p);
    scene->addLine(INDENT,INDENT, INDENT, INDENT+CELL*9, p);
    scene->addLine(INDENT+CELL*9,INDENT,INDENT+CELL*9,INDENT+CELL*9, p);
    scene->addLine(INDENT,INDENT+CELL*9,INDENT+CELL*9,INDENT+CELL*9, p);

    p.setWidth(3);
    scene->addLine(INDENT + CELL*3, INDENT, INDENT+CELL*3, INDENT+CELL*9, p);
    scene->addLine(INDENT + CELL*6, INDENT, INDENT+CELL*6, INDENT+CELL*9, p);
    scene->addLine(INDENT, INDENT + CELL*3, INDENT+CELL*9, INDENT+CELL*3, p);
    scene->addLine(INDENT, INDENT + CELL*6, INDENT+CELL*9, INDENT+CELL*6, p);


    //
    // Draw Buttons
    //


    int button_pos[10][2] = {
        {450,50},  {500,50},  {550,50},       // 1 2 3
        {450,100}, {500,100}, {550,100},      // 4 5 6
        {450,150}, {500,150}, {550,150},      // 7 8 9
        {470,200} };                          // Erase


    for(int i = 0; i < 9; i++){
        options_[i] = new Pencil(button_pos[i][0], button_pos[i][1], 40, 40, i+1);
        scene->addItem(options_[i]);
        connect(options_[i], &Pencil::pencilButtonClicked, this, &MainWindow::pencilButtonClickedSlot);
    }
    options_[9] = new Pencil(button_pos[9][0], button_pos[9][1], 100, 40, 0);
    scene->addItem(options_[9]);
    connect(options_[9], &Pencil::pencilButtonClicked, this, &MainWindow::pencilButtonClickedSlot);

    selected_digit_ = options_[9];    clicked_num_ = 0;



    // Dificulty Buttons
    QString dif_str[3]     = { QString(  "Easy"  ),QString(   "Med"    ),QString(     "Hard"      ) };
    QPoint  dif_pos[3]     = {  QPoint( 420, 270 ), QPoint(  490, 270  ), QPoint(    560, 270     ) };
    //QSize   dif_size[3]    = {   QSize(  60,  40 ),  QSize(   60,  40  ),  QSize(     60,  40     ) };

    // Solver Buttons
    //QString solver_str[3]  = { QString( "Verify" ),QString( "Get Hint" ),QString( "Auto-Complete" ) };
    //QPoint  solver_pos[3]  = {  QPoint( 300, 425 ), QPoint(  500, 425  ), QPoint(     50, 425     ) };
    //QSize   solver_size[3] = {   QSize(  90,  40 ),  QSize(   90,  40  ),  QSize(    150,  40     ) };


    for(int i=0;i<3;i++){
        difficulty_[i] = new Difficulty(dif_pos[i], dif_str[i], i+1);
        scene->addItem(difficulty_[i]);
        connect(difficulty_[i], &Difficulty::difficultyButtonClicked, this, &MainWindow::difficultyButtonClickedSlot);
    }
        //solver_[i] = new Button(solver_pos[i], solver_size[i], solver_str[i], false);
        //scene->addItem(solver_[i]);
        //connect(solver_[i], &, this, &MainWindow::);



    //
    // New_Game / Reset button
    //

    start_button_ = new Button(QPoint(445,320), QSize(160, 40), QString("Start New Game"), false);
    scene->addItem(start_button_);
    connect(start_button_, &Button::startButtonClicked, this, &MainWindow::startButtonClickedSlot);


    auto_button_ = new AutoComplete(QPoint(50,425), QSize(150,40)); //, QString("Auto-Complete"), false);
    scene->addItem(auto_button_);
    connect(auto_button_, &AutoComplete::autoButtonClicked, this, &MainWindow::autoCompleteClickedSlot);


    // Verify

    verify_button_ = new Verify(QPoint(300,425), QSize(90,40));
    scene->addItem(verify_button_);
    connect(verify_button_, &Verify::verifyButtonClicked, this, &MainWindow::verifyButtonClickedSlot);

    hint_button_ = new Hint(QPoint(500,425), QSize(90,40));
    scene->addItem(hint_button_);
    connect(hint_button_, &Hint::hintButtonClicked, this, &MainWindow::hintButtonClickedSlot);


}


void MainWindow::SetBoard(int *arr){
    int j = 0;
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            grid_[row][col]->changeDigit(arr[j]);
            if(arr[j] != 0){
                grid_[row][col]->set_given();
            }
            grid_[row][col]->update();
            j++;
        }
    }
}


void MainWindow::activate_buttons(){
    for(int i = 0; i < 10; i++){
        options_[i]->set_active();
    }
    for(int i = 0; i < 3; i++){
        difficulty_[i]->set_active();
    }
    start_button_->set_active();
    verify_button_->set_active();
    hint_button_->set_active();
    auto_button_->set_active();
}


void MainWindow::startButtonClickedSlot(Button& b){
    //qDebug() << "startButtonClickedSlot called" << endl;
    game_started_ = true;
    SetBoard(easy);
    activate_buttons();
    update();
}


void MainWindow::tileClickedSlot(Tile& t){
    t.changeDigit(get_selected_digit());
    //t.select();
    qDebug() << "Tile clicked " << endl;
}


void MainWindow::pencilButtonClickedSlot(Pencil& p){
    selected_digit_ = &p;
    for(int i=0; i<10; i++){
        options_[i]->unhighlight();
    }
    selected_digit_->highlight();
}



void MainWindow::difficultyButtonClickedSlot(Difficulty& d){
    dif_lvl_ = d.get_lvl();
    start_button_->set_active();
    //start_button_->update();
    for(int i = 0; i < 3; i++){
        difficulty_[i]->unhighlight();
    }
    d.highlight();
    update();
}


void MainWindow::autoCompleteClickedSlot(AutoComplete& a){
    qDebug() << "Auto-Complete button clicked slot " << endl;

    attempt_stack_.clear();


    for(int r = 0; r < 9; r++){
        for(int c = 0; c < 9; c++){
            if(!grid_[r][c]->is_given()){

                attempt_stack_.push_back(grid_[r][c]);

            }
        }
    }

    qDebug() << "There are" << attempt_stack_.size() << "tiles yet to be solved" << endl;



    Tile& t = *attempt_stack_.front();
    attempt_stack_.erase(attempt_stack_.begin());

    qDebug() << "There are now" << attempt_stack_.size() << "tiles yet to be solved" << endl;
    qDebug() << "The separated tile has digit" << t.get_digit() << endl;


    Solver(t, attempt_stack_);

}

// This Works v
// rest.assign( Rest.begin()+1, Rest.end() );
// Solver(*Rest.front(), rest );

int MainWindow::Solver(Tile& T, std::vector<Tile*> Rest){

    qDebug() << "Rest size is" << Rest.size() << endl;

    /*
    if(Rest.size() == 0){
        T.changeDigit(1);
        return 1;
    }else{
        std::vector<Tile*> rest;
        rest.assign( Rest.begin()+1, Rest.end() );
        T.changeDigit(1 + Solver(*Rest.front(), rest) );
        return T.get_digit();
    }
    */


    if(Rest.size() == 0){
        for(int d = 1; d <= 9; d++){
            T.changeDigit(d);
            if(verify_board()){
                return 1;
            }
        }
        return 0;
    }else{
        std::vector<Tile*> rest;
        rest.assign( Rest.begin()+1, Rest.end() );

        for(int d = 1; d <= 9; d++){
            T.changeDigit(d);
            if(verify_board()){
                if(Solver(*Rest.front(), rest) == 1){
                    return 1;
                }
            }
            T.changeDigit(0);
        }
        return 0;

    }

    //std::vector<Tile*> rest;
    //rest.assign( Rest.begin()+1, Rest.end() );
    //Solver(*Rest.front(), rest );





}





void MainWindow::update_available(Tile& t){
    // check row

    // check column

    // check block
}





/*
int** MainWindow::grid_attempt(int g[9][9]){
    
}*/




void MainWindow::verifyButtonClickedSlot(Verify&){
    // qDebug() << "Verify Button Slot " << endl;

    verify_board();

}


bool MainWindow::verify_board(){

    bool verify = true;

    for(int r = 0; r < 9; r++){
        for(int c = 0; c < 9; c++){

            int d = grid_[r][c]->get_digit();
            int b = int(floor(r/3) * 3 + floor(c/3));

            if( !grid_[r][c]->is_given() && (d != 0) ){ // so long as the tile is not given or zero

                qDebug() << "Checking tile" << r << "," << c << "=" << grid_[r][c]->get_digit() << endl;

                verify = verify && check_row(r,d) && check_col(c,d) && check_block(b,d);

            } // end if statement

        }
    }

    if(verify){
        qDebug() << "The puzzle is valid!" << endl;
    }
    else{
        qDebug() << "The puzzle is not valid" << endl;
    }

    return verify;

}


bool MainWindow::check_row(int r, int d){
    int t = 0;
    for(int i = 0; i < 9; i++){
        if(d == grid_[r][i]->get_digit()){
            t++;
        }
    }
    if(t > 1){
        return false;
    }
    return true;
}

bool MainWindow::check_col(int c, int d){
    int t = 0;
    for(int i = 0; i < 9; i++){
        if(d == grid_[i][c]->get_digit()){
            t++;
        }
    }
    if(t > 1){
        return false;
    }
    return true;
}

bool MainWindow::check_block(int b, int d){
    int r = int(floor(b/3)*3);
    int c = int( (b%3) * 3 );

    int t = 0;
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            if(d == grid_[r+x][c+y]->get_digit()){
                t++;
            }
        }
    }

    if(t > 1){
        return false;
    }
    return true;
}


void MainWindow::hintButtonClickedSlot(Hint&){
    qDebug() << "Hint Button Slot " << endl;
}


MainWindow::~MainWindow()
{
    delete ui;
}

