#include "board.h"


Board::Board(size_t _width, size_t _height) :
    width(_width),
    height(_height)
{
    board = new int*[width];
    for(size_t i=0; i<width; i++) {
        board[i] = new int[height];
        for(size_t j=0; j<height; j++) {
            board[i][j] = COLOR_NONE;
        }
    }
}

Board::Board(const Board &b) :
    width(b.width),
    height(b.height)
{
    board = new int*[width];
    for(size_t i=0; i<width; i++) {
        board[i] = new int[height];
        for(size_t j=0; j<height; j++) {
            board[i][j] = b.board[i][j];
        }
    }
}

Board::~Board()
{
    for(size_t i=0; i<width; i++) {
        delete[] board[i];
    }
    delete[] board;
}

Board& Board::operator=(const Board &b)
{
    if(this != &b) {
        for(size_t i=0; i<width; i++) {
            delete[] board[i];
        }
        delete[] board;

        width = b.width;
        height = b.height;

        board = new int*[width];
        for(size_t i=0; i<width; i++) {
            board[i] = new int[height];
            for(size_t j=0; j<height; j++) {
                board[i][j] = b.board[i][j];
            }
        }
    }
    return *this;
}



void Board::setSquare(size_t x, size_t y, int color)
{
    board[x][y] = color;
}

void Board::addForm(const Form &form, int x, int y, int color)
{
    for(size_t i=0; i<form.getsize(); i++) {
        if(0 <= x + form[i].x && x + form[i].x < width &&
           0 <= y + form[i].y && y + form[i].y < height) {
            board[x + form[i].x][y + form[i].y] = color;
        }
    }
}


bool Board::formCollide(const Form &form, int x, int y) const
{
    // test if the form is inside the board
    if(x + form.getboxmin().x < 0 || x + form.getboxmax().x >= width ||
       y + form.getboxmin().y < 0 || y + form.getboxmax().y >= height) {
        return true;
    }

    // we are certain the form is inside the board
    for(size_t i=0; i<form.getsize(); i++) {
        if(board[x + form[i].x][y + form[i].y]) {
            return true;
        }
    }

    return false;
}


void Board::clean(int &n_line, int &n_column)
{
    // first mark full lines / columns
    bool *lines = new bool[height];
    bool *columns = new bool[width];

    for(size_t y=0; y<height; y++) {
        bool full = true;
        for(size_t x=0; x<width && full; x++) {
            if( !board[x][y] ) full = false;
        }

        if(full) {
            lines[y] = true;
            n_line++;
        }
    }

    for(size_t x=0; x<width; x++) {
        bool full = true;
        for(size_t y=0; y<height && full; y++) {
            if( !board[x][y] ) full = false;
        }

        if(full) {
            columns[x] = true;
            n_column++;
        }
    }

    // the clean. we can't do both at once obviously as it would delete
    // squares before tests
    for(size_t y=0; y<height; y++) {
        if(lines[y]) {
            for(size_t x=0; x<width; x++) {
                board[x][y] = COLOR_NONE;
            }
        }
    }

    for(size_t x=0; x<width; x++) {
        if(columns[x]) {
            for(size_t y=0; y<height; y++) {
                board[x][y] = COLOR_NONE;
            }
        }
    }

    delete[] lines; delete[] columns;
}


const int* Board::operator[](size_t n) const {
    return board[n];
}

size_t Board::getwidth() const {
    return width;
}

size_t Board::getheight() const {
    return height;
}
