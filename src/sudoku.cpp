#include "sudoku.hpp"
#include <fstream>
#include "math.h"
#include <algorithm>

// COnstructor
Sudoku::Sudoku(int n){
    this->n = n;
    this->subMatrices = n;
    this->board = vector<vector<int>>(n, vector<int>(n, 0));
    this->subMatrixFilled = vector<vector<bool>>(n, vector<bool>(n, false));
}

Sudoku::Sudoku(int n, vector<vector<int>> board){
    this->n = n;
    this->subMatrices = n;
    this->board = board;
    // Isi informasi subMatrixFilled, yaitu apakah angka 1 pada submatrix 1 sudah ada atau belum
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (board[i][j] != 0){
                this->subMatrixFilled[getSubmatrix(i, j)][board[i][j] - 1] = true;
            }
        }
    }
}


Sudoku::Sudoku(const Sudoku& sudoku){
    this->n = sudoku.n;
    this->subMatrices = sudoku.subMatrices;
    this->board = vector<vector<int>>(n, vector<int>(n, 0));
    this->subMatrixFilled = vector<vector<bool>>(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            this->board[i][j] = sudoku.board[i][j];
            if (board[i][j] != 0){
                this->subMatrixFilled[getSubmatrix(i, j)][board[i][j] - 1] = true;
            }
        }
    }
}

void Sudoku::print(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << board[i][j] << " ";
            if ((j + 1) % (int) sqrt(this->n) == 0){
                cout << "| ";
            }
        }
        cout << endl;
        if ((i + 1) % (int) sqrt(this->n) == 0){
            for (int k = 0; k < n + (n/3); k++){
                cout << "- ";
            }
            cout << endl;
        }
    }
}

void Sudoku::fillBoard(string filename){
    string line;
    ifstream file("test/" + filename);
    try {
        int i = 0;
        if (file.is_open()){
            while (getline(file, line)){
                for (int j = 0; j < n; j++){
                    board[i][j] = (int)((line[j]) - 48);
                    // Update informasi pada subMatrixFilled
                    if (board[i][j] != 0){
                        this->subMatrixFilled[getSubmatrix(i, j)][board[i][j] - 1] = true;
                    }
                }
                i++;
            }
        }
    } catch (exception *e){
        e->what();
    }
    file.close();
}

void Sudoku::set(int i, int j, int val){
    board[i][j] = val;
    // Update informasi pada subMatrixFilled
    if (val != 0){
        this->subMatrixFilled[getSubmatrix(i, j)][val - 1] = true;
    }
}

int Sudoku::get(int i, int j){
    return board[i][j];
}

// Mengembalikan submatrix dari i dan j
int Sudoku::getSubmatrix(int i, int j){
    // Cari maksimal antara i dan j
    // int maks = max(i, j);
    int barisSubMatrix = 0;
    int kolomSubMatrix = 0;
    barisSubMatrix = (i / (int) sqrt(this->n));
    kolomSubMatrix = (j / (int) sqrt(this->n)); // Nilai dari submatrix adalah 0 hingga n - 1
    return (barisSubMatrix) * sqrt(this->n) + kolomSubMatrix;
}

// SOLVER DAN HELPER
bool Sudoku::checkRow(int i, int j, int val){
    for (int k = 0; k < n; k++){
        if (board[i][k] == val && k != j){
            return false;
        }
    }
    return true;
}
bool Sudoku::checkCol(int i, int j, int val){
    for (int k = 0; k < n; k++){
        if (board[k][j] == val && k != i){
            return false;
        }
    }
    return true;
}

bool Sudoku::checkSubMatrix(int i, int j, int val){
    // return true jika pada submatrix tersebut belum ada nilai val-1
    int subMatrix = getSubmatrix(i, j);
    int modifierKolom = ((subMatrix) % (int) sqrt(n)) * sqrt(n);
    int modifierBaris = ((subMatrix) / (int) sqrt(n)) * sqrt(n);
    for (int k = modifierBaris; k < sqrt(this->n) + modifierBaris; k++){
        for (int l = modifierKolom; l < sqrt(this->n) + modifierKolom; l++){
            if (board[k][l] == val && (i != k || l != j)){
                return false;
            }
        }
    }
    return true;
    // return (this->subMatrixFilled[subMatrix][val - 1]);
}

bool Sudoku::isValid(int i, int j, int val){
    return checkRow(i, j, val) && checkCol(i, j, val) && checkSubMatrix(i, j, val);
}

bool Sudoku::isValidBacktrack(int i, int j, int val){
    return checkRow(i, j, val) && checkCol(i, j, val) && (this->subMatrixFilled[getSubmatrix(i, j)][val - 1] == false);
}

bool Sudoku::isThereEmptySpace(int &i, int &j){
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (board[i][j] == 0){
                return true;
            }
        }
    }
    return false;
}


bool Sudoku::solveBacktracking(int *simpulDibangkitkan){
    int i , j ;
    // Basis ketika sudah tidak ada yang kosong
    if (!this->isThereEmptySpace(i, j)){
        return true;
    } else {
        // Jika masih ada slot kosong, akan diisi dengan angka 1 sampai n
        for (int k = 1; k <= n; k++){
            // Cek apakah penempatan valid, jika iya, lakukan rekursi
            if (isValidBacktrack(i, j, k)){
                set(i, j, k);
                *simpulDibangkitkan += 1;
                if (solveBacktracking(simpulDibangkitkan)){
                    return true;
                } else {
                    // Kembalikan lagi ke 0 karena itu berarti tidak mengarah ke solusi
                    set(i, j, 0);
                    subMatrixFilled[getSubmatrix(i, j)][k - 1] = false;
                }
            }
        }
    }
    return false;
}

// Fungsi untuk mengecek apakah sudoku yang dihasilkan merupakan solusi
bool Sudoku::isSolution(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (!isValid(i, j, get(i, j))){
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::solveBruteForce(int *solusiDibangkitkan){
    // Basis adalah ketika sudah penuh semua, cek apakah dia solusi
    int i , j ;
    // Basis ketika sudah tidak ada yang kosong
    // this->print();
    if (!this->isThereEmptySpace(i, j)){
        *solusiDibangkitkan += 1;
        // cout << "Jumlah simpul yang dibangkitkan saat ini: " << *solusiDibangkitkan << endl;
        if (this->isSolution()) return true;
        else return false;
    } else {
        // Jika masih ada slot kosong, akan diisi dengan angka 1 sampai n
        for (int k = 1; k <= n; k++){
            // lakukan rekursi
            set(i, j, k);
            if (solveBruteForce(solusiDibangkitkan) ){
                return true;
            } else {
                // Kembalikan lagi ke 0 karena itu berarti tidak mengarah ke solusi
                set(i, j, 0);
                subMatrixFilled[getSubmatrix(i, j)][k - 1] = false;
            }
            
        }
    }
    return false;
}