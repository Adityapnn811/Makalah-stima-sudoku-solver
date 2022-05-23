#include "sudoku.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    int simpulExSearch = 0;
    int simpulBacktrack = 0;
    // s.print();
    int sudokuSize, pilihanAlgo;
    string fileName;
    cout << "Masukkan ukuran sudoku: ";
    cin >> sudokuSize;
    if (sudokuSize != 9 && sudokuSize != 4){
        cout << "Ukuran sudoku harus 9 atau 4" << endl;
        return 0;
    }
    Sudoku s(sudokuSize);
    cout << "Masukkan pilihan sudoku: ";
    cin >> fileName;
    s.fillBoard(fileName + ".txt");
    s.print();
    // cout << s.getSubmatrix(1, 1) << endl;
    // cout << s.getSubmatrix(1, 2) << endl;
    // cout << s.get(2, 4) << endl;
    // cout << s.checkSubMatrix(0, 1, 4) << endl;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cout << "Masukkan pilihan algo:\n 1. Backtracking\n 2. Brute force\n";
    cin >> pilihanAlgo;
    if (pilihanAlgo == 1){
        cout << "Penyelesaian menggunakan algoritma backtracking" << endl;
        if (s.solveBacktracking(&simpulBacktrack)){
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Jumlah simpul yang dibangkitkan: " << simpulBacktrack << endl;
            s.print();
            cout << "Waktu yang dibutuhkan: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
        } else {
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Tidak bisa diselesaikan" << endl;
            cout << "Waktu yang dibutuhkan: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
        }
    } else if (pilihanAlgo == 2){
        cout << "Penyelesaian menggunakan algoritma brute force" << endl;
        if (s.solveBruteForce(&simpulExSearch)){
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Jumlah simpul yang dibangkitkan: " << simpulExSearch << endl;
            s.print();
            cout << "Waktu yang dibutuhkan: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
        } else {
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Tidak bisa diselesaikan" << endl;
            cout << "Jumlah simpul yang dibangkitkan: " << simpulExSearch << endl;
            cout << "Waktu yang dibutuhkan: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
        }
    }


    return 0;
}

