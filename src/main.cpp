#include "sudoku.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    Sudoku s(4);
    int simpulExSearch = 0;
    int simpulBacktrack = 0;
    s.print();
    s.fillBoard("4_dua.txt");
    s.print();
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    // cout << s.getSubmatrix(1, 1) << endl;
    // cout << s.getSubmatrix(1, 2) << endl;
    // cout << s.get(2, 4) << endl;
    cout << s.checkSubMatrix(0, 1, 4) << endl;
    // if (s.solveBacktracking(&simpulBacktrack)){
    //     chrono::steady_clock::time_point end = chrono::steady_clock::now();
    //     cout << simpulBacktrack << endl;
    //     s.print();
    //     cout << "Waktu yang dibutuhkan: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ns" << endl;
    // } else {
    //     chrono::steady_clock::time_point end = chrono::steady_clock::now();
    //     cout << "Tidak bisa diselesaikan" << endl;
    //     cout << "Waktu yang dibutuhkan: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ns" << endl;
    // }
    if (s.solveBruteForce(&simpulExSearch)){
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << simpulExSearch << endl;
        s.print();
        cout << "Waktu yang dibutuhkan: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ns" << endl;
    } else {
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        cout << "Tidak bisa diselesaikan" << endl;
        cout << simpulExSearch << endl;
        cout << "Waktu yang dibutuhkan: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ns" << endl;
    }


    return 0;
}

