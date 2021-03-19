#include <iostream>
#include "bbv.h"
using namespace std;

bbv::bbv()//по умолчанию
{
    len = 16;
    size = 2;
    bits = new unsigned char[size];
    for (int i = 0; i < size;i++)
        bits[i] = 0;
}
bbv::bbv(int i)//с заданой длиной
{
    len = i;
    size = len / 8;
    if (len % 8 != 0)
        size++;
    bits = new unsigned char[size];
    for (int i = 0; i < size;i++)
        bits[i] = 0;   
}
bbv::bbv(bbv& obj)//копирование
{
    len = obj.len;
    size = obj.size;
    bits = new unsigned char[size];
    for (int i = 0; i < size; i++)
        bits[i] = obj.bits[i];        
}
bbv::bbv(char* str)//из строки
{
    if (str)
    {
        //узнаем размер
        len = 0;
        for (char* ptr = str; *ptr; ptr++)
            len++;
        size = len / 8;
        if (len % 8 != 0)
            size++;
        //создаем массив
        bits = new unsigned char[size];
        for (int i = 0; i < size; i++)
            bits[i] = 0;
        //заполняем
        unsigned char m = 1;
            for (int j = 0; *str;j++)			//заполнение ячеек
            {
                unsigned char mask = 1;
                for (int i = 0; i < 8 && *str; i++, str++, mask = mask << 1)//записываем значение строки в бит
                {
                    if (*str - 48)//если не 0
                        bits[j] |= mask;
                }
            }    
    }
}
bbv::bbv(std::string& str)//конструктор из строки
{
	if (str.length())
	{
		len = str.length();

		size = len / 8;
		if (len % 8 != 0)
			size++;

		bits = new unsigned char[size];
		for (int i = 0; i < size; bits[i++] = 0);

		for (int j = 0, k = 0; str[k]; j++)
		{
			unsigned char mask = 1;
			for (int i = 0; i < 8 && str[k]; i++, k++, mask = mask << 1)
			{
				if (str[k] - 48)//если элемент строки не равен нулю
					bits[j] |= mask;
			}
		}
	}
bbv::bbv(char* str, int LEN)//из строки с заданной длиной
{
    if (str && len > 0)
    {
        len = LEN;
        size = len / 8;

        if (len % 8)
            size++;
        //создаем массив
        for (int i = 0; i < size; i++)
            bits[i] = 0;
        //заполняем
            for (int i = 0; i < len && *str; i++, str++)
            {
                unsigned char mask = 1;
                for (int j = 0; j < 8 && i < len && *str; i++, str++, j++, mask <<= 1)
                    if (*str - 48)
                        bits[i] |= mask;
            }
    }
}
int bbv:: getLength()
{
    return len;
}
int bbv::getSize()
{
    return size;
}
void bbv::set0(int i)
{
    if (i >= 0 && i < len)
    {
        int j = i / 8;        
        unsigned char mask = 1 << (i % 8);
        bits[j] &= ~mask;
        return;
    }
    throw "wrong i";
}
void bbv::set0(int i, int n=1)//с i позиции обнуляем n знаков
{
    if (i > -1 && n > -1 && (i + n-1) < len)
    {
    
            int b1 = i / 8;//первый байт
            int p1 = i % 8;
            int b2 = (i + n) / 8;//последний байт
            int p2 = (i + n) % 8;
                unsigned char mask1;
                mask1 = 1 << p1;
                if (b1 == b2)
                {
                    for (int k = p1+1; k < p2; k++)
                        mask1 = mask1 | (mask1 << 1);
                    mask1 = ~mask1;//устанавливаем первый байт-маску
                    bits[b1] &= mask1;
                 }
                else
                {
                    for (int k = p1; k < 8; k++)
                        mask1 = mask1 | (mask1 << 1);
                    mask1 = ~mask1;//устанавливаем первый байт-маску
                    bits[b1] &= mask1;
                    unsigned char mask2;
                    mask2 = 1 << p2-1;
                    for (int k = p2; k > 0; k--)
                        mask2 = mask2 | (mask2 >> 1);
                    mask2 = ~mask2; //устанавливаем последний байт-маск
                    for (int i = b1 + 1; i < b2; i++)
                        bits[i] = 0;
                    bits[b2] &= mask2;
                    return;
                }
    }
    else throw 1;
}
void bbv::set1(int i)
{
    if (i >= 0 && i < len)
    {
        int j = i / 8;
        unsigned char mask = 1 << (i % 8);
        bits[j] |= mask;
        return;
    }
    throw "wrong i";
}
void bbv::set1(int i, int n = 1)//с i позиции обращаем в единицу n знаков
{
    if (i > -1 && n > -1 && (i + n - 1) < len)
    {

            int b1 = i / 8;//первый байт
            int p1 = i % 8;
            unsigned char mask1 = 0;
            mask1 = 1 << p1;
            int b2 = (i + n) / 8;//последний байт
            int p2 = (i + n) % 8;
            if (b1 == b2)
            {
                for (int k = p1 + 1; k < p2; k++)
                    mask1 = mask1 | (mask1 << 1);
                bits[b1] |= mask1;
            }
            else
            {
                for (int k = p1 + 1; k < 8; k++)
                    mask1 = mask1 | (mask1 << 1);
                bits[b1] |= mask1;//устанавливаем первый байт-маску
                unsigned char mask2 = 0;
                mask2 = 1 << p2-1;
                for (int k = p2; k > 0; k--)
                    mask2 = mask2 | (mask2 >> 1);
                bits[b2] |= mask2;//устанавливаем последний байт-маску
                for (int i = b1 + 1; i < b2; i++)
                    bits[i] = 255;
                return;
            }
    }
    else throw 1;
}
void bbv::inversion(int i)
{
    if (i > -1 && i < len)
    {
        int b = i / 8;
        unsigned char mask = 1 << (i % 8);

        bits[b] ^= mask;
        return;
    }
    throw "memory error";
}
void bbv::inversion(int i, int n = 1)//с i позиции инвертируем n знаков
{
    if (i > -1 && n > -1 && (i + n - 1) < len)
    {

        int b1 = i / 8;//первый байт
        int p1 = i % 8;
        unsigned char mask1 = 0;
        mask1 = 1 << p1;
        int b2 = (i + n) / 8;//последний байт
        int p2 = (i + n) % 8;
        if (b1 == b2)
        {
            for (int k = p1+1; k < p2; k++)
                mask1 = mask1 | (mask1 << 1);
            bits[b1] ^= mask1;
        }
        else
        {
            for (int k = p1 + 1; k < 8; k++)
                mask1 = mask1 | (mask1 << 1);
            bits[b1] ^= mask1;//устанавливаем первый байт-маску
            unsigned char mask2 = 0;
            mask2 = 1 << p2;
            for (int k = p2; k > 0; k--)
                mask2 = mask2 | (mask2 >> 1);
            bits[b2] ^= mask2;//устанавливаем последний байт-маску
            for (int i = b1 + 1; i < b2; i++)
                bits[i] ^= 255;
            return;
        }
    }
    else throw 1;
}
int bbv::weight()//кол-во единиц
{
    int res = 0;
    for (int i = 0, k = 0; i < len; k++)
    {
        unsigned char mask = 1;
        for (int j = 0; j < 8 && i < len; j++, i++, mask <<= 1)
            if (bits[k] & mask)
                res++;
    }
    return res;
}
bbv::~bbv()//деструктор
{
    delete[]bits;
    len = 0;
    bits = 0;
    bits = nullptr;
}
//перегрузки
bbv& bbv::operator = (const bbv& obj)//присвоение
{
    if (this != &obj)
    {
        delete[] bits;
        len = obj.len;
        size = obj.size;
        bits = new unsigned char[size];
        for (int i = 0; i < size; i++)
            bits[i] = obj.bits[i];
    }
    return *this;
}
bbv bbv::operator | (bbv& obj)
{
    if (len == obj.len)
    {
        bbv result;
        result.len = len;
        result.size = size;
        result.bits = new unsigned char[size];

        for (int i = 0; i < size; result.bits[i] = bits[i] | obj.bits[i], i++);

        return result;
    }
    throw "2";
}
bbv& bbv::operator |= (bbv& obj)
{
    if (len == obj.len)
    {
        for (int i = 0; i < size; bits[i] |= obj.bits[i], i++);

        return *this;
    }
    throw "2";
}
bbv bbv::operator & (bbv& obj)
{
    if (len == obj.len)
    {
        bbv result;
        result.len = len;
        result.size = size;
        result.bits = new unsigned char[size];

        for (int i = 0; i < size; result.bits[i] = bits[i] & obj.bits[i], i++);

        return result;
    }
    throw "2";
}
bbv& bbv::operator &= (bbv& obj)
{
    if (len == obj.len)
    {
        for (int i = 0; i < size; bits[i] &= obj.bits[i], i++);

        return *this;
    }
    throw "2";
}
bbv bbv::operator ^ (bbv& obj)
{
    if (len == obj.len)
    {
        bbv result;
        result.len = len;
        result.size = size;
        result.bits = new unsigned char[size];

        for (int i = 0; i < size; result.bits[i] = bits[i] ^ obj.bits[i], i++);

        return result;
    }
    throw "2";
}
bbv& bbv::operator ^= (bbv& obj)
{
    if (len == obj.len)
    {              
        for (int i = 0; i < size; bits[i] = bits[i] ^ obj.bits[i], i++);
               return *this;
    }
    throw "2";
}
bbv bbv::operator ~ ()
{
    bbv result(len);
    for (int i = 0; i < size; i++)
        result.bits[i] = ~bits[i];
    return result;
}
bbv::bitK::bitK(unsigned char* BAIT, unsigned char MASK)//передаем байт и маску с 1 в бите
{
    bait = BAIT;
    mask = MASK;
}

bbv::bitK& bbv::bitK::operator ~ ()//инвертируем нужный бит в байте
{
    *bait ^= mask;

    return *this;
}

bbv::bitK& bbv::bitK::operator = (const bbv::bitK& obj)//a[1]=a[5]
{
    if (*(obj.bait) & obj.mask)//если у обьекта есть такие байт и бит
    {
        *bait |= mask;//прибавляем маску, т.е в 1 
        return *this;
    }
    *bait &= ~mask;//умножаем на инвертированную маску, т.е в 0
    return *this;
}

bbv::bitK& bbv::bitK::operator = (bool x)
{
    if (x)//если 1
        *bait |= mask;//прибавляем маску, т.е в 1 
    else
        *bait &= ~mask;//умножаем на инвертированную маску, т.е в 0

    return *this;
}
std::ostream& operator << (std::ostream& out, bbv::bitK& obj)
{
    if (*(obj.bait) & obj.mask)
        out << '1';
    else
        out << '0';
    return out;
}

std::istream& operator >> (std::istream& in, bbv::bitK& obj)
{
    char a;
    in >> a;

    if (a - 48)
        *(obj.bait) |= obj.mask;
    else
        *(obj.bait) &= obj.mask;

    return in;
}
bbv::bitK::operator bool()
{
    if (*bait & mask)//если 1 в бите
        return true;
    return false;//если 0
}
bbv::bitK bbv::operator [] (int N)
{
    int n = N / 8;//байт
    int k = N % 8;//бит

    bitK res(bits + n, 1 << k);//передаем байт и бит

    return res;
}
bbv& bbv::operator >>= (int N)//сдвигаем на н
{
    if (N >= len)//если выходит за пределы вектора сразу 0
    {
        for (int i = 0; i < size; bits[i++] = 0);
    }
    else
    {
        unsigned char b1, b2;
        for (int j = 0; j < N; j++)
        {
            b1 = 0;
            b2 = 0;
            for (int i = size - 1; i > -1; i--)
            {
                b1 = bits[i] << 7;//записываем переносимый бит для следующего байта
                bits[i] = bits[i] >> 1;//сдвигаем
                bits[i] |= b2;//прибавляем переносимый бит с прошлого байта
                b2 = b1;//запоминаем бит для следующего байта
            }
        }
    }
   return *this;
}
bbv bbv::operator >> (int N)
{
    bbv res(len);
    if (N >= len)
    {
        for (int i = 0; i < size; res.bits[i++] = 0);
    }
    else
    {
        unsigned char b1, b2;
        for (int j = 0; j < N; j++)
        {
            b1 = 0;
            b2 = 0;
            for (int i = size - 1; i > -1; i--)
            {
                b1 = bits[i] << 7;
                res.bits[i] = bits[i] >> 1;
                res.bits[i] |= b2;
                b2 = b1;
            }
        }
    }
    return res;
}
bbv& bbv::operator <<= (int N)
{
    if (N >= len)
    {
        for (int i = 0; i < size; bits[i++] = 0);
    }
    unsigned char b1, b2;
    for (int j = 0; j < N; j++)
    {
        b1 = 0;
        b2 = 0;
        for (int i = 0; i <size; i++)
        {
            b1 = bits[i] >> 7;
            bits[i] = bits[i] << 1;
            bits[i] |= b2;
            b2 = b1;
        }
        if (len % 8)//обрабатываем последний байт
        {
            unsigned char mask = (1 << (len % 8)) - 1;
            bits[size - 1] &= mask;
        }
    }
    return *this;
}
bbv bbv::operator << (int N)
{
    bbv res(len);
    if (N >= len)
    {
        for (int i = 0; i < size; res.bits[i++] = 0);
    }
    unsigned char b1, b2;
    for (int j = 0; j < N; j++)
    {
        b1 = 0;
        b2 = 0;
        for (int i = 0; i < size; i++)
        {
            b1 = bits[i] >> 7;
            res.bits[i] = bits[i] << 1;
            res.bits[i] |= b2;
            b2 = b1;
        }
        if (len % 8)//обрабатываем последний байт
        {
            unsigned char mask = (1 << (len % 8)) - 1;
            bits[size - 1] &= mask;
        }
    }
    return res;
}
bool bbv::operator ==(bbv& obj)
{
    if (size == obj.size)
    {
        for (int i = 0; i < size && bits[i] == obj.bits[i]; i++)

            if (i == size)//если все байты равны
                return true;
        
    }
    return false;//если какая то пара байтов не равно или если длины не совпадают
}
bbv::operator char* ()
{
    char* str = new char[len + 1];//память

    for (int i = 0, k = 0; i < len; k++)
    {
        unsigned char mask = 1;
        for (int j = 0; j < 8; j++, i++, mask <<= 1)
            if (bits[k] & mask)
                str[i] = '1';//если в бите 1
            else
                str[i] = '0';//если в бите 
    }

    str[len] = '\0';

    return str;
}
bbv::operator string()
{
    std::string str;
    str.resize(len + 1);

    for (int i = 0, k = 0; i < len; k++)
    {
        unsigned char mask = 1;
        for (int j = 0; j < 8; j++, i++, mask <<= 1)
            str[i] = bits[k] & mask + 48;
    }

    str[len] = '\0';

    return str;
}
bool bbv::operator != (bbv& obj)
{
    if (len == obj.len)
    {
        int i;
        for (i = 0; i < size && bits[i] == obj.bits[i]; i++);

        if (i == size)
            return false;//если все пары байтов равны
    }
    return true;//если какая-то пара не равна или если длины не равны
}
std::ostream& operator << (std::ostream& out, bbv& obj)
{
    int p = obj.len % 8;
    int i = obj.size - 1;
    if (p)//если последний байт не полный обрабатываем отдельно
    {
        unsigned char mask = 1 << (p - 1);
        for (int j = 0; j < p; j++, mask >>= 1)
            if (obj.bits[i] & mask)
                std::cout << '1';
            else
                std::cout << '0';
        cout << '.';
        i--;
    }

    for (; i > -1; i--)//обрабатываем полные байты
    {
        unsigned char mask = 1 << 7;
        for (int j = 0; j < 8; j++, mask >>= 1)
            if (obj.bits[i] & mask)
                std::cout << '1';
            else
                std::cout << '0';
        cout << '.';
    }

    return out;
}
std::istream& operator >> (std::istream& in, bbv& obj)
{
    if (obj.bits)
        delete[] obj.bits;//освобождаем память

    std::string str;

    std::getline(in, str);//вводим строку
    obj.len = str.length();//длина
    obj.size = obj.len / 8;//размер

    obj.bits = new unsigned char[obj.size];//выделяем память

    for (int i = 0, k = 0; i < obj.len; k++)
    {
        unsigned char mask = 1;
        for (int j = 0; j < 8 && i < obj.len; i++, j++, mask <<= 1)
        {
            if (str[i] - 48)//если не 0
                obj.bits[k] |= mask;//то 1
            else
                obj.bits[k] &= ~mask;
        }
    }

    return in;
}
//void bbv:: print()
//{
//    for (int i = size-1; i > -1; i--)
//        cout << (int)bits[i] << ' ';
//    cout << endl;
//}

