#include <iostream>
char board[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
int gameMoves = {0};

void print_board(){

    for (int i=0;i<9;i++){
        std::cout << board[i] << '\t';
        if (i == 2 || i == 5 || i ==8){
            std::cout << '\n';
        }
    }
}

bool valid_move(int move){
    if (move < 0 || move > 8){
        std::cout << "Outside of bounds!\n";
        return false;
    }else {
        if (board[move] == 'X' || board[move] == 'O'){
            std::cout << "Already taken!\n";
            std::cout << move;
            return false;
        }else {
            return true;
        }
    }
}

int player_input(){
    while (true){
        std::cout << "Choose your square: \n";
        int playerMove {};
        std::cin >> playerMove;

        if (valid_move(playerMove)){
            gameMoves += 1;
            return playerMove;
        }
    }

}


int check_win() {
    if ((board[0] == board[1]) && (board[0] == board[2])){
        if (board[0] == 'X'){
            return 1;
        }else {
            return 2;
        }
    }else if ((board[3] == board[4]) && (board[3] == board[5])){
        if (board[0] == 'X'){
            return 1;
        }else {
            return 2;
        }

    }else if ((board[6] == board[7]) && (board[6] == board[8])){
        if (board[0] == 'X'){
            return 1;
        }else {
            return 2;
        }

    }else if ((board[0] == board[3]) && (board[0] == board[6])){
        if (board[0] == 'X'){
            return 1;
        }else {
            return 2;
        }

    }else if ((board[1] == board[4]) && (board[1] == board[7])){
        if (board[0] == 'X'){
            return 1;
        }else {
            return 2;
        }

    }else if ((board[2] == board[5]) && (board[2] == board[8])){
        if (board[0] == 'X'){
            return 1;
        }else {
            return 2;
        }

    }else if ((board[0] == board[4]) && (board[0] == board[8])){
        if (board[0] == 'X'){
            return 1;
        }else {
            return 2;
        }

    }else if ((board[2] == board[4]) && (board[2] == board[6])){
        if (board[2] == 'X'){
            return 1;
        }else {
            return 2;
        }

    }else {
        return 0;
    }   
}

void update_board(int player, int space){
    if (player == 1){
        board[space] = 'X';
    }else {
        board[space] = 'O';
    }

}

void welcome_screen(){
    std::cout << "Welcome!\n" << "Please choose a square to play using the corresponding numbers.\n";
    print_board();
}

int main() {
    welcome_screen();

    while (true){
    
        int playerMove = player_input();

        if (gameMoves % 2 == 1){
            update_board(1, playerMove);
        }else {
            update_board(2, playerMove);
        }
        
        print_board();

        
        int result = check_win();

        if (result == 1){
            std::cout << "Congrats Player 1!\n";
            break;
        }else if (result == 2){
            std::cout << "Congrats Player 2!\n";
            break;
        }else if (gameMoves == 9){
            std::cout << "DRAW!\n";
            break;
        }
        
    }

    return 0;

}