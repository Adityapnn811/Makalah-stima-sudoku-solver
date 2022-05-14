#include "sudoku.hpp"
#include <iostream>
#include <fstream>

int main(){
    Sudoku s(4);
    int simpulExSearch = 0;
    int simpulBacktrack = 0;
    s.print();
    s.fillBoard("4_satu.txt");
    s.print();
    // cout << s.getSubmatrix(1, 1) << endl;
    // cout << s.getSubmatrix(1, 2) << endl;
    // cout << s.getSubmatrix(2, 2) << endl;
    // cout << s.checkSubMatrix(2, 3, 5) << endl;
    // if (s.solveBacktracking(&simpulBacktrack)){
    //     cout << simpulBacktrack << endl;
    //     s.print();
    // } else {
    //     cout << "Tidak bisa diselesaikan" << endl;
    // }
    if (s.solveExhaustiveSearch(&simpulExSearch)){
        cout << simpulExSearch << endl;
        s.print();
    } else {
        cout << "Tidak bisa diselesaikan" << endl;
    }


    return 0;
}

