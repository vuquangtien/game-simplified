#include<bits/stdc++.h>

using namespace std ;

#define st first
#define nd second

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

int Rand(int l, int h) {
    assert(l <= h);
    return l + rd() % (h - l + 1);
}

int board[4][4] ;
int dir[4][2] = {1 , 0 , 0 , -1 , 0 , 1 , -1 , 0} ;
bool used[4][4] ;
int canMoveAll ;
int yourScore = 0 ; 
pair<string , int> highScore[5] ;

char toChar(int x) {
    return x + '0' ;
}

void startGame() {
    int i = Rand(0 , 3) , j = Rand(0 , 3) ;
    board[i][j] = 2 ;
}

void genNewNum() {
    while(true) {
        int i = Rand(0 , 3) , j = Rand(0 , 3) ;
        if (board[i][j] == 0) {
            int _2_or_4_ = Rand(1 , 10) ;
            board[i][j] = _2_or_4_ == 1 ? 4 : 2 ;
            return ;
        }
    }
}

void printUI() {
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            if (board[i][j] == 0) cout << "-   " ;
            else cout << board[i][j] << (board[i][j] < 10 ? "   " : (board[i][j] < 100 ? "  " : (board[i][j] < 1000 ? " " : ""))) ;
        }
        cout << '\n' ;
    }
    cout << "------------------------\n" ;
}

bool valid(int x , int y) {
    return x >= 0 && x < 4 && y >= 0 && y < 4 ;
}

void genMove(int move) {
    canMoveAll = 0 ;
    while(true) {
        bool canMove = 0 ;
        int x = dir[move][0] , y = dir[move][1] ;
        if (move == 1 || move == 3) {
            for (int i = 0 ; i < 4 ; i++) {
                for (int j = 0 ; j < 4 ; j++) {
                    if (!valid(i + x , j + y)) continue ;
                    if (board[i + x][j + y] == 0 && board[i][j] != 0) {
                        board[i + x][j + y] = board[i][j] ;
                        board[i][j] = 0 ;
                        if (used[i][j] == 1) {
                            used[i + x][j + y] = 1 ;
                            used[i][j] = 0 ;
                        }
                        canMove = 1 ;
                    }
                    if (board[i + x][j + y] == board[i][j] && board[i][j] != 0 && !used[i][j] && !used[i + x][j + y]) {
                        board[i + x][j + y] = 2 * board[i][j] ;
                        board[i][j] = 0 ;
                        used[i + x][j + y] = 1 ;
                        canMove = 1 ;
                    }
                }
            }
        }
        else {
            for (int i = 3 ; i >= 0 ; i--) {
                for (int j = 3 ; j >= 0 ; j--) {
                    if (!valid(i + x , j + y)) continue ;
                    if (board[i + x][j + y] == 0 && board[i][j] != 0) {
                        board[i + x][j + y] = board[i][j] ;
                        board[i][j] = 0 ;
                        if (used[i][j] == 1) {
                            used[i + x][j + y] = 1 ;
                            used[i][j] = 0 ;
                        }
                        canMove = 1 ;
                    }
                    if (board[i + x][j + y] == board[i][j] && board[i][j] != 0 && !used[i][j] && !used[i + x][j + y]) {
                        board[i + x][j + y] = 2 * board[i][j] ;
                        board[i][j] = 0 ;
                        used[i + x][j + y] = 1 ;
                        canMove = 1 ;
                    }
                }
            }
        }
        canMoveAll |= canMove ;
        if (!canMove) break ;
    }
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            used[i][j] = 0 ;
        }
    }
}

int whichMove(char direction) {
    if (direction == 's') return 0 ;
    if (direction == 'a') return 1 ;
    if (direction == 'd') return 2 ;
    if (direction == 'w') return 3 ;
    if (direction == 'r') return 4 ;
    if (direction == 'q') return 5 ;
    return -1 ;
}

bool checkLose() {
    yourScore = 0 ;
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            if ((board[i][j] == board[i + 1][j] && valid(i + 1 , j)) || (board[i][j] == board[i][j + 1] && valid(i , j + 1)) || board[i][j] == 0) return false ;
            yourScore += board[i][j] ;
        }
    }
    cout << "Haha you lose\n" ;
    cout << "Your score is : " << yourScore << '\n' ;
    return true ;
}

void resetGame() {
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            board[i][j] = 0 ;
        }
    }
    startGame() ;
}

void quitGame() {
    exit(0) ;
}

void updateHighScore(pair<string , int> player) {
    pair<string , int> gettingDown ;
    bool used = 0 ;
    for (int i = 0 ; i < 5 ; i++) {
        if (player.nd > highScore[i].nd && used == 0) {
            gettingDown = highScore[i] ;
            highScore[i] = player ;
            used = 1 ;
            continue ;
        }
        if (used == 1) {
            swap(highScore[i] , gettingDown) ;
        }
    }
}

void showHighScore() {
    for (int i = 0 ; i < 5 ; i++) {
        cout << highScore[i].st << ' ' << highScore[i].nd << '\n' ;
    }
}

int main() {
    srand(time(NULL));
    startGame() ;
    while(true) {
        printUI() ;
        if (checkLose()) {
            resetGame() ;
            cout << "This is the highscore board : \n" ;
            showHighScore() ;
            if (yourScore > highScore[4].nd) {
                cout << "Congrats on being on highscore board , please write your name : " ;
                string name ; cin >> name ;
                updateHighScore({name , yourScore}) ;
                cout << "Now this is the new highscore board : \n" ;
                showHighScore() ;
            }
            continue ;
        }
        cout << "Choose : w = up , a = left , s = down , d = right , r = reset , q = quit " ;
        char command ; cin >> command ;
        int move = whichMove(command) ;
        if (move == -1) {
            cout << '\n' ;
            continue ;
        }
        if (move == 4) {
            resetGame() ;
            continue ;
        }
        if (move == 5) {
            quitGame() ;
            continue ;
        }
        genMove(move) ;
        if (canMoveAll) genNewNum() ;
    }
    return 0 ;
}