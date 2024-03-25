#include <iostream>
#include <math.h>

using namespace std;


// Функция GetFunction вычисляет различные математические функции в зависимости от значения параметра option.
// Возвращает результат вычисления функции для заданного аргумента Arguments.

double GetFunction(double Arguments, int option)
{
    double y; // Инициализация вектора результата

    if (option == 1) {
        y = (Arguments * Arguments);  // Вычисление x^2 для каждого x
    }
    if (option == 2) {
        y = (Arguments * Arguments * Arguments); // Вычисление x^3 для каждого x
    }
    if (option == 3) {
        y = (1 / Arguments);  // Вычисление 1/x для каждого x
    }
    if (option == 4) {
        y = (fabs(Arguments)); // Вычисление |x| для каждого x
    }
    if (option == 5) {
        y = (exp(-Arguments)); // Вычисление e^-x для каждого x
    }
    else if (option == 6) {
        y = (sin(Arguments)); // Вычисление sin(x) для каждого x
    }

    return y;
}

// Функция LeftRectangular вычисляет интеграл методом левых прямоугольников.
// Принимает границы интегрирования a и b, количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
//I ≈ h * (f(a) + f(a + h) + f(a + 2h) + ... + f(a + (n-1)h))
double LeftRectangular(double a, double b, int n, int option)
{
    double h = (b - a) / n;
    double res = 0;
    for (int i = 0; i < n; i++)
        res += GetFunction(a + i * h, option) * h;
    return res;
}
// Функция LeftRectangularAuto вычисляет интеграл методом левых прямоугольников с автоматическим выбором шага.
// Принимает границы интегрирования a и b, количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
//I ≈ h * (f(a) + f(a + h) + f(a + 2h) + ... + f(a + (n-1)h))
//где h = (b - a) / n, n - количество разбиений, f(x) - подынтегральная функция.
double LeftRectangularAuto(double a, double b, double eps, int n, int option)
{
    double h = (b - a) / n;
    double res = 0;
    for (int i = 0; i < n; i++)
        res += GetFunction(a + i * h, option) * h;
    double oldres = 0;
    int count = 0;
    double err = max(1., fabs(res));
    while (err > eps) {
        oldres = res;
        res = 0;
        n *= 2;
        for (int i = 0; i < n; i++)
            res = LeftRectangular(a, b, n, option);
        count++;
        err = fabs(res - oldres);
    };
    cout << "\nЧисло вызовов: " << count << endl;
    cout << "Итоговое число n: " << n << endl;
    return res;
}

// Функция RightRectangular вычисляет интеграл методом правых прямоугольников.
// Метод правых прямоугольников
// Принимает границы интегрирования a и b, количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
//I ≈ h * (f(a + h) + f(a + 2h) + ... + f(a + nh))
double RightRectangular(double a, double b, int n, int option)
{
    double h = (b - a) / n;
    double res = 0;
    for (int i = 1; i <= n; i++)
        res += GetFunction(a + i * h, option) * h;
    return res;
}
// Функция RightRectangularAuto вычисляет интеграл методом правих прямоугольников с автоматическим выбором шага.
// Принимает границы интегрирования a и b, количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
//I ≈ h * (f(a + h) + f(a + 2h) + ... + f(a + nh))
//где h = (b - a) / n, n - количество разбиений, f(x) - подынтегральная функция.
double RightRectangularAuto(double a, double b, double eps, double n, int option)
{
    double h = (b - a) / n;
    double res = 0;
    for (int i = 1; i <= n; i++)
        res += GetFunction(a + i * h, option) * h;
    double oldres = 0;
    int count = 0;
    double err = max(1., fabs(res));
    while (err > eps) {
        oldres = res;
        res = 0;
        n *= 2;
        for (int i = 0; i < n; i++)
            res = RightRectangular(a, b, n, option);
        count++;
        err = fabs(res - oldres);
    };
    cout << "\nЧисло вызовов: " << count << endl;
    cout << "Итоговое число n: " << n << endl;
    return res;
}

// Функция Rectangular вычисляет интеграл методом средних прямоугольников.
// Принимает границы интегрирования a и b, количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
// I ≈ h * (f(a + h/2) + f(a + 3h/2) + ... + f(a + (2n-1)h/2))
double Rectangular(double a, double b, int n, int option)
{
    double h = (b - a) / n;
    double res = 0;
    for (int i = 0; i < n; i++)
        res += GetFunction(a + i * h + h / 2, option) * h;
    return res;
}

// Функция RectangularAuto вычисляет интеграл методом средних прямоугольников с автоматическим выбором шага.
// Принимает границы интегрирования a и b, требуемую точность eps, начальное количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
// I ≈ h * (f(a + h/2) + f(a + 3h/2) + ... + f(a + (2n-1)h/2))
// где h = (b - a) / n, n - начальное количество разбиений, f(x) - подынтегральная функция.
double RectangularAuto(double a, double b, double eps, int n, int option)
{
    double h = (b - a) / n;
    double res = 0;
    for (int i = 0; i < n; i++)
        res += GetFunction(a + i * h + h / 2, option) * h;
    int count = 0;
    double err = max(1., fabs(res));
    while (err > eps)
    {
        double oldres = res;
        n *= 2;
        for (int i = 0; i < n; i++)
            res = Rectangular(a, b, n, option);
        err = fabs(res - oldres);
        count++;
    }
    cout << "\nЧисло вызовов: " << count << endl;
    cout << "Итоговое число n: " << n << endl;
    return res;
}

// Функция Trapezoidal вычисляет интеграл методом трапеций.
// Принимает границы интегрирования a и b, количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
// I ≈ (h/2) * (f(a) + 2f(a + h) + 2f(a + 2h) + ... + 2f(a + (n-1)h) + f(b))
double Trapezoidal(double a, double b, int n, int option)
{
    double h = (b - a) / n;
    double res = GetFunction(a, option) + GetFunction(b, option);
    for (int i = 1; i < n; i++)
        res += 2 * GetFunction(a + i * h, option);
    res *= h / 2;
    return res;
}

// Функция TrapezoidalAuto вычисляет интеграл методом трапеций с автоматическим выбором шага.
// Принимает границы интегрирования a и b, требуемую точность eps, начальное количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
// I ≈ (h/2) * (f(a) + 2f(a + h) + 2f(a + 2h) + ... + 2f(a + (n-1)h) + f(b))
// где h = (b - a) / n, n - количество разбиений, f(x) - подынтегральная функция.
double TrapezoidalAuto(double a, double b, double eps, int n, int option)
{
    double h = (b - a) / n;
    double res = GetFunction(a, option) + GetFunction(b, option);
    for (int i = 1; i < n; i++)
        res += 2 * GetFunction(a + i * h, option);
    res *= h / 2;
    int count = 0;
    double err = max(1., fabs(res));
    while (err > eps)
    {
        double oldres = res;
        n *= 2;
        res = Trapezoidal(a, b, n, option);
        err = fabs(res - oldres);
        count++;
    }
    cout << "\nЧисло вызовов: " << count << endl;
    cout << "Итоговое число n: " << n << endl;
    return res;
}

// Функция Simpsons вычисляет интеграл методом Симпсона.
// Принимает границы интегрирования a и b, количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
// I ≈ (h/3) * (f(a) + 4f(a + h) + 2f(a + 2h) + 4f(a + 3h) + ... + 2f(a + (2n-2)h) + 4f(a + (2n-1)h) + f(b))
double Simpsons(double a, double b, int n, int option)
{
    if (n % 2 == 1)
        n += 1;
    double h = (b - a) / n;
    double res = GetFunction(a, option) + 4 * GetFunction(a + h, option) + GetFunction(b, option);
    for (int i = 1; i < n / 2; i++)
        res += 2 * GetFunction(a + (2 * i) * h, option) + 4 * GetFunction(a + (2 * i + 1) * h, option);
    res *= h / 3;
    return res;
}

// Функция SimpsonsAuto вычисляет интеграл методом Симпсона с автоматическим выбором шага.
// Принимает границы интегрирования a и b, требуемую точность eps, начальное количество разбиений n и параметр option.
// Возвращает приближенное значение интеграла.
// I ≈ (h/3) * (f(a) + 4f(a + h) + 2f(a + 2h) + 4f(a + 3h) + ... + 2f(a + (2n-2)h) + 4f(a + (2n-1)h) + f(b))
// где h = (b - a) / n, n - начальное количество разбиений, f(x) - подынтегральная функция.
double SimpsonsAuto(double a, double b, double eps, int n, int option)
{
    if (n % 2 == 1)
        n += 1;
    double h = (b - a) / n;
    double res = GetFunction(a, option) + 4 * GetFunction(a + h, option) + GetFunction(b, option);
    for (int i = 1; i < n / 2; i++)
        res += 2 * GetFunction(a + (2 * i) * h, option) + 4 * GetFunction(a + (2 * i + 1) * h, option);
    res *= h / 3;
    int count = 1;
    double err = max(1., fabs(res));
    while (err > eps)
    {
        double oldres = res;
        n *= 2;
        res = Simpsons(a, b, n, option);
        err = fabs(res - oldres) / 7;
        count++;
    }
    cout << "\nЧисло вызовов: " << count << endl;
    cout << "Итоговое число n: " << n << endl;
    return res;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int option, n, hop;
    double a, b, eps;
    cout << "Выберите режим:\n1 для постоянного разбиения\n2 для автоматического\n";
    cin >> hop;

    cout << "Функции для интегрирования:\n1). x^2 \n2). x^3 \n3). 1/x \n4). |x|\n5). e^-x\n6). sin(x)\n";
    cout << "Функция: ";
    cin >> option;

    cout << "Интервал интегрирования (a,b):\n";
    cout << "Начало для интегрирования a = ";
    cin >> a;

    cout << "Конец для интегрирования b = ";
    cin >> b;
    if (hop == 1)
    {
        cout << "Число разбиений n: ";
        cin >> n;
        cout << "\nМетод левых прямоугольников = " << LeftRectangular(a, b, n, option) << endl;
        cout << "\nМетод правых прямоугольников = " << RightRectangular(a, b, n, option) << endl;
        cout << "\nМетод прямоугольников = " << Rectangular(a, b, n, option) << endl;
        cout << "\nМетод трапеций = " << Trapezoidal(a, b, n, option) << endl;
        cout << "\nМетод Симпсона = " << Simpsons(a, b, n, option) << endl;
    }
    if (hop == 2)
    {
        cout << "Число разбиений (отрезков) n = ";
        cin >> n;

        cout << "Погрешность eps = ";
        cin >> eps;
        cout << "Метод левых прямоугольников = " << LeftRectangularAuto(a, b, eps, n, option) << endl << endl;
        cout << "Метод правых прямоугольников = " << RightRectangularAuto(a, b, eps, n, option) << endl << endl;
        cout << "Метод прямоугольников = " << RectangularAuto(a, b, eps, n, option) << endl << endl;
        cout << "Метод трапеций = " << TrapezoidalAuto(a, b, eps, n, option) << endl << endl;
        cout << "Метод Симпсона = " << SimpsonsAuto(a, b, eps, n, option) << endl << endl;
    }
}