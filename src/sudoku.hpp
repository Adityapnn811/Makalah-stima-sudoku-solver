#ifndef _SUDOKU_HPP_
#define _SUDOKU_HPP_

#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Sudoku {
    private:
        int n;
        int subMatrices;
        vector<vector<int>> board;
    public:
        // Constructor sebuah matriks n x n, submatrix ditentukan dari n
        Sudoku(int n);
        Sudoku(int n, vector<vector<int>> board);
        Sudoku(const Sudoku& sudoku);
        // Melakukan print board
        void print();
        // Fill board dengant xt
        void fillBoard(string filename);
        // Mengganti value pada board[i][j][k] dengan val
        void set(int i, int j, int val);
        // Mengembalikan value pada board[i][j][k]
        int get(int i, int j);

        // Mengembalikan submatrix berdasarkan nilai i dan j
        int getSubmatrix(int i, int j);

        // UNTUK SOLVER DAN HELPERNYA
        bool checkRow(int i, int j, int val); // Return true apabila val tidak ada di row i
        bool checkCol(int i, int j, int val); // Return true apabila val tidak ada di col j
        bool checkSubMatrix(int i, int j, int val); // Return true apabila val tidak ada di submatrix
        bool isValid(int i, int j, int val); // Mengecek apakah val legal
        bool isThereEmptySpace(int &i, int &j); // Mengecek apakah masih ada 0 di papan sekaligus mengembalikan nilai i dan j tempat 0 berada
        bool isSolution(); // Untuk exhaustive search
        bool solveBacktracking(int *simpulDIbangkitkan);
        bool solveExhaustiveSearch(int *simpulDibangkitkan);
        // Mungkin bisa liat algoritma branch and bound, nanti fungsi boundnya adalah tinggal berapa yang kosong

};



#endif