// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"
#include <string>

TBitField::TBitField(size_t len)
{
    bitLen = len;
    if (len % (sizeof(uint) * 8) != 0)
        memLen = len / (sizeof(uint) * 8) + 1;
    else
        memLen = len / (sizeof(uint) * 8);
    pMem = new uint[memLen];
    //for (int i = 0; i < memLen; i++) pMem[i] = 0;
    memset(pMem, 0, memLen*sizeof(uint));
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
    if (n > bitLen) throw(1);
    else {
        uint capacity = 8 * sizeof(pMem[0]);
        size_t indexBit = (n / capacity);
        return indexBit;
    }
}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    int capacity = sizeof(pMem[0]) * 8;
    uint mask = 1 << (n % capacity);
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
    if (n > bitLen) throw(1);
    pMem[getIndex(n)] |= getMask(n);
}

void TBitField::clrBit(const size_t n) // очистить бит
{
    if (n > bitLen) throw(1);
    pMem[getIndex(n)] &= ~getMask(n);
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    if (n > bitLen) throw(1);
    if (pMem[getIndex(n)] & getMask(n)) return true;
    else false;
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        this->bitLen = bf.bitLen;
        this->memLen = bf.memLen;
        delete[] pMem;
        pMem = new uint[memLen];
        for (int i = 0; i < memLen; i++) this->pMem[i] = bf.pMem[i];
    }
    return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bitLen != bf.bitLen) return false;
    else {
        for (int i = 0; i < memLen; i++)
            if (pMem[i] != bf.pMem[i]) return false;
    }
    return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (bitLen != bf.bitLen) return true;
    else {
        for (int i = 0; i < memLen; i++)
            if (pMem[i] != bf.pMem[i]) return true;
    }
    return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    //костыли на случай если дело все в max и min
    /*uint mmax = 0, mmin = 0;
    if (bitLen > bf.bitLen) {
        mmax = bitLen;
        mmin = bf.bitLen;
    }
    else {
        mmax = bf.bitLen;
        mmin = bitLen;
    }*/
    TBitField or (std::max( bitLen,bf.bitLen ));
    //TBitField or (mmax);
    for (int i = 0; i < std::min(memLen, bf.memLen); i++) {
    //for (int i = 0; i < mmin; i++) {
        or.pMem[i] = this->pMem[i] | bf.pMem[i];
    }
    return or;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    //костыли на случай если дело все в max и min
    /*uint mmax = 0,mmin =0;
    if (bitLen > bf.bitLen) {
        mmax = bitLen;
        mmin = bf.bitLen;
    }
    else {
        mmax = bf.bitLen;
        mmin = bitLen;
    }*/
    TBitField and (std::max(bitLen, bf.bitLen));
    //TBitField and (mmax);
    for (int i = 0; i < std::min(memLen, bf.memLen); i++) {
    //for (int i = 0; i < mmin; i++){
        and.pMem[i] = this->pMem[i] & bf.pMem[i];
    }
    return and;
}

TBitField TBitField::operator~() // отрицание
{
    size_t capacity = sizeof(pMem[0]) * 8;
    TBitField invert(bitLen);
    for (int i = 0; i < memLen-1; i++) {
        invert.pMem[i] = ~pMem[i];
    }
    //uint mask = ~0;
    uint mask = 0;
    for (int i = 0; i < bitLen % capacity; i++) {
        mask  |= 1 << i;
    }
    //mask = 1 >> (bitLen % capacity);
    invert.pMem[memLen-1] = pMem[memLen-1] ^ mask;
    return invert;
}

TBitField::~TBitField()
{
    delete[] pMem;
    memLen = 0;
    bitLen = 0;
}

// ввод/вывод
std::istream &operator>>(std::istream &istr, TBitField &bf) // ввод
{
    std::string str;
    size_t length;
    istr >> length>> str;
    bf.bitLen = length;
    int capacity = 8 * sizeof(uint);
    bf.memLen = (bf.getLength() / capacity);
    for (int i = 0; i < str.size(); i++)
        if (bool(str[i])) bf.setBit(i);
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    ostr << "Length of bit field: " << bf.getLength() << "\n";
    ostr << "Length of array of bit field: " << bf.getIndex(bf.getLength())+1 << "\n";
    ostr << "Bit field: \n";
    int capacity = 8 * sizeof(bf.pMem[0]);
    for (int i = 0; i < bf.getIndex(bf.getLength()); i++) {
        for (int j = 0; j < bf.getLength() % capacity;j++) {
            ostr << bf.getBit(j);
        }
    }
    return ostr;
}
