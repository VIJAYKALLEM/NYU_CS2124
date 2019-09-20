/* 
 Simran Soin
 CS2124
 20 Sept 2019
 Minesweeper: Using Classes - encapsulation and data hiding
 */

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

const int BOMB_PROBABILITY = 10;
const int BOARD_SIZE_INCLUDING_BORDER = 12;

struct Tile{
    bool bomb;
    int num_adjacent_bombs;
    bool visible;
};

void createBoard(vector<vector<Tile>>& board);
int getNumAdjacentBombs(const vector<vector<Tile>>& board, size_t col_index, size_t row_index);
void fillInAdjacents(vector<vector<Tile>>& board);



class Minesweeper{
    friend void createBoard(vector<vector<Tile>>& board);
public:
    Minesweeper(){ createBoard(board);};
    
    void display(bool display_everything) const{
        for (size_t row_index=1; row_index <(board.size()-2); ++ row_index){
            for (size_t col_index = 1; col_index < (board[row_index].size()-2); ++col_index){
                if (display_everything || board[row_index][col_index].visible){
                    if (board[row_index][col_index].bomb){
                        cout << " B ";
                    }
                    else{
                        cout << " " << board[row_index][col_index].num_adjacent_bombs << " ";
                    }
                
                }
                else {
                    cout << " - ";
                }
            }
            cout << endl;
        }
    }
    
    bool done() const{
        for (size_t row_index=1; row_index < (board.size()-2); ++ row_index){
            for (size_t col_index = 1; col_index < (board[row_index].size()-2); ++col_index){
                if(!board[row_index][col_index].bomb && !board[row_index][col_index].visible){
                    return false;
                }
            }
        }
        return true;
    }
    
    bool validRow(size_t row_number) const{
        
        if(row_number >= 1 && row_number < (board.size()-2)){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool validCol(size_t col_number) const{
        
        if(col_number >= 1 && col_number < (board[1].size()-2)){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool isVisible(size_t row_number, size_t col_number) const{
        if (board[row_number][col_number].visible){
            return true;
        }
        else {
            return false;
        }
    }
    
    bool play(size_t row_number, size_t col_number){
        if (board[row_number][col_number].bomb){
            return false;
        }
        else if (board[row_number][col_number].num_adjacent_bombs > 0){
            board[row_number][col_number].visible = true;
        }
        else {
            vector<size_t> cols_to_make_visible = {col_number-1, col_number, col_number+1};
            vector<size_t> rows_to_make_visible = {row_number-1, row_number, row_number+1};
            for (size_t curr_col : cols_to_make_visible){
                for (size_t curr_row : rows_to_make_visible){
                    board[curr_row][curr_col].visible = true;
                }
            }
        }
        return true;
    }
    

private:
    vector<vector<Tile>> board;
};


int main() {
    srand(time(NULL));
    Minesweeper sweeper;
    // sweeper.display(true); // only for testing
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs
        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
}


int getNumAdjacentBombs(const vector<vector<Tile>>& board, size_t col_index, size_t row_index){
    int num_bombs_to_add = 0;
    vector<size_t> cols_to_check = {col_index-1, col_index, col_index+1};
    vector<size_t> rows_to_check = {row_index-1, row_index, row_index+1};
    for (size_t curr_col : cols_to_check){
        for (size_t curr_row : rows_to_check){
            if(board[curr_row][curr_col].bomb){
                ++num_bombs_to_add;
            }
        }
    }
    return num_bombs_to_add;
}


void fillInAdjacents(vector<vector<Tile>>& board){
    for (size_t row_index = 1; row_index < board.size() - 2; ++row_index){
        // start from 1 and end 1 early to account for borders
        vector<Tile>& curr_row = board[row_index];
        for (size_t col_index = 1; col_index < board[row_index].size() - 2; ++col_index){
            // start from 1 and end 1 early to account for borders
            Tile& curr_tile = curr_row[col_index];
            if (!curr_tile.bomb){
                curr_tile.num_adjacent_bombs += getNumAdjacentBombs(board, col_index, row_index);
                
            }
        }
    }
}


void createBoard(vector<vector<Tile>>& board){
    Tile empty_border_block{false, 0, false};
    for (int curr_row = 0; curr_row <= BOARD_SIZE_INCLUDING_BORDER; ++curr_row){
        vector<Tile> row;
        for (int curr_val_in_row = 0; curr_val_in_row<=BOARD_SIZE_INCLUDING_BORDER; ++curr_val_in_row){
            // if it is the first row, the last row, the first column, or last column: should be empty tile
            if (curr_row == 0 || curr_row == BOARD_SIZE_INCLUDING_BORDER || curr_val_in_row == 0 || curr_val_in_row == BOARD_SIZE_INCLUDING_BORDER){
                row.push_back(empty_border_block);
            }
            else{
                if (rand()%100 < BOMB_PROBABILITY){
                    Tile bomb{true, 0, false};
                    row.push_back(bomb);
                }
                else{
                    Tile curr_tile{false, 0, false};
                    row.push_back(curr_tile);
                }
            }
        }
        board.push_back(row);
    }
    fillInAdjacents(board);
}
