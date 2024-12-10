#include "Matrices.h"


namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        /*
        a.resize(_rows);
        for (int i = 0; i < a.size(); i++)
        {
            a[i] = vector<double>(_cols);
            for (int j = 0; i < a[i].size(); j++)
            {
                a[i][j] = 0;
            }
        }
        */

        a = vector<vector<double>>(_rows, vector<double>(_cols, 0));        // This is a simpler condensed version of the above for loops
        rows = _rows;
        cols = _cols;

    }


    ///Add each corresponding element.
    ///usage:  c = a + b;
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() ||
            a.getCols() != b.getCols()) 
            throw runtime_error("Error: dimensions must agree");

        Matrix sum(a.getRows(), a.getCols());

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                sum(i, j) = a(i, j) + b(i, j);
            }
        }
        return sum;
    }

    ///Matrix multiply.  See description.
    ///usage:  c = a * b;
    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows()) 
            throw runtime_error("Error: dimensions must agree");

        Matrix product(a.getRows(), b.getCols());

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getCols(); j++)
            {
                product(i, j) = 0;
                for (int k = 0; k < a.getCols(); k++)
                {
                    product(i, j) += a(i, k) * b(k, j);
                }
            }
        }
        return product;
    }

    ///Matrix comparison.  See description.
    ///usage:  a == b
    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) return false;

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getRows(); j++)
            {
                if (abs(a(i, j) - b(i, j)) >= 0.001)
                {
                    //cout << "i: " << i << " " << "j: " << j << endl;      // This is just a test line to check if the program gets here
                    return false;
                }
            }
        }
        return true;
    }

    ///Matrix comparison.  See description.
    ///usage:  a != b
    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }

    ///Output matrix.
    ///Separate columns by ' ' and rows by '\n'
    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(10+j) << a(i, j);
            }
            os << endl;
        }
        return os;
    }

    // RotationMatrix constructor definition
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {
        a[0][0] = cos(theta);
        a[0][1] = -sin(theta);
        a[1][0] = sin(theta);
        a[1][1] = cos(theta);
    }

    // ScalingMatrix constructor definition
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {
        a[0][0] = scale;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = scale;
    }

    // TranslationMatrix constructor definition
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) {
        for (int i = 0; i < nCols; i++) {
            a[0][i] = xShift;
            a[1][i] = yShift;
        }
    }

}