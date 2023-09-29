// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля

#include <iostream>
#include "tbitfield.h"
#include "tset.h"

TSet::TSet(size_t mp) : bitField(mp) {
    maxPower = bitField.getLength();
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField), maxPower(s.maxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf), maxPower(bf.getLength()) {}

TSet::operator TBitField()
{
    return bitField;
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return maxPower;
}

bool TSet::isMember(const uint elem) const // элемент множества?
{
    if (elem >= maxPower) throw(1);
    else return bitField.getBit(elem);
}

void TSet::insElem(const uint elem) // включение элемента множества
{
    if (elem >= maxPower) throw(1);
    else bitField.setBit(elem);
}

void TSet::delElem(const uint elem) // исключение элемента множества
{
    if (elem >= maxPower) throw(1);
    else bitField.clrBit(elem);
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet &s) // присваивание
{
    maxPower = s.maxPower;
    bitField = s.bitField;
    return *this;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
    if (maxPower != s.maxPower) return false;
    else return (bitField == s.bitField);
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    if (maxPower != s.maxPower) return true;
    else return (bitField != s.bitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    //maxPower = std::max(maxPower, s.maxPower);
    TSet n (std::max(maxPower, s.maxPower));
    n.bitField = bitField | s.bitField;
    return n;
}

TSet TSet::operator+(const uint elem) // объединение с элементом
{
    if (elem >= maxPower) throw(1);
    this->insElem(elem);
    return *this;
}

TSet TSet::operator-(const uint elem) // разность с элементом
{
    if (elem >= maxPower) throw(1);
    this->delElem(elem);
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet n(std::max(maxPower, s.maxPower));
    n.bitField = bitField & s.bitField;
    return n;
}

TSet TSet::operator~() // дополнение
{
    TBitField n(maxPower);
    n = ~bitField;
    bitField = n;
    ~n;
    return *this;
}

// перегрузка ввода/вывода
std::istream &operator>>(std::istream &istr, TSet &s) // ввод
{
    std::string str;
    size_t length;
    istr >> length >> str;
    s.maxPower = length;
    for (int i = 0; i < str.size(); i++) 
        s.insElem(str[i]);
    return istr;
}

std::ostream& operator<<(std::ostream &ostr, const TSet &s) // вывод
{
    ostr << "Size of set: " << s.maxPower << "\n";
    int capacity = 8 * sizeof(uint);
    for (int i = 0; i < s.maxPower; i++)
        if (s.isMember(i)) ostr << i << " ";
    return ostr;
}
