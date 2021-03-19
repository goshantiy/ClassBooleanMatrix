#pragma once
#include <iostream>
#include <string>
using namespace std;
class boolMatrix;
class bbv 
{
public:
friend boolMatrix;
	class bitK
	{
	public:
		bitK(unsigned char* BAIT, unsigned char MASK);

		bitK& operator ~ ();

		bitK& operator = (const bitK& obj);

		bitK& operator = (bool x);	
		operator bool();
		friend std::istream& operator >> (std::istream& in, bitK& obj);
		friend std::ostream& operator << (std::ostream& out, bitK& obj);

	private:
		unsigned char* bait;
		unsigned char mask;
	};
	bbv();
	explicit bbv(int len);
	bbv(bbv& obj);
	explicit bbv(char* str);
	explicit bbv(char* str, int LEN);
	explicit bbv(std::string& str);
	~bbv();
	int getLength();
	int getSize();
	void set0(int i);
	void set0(int i, int n);
	void set1(int i);
	void set1(int i, int n);
	void inversion(int i);
	void inversion(int i,int n);
	int weight();
	void print();
	bbv& operator = (const bbv& obj); 
	bbv operator & (bbv& obj); 
	bbv& operator &= (bbv& obj);
	bbv operator | (bbv& obj);
	bbv& operator |= (bbv& obj);
	bbv operator ^ (bbv& obj); 
	bbv& operator^= (bbv& obj);
	bbv operator ~ ();
	bool operator == (bbv& obj);
	bitK operator [](int n);
	bbv operator >>(int n) ;
	bbv operator <<(int n) ;
	bbv& operator <<=(int n); 
	bbv& operator >>=(int n); 
	operator string();
	bool operator != (bbv& obj);
	operator char* ();
	friend std::istream& operator >> (std::istream& in, bbv& obj);
	friend std::ostream& operator << (std::ostream& out, bbv& obj);
	
private:
	int size;
    int len;
	unsigned char* bits;
};

class bbv
{
};
