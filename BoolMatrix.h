#pragma once
#include "bbv.h"
#include <string.h>
class boolMatrix
{
	boolMatrix();
	boolMatrix(int, int);
	boolMatrix(char**, int, int);
	boolMatrix(boolMatrix&);
	~boolMatrix();
	boolMatrix& operator = (const boolMatrix&);
	boolMatrix operator & (const boolMatrix&);
	boolMatrix& operator &= (const boolMatrix&);
	boolMatrix operator | (const boolMatrix&);
	boolMatrix& operator |= (const boolMatrix&);
	boolMatrix operator ^ (const boolMatrix&);
	boolMatrix& operator ^= (const boolMatrix&);
	boolMatrix operator ~ ();
	operator bool();
	bbv& operator [](int);
	bool operator == (const boolMatrix&);
	bbv Conjunction();
	bbv Disjunction();
	void Set0(int, int, int);
	void Set1(int, int, int);
	void Inversion(int, int, int);
	int WeightOfRow(int);
	int Weight();
	int GetRows();
	int GetColumns();
	friend std::istream& operator >> (std::istream&,  boolMatrix& obj);
	friend std::ostream& operator << (std::ostream&, const boolMatrix& obj);

private:
	bbv** matrix;
	int row;
	int column;
};

