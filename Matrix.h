#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include"LinalErrors.h"
template <typename T>
class Matrix {

private:
    unsigned int rows;
    unsigned int columns;
    T *elements;
public:
    Matrix();//+
    Matrix(unsigned int _rows, unsigned int _columns, T _default_val=T(0));//+
    Matrix(unsigned int _rows, unsigned int _columns, std::vector<T>  _elements);//+
    Matrix(const Matrix<T> &M);
    ~Matrix();

    Matrix<T>& operator =(const Matrix<T> &M);
    //Matrix<T> operator *(T a) const;
    Matrix<T> operator +(const Matrix<T> &M) const;
    Matrix<T> operator -(const Matrix<T> &M) const;
    Matrix<T>& operator +=(const Matrix<T> &M);
    Matrix<T>& operator -=(const Matrix<T> &M);
    Matrix<T>& operator *=(const Matrix<T> &M);

    template <typename U>
    Matrix<T>& operator *=(const U a);

    Matrix<T> operator +() const;
    Matrix<T> operator -() const;
    bool operator ==(const Matrix<T> &M) const;
    bool operator !=(const Matrix<T> &M) const;

    T& operator ()(unsigned int i, unsigned int j);
    const T operator ()(unsigned int i, unsigned int j) const;

    unsigned int get_rows() const;
    unsigned int get_columns() const;

    Matrix<T> get_resized(unsigned int new_rows, unsigned int new_columns) const;
    void resize(unsigned int new_rows, unsigned int new_columns);
    Matrix<T> get_resized(unsigned int new_rows, unsigned int new_columns, T _default) const;
    void resize(unsigned int new_rows, unsigned int new_columns, T _default);

    Matrix<T> get_submatrix(unsigned int rows_begin, unsigned int rows_end, unsigned int columns_begin, unsigned int columns_end) const;
    Matrix<T> get_minor(unsigned int row, unsigned int column) const;


    Matrix<T> get_transposed() const;
    Matrix<T> get_reversed() const;
    static Matrix<T> get_zero(unsigned int size);
    static Matrix<T> get_identity(unsigned int size);
    void transpose();


    std::vector<T> generate_vector() const;
    T determinant() const;
    //std::ostream& operator <<(std::ostream& os, Matrix<T> M);
//    void print_matrix(std::ostream& os, const Matrix<T>& M);
};




template <typename T,typename U>
    Matrix<T> operator *(const Matrix<T> &M, U a);

template <typename T, typename U>
    Matrix<T> operator *(U a, const Matrix<T> &M);

template <typename T>
    Matrix<T> operator *(const Matrix<T> &A, const Matrix<T> &B);

//template <typename T>
//    Vector2D<T> operator *(const Matrix<T> &A, const Vector2D<T> &v);
//
//       template<typename T>
//    Matrix<T>::Matrix(unsigned int _rows, unsigned int _columns): rows(_rows), columns(_columns), elements(new T[rows*columns]) {}



    template<typename T>
    Matrix<T>::Matrix(): rows(1), columns(1), elements(new T[rows*columns]) {
        (*this)(0,0)=0;
    }

    template<typename T>
    Matrix<T>::Matrix(unsigned int _rows, unsigned int _columns, T _default_val): rows(_rows), columns(_columns), elements(new T[rows*columns]) {
//        std::cout<<"DV " << _default_val << "\n";
        for (unsigned int i=0; i<rows; i++)
            for (unsigned int j=0; j<columns; j++)
                (*this)(i, j)=_default_val;
    }

    template<typename T>
    Matrix<T>::Matrix(unsigned int _rows, unsigned int _columns, std::vector<T> _elements): Matrix(_rows, _columns) {
        if(_elements.size()!=_rows*_columns)
            throw MatrixError_WrongOriginSize();
        for (unsigned int i=0; i<rows; i++)
            for (unsigned int j=0; j<columns; j++)
                (*this)(i, j)=_elements[i*columns+j];
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix<T> &M): Matrix(M.get_rows(), M.get_columns()) {
        for (unsigned int i=0; i<rows; i++)
            for (unsigned int j=0; j<columns; j++)
                (*this)(i, j)=M(i,j);

    }

    template<typename T>
    Matrix<T>::~Matrix() {
        delete[] elements;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator =(const Matrix<T> &M) {
        if (this==&M||*this==M)
            return *this;
        delete[] elements;
        rows=M.get_rows();
        columns=M.get_columns();
        elements=new T[rows*columns];
        for (unsigned int i=0; i<rows; i++)
            for (unsigned int j=0; j<columns; j++)
                (*this)(i, j)=M(i,j);
        return *this;
    }

//    template<typename T>
//    Matrix<T> Matrix<T>::operator *(T a) const {
//        Matrix<T> R(*this);
//        for (unsigned int i=0; i<R.get_rows(); i++)
//            for (unsigned int j=0; j<R.get_columns(); j++)
//                R(i, j)= a*(*this)(i,j);
//        return R;
//    }
    template<typename T>
    Matrix<T> Matrix<T>::operator +(const Matrix<T> &M) const{
        if(get_rows()!=M.get_rows()||get_columns()!=M.get_columns())
            throw MatrixError_WrongSize();
        Matrix<T> R(*this);
        for (unsigned int i=0; i<R.get_rows(); i++)
            for (unsigned int j=0; j<R.get_columns(); j++)
                R(i, j)= R(i,j) + M(i,j);
        return R;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator -(const Matrix<T> &M) const{
        if(get_rows()!=M.get_rows()||get_columns()!=M.get_columns())
            throw MatrixError_WrongSize();
        Matrix<T> R(*this);
        for (unsigned int i=0; i<R.get_rows(); i++)
            for (unsigned int j=0; j<R.get_columns(); j++)
                R(i, j)= R(i,j) - M(i,j);
        return R;

    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator +=(const Matrix<T> &M) {
        (*this)=(*this)+M;
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator -=(const Matrix<T> &M) {
        (*this)=(*this)-M;
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator *=(const Matrix<T> &M) {
        (*this)=(*this)*M;
        return *this;
    }

    template <typename T>
    template <typename U>
    Matrix<T>& Matrix<T>::operator *=(const U a) {
        (*this)=(*this)*a;
        //std::cout << "OK\n";
        return *this;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator +() const{
        return *this;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator -() const{
        Matrix<T> R(*this);
        for (unsigned int i=0; i<R.get_rows(); i++)
            for (unsigned int j=0; j<R.get_columns(); j++)
                R(i, j)= -R(i,j);
        return R;
    }

    template<typename T>
    bool Matrix<T>::operator ==(const Matrix<T> &M) const{
        if(get_rows()!=M.get_rows()||get_columns()!=M.get_columns())
            return false;
        for (unsigned int i=0; i<get_rows(); i++)
            for (unsigned int j=0; j<get_columns(); j++)
                if((*this)(i, j)!=M(i, j))
                    return false;
        return true;
    }

    template<typename T>
    bool Matrix<T>::operator !=(const Matrix<T> &M) const{
        return !((*this)==M);
    }

    template<typename T>
    unsigned int Matrix<T>::get_rows() const{
        return rows;
    }

    template<typename T>
    unsigned int Matrix<T>::get_columns() const{
        return columns;
    }

    template<typename T>
    const T Matrix<T>::operator ()(unsigned int i, unsigned int j) const{
        if(i>=rows||j>=columns||i<0||j<0)
            throw MatrixError_AccessViolation();
        return elements[i*columns+j];
    }

    template<typename T>
    T& Matrix<T>::operator ()(unsigned int i, unsigned int j) {
        if(i>=rows||j>=columns||i<0||j<0)
            throw MatrixError_AccessViolation();
        return elements[i*columns+j];
    }


    template<typename T>
    Matrix<T> Matrix<T>::get_resized(unsigned int new_rows, unsigned int new_columns) const {
        if(new_rows==0||new_columns==0)
            throw MatrixError_ZeroResize();
        Matrix<T> R(new_rows, new_columns);
        unsigned int imax = std::min(rows, new_rows);
        unsigned int jmax = std::min(columns, new_columns);
        for (unsigned int i=0; i<imax; i++)
            for (unsigned int j=0; j<jmax; j++){
                R(i, j) =(*this)(i, j);
            }
        return R;
    }

    template<typename T>
    void Matrix<T>::resize(unsigned int new_rows, unsigned int new_columns) {
        Matrix<T> R=get_resized(new_rows, new_columns);
        *this=R;
    }

    template<typename T>
    Matrix<T> Matrix<T>::get_resized(unsigned int new_rows, unsigned int new_columns, T _default) const {
        if(new_rows==0||new_columns==0)
            throw MatrixError_ZeroResize();
        Matrix<T> R(new_rows, new_columns, _default);
        unsigned int imax = std::min(rows, new_rows);
        unsigned int jmax = std::min(columns, new_columns);
        for (unsigned int i=0; i<imax; i++)
            for (unsigned int j=0; j<jmax; j++){
                R(i, j) =(*this)(i, j);
            }
        return R;
    }

    template<typename T>
    void Matrix<T>::resize(unsigned int new_rows, unsigned int new_columns, T _default) {
        Matrix<T> R=get_resized(new_rows, new_columns, _default);
        *this=R;
    }

    template<typename T>
    Matrix<T> Matrix<T>::get_submatrix(unsigned int rows_begin, unsigned int rows_end, unsigned int columns_begin, unsigned int columns_end) const{
        if(rows_begin>=rows||rows_end>=rows||rows_begin>=rows_end||columns_begin>=columns||columns_end>=columns||columns_begin>=columns_end)
            throw MatrixError_WrongSubmatrix();
        unsigned int imax = rows_end-rows_begin;
        unsigned int jmax = columns_end-columns_begin;
        Matrix<T> R(jmax, jmax);
        for (unsigned int i=0; i<imax; i++)
            for (unsigned int j=0; j<jmax; j++)
                R(i, j)=(*this)(i+rows_begin, j+rows_begin);
        return R;
    }

    template <typename T>
    Matrix<T> Matrix<T>::get_minor(unsigned int row, unsigned int column) const {
        if(rows==1||columns==1||row>=rows||column>=columns)
            throw MatrixError_WrongMinor();
        Matrix<T> R(rows-1, columns-1);
        unsigned int i_for_R;
        unsigned int j_for_R;
        for (unsigned int i=0; i<rows; i++){
                i_for_R=i-(i>row);
            for (unsigned int j=0; j<columns; j++){
                    j_for_R=j-(j>column);
                if (i!=row&&j!=column){
                    //std::cout <<"\nOK\n" <<i-(i>row) << " " << j-(j>column) <<"\n";
                    R(i_for_R, j_for_R)=(*this)(i, j);
                    //std::cout<< R(i_for_R, j_for_R) << " ";
                }
                //else std::cout<< "\nnotOK\n";
            }
        }
        return R;
    }

    template<typename T>
    Matrix<T> Matrix<T>::get_identity(unsigned int size) {
        Matrix<T> R(size, size, T(0));
        for (unsigned int i=0; i<size; i++)
            R(i, i)=1;
        return R;
    }

    template<typename T>
    Matrix<T> Matrix<T>::get_zero(unsigned int size) {
        return Matrix<T>(size, size, T(0));
    }


    template<typename T>
    Matrix<T> Matrix<T>::get_transposed() const{
        Matrix<T> R(columns, rows);
        for (unsigned int i=0; i<rows; i++)
            for (unsigned int j=0; j<columns; j++)
                R(j, i)=(*this)(i,j);
        return R;
    }

    template<typename T>
    void Matrix<T>::transpose() {
        *this=get_transposed();
    }

    template <typename T>
    std::vector<T> Matrix<T>::generate_vector() const {
        std::vector<T> result;
        for (unsigned int i=0; i<rows; i++)
            for (unsigned int j=0; j<columns; j++)
                result.push_back((*this)(i,j));
        return result;
    }

    template <typename T>
    T Matrix<T>::determinant() const {
        if(columns!=rows)
            throw MatrixError_NotSquare();
        if(columns==1)
            return (*this)(0,0);
        T sum=(*this)(0, 0)*get_minor(0, 0).determinant();
        for (unsigned int i=1; i<columns; i++)
            sum=sum+pow(-1,i)*(*this)(0, i)*get_minor(0, i).determinant();
        return sum;
    }

    template <typename T>
    Matrix<T> Matrix<T>::get_reversed() const {
        if(columns!=rows)
            throw MatrixError_NotSquare();
        if(determinant()==0)
            throw MatrixError_Degenerate();
        Matrix<T> R(rows, rows);
        T det=determinant();
        for (unsigned int i=0; i<rows; i++)
            for (unsigned int j=0; j<columns; j++)
                R(i,j)=pow(-1,(i+j))*get_minor(j, i).determinant()/det;
        return R;
    }


//    template <typename T>
//    void Matrix::print_matrix() {
//        T* pr_array=generate_array();
//
//    }

//    template <typename T>
//    bool comparator(T a, T b) {
//        return digit_count(a) < digit_count(b)
//    }

    template <typename T>
    std::ostream& operator <<(std::ostream& os, const Matrix<T>& M) {
        for (unsigned int i=0; i<M.get_rows(); i++)
            for (unsigned int j=0; j<M.get_columns(); j++)
//                if (i!=M.get_rows()-1||j!=M.get_columns()-1)
                    os << M(i,j) << " ";
                //else os << M(i, j) <<"\n";
        return os;
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, Matrix<T>& M) {
        T x;
        for (unsigned int i=0; i<M.get_rows(); i++)
            for (unsigned int j=0; j<M.get_columns(); j++){
                is >> x;
                M(i, j)= x;
            }
        return is;
    }

    template <typename T>
    Matrix<T> operator *(const Matrix<T> &A, const Matrix<T> &B) {
        if(A.get_columns()!=B.get_rows())
            throw MatrixError_WrongSize();
        Matrix<T> R(A.get_rows(), B.get_columns());
        for (unsigned int i=0; i<R.get_rows(); i++)
            for (unsigned int j=0; j<R.get_columns(); j++){
                T s=A(i,0)*B(0,j);
                for (unsigned int k=1; k<A.get_columns(); k++)
                    s = s + A(i,k)*B(k,j);
                R(i,j)= s;
            }
        return R;
    }

    template <typename T, typename U>
    Matrix<T> operator *(U a,const Matrix<T> &M) {
        Matrix<T> R=M;
        for (unsigned int i=0; i<M.get_rows(); i++)
            for (unsigned int j=0; j<M.get_columns(); j++)
                R(i, j)=a*M(i,j);
        return R;
    }

    template <typename T, typename U>
    Matrix<T> operator *(const Matrix<T> &M, U a) {
        Matrix<T> R=M;
        //T n_a= a;
        for (unsigned int i=0; i<M.get_rows(); i++)
            for (unsigned int j=0; j<M.get_columns(); j++){
                //std::cout << a*M(i,j) << "\n";
                R(i, j)= a*M(i,j);
            }
        return R;
    }


#endif // MATRIX_H_INCLUDED
