#include <iostream>
#include"Linal.h"
using namespace std;

int main()
{
    try {
///__________________________�������____________________

        //����������� �� ��������� - ������� ������� ������� �� ��������� �������� �� ���������
        Matrix<double> A;

        //����������� � ����������� (������� �������), �������� ��������� �� ���������
        Matrix<double> B(2,3);

        std::vector<double> v={0,2,3,4,5,6,7,8,9};

        //����������� � ����������� (������� ������� � ���������������� ������), �������� ��������� ���� �� ������� v
        Matrix<double> M(3,3,v);

        //���������� �����������
        Matrix<double> C(M);

        //������� ������� �����������
        std::cout << A << "\n" << B << "\n" << C;

        //������� �����������
        std::cout<< M.determinant();

        //���� ����������� �� ����,
        if(M.determinant()!=0) {
            //���� �������� �������
            Matrix<double> R=M.get_reversed();
            cout << M.get_reversed() << "\n";
            //� ���������, �������� �� ��� ��������
            std::cout << R*M << "\n";
        }

        Matrix<double> D(2, 3);

        //���� D �����������
        cin >> D;

        //������ ��������� �������� ������� B
        B(0,0)=4;
        B(1,2)=10;

        //��������
        cout << D+B << "\n";

        //���������
        cout << D-B << "\n";

        //��������� �� �����
        cout << D*3 << "\n" << 3*D << "\n";

        //� ��������� ������
        cout << B*C << "\n";


///__________________�������(3D)___________________________

        //������ �� ���������
        Vector3D<double> a;

        //Copy-�����������
        Vector3D<double> b(a);

        //���� �������������
        Vector3D<double> c(1, 2, 3);

        std::vector<double> v={9,4,2};
        Matrix<double> S(3,1,v);

        //������������� �� �������
        Vector3D<double> d(S);

        //����� ���������
        a.X()=4;
        a.Y()=10;
        a.Z()=5;

        //�������������� ����
        cin >> b;

        //��������
        cout << a+b <<"\n";

        //���������
        cout << a-b <<"\n";

        //��������� �� �����
        cout << a*10 << "\n" << 10*a << "\n";

        //��������� ���������
        cout << a*b << "\n";

        //��������� ���������
        cout << Vector3D<double>::vector_product(a, b) << "\n";

        //� ���������
        cout << Vector3D<double>::triple_scalar_product(a, b, c);

    }
    catch(const std::runtime_error& e){
        cout << e.what();
    }

    return 0;
}
