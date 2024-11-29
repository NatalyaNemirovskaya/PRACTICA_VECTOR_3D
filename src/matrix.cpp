#include "matrix.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace math;

Matrix::Matrix()
{

};


Matrix::Matrix(int rows, int cols): rows_(rows),cols_(cols), mvec_(std::vector<real>(cols*rows))
     {

     };

real& Matrix::operator()(int row, int col)
{
     if(row >= this->rows_)
     {
        std::cerr << "Matrix row number out of bounds";
        //return 0;
     } 

      if(col >= this->cols_)
     {
        std::cerr << "Matrix col number out of bounds";
        //return 0;
     } 

    int pos(0);

    pos = cols_*row + col;
    return this->mvec_.at(pos);
}

real  Matrix::operator()(int row, int col) const
{
     if(row >= this->rows_)
     {
        std::cerr << "Matrix row number out of bounds";
        //return 0;
     } 

      if(col >= this->cols_)
     {
        std::cerr << "Matrix col number out of bounds";
        //return 0;
     } 

    int pos(0);

    pos = cols_*row + col;
    return this->mvec_.at(pos);
}



void Matrix::print()
{
    for(int i = 0; i < this->rows_; ++i)
    {
       for(int j = 0; j< this->cols_; ++j) 
       std::cout << this->mvec_.at(cols_*i+ j) << " " ;

       std::cout << std::endl;
    }

    
}

Matrix math::operator+(const Matrix &A, const Matrix &B)
{
   if ((A.cols_ != B.cols_) || (A.rows_ != B.rows_))
   {
      std::cerr << "Matrix: Matrices can`t be added!" << std::endl;
      return Matrix(0, 0);
   }

   Matrix M(A.cols_, A.rows_);

   for(int i = 0; i < M.mvec_.size(); ++i)
   {
      M.mvec_.at(i) = A.mvec_.at(i) + B.mvec_.at(i);
   }

   return M;
}

Matrix math::operator-(const Matrix &A, const Matrix &B)
{
   if ((A.cols_ != B.cols_) || (A.rows_ != B.rows_))
   {
      std::cerr << "Matrix: Matrices can`t be subtracted!" << std::endl;
      return Matrix(0, 0);
   }

   Matrix M(A.cols_, A.rows_);

   for(int i = 0; i < M.mvec_.size(); ++i)
   {
      M.mvec_.at(i) = A.mvec_.at(i) - B.mvec_.at(i);
   }

   return M;
}

Matrix math::operator*(const Matrix &A, const Matrix &B)
{
   if (A.cols_ != B.rows_)
   {
      std::cerr << "Matrix: Matrices can`t be multiplied!" << std::endl;
      return Matrix(0, 0);
   }

   Matrix M(A.rows_, B.cols_);

   for (int pos = 0; pos < M.mvec_.size(); ++pos)
   {
      int row = (int)(pos / M.cols_);
      int col = pos - row * M.cols_;

      for (int k = 0; k < A.cols_; ++k)
         M.mvec_.at(pos) += A(row, k) * B(k, col);
   }

   return M;
}


//
Matrix &Matrix::operator+=(const Matrix &M)
{
  /*if ((this->cols_ != M.cols_) || (this->rows_ != M.rows_))
   {
      std::cerr << "Matrix: Matrices can`t be added!" << std::endl;
      return *this;
   } */
   *this = math::operator+(*this, M);
   return *this;

   // for (int i = 0; i < this->mvec_.size(); ++i)
   // {
   //  this->mvec_.at(i) = this->mvec_.at(i) + M.mvec_.at(i);
   // }
   // return *this;
}

Matrix & Matrix::operator-=(const Matrix &M)
{
   *this = math::operator-(*this, M);
   return *this;
}


Matrix& Matrix::operator*=(const Matrix& M) // перегрузка оператора *=
{
*this = math::operator*(*this, M);
   return *this;
}

int Matrix::get_n_col() const //return cols_
{
  return cols_;
}

    int Matrix::get_n_row() const //return row
   {
      return rows_;
   }

  

/*std::ostream&  math::operator<<(std::ostream& os, const Matrix& M)
{
    for(int i = 0; i < M.rows_; ++i)
    {
       for(int j = 0; j< M.cols_; ++j) 
       os << M.mvec_.at(M.cols_*i+ j) << " " ;
       

       os << std::endl;
    }
    
   return  os;
} */


/*std::istream &math::operator>>(std::istream &in, Matrix &M)
{
   for (int i = 0; i < M.mvec_.size(); ++i)
   {
      in >> M.mvec_.at(i);
   }
   return in;
}*/

/*std::istream &math::operator>>(std::istream &in, math::Matrix &M(int row, int col))
{

   in >> *M;

   return in;
}*/