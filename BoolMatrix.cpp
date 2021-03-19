#include <iostream>
#include "BoolMatrix.h"
using namespace std;

boolMatrix::boolMatrix()
{
    row = 8;
    column = 8;
    matrix = new bbv *[row];
    for (int i = 0; i < row; i++)
        matrix[i] = new bbv[column];
}

boolMatrix::boolMatrix(int r, int c)
{
    if (r < 1 || c < 1)
    {
        r = 8;
        c = 8;
    }
    row = r;
    column = c;
    matrix = new bbv *[row];
    for (int i = 0; i < row; i++)
        matrix[i] = new bbv[column];
}

boolMatrix::boolMatrix(char** m, int r, int c)
{
    if (r < 1 || c < 1)
    {
        r = 8;
        c = 8;
        matrix = nullptr;
    }
    row = r;
    column = c;
    matrix = new bbv *[row];
    if (m)
        for (int i = 0; i < row; i++)
            matrix[i] = new bbv(m[i], column);
}

boolMatrix::boolMatrix(boolMatrix& obj)
{
    row = obj.row;
    column = obj.column;
    matrix = new bbv * [row];
    for (int i = 0; i < row; i++)
        matrix[i] = new bbv(obj[i]);
}

boolMatrix::~boolMatrix()
{
    for (int i = 0; i < row; i++)
        delete matrix[i];
    delete[] matrix;
    matrix = nullptr;
    row = 0;
    column = 0;
}

int boolMatrix::GetRows()
{
    return row;
}
int boolMatrix::GetColumns()
{
    return column;
}
int boolMatrix::Weight()
{
    int result = 0;
    for (int i = 0; i < row; i++)
       result+=matrix[i]->weight();
    return result;
}
int boolMatrix::WeightOfRow(int i)
{
    return matrix[i]->weight();
}
void boolMatrix::Set0(int start, int len, int n)
{
    matrix[n]->set0(start, len);
}
void boolMatrix::Set1(int start, int len, int n)
{
    matrix[n]->set1(start, len);
}
void boolMatrix::Inversion(int start, int len, int n)
{
    matrix[n]->inversion(start, len);
}
bbv boolMatrix::Conjunction()
{
    bbv result(column);
    for (int i = 0; i < row; i++)
        result &= *matrix[i];
    return result;
}
bbv boolMatrix::Disjunction()
{
    bbv result(column);
    for (int i = 0; i < row; i++)
        result |= *matrix[i];
    return result;
}

boolMatrix& boolMatrix::operator= (const boolMatrix& obj)
{
    if (row != obj.row)
    {
        this->~boolMatrix();
        row = obj.row;
        matrix = new bbv *[row];
        for (int i = 0; i < row; i++)
            matrix[i] = new bbv;
    }
    column = obj.column;
    for (int i = 0; i < row; i++)
        *matrix[i] = *obj.matrix[i];
    return *this;
}

boolMatrix boolMatrix::operator&(const boolMatrix& obj)
{
    if (row == obj.row && column == obj.column)
    {
        boolMatrix result(row, column);
        int size = column / 8;
        if (column % 8)
            size++;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < size; j++)
               result.matrix[i]->bits[j] = matrix[i]->bits[j] & obj.matrix[i]->bits[j];
        }
        return result;
    }
    throw"wrong rows/columns size";
}

boolMatrix& boolMatrix::operator&=(const boolMatrix& obj)
{
    if (row == obj.row && column == obj.column)
    {
        int size = column / 8;
        if (column % 8)
            size++;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < size; j++)
            matrix[i]->bits[j] &= obj.matrix[i]->bits[j];
        }
        return *this;
    }
    throw"wrong rows/columns size";
}

boolMatrix boolMatrix::operator|(const boolMatrix& obj)
{
    if (row == obj.row && column == obj.column)
    {
        boolMatrix result(row, column);
        int size = column / 8;
        if (column % 8)
            size++;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < size; j++)
                result.matrix[i]->bits[j] = matrix[i]->bits[j] | obj.matrix[i]->bits[j];
        }
        return result;
    }
    throw"wrong rows/columns size";
}

boolMatrix& boolMatrix::operator|=(const boolMatrix& obj)
{
    if (row == obj.row && column == obj.column)
    {
               int size = column / 8;
        if (column % 8)
            size++;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < size; j++)
                matrix[i]->bits[j] |= obj.matrix[i]->bits[j];
        }
        return *this;
    }
    throw"wrong rows/columns size";
}

boolMatrix boolMatrix::operator^(const boolMatrix& obj)
{
    if (row == obj.row && column == obj.column)
    {
        boolMatrix result(row, column);
        int size = column / 8;
        if (column % 8)
            size++;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < size; j++)
                result.matrix[i]->bits[j] = matrix[i]->bits[j] ^ obj.matrix[i]->bits[j];
        }
        return result;
    }
    throw"wrong rows/columns size";
}

boolMatrix& boolMatrix::operator^=(const boolMatrix& obj)
{
    if (row == obj.row && column == obj.column)
    {
        int size = column / 8;
        if (column % 8)
            size++;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < size; j++)
                matrix[i]->bits[j] ^= obj.matrix[i]->bits[j];
        }
        return *this;
    }
    throw"wrong rows/columns size";
}

boolMatrix boolMatrix::operator ~()
{
    boolMatrix result(row, column);
    int size = column / 8;
    if (column % 8)
        size++;
    for(int i=0;i<row;i++)
        for (int j = 0; j < size; j++)
        {
            result.matrix[i]->bits[j] = ~matrix[i]->bits[j];

            if (matrix[i]->len % 8)//последний байт
            {
                int bait = matrix[i]->len % 8;
                unsigned char mask = (1 << bait) - 1;
                result.matrix[i]->bits[size - 1] ^= mask;
            }
        }
    return result;
}

bbv& boolMatrix::operator [] (int i)
{
    if (i > -1 && i < row)
        return *matrix[i];
    throw "wrong index";
}
boolMatrix::operator bool()
{
   bbv res(column);

    for (int i = 0; i < row; i++)
        res |= *matrix[i];

    if (res)
        return true;
    return false;
}

bool boolMatrix::operator == (const boolMatrix& obj)
{
    if (row == obj.row && column == obj.column)
    {
        for (int i = 0; i < row; i++)
            if (*(matrix[i]) != *(obj.matrix[i]))
                return false;
        return true;
    }
    return false;
}

std::istream& operator >> (std::istream& in, boolMatrix& obj)
{
    if (obj.matrix)
    {
        for (int i = 0; i < obj.row; i++)
            delete obj.matrix[i];
        delete[] obj.matrix;
    }

    in >> obj.row >> obj.column;

    obj.matrix = new bbv * [obj.row];

    in.get();
    for (int i = 0; i < obj.row; i++)
    {
        std::string str;
        std::getline(in, str);
        obj.matrix[i] = new bbv(str);
    }

    return in;
}

std::ostream& operator << (std::ostream& out, const boolMatrix& obj)
{
    for (int i = 0; i < obj.row; i++)
        out << *obj.matrix[i] << std::endl;
    return out;
}

int main()
{
    boolMatrix a();
    cout << a;
}

