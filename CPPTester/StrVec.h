#pragma once
#include <iostream>
#include <memory>
#include <string>

using namespace std;
static std::allocator<std::string> alloc;   // ����Ԫ��

class StrVec
{
public:
    StrVec() :
        elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const StrVec&);  // �������캯��
    StrVec& operator =(const StrVec&); // ������ֵ�����
    ~StrVec();  // ��������
    void push_back(const std::string&); // ����Ԫ��
    void push_back(std::string&&); // �ƶ�Ԫ��
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string* begin() const { return elements; }
    std::string* end() const { return first_free; }

private:
    //static std::allocator<std::string> alloc;   // ����Ԫ��
    void check_n_alloc()
    {
        if (size() == capacity()) reallocate();
    }
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string* elements;
    std::string* first_free;
    std::string* cap;
};

