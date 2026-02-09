#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

char board[3][3];
string lastWinner = "None";

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void initializeBoard() {
    char ch = '1';
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j] = ch++;
}

void displayBoard() {
    setColor(11);
    cout << "\n";
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            cout << " " << board[i][j] << " ";
            if(j<2) cout << "|";
        }
        if(i<2) cout << "\n---|---|---\n";
    }
    cout << "\n";
    setColor(7);
}

bool checkWin(char mark) {
    for(int i=0;i<3;i++) {
        if(board[i][0]==mark && board[i][1]==mark && board[i][2]==mark) return true;
        if(board[0][i]==mark && board[1][i]==mark && board[2][i]==mark) return true;
    }
    if(board[0][0]==mark && board[1][1]==mark && board[2][2]==mark) return true;
    if(board[0][2]==mark && board[1][1]==mark && board[2][0]==mark) return true;
    return false;
}

bool isFull() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]>='1' && board[i][j]<='9')
                return false;
    return true;
}

char generateSecondMark(char firstMark) {
    for(char c='A'; c<='Z'; c++)
        if(c != firstMark) return c;
    return 'Z';
}

int getValidPosition() {
    int choice;

    while(true) {
        cin >> choice;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000,'\n');
            setColor(12);
            cout << "Invalid input! Enter a number between 1-9: ";
            setColor(7);
            continue;
        }

        if(choice < 1 || choice > 9) {
            setColor(12);
            cout << "Out of range! Choose between 1-9: ";
            setColor(7);
            continue;
        }

        int row = (choice-1)/3;
        int col = (choice-1)%3;

        if(!(board[row][col]>='1' && board[row][col]<='9')) {
            setColor(12);
            cout << "Position already taken! Choose again: ";
            setColor(7);
            continue;
        }

        return choice;
    }
}

void computerMove(char mark) {
    int r,c;
    do {
        r = rand()%3;
        c = rand()%3;
    } while(!(board[r][c]>='1' && board[r][c]<='9'));

    board[r][c] = mark;
    cout << "Computer played!\n";
}

void playGame() {

    int mode;

    while(true) {
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "Choose mode (1 or 2): ";
        cin >> mode;

        if(cin.fail() || (mode!=1 && mode!=2)) {
            cin.clear();
            cin.ignore(1000,'\n');
            setColor(12);
            cout << "Invalid choice! Please enter 1 or 2.\n";
            setColor(7);
        } else break;
    }

    string player1, player2;
    cout << "Enter Player 1 Name: ";
    cin >> player1;

    char mark1 = toupper(player1[0]);
    char mark2;

    if(mode==1) {
        cout << "Enter Player 2 Name: ";
        cin >> player2;
        mark2 = toupper(player2[0]);

        if(mark1==mark2) {
            mark2 = generateSecondMark(mark1);
            cout << "Same letter detected! New mark for " 
                 << player2 << " is " << mark2 << "\n";
        }
    } else {
        player2="Computer";
        mark2=generateSecondMark(mark1);
    }

    initializeBoard();
    displayBoard();

    string currentPlayer=player1;
    char currentMark=mark1;

    while(true) {

        if(mode==2 && currentPlayer=="Computer") {
            computerMove(currentMark);
        } else {
            cout << currentPlayer << " (" << currentMark 
                 << ") choose position (1-9): ";
            int choice = getValidPosition();
            int row=(choice-1)/3;
            int col=(choice-1)%3;
            board[row][col]=currentMark;
        }

        displayBoard();

        if(checkWin(currentMark)) {
            setColor(10);
            cout << "\n WINNER: " << currentPlayer << " \n";
            setColor(11);
            cout << "Previous Winner was: " << lastWinner << "\n";
            setColor(7);
            lastWinner=currentPlayer;
            break;
        }

        if(isFull()) {
            setColor(14);
            cout << "\nGame Draw! Restarting...\n";
            setColor(7);
            break;
        }

        if(currentPlayer==player1) {
            currentPlayer=player2;
            currentMark=mark2;
        } else {
            currentPlayer=player1;
            currentMark=mark1;
        }
    }
}

int main() {

    srand(time(0));

    setColor(14);
    cout << "====== LETTER MATCHING GAME ======\n";
    setColor(10);
    cout << "Previous Winner: " << lastWinner << "\n\n";
    setColor(7);

    while(true) {
        playGame();

        char again;
        cout << "\nDo you want to play again? (y/n): ";
        cin >> again;

        if(tolower(again) != 'y') {
            cout << "Thanks for playing!\n";
            break;
        }
    }

    return 0;
}
