//
//  Matrix.hpp
//  MD Workshop
//
//  Created by Joel Eaves on 6/1/19.
//  Edited by Joe Raso on 6/7/19.
//  Copyright © 2019 Joel Eaves. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>

using namespace std;
class Matrix{
public:
    Matrix(); //Default Constructor
    //Construct a matrix with a number of rows and columns
    Matrix(const int& rows,const int& columns);
    Matrix & operator =(const Matrix& rhs);//Assignment operator
    Matrix(const Matrix& rhs);//Copy constructor
    //Accessor functions
    inline int Rows(){return rows;};
    inline int Columns(){return columns;};
    double** Data(){return data;};
    //This is a useful operator to overload
    friend ostream & operator << (ostream& os,const Matrix& rhs);
    ~Matrix();//Destructor
protected:
    int rows,columns;
    double** data;
};

#endif /* Matrix_hpp */
