// Monom.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Monom.h"

using namespace std;

int main()
{
    Monom A;
    cout << "===============================" << endl;
    cout << "MonomToString A: " << A.getStringMonomial(10, 10) << endl;

    Monom B("-35x1^2x3^7x5^9", 10, 10);
    cout << "===============================" << endl;
    cout << "MonomToString B: " << B.getStringMonomial(10, 10) << endl;
    A = B;

    cout << "===============================" << endl;
    cout << "MonomToString A (A=B): " << A.getStringMonomial(10, 10) << endl;
    B = B + B;

    cout << "===============================" << endl;
    cout << "MonomToString B (B = B + B): " << B.getStringMonomial(10, 10) << endl;

    B = B + A;

    cout << "===============================" << endl;
    cout << "MonomToString B (B = B + A): " << B.getStringMonomial(10, 10) << endl;

    Monom C("35x1^2x7^3", 10, 10);

    cout << "===============================" << endl;
    cout << "MonomToString C: " << C.getStringMonomial(10, 10) << endl;

    Monom D("47x1^2x7^3", 10, 10);

    cout << "===============================" << endl;
    cout << "MonomToString D: " << D.getStringMonomial(10, 10) << endl;

    C = D - C;

    cout << "===============================" << endl;
    cout << "MonomToString C (C = D - C): " << C.getStringMonomial(10, 10) << endl;

    Monom E(C);

    cout << "===============================" << endl;
    cout << "MonomToString E (E(C)): " << E.getStringMonomial(10, 10) << endl;

    Monom F(123, 35246);
    cout << "===============================" << endl;
    cout << "MonomToString F: " << F.getStringMonomial(10, 10) << endl;

    Monom G(-7, 1000000009);
    cout << "===============================" << endl;
    cout << "MonomToString G: " << G.getStringMonomial(10, 10) << endl;

    Monom H("-5x1x5^3x10^4", 10, 10);
    cout << "===============================" << endl;
    cout << "MonomToString H: " << H.getStringMonomial(10, 10) << endl;
    cout << "MonomSv H: " << H.getSV() << endl;
    H = H.multiply(H, 10, 10);

    cout << "===============================" << endl;
    cout << "MonomToString H^2: " << H.getStringMonomial(10, 10) << endl;
    cout << "MonomSv H^2: " << H.getSV() << endl;

    Monom I("-5x1x6^3x2^3x10^4", 10, 10);
    Monom J("123x5^3x10^3x2^4x6^2", 10, 10);
    cout << "===============================" << endl;
    cout << "MonomToString J: " << J.getStringMonomial(10, 10) << endl;
    cout << "MonomToString I: " << I.getStringMonomial(10, 10) << endl;
    cout << "MonomToString J: " << J.getSV() << endl;
    cout << "MonomToString I: " << I.getSV() << endl;

    J = J.multiply(I, 10, 10);

    cout << "===============================" << endl;
    cout << "MonomToString J*I: " << J.getStringMonomial(10, 10) << endl;
    cout << "MonomToString J*I: " << J.getSV() << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
