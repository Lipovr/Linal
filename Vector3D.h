#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED
#include<exception>
#include"Matrix.h"
template<typename T>
class Vector2D;

template <typename T>
class Vector3D {
private:
    Matrix<T> coords;
public:
    Vector3D();
    Vector3D(T x, T y, T z);
    Vector3D(const Matrix<T> &M);

    const T X() const;
    const T Y() const;
    const T Z() const;
    T& X();
    T& Y();
    T& Z();

    static Vector3D<T> vector_product(const Vector3D<T> &a, const Vector3D<T> &b);
    static T triple_scalar_product(const Vector3D<T> &a, const Vector3D<T> &b, const Vector3D<T> &c);

    operator Vector2D<T>() const;
    operator Matrix<T>() const;

    bool operator ==(const Vector3D<T> &v) const;
    bool operator !=(const Vector3D<T> &v) const;

    Vector3D<T> operator +() const;
    Vector3D<T> operator -() const;


    T operator *(const Vector3D<T> &v) const;
    template<typename U>
    Vector3D<T> operator *(const U a) const;
    template<typename U>
    Vector3D<T>& operator *=(const U a);
    Vector3D<T> operator +(const Vector3D<T> &v) const;
    Vector3D<T>& operator +=(const Vector3D<T> &v);
    Vector3D<T> operator -(const Vector3D<T> &v) const;
    Vector3D<T>& operator -=(const Vector3D<T> &v);

    template<typename U>
    friend std::ostream& operator <<(std::ostream &os, const Vector3D<U> &v);
    template<typename U>
    friend std::istream& operator >>(std::istream &is, Vector3D<U> &v);
};
    template<typename T, typename U>
    Vector3D<T> operator *(const U a, const Vector3D<T> &v);

    template <typename T>
    Vector3D<T> operator *(const Matrix<T> &A, const Vector3D<T> &v);

    template<typename T>
    std::ostream& operator <<(std::ostream &os, const Vector3D<T> &v);

    template<typename U>
    std::istream& operator >>(std::istream &is, Vector3D<U> &v);




    template<typename T>
    Vector3D<T>::Vector3D(): coords(Matrix<T>(3, 1, T(0))) {}

    template<typename T>
    Vector3D<T>::Vector3D(T x, T y, T z): Vector3D() {
        coords(0,0)=x;
        coords(1,0)=y;
        coords(2,0)=z;
    }

    template<typename T>
    Vector3D<T>::Vector3D(const Matrix<T> &M): Vector3D() {
        if(M.get_columns()!=1||M.get_rows()!=3)
            throw Vector3DError_WrongMatrixSize();
        coords(0,0)=M(0,0);
        coords(1,0)=M(1,0);
        coords(2,0)=M(2,0);
    }

    template<typename T>
    T& Vector3D<T>::X() {
        return coords(0,0);
    }

    template<typename T>
    T& Vector3D<T>::Y() {
        return coords(1,0);
    }

    template<typename T>
    T& Vector3D<T>::Z() {
        return coords(2,0);
    }


    template<typename T>
    const T Vector3D<T>::X() const {
        return coords(0,0);
    }

    template<typename T>
    const T Vector3D<T>::Y() const {
        return coords(1,0);
    }

    template<typename T>
    const T Vector3D<T>::Z() const {
        return coords(2,0);
    }

    template<typename T>
    Vector3D<T> Vector3D<T>::vector_product(const Vector3D<T> &a, const Vector3D<T> &b) {
        return Vector3D<T>(a.Y()*b.Z()-a.Z()*b.Y(), -(a.X()*b.Z()-a.Z()*b.X()), a.X()*b.Y()-a.Y()*b.X());
    }

    template<typename T>
    T Vector3D<T>::triple_scalar_product(const Vector3D<T> &a, const Vector3D<T> &b, const Vector3D<T> &c) {
        Matrix<T> M(3,3);
        for (int i=0; i<3; i++)
            M(0,i)=a.coords(i,0);
        for (int i=0; i<3; i++)
            M(1,i)=b.coords(i,0);
        for (int i=0; i<3; i++)
            M(2,i)=c.coords(i,0);
        return M.determinant();
    }


    template<typename T>
    Vector3D<T>::operator Vector2D<T>() const {
        return Vector2D<T>(X(), Y());
    }

    template<typename T>
    Vector3D<T>::operator Matrix<T>() const {
        return coords;
    }

    template<typename T>
    bool Vector3D<T>::operator ==(const Vector3D<T> &v) const {
        if (X()==v.X()&&Y()==v.Y()&&Z()==v.Z())
            return true;
        return false;
    }

    template<typename T>
    bool Vector3D<T>::operator !=(const Vector3D<T> &v) const {
        return !((*this)==v);
    }

    template<typename T>
    Vector3D<T> Vector3D<T>::operator+() const {
        return (*this);
    }


    template<typename T>
    Vector3D<T> Vector3D<T>::operator-() const {
        return (*this)*T(-1);
    }

    template<typename T>
    T Vector3D<T>::operator*(const Vector3D<T> &v) const {
        return (coords.get_transposed()*v.coords)(0,0);
    }

    template<typename T>
    template<typename U>
    Vector3D<T> Vector3D<T>::operator *(const U a) const {

        return Vector3D<T>(coords*T(a));
    }

    template<typename T>
    template<typename U>
    Vector3D<T>& Vector3D<T>::operator *=(const U a) {
        coords*=T(a);
        return *this;
    }

    template<typename T>
    Vector3D<T> Vector3D<T>::operator +(const Vector3D<T> &v) const {
        return Vector3D<T>(coords+v.coords);
    }

    template<typename T>
    Vector3D<T>& Vector3D<T>::operator +=(const Vector3D<T> &v) {
        coords+=v.coords;
        return *this;
    }

    template<typename T>
    Vector3D<T> Vector3D<T>::operator -(const Vector3D<T> &v) const {
        return Vector3D<T>(coords-v.coords);
    }

    template<typename T>
    Vector3D<T>& Vector3D<T>::operator -=(const Vector3D<T> &v) {
        coords-=v.coords;
        return *this;
    }

    template<typename T, typename U>
    Vector3D<T> operator *(const U a, const Vector3D<T> &v) {
        return v*a;
    }

    template<typename U>
    std::ostream& operator <<(std::ostream &os,const Vector3D<U> &v) {
        os << v.coords;
        return os;
    }

    template<typename U>
    std::istream& operator >>(std::istream &is, Vector3D<U> &v) {
        is >> v.coords;
        return is;
    }

    template <typename T, typename U>
    Vector3D<T> operator *(const Matrix<U> &A, const Vector3D<T> &v) {
        return Vector3D<T>(A*Matrix<T>(v));
    }


#endif // VECTOR3D_H_INCLUDED
