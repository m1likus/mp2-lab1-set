// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"

TBitField::TBitField(size_t len)
{
    bitLen = len;
    if (len % (sizeof(uint) * 8) != 0)
        memLen = len / (sizeof(uint) * 8) + 1;
    else
        memLen = len / (sizeof(uint) * 8);
    pMem = new uint[memLen];
    memset(pMem, 0, memLen);
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    uint capacity = 8 * sizeof(pMem[0]);
    uint indexBit = n / capacity;
    return indexBit;
}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    uint mask = ~(1 << n);
    return mask;
}

// доступ к битам битового поля
uint TBitField::getLength() const // получить длину (к-во битов)
{
    return bitLen;
}

size_t TBitField::getNumBytes() const // получить количество байт выделенной памяти
{
    return memLen * sizeof(uint);
}

void TBitField::setBit(const size_t n) // установить бит
{

}

void TBitField::clrBit(const size_t n) // очистить бит
{

}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    return false;
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return TBitField(1);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return TBitField(1);
}

TBitField TBitField::operator~() // отрицание
{
    return TBitField(1);
}

TBitField::~TBitField()
{

}

// ввод/вывод
std::istream &operator>>(std::istream &istr, TBitField &bf) // ввод
{
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
