#include <iostream>
#include"Linal.h"
using namespace std;

int main()
{
    try {
///__________________________Матрицы____________________

        //Конструктор по умолчанию - матрица первого порядка со значением элемента по умолчанию
        Matrix<double> A;

        //Конструктор с параметрами (размеры матрицы), значение элементов по умолчанию
        Matrix<double> B(2,3);

        std::vector<double> v={0,2,3,4,5,6,7,8,9};

        //Конструктор с параметрами (размеры матрицы и инициализирующий вектор), значения элементов берём из вектора v
        Matrix<double> M(3,3,v);

        //Копирующий конструктор
        Matrix<double> C(M);

        //Выводим матрицы поэлементно
        std::cout << A << "\n" << B << "\n" << C;

        //Считаем детерминант
        std::cout<< M.determinant();

        //Если детерминант не ноль,
        if(M.determinant()!=0) {
            //Ищем обратную матрицу
            Matrix<double> R=M.get_reversed();
            cout << M.get_reversed() << "\n";
            //И проверяем, является ли она обратной
            std::cout << R*M << "\n";
        }

        Matrix<double> D(2, 3);

        //Ввод D поэлементно
        cin >> D;

        //Меняем некоторые элементы матрицы B
        B(0,0)=4;
        B(1,2)=10;

        //Сложение
        cout << D+B << "\n";

        //Вычитание
        cout << D-B << "\n";

        //Умножение на число
        cout << D*3 << "\n" << 3*D << "\n";

        //И умножение матриц
        cout << B*C << "\n";


///__________________Векторы(3D)___________________________

        //Вектор по умолчанию
        Vector3D<double> a;

        //Copy-конструктор
        Vector3D<double> b(a);

        //Инит покоординатно
        Vector3D<double> c(1, 2, 3);

        std::vector<double> v={9,4,2};
        Matrix<double> S(3,1,v);

        //Инициализация из столбца
        Vector3D<double> d(S);

        //Смена координат
        a.X()=4;
        a.Y()=10;
        a.Z()=5;

        //Покоординатный ввод
        cin >> b;

        //Сложение
        cout << a+b <<"\n";

        //Вычитание
        cout << a-b <<"\n";

        //Умножение на число
        cout << a*10 << "\n" << 10*a << "\n";

        //Скалярное умножение
        cout << a*b << "\n";

        //Векторное умножение
        cout << Vector3D<double>::vector_product(a, b) << "\n";

        //И смешанное
        cout << Vector3D<double>::triple_scalar_product(a, b, c);

    }
    catch(const std::runtime_error& e){
        cout << e.what();
    }

    return 0;
}
