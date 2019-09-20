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
    friend void fillInAdjacents(vector<vector<Tile>>& board);
public:
    Minesweeper(){
        // creates initial board
        Tile border_block{false, -1, false};
        for (int curr_row = 0; curr_row < BOARD_SIZE_INCLUDING_BORDER; ++curr_row){
            vector<Tile> row;
            for (int curr_val_in_row = 0; curr_val_in_row<BOARD_SIZE_INCLUDING_BORDER;
                 ++curr_val_in_row){
                // if it is the first row, last row, first column, or last column: empty tile
                if (curr_row == 0 || curr_row == BOARD_SIZE_INCLUDING_BORDER-1 ||
                    curr_val_in_row == 0 || curr_val_in_row == BOARD_SIZE_INCLUDING_BORDER-1){
                    row.push_back(border_block);
                }
                else{
                    // randomly assigns bomb
                    if (rand()%100 < BOMB_PROBABILITY){
                        Tile bomb{true, 0, false};
                        row.push_back(bomb);
                    }
                    else{
                        // if not a bomb, sets default empty tiles
                        Tile curr_tile{false, 0, false};
                        row.push_back(curr_tile);
                    }
                }
            }
            board.push_back(row);
        }
        // fills in all the default empty tiles with the number of adjacent bombs
        fillInAdjacents(board);
    };
    
    void display(bool display_everything) const{
        for (size_t row_index=1; row_index <(board.size()-1); ++ row_index){
            for (size_t col_index = 1; col_index < (board[row_index].size()-1); ++col_index){
                if (display_everything && board[row_index][col_index].bomb){
                    // if the game is lost, display all the bombs
                    cout << " B ";
                }
                else if (board[row_index][col_index].visible){
                    // if the tile is visible, display it
                        cout << " " << board[row_index][col_index].num_adjacent_bombs << " ";
                }
                // if the game isnt lost AND the tile isnt visible, put a placeholder '-'.
                else {cout << " - ";}
            }
            //end of each row ends line
            cout << endl;
        }
    }
    
    bool done() const{
        for (size_t row_index=1; row_index < (board.size()-1); ++ row_index){
            for (size_t col_index = 1; col_index < (board[row_index].size()-1); ++col_index){
                if(!board[row_index][col_index].bomb && !board[row_index][col_index].visible){
                    // if a non-bomb tile is not visible, the game is not done
                    return false;
                }
            }
        }
        // if we iterate through everything without returning false, then the game is done
        return true;
    }
    
    bool validRow(size_t row_number) const{
        // returns true if row is within the border limits
        return (row_number >= 1 && row_number < (board.size()-1));
    }
    
    bool validCol(size_t col_number) const{
        // returns true if col is within the border limits
        return (col_number >= 1 && col_number < (board[1].size()-1));
    }
    
    bool isVisible(size_t row_number, size_t col_number) const{
        return board[row_number][col_number].visible;
    }
    
    bool play(size_t row_number, size_t col_number){
        if (board[row_number][col_number].bomb){
            // if the selected tile is a bomb, return false
            return false;
        }
        else if (board[row_number][col_number].num_adjacent_bombs > 0){
            // if the selected tile has a nonzero # of adjacent bombs
                    // only make that tile visible
            board[row_number][col_number].visible = true;
        }
        else {
            // if we are here, the # of adjacent bombs < 0
            // 1) check that the tile isnt a border tile (num_adjacent_bombs = -1)
            // 2) check that the tile isnt already visible
            // 3) iterate through all of the adjacent tiles
                    // a. if it is the original tile --> make visible
                    // b. if it is an adjacent tile --> recursively play(tile)
            if (board[row_number][col_number].num_adjacent_bombs != -1
                && !isVisible(row_number, col_number)){
                vector<size_t> cols_to_play = {col_number-1, col_number, col_number+1};
                vector<size_t> rows_to_play = {row_number-1, row_number, row_number+1};
                for (size_t curr_row : rows_to_play){
                    for (size_t curr_col : cols_to_play){
                        if (curr_row == row_number && curr_col == col_number){
                            board[curr_row][curr_col].visible = true;
                        }
                        else {
                            play(curr_row, curr_col);
                        }
                    }
                }
            }
        }
        // if num_adjacent tiles <= 0, we reach here and return true
        // (we return true because it is not a bomb, so we successfully played the tile)
        return true;
    }
    

private:
    vector<vector<Tile>> board;
};


int main() {
    //seed the random number sequence
    srand(time(NULL));
    Minesweeper sweeper;
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


int getNumAdjacentBombs(const vector<vector<Tile>>& board,
                        size_t col_index, size_t row_index){
    // checks every adjacent cell and returns the total number of adjacent bombs
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
    // calls getNumAdjacentBombs on every non-bomb tile in the row
    // sets the tile.num_adjacent_bombs to getNumAdjacentBombs
    for (size_t row_index = 1; row_index < board.size() - 1; ++row_index){
        // start from 1 and end 1 early to account for borders
        vector<Tile>& curr_row = board[row_index];
        for (size_t col_index = 1; col_index < board[row_index].size() - 1;
             ++col_index){
            // start from 1 and end 1 early to account for borders
            Tile& curr_tile = curr_row[col_index];
            if (!curr_tile.bomb){
                curr_tile.num_adjacent_bombs +=
                getNumAdjacentBombs(board, col_index, row_index);
                
            }
        }
    }
}
