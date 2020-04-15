#ifndef LINALERRORS_H_INCLUDED
#define LINALERRORS_H_INCLUDED
#include<stdexcept>
class MatrixError_WrongSize: public std::runtime_error {
public:
    MatrixError_WrongSize(): std::runtime_error("Wrong matrices size") {};
};

class MatrixError_WrongOriginSize: public std::runtime_error {
public:
    MatrixError_WrongOriginSize(): std::runtime_error("Wrong origin size"){};
};

class MatrixError_WrongSubmatrix: public std::runtime_error {
public:
    MatrixError_WrongSubmatrix(): std::runtime_error("Wrong submatrix"){};
};

class MatrixError_AccessViolation: public std::runtime_error {
public:
    MatrixError_AccessViolation(): std::runtime_error("Access violation"){};
};

class MatrixError_WrongMinor: public std::runtime_error {
public:
    MatrixError_WrongMinor(): std::runtime_error("Wrong minor"){};
};

class MatrixError_NotSquare: public std::runtime_error {
public:
    MatrixError_NotSquare(): std::runtime_error("Matrix is not square"){};
};

class MatrixError_Degenerate: public std::runtime_error {
public:
    MatrixError_Degenerate(): std::runtime_error("Matrix is degenerate"){};
};

class MatrixError_ZeroResize: public std::runtime_error {
public:
    MatrixError_ZeroResize(): std::runtime_error("Resizing to zero"){};
};

class Vector2DError_WrongMatrixSize: public std::runtime_error {
public:
    Vector2DError_WrongMatrixSize(): std::runtime_error("Wrong matrix size"){};
};

class Vector3DError_WrongMatrixSize: public std::runtime_error {
public:
    Vector3DError_WrongMatrixSize(): std::runtime_error("Wrong matrix size"){};
};

#endif // LINALERRORS_H_INCLUDED
