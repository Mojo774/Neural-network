#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

float** additionMatrix(float** A, float** B) {
    int rows = _msize(A) / sizeof(A);
    int colsA = _msize(A[0]) / sizeof(A[0][0]);
    int colsB = _msize(B[0]) / sizeof(B[0][0]);
    int cols = colsA + colsB;

    float** C = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        C[i] = new float[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colsA; j++) {
            C[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = colsA; j < cols; j++) {

            C[i][j] = B[i][j - colsA];
        }
    }

    return C;
}

void toString(float** A, int rows, int cols, string name) {
    cout << name << endl << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << round(A[i][j]) << " ";
        }
        cout << endl << endl;
    }
}

float activationElement(float a) {
    a = 1 / (1 + exp((-1) * a));
    //a = tanh(a);
    return a;
}

float** activation(float** A) {
    int rows = _msize(A) / sizeof(A);
    int cols = _msize(A[1]) / sizeof(A[0][0]);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            A[i][j] = activationElement(A[i][j]);
        }
    }

    return A;
}




float** multiplicationMatrix(float** A, float** B) {
    int rows1 = _msize(A) / sizeof(A);
    int cols1 = _msize(A[1]) / sizeof(A[0][0]);
    int rows2 = _msize(B) / sizeof(B);
    int cols2 = _msize(B[0]) / sizeof(B[0][0]);

    // Проверка размеров? 2х3 3х2
    if (rows2 != cols1) { // _msize(A) / sizeof(A) != _msize(B[1]) / sizeof(B[1][1]) || 
        cout << "\nSize error\n" << rows1 << " " << cols1 << " " << rows2 << " " << cols2 << endl;
        return 0;
    }

    // Создание массива - результата
    float** C = new float* [rows1];
    for (int i = 0; i < rows1; i++)
    {
        C[i] = new float[cols2];
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            C[i][j] = 0;
        }
    }
    
    // Перемножение матриц   m X x  x X n
    
    for (int m = 0; m < rows1; m++) {
        for (int x = 0; x < rows2; x++) {
            for (int n = 0; n < cols2; n++) {
                C[m][n] += A[m][x] * B[x][n];
            }
        }
    }

    return C;
}

void deleteMatrix(float** A) {

    for (int i = 0; i < _msize(A) / sizeof(A); i++)
    {
        delete[] A[i];
    }
    delete[] A;
}

int main()
{
    // Входные данные 

    int rows = 11; // Строки
    int cols = 4; // Столбцы

    float** A = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        A[i] = new float[cols];
    }

    int A1[11][4] = { { 1, 0, 1, 0 },
                     { 0, 0, 0, 1 },
                     { 0, 0, 1, 0 },
                     { 1, 1, 0, 0 },
                     { 0, 1, 0, 0 },
                     { 0, 0, 0, 0 },
                     { 0, 1, 1, 0 },
                     { 0, 1, 1, 1 },
                     { 1, 0, 0, 0 },
                     { 1, 0, 0, 1 },
                     { 1, 1, 1, 0 } };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j] = A1[i][j];
        }
    }



    // Ожидаемый результат

    float** B = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        B[i] = new float[1];
    }

    int B1[11][1] = { { 0 },
                     { 0 },
                     { 0 },
                     { 1 },
                     { 1 },
                     { 0 },
                     { 0 },
                     { 0 },
                     { 1 },
                     { 1 },
                     { 1 } };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 1; j++) {
            B[i][j] = B1[i][j];
        }
    }

    /////////////
    // Нейроны //
    /////////////

    // Первый нейрон (1 слой)
    int k = cols; // Кол-во связей с нейроном (компонентов входных данных) 
    srand(time(0));

    float** P1 = new float* [k];
    for (int i = 0; i < k; i++)
    {
        P1[i] = new float[1];
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 1; j++) {
            P1[i][j] = ((rand() % 10) * (rand() % 10) * (rand() % 10)) / 1000.0;
        }
    }
    // Второй нейрон (1 слой)
    float** P2 = new float* [k];
    for (int i = 0; i < k; i++)
    {
        P2[i] = new float[1];
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 1; j++) {
            P2[i][j] = ((rand() % 10) * (rand() % 10) * (rand() % 10)) / 1000.0;
        }
    }
    

    /////////////////
    // Второй слой
    /////////////////


    // Первый нейрон
    k = 2+1; // Кол-во связей с нейроном (кол-во нейронов первого слоя) 

    float** P3 = new float* [k];
    for (int i = 0; i < k; i++)
    {
        P3[i] = new float[1];
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 1; j++) {
            P3[i][j] = ((rand() % 10) * (rand() % 10) * (rand() % 10)) / 1000.0;
        }
    }
    ///////////////////

// Входные данные 

    //tostring(A, _msize(A)/ sizeof(A),_msize(A[1])/ sizeof(A[1][1]), "A"); //  tostring(A, rows, cols);
    //tostring(B, _msize(B) / sizeof(B), _msize(B[1]) / sizeof(B[1][1]), "B"); //  tostring(A, rows, cols);
    //tostring(P1, _msize(P1) / sizeof(P1), _msize(P1[0]) / sizeof(P1[0][0]), "P1");
    //tostring(P2, _msize(P2) / sizeof(P2), _msize(P2[0]) / sizeof(P2[0][0]), "P2");
    //tostring(P3, _msize(P3) / sizeof(P3), _msize(P3[0]) / sizeof(P3[0][0]), "P3");






    // Проверочка методов

        //tostring(um(A, P1), rows, 1, "A*P1"); // ВД проходят через первый нейрон
        //tostring(um(A, P2), rows, 1, "A*P2"); // Через второй

        //tostring(ac(um(A, P1)), rows, 1, "A**1"); // Функция активации первого набора
        //tostring(ac(um(A, P2)), rows, 1, "A**2"); // Второго

        //tostring(sl( ac(um(A, P1)), ac(um(A, P2)) ), rows, 2, "A1+A2"); // Все что выше + объединеие выходных значений из первого и второго нейрона
        //ac(um(sl(ac(um(A, P1)), ac(um(A, P2))), P3)); // финалити, + передача на 3 нейрон и активация




    ///////////////////////////////// Выходы нейронов/////////////////////////////////////////////

        // Записываем выход первого нейрона в R1
    float** R1 = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        R1[i] = new float[1];
    }
    R1 = activation(multiplicationMatrix(A, P1));

    // Записываем выход второго нейрона в R2
    float** R2 = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        R2[i] = new float[1];
    }
    R2 = activation(multiplicationMatrix(A, P2));

   
    
    //tostring(PR4, rows, cols, "PR4");
    //tostring(P4, _msize(P4) / sizeof(P4), _msize(P4[0]) / sizeof(P4[0][0]), "P4");
    //tostring(um(PR4, P4),rows,1,"PR4*P4");

    /////////////////////////// НЕЙРОН СМЕЩЕНИЯ (его выход (единички))/////////////////////////////////////////////////
    float** R4 = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        R4[i] = new float[1];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 1; j++) {
            R4[i][j] = 1.0;
        }
        
    }
    ///////////////////////////////////////////////////////////////////
    
    //tostring(R4, _msize(R4) / sizeof(R4), _msize(R4[0]) / sizeof(R4[0][0]), "R4");

    // Записываем первый результат в R3
    float** R3 = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        R3[i] = new float[1];
    }
    //tostring(sl(sl(R1, R2), R4), _msize(sl(sl(R1, R2), R4)) / sizeof(sl(sl(R1, R2), R4)), _msize(sl(sl(R1, R2), R4)[0]) / sizeof(sl(sl(R1, R2), R4)[0][0]), "sss");
    R3 = activation(multiplicationMatrix(additionMatrix(additionMatrix(R1, R2),R4), P3));
    // R3 = ac(um(sl(ac(um(A, P1)), ac(um(A, P2))), P3));
    //tostring()
    //tostring(R1, _msize(R1) / sizeof(R1), _msize(R1[0]) / sizeof(R1[0][0]), "R1");
    //tostring(R2, _msize(R2) / sizeof(R2), _msize(R2[0]) / sizeof(R2[0][0]), "R2");
    //tostring(R3, _msize(R3) / sizeof(R3), _msize(R3[0]) / sizeof(R3[0][0]), "R3");

    // Обратное распространение ошибки
    int epoh = 12000;
    float error;
    float error1;
    float error2;
    float weights_delta;
    float learning_rate = 0.8;

    float grad;
    float weights_delta_layer;
    for (int sh = 0; sh < epoh; sh++) { // Проход по эпохам

        for (int i = 0; i < rows; i++) { // Изменение весов нейрона второго слоя (одного (он один на слое)) 
            error = (R3[i][0] - B[i][0]);
            weights_delta = error * (R3[i][0] * (1 - R3[i][0]));

            P3[0][0] = (P3[0][0] - (R1[i][0] * weights_delta * learning_rate));
            P3[1][0] = (P3[1][0] - (R2[i][0] * weights_delta * learning_rate));
            P3[2][0] = (P3[2][0] - (R4[i][0] * weights_delta * learning_rate));
        }

        // Изменение весов нейронов внутреннего  слоя 

        for (int i = 0; i < rows; i++) { // 
            error = (R3[i][0] - B[i][0]) * (R3[i][0] * (1 - R3[i][0]));
            error1 = (error * P3[0][0]);



            for (int j = 0; j < cols; j++) {
                weights_delta = error1 * (R1[i][0] * (1 - R1[i][0]));

                P1[j][0] = (P1[j][0] - (activationElement(A[i][j]) * weights_delta * learning_rate));
            }

            error2 = (error * P3[1][0]);

            for (int j = 0; j < cols; j++) {
                weights_delta = error2 * (R2[i][0] * (1 - R2[i][0]));

                P2[j][0] = (P2[j][0] - (activationElement(A[i][j]) * weights_delta * learning_rate));
            }
        }

        R1 = activation(multiplicationMatrix(A, P1));
        R2 = activation(multiplicationMatrix(A, P2));
        R3 = activation(multiplicationMatrix(additionMatrix(additionMatrix(R1, R2), R4), P3));
    }

    //R1 = ac(um(A, P1));
    //R2 = ac(um(A, P2));
    //R3 = ac(um(sl(R1, R2), P3));
   // tostring(P1, _msize(P1) / sizeof(P1), _msize(P1[0]) / sizeof(P1[0][0]), "P1");
    //tostring(P2, _msize(P2) / sizeof(P2), _msize(P2[0]) / sizeof(P2[0][0]), "P2");
   // tostring(P3, _msize(P3) / sizeof(P3), _msize(P3[0]) / sizeof(P3[0][0]), "P3");
    //tostring(R3, _msize(R3) / sizeof(R3), _msize(R3[0]) / sizeof(R3[0][0]), "R3");
   // tostring(R3, rows, 1, "Delo sdelano"); // финалити, + передача на 3 нейрон и активация


    // Новые данные

    rows = 6;
    cols = 4;

    float** A2 = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        A2[i] = new float[cols];
    }

    // Логика такая же как и на входных данных
    int A_2[6][4] = { { 0, 1, 0, 1 },
                     { 1, 0, 1, 1 },
                     { 1, 1, 0, 0 },
                     { 1, 1, 0, 1 },
                     { 1, 1, 1, 0 },
                     { 1, 1, 1, 1 } };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A2[i][j] = A_2[i][j];
        }
    }
    R1 = activation(multiplicationMatrix(A2, P1));
    R2 = activation(multiplicationMatrix(A2, P2));
    R3 = activation(multiplicationMatrix(additionMatrix(additionMatrix(R1, R2), R4), P3));

    toString(R3, rows, 1, "Delo sdelano");















    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(R1);
    deleteMatrix(R2);
    deleteMatrix(R3);
    deleteMatrix(P1);
    deleteMatrix(P2);
    deleteMatrix(P3);
    deleteMatrix(A2);
    return 0;
}


