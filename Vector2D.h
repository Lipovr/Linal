#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED
#include<exception>
#include"Linal.h"

template <typename T>
class Vector3D;

template <typename T>
class Vector2D {
private:
    Matrix<T> coords;
public:
    Vector2D();
    Vector2D(T x, T y);
    Vector2D(const Matrix<T> &M);

    const T X() const;
    const T Y() const;
    T& X();
    T& Y();

    operator Matrix<T>() const;
    operator Vector3D<T>() const;

    bool operator ==(const Vector2D<T> &v) const;
    bool operator !=(const Vector2D<T> &v) const;

    Vector2D<T> operator +() const;
    Vector2D<T> operator -() const;


    T operator *(const Vector2D<T> &v) const;
    template<typename U>
    Vector2D<T> operator *(const U a) const;
    template<typename U>
    Vector2D<T>& operator *=(const U a);
    Vector2D<T> operator +(const Vector2D<T> &v) const;
    Vector2D<T>& operator +=(const Vector2D<T> &v);
    Vector2D<T> operator -(const Vector2D<T> &v) const;
    Vector2D<T>& operator -=(const Vector2D<T> &v);

    template<typename U>
    friend std::ostream& operator <<(std::ostream &os, const Vector2D<U> &v);
    template<typename U>
    friend std::istream& operator >>(std::istream &is, Vector2D<U> &v);
};
    template<typename T, typename U>
    Vector2D<T> operator *(const U a, const Vector2D<T> &v);

    template <typename T>
    Vector2D<T> operator *(const Matrix<T> &A, const Vector2D<T> &v);

    template<typename T>
    std::ostream& operator <<(std::ostream &os, const Vector2D<T> &v);

    template<typename U>
    std::istream& operator >>(std::istream &is, Vector2D<U> &v);
        template<typename T>
    Vector2D<T>::Vector2D(): coords(Matrix<T>(2, 1, T(0))) {}

    template<typename T>
    Vector2D<T>::Vector2D(T x, T y): Vector2D() {
        coords(0,0)=x;
        coords(1,0)=y;
    }

    template<typename T>
    Vector2D<T>::Vector2D(const Matrix<T> &M): Vector2D() {
        if(M.get_columns()!=1||M.get_rows()!=2)
            throw Vector2DError_WrongMatrixSize();
        coords(0,0)=M(0,0);
        coords(1,0)=M(1,0);
    }

    template<typename T>
    T& Vector2D<T>::X() {
        return coords(0,0);
    }

    template<typename T>
    T& Vector2D<T>::Y() {
        return coords(1,0);
    }

    template<typename T>
    const T Vector2D<T>::X() const {
        return coords(0,0);
    }

    template<typename T>
    const T Vector2D<T>::Y() const {
        return coords(1,0);
    }

    template<typename T>
    Vector2D<T>::operator Vector3D<T>() const {
        return Vector3D<T>(X(), Y(), T(0));
    }


    template<typename T>
    Vector2D<T>::operator Matrix<T>() const {
        return coords;
    }

    template<typename T>
    bool Vector2D<T>::operator ==(const Vector2D<T> &v) const {
        if (X()==v.X()&&Y()==v.Y())
            return true;
        return false;
    }

    template<typename T>
    bool Vector2D<T>::operator !=(const Vector2D<T> &v) const {
        return !((*this)==v);
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator+() const {
        return (*this);
    }


    template<typename T>
    Vector2D<T> Vector2D<T>::operator-() const {
        return (*this)*T(-1);
    }

    template<typename T>
    T Vector2D<T>::operator*(const Vector2D<T> &v) const {
        return (coords.get_transposed()*v.coords)(0,0);
    }

    template<typename T>
    template<typename U>
    Vector2D<T> Vector2D<T>::operator *(const U a) const {

        return Vector2D<T>(coords*T(a));
    }

    template<typename T>
    template<typename U>
    Vector2D<T>& Vector2D<T>::operator *=(const U a) {
        coords*=T(a);
        return *this;
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator +(const Vector2D<T> &v) const {
        return Vector2D<T>(coords+v.coords);
    }

    template<typename T>
    Vector2D<T>& Vector2D<T>::operator +=(const Vector2D<T> &v) {
        coords+=v.coords;
        return *this;
    }

    template<typename T>
    Vector2D<T> Vector2D<T>::operator -(const Vector2D<T> &v) const {
        return Vector2D<T>(coords-v.coords);
    }

    template<typename T>
    Vector2D<T>& Vector2D<T>::operator -=(const Vector2D<T> &v) {
        coords-=v.coords;
        return *this;
    }

    template<typename T, typename U>
    Vector2D<T> operator *(const U a, const Vector2D<T> &v) {
        return v*a;
    }

    template<typename U>
    std::ostream& operator <<(std::ostream &os, Vector2D<U> &v) {
        os << v.coords;
        return os;
    }

    template<typename U>
    std::istream& operator >>(std::istream &is, Vector2D<U> &v) {
        is >> v.coords;
        return is;
    }

    template <typename T, typename U>
    Vector2D<T> operator *(const Matrix<U> &A, const Vector2D<T> &v) {
        return Vector2D<T>(A*Matrix<T>(v));
    }

#endif // VECTOR2D_H_INCLUDED
