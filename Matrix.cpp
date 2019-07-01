//
//  Matrix.cpp
//  MD Workshop
//
//  Created by Joel Eaves on 6/1/19.
//  Edited by Joe Raso on 6/7/19.
//  Copyright © 2019 Joel Eaves. All rights reserved.
//

#include "Matrix.hpp"


Matrix::Matrix():data(0),rows(0),columns(0){}

Matrix::Matrix(const int& rows,const int& columns):rows(rows),columns(columns){
    data = new double* [rows];
    data[0] = new double [rows*columns];
    for(int i=1;i<rows;i++)
        data[i]=data[i-1]+columns;//Use pointer math to allocate it
}

Matrix & Matrix::operator=(const Matrix& rhs){
    if(this!= &rhs){//Check for user/compiler stupidity
        int i,j;
        rows = rhs.rows;
        columns = rhs.columns;
        if(data !=0){
            delete [] data[0];
            delete [] data;
        }
        data = new double* [rows];
        data[0] = new double [rows*columns];
        for(i=1;i<rows;i++)
            data[i]=data[i-1]+columns;
        for(i=0;i<rows;i++)
            for(j=0;j<columns;j++)
                data[i][j] = rhs.data[i][j];
    }
    return *this;
}

Matrix::Matrix(const Matrix& rhs){
    int i,j;
    rows = rhs.rows;
    columns = rhs.columns;
    if(data !=0){
        data = 0;
    }
    data = new double* [rows];
    data[0] = new double [rows*columns];
    for(i=1;i<rows;i++)
        data[i]=data[i-1]+columns;
    for(i=0;i<rows;i++)
        for(j=0;j<columns;j++)
            data[i][j] = rhs.data[i][j];
}

Matrix::~Matrix(){
    if(data !=0){
        delete [] data[0];
        delete [] data;
    }
}

ostream& operator << (ostream& os,const Matrix& rhs){
    // Edited this to make it comma delimited, cause that's easier to read.-JR
    for(int i=0;i<rhs.rows;i++){
        for(int j=0;j<rhs.columns;j++){
            os << rhs.data[i][j];
            if(j<(rhs.columns-1)){os << ",";}
        }
        os << endl;
    }
    return os;
}
