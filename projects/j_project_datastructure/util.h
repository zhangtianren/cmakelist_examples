
#include "iostream"

#include <string>
//#include <stdlib.h>

#pragma once



class ElementType {
public:
    int key;
    void* data;
    virtual ~ElementType(){}
    ElementType()
    {
        key = 0;
        data = nullptr;
    }
    ElementType(int k)
    {
        key = k;
        data = nullptr;
    }
    ElementType(int k, void* d)
    {
        key = k;
        data = d;
    }

    // ElementType(const ElementType & outer)
    // {

    // }

    // ElementType& operator =(const ElementType& other)
    // {

    // }

    virtual void print()
    {
        printf("[%d, 0x%02x]", key, data);
    }
    virtual std::string tostring()
    {
        char temp[256] = {0};
        sprintf(temp, "[%d]", key);
        return std::string(temp);
    }

    int compare(const ElementType& e)
    {
        return key > e.key ? 1 : (key < e.key ? -1 : 0);
    }
};

inline int compElement(const ElementType& e1, const ElementType& e2)
{
    return e1.key > e2.key ? 1 : (e1.key < e2.key ? -1 : 0);
}