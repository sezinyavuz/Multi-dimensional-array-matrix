#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>



using namespace std;


//function for multiplication
int multiplication(int **mapmatrix, int **keymatrix, int rowkey, int *x , int *y) {

    int result = 0;

    for (int i = 0; i < rowkey; i++) {
        for (int j = 0; j < rowkey; ++j) {

            int multiplication = mapmatrix[i+*x][j+*y] * keymatrix[i][j];
            result += multiplication;
        }
    }

    return result;
}




int direction(int result){

    int mod;
    if (result < 0){
        while(result <0){
            result+=5;
        }
        mod = result % 5 ;
    }
    else{
        mod = result % 5;
    }

    return mod;
}




void slide(int *x, int *y, int result, int direction, int rowkey, int row, int column, int *midpointx, int *midpointy){

    if (direction==1){
        *x -= rowkey;
        *midpointx -= rowkey;
        if(*x < 0){
            *x += (rowkey*2);
            *midpointx += (rowkey*2);
        }
    }

    else if(direction == 2){
        *x += rowkey;
        *midpointx += rowkey;
        if(*x >= row){
            *x -= (rowkey*2);
            *midpointx-= (rowkey*2);
        }
    }

    else if(direction ==3 ){
        *y += rowkey;
        *midpointy+= rowkey;
        if( *y >= column){
            *y-=(rowkey*2);
            *midpointy-=(rowkey*2);

        }
    }

    else if(direction == 4){
        *y -= rowkey;
        *midpointy-= rowkey;
        if(*y < 0){
            *y +=(rowkey*2);
            *midpointy+=(rowkey*2);
        }
    }
}




int main(int argc, char *argv[]) {

    string s = argv[1];
    string delimiter = "x";
    string token = s.substr( 0,s.find(delimiter));// token is "scott"
    string token1= s.substr(1+ s.find(delimiter));
    int rowkey = stoi(argv[2]);
    int columnkey = stoi(argv[2]);
    int x = 0; // map matrix row
    int *px;
    px = &x;
    int y = 0; // map matrix column
    int *py;
    py = &y;
    int midpointx = (rowkey / 2);
    int *pmidpointx;
    pmidpointx = &midpointx;
    int midpointy = (rowkey/2);
    int *pmidpointy;
    pmidpointy = &midpointy;


    int row2 = 0;

    //Alocating memory for keyMatrix
    int** keymatrix = new int*[rowkey]();
    for(auto i =0; i<rowkey; i++){
        keymatrix[i]= new int[columnkey]();
    }


    fstream keyfile;
    keyfile.open(argv[4], ios::in);  //open keymatrix file

    if(!keyfile){
        cout<< "no such file!";
    }
    else{
        string mystring;
        while(getline(keyfile,mystring)){
            vector <string> tokens1;


            stringstream check1(mystring);

            string intermediate;


            while(getline(check1, intermediate, ' '))
            {
                tokens1.push_back(intermediate);
            }

            // adding columns and rows to the keymatrix
            for(int i = 0; i < tokens1.size(); i++){
                keymatrix[row2][i] = stoi(tokens1[i]);
            }

            row2+=1;
        }
    }
    keyfile.close();




    fstream myfile;
    myfile.open(argv[3], ios::in);  //open mapmatrix file

    int row = stoi(token);
    int column = stoi(token1);

    int row1 = 0;


    //Allocating memory for mapMatrix
    int** matrix = new int*[row]();
    for(auto i =0; i<row; i++){
        matrix[i]= new int[column]();
    }


    if(!myfile){
        cout<< "no such file!";
    }
    else{
        string mystring;
        while(getline(myfile,mystring)){
            vector <string> tokens;


            stringstream check1(mystring);

            string intermediate;


            while(getline(check1, intermediate, ' '))
            {
                tokens.push_back(intermediate);
            }

            // adding columns and rows to the matrix
            for(int i = 0; i < tokens.size(); i++){
                matrix[row1][i] = stoi(tokens[i]);
            }

            row1+=1;
        }
    }
    myfile.close();



    // Create the output file
    ofstream outputFile(argv[5]);


    while(multiplication(matrix, keymatrix, rowkey, px , py) % 5 != 0){

        outputFile << midpointx <<","<< midpointy <<":" << multiplication(matrix, keymatrix, rowkey, px , py)<< endl;
        slide(px, py, multiplication(matrix, keymatrix, rowkey, px , py), direction(multiplication(matrix, keymatrix, rowkey, px , py)), rowkey, row, column, pmidpointx, pmidpointy);

    }
    outputFile << midpointx <<","<< midpointy <<":" << multiplication(matrix, keymatrix, rowkey, px , py)<< endl;


    outputFile.close();



    delete[] keymatrix;
    delete[] matrix;
    return 0;
}