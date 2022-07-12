#include "StrVec.h"

void StrVec::push_back(const std::string& s)
{
    check_n_alloc();    // ȷ���пռ�������Ԫ��
    // ��first_freeָ���Ԫ���У�����s�ĸ���
    alloc.construct(first_free++, s);
}
void StrVec::push_back(std::string&& s)
{
    check_n_alloc();    // ȷ���пռ�������Ԫ��
    // ��first_freeָ���Ԫ���У�����s�ĸ���
    alloc.construct(first_free++, std::move(s));
}
std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* a, const std::string* b)
{
    // ����ռ䱣�������Χ��Ԫ��
    auto data = alloc.allocate(b - a);
    // ��ʼ��������һ��pair����pair��data��uninitialized_copy�ķ���ֵ����
    return { data, uninitialized_copy(a, b, data) };
}

void StrVec::free()
{
    // ���ܴ��ݸ�deallocateһ����ָ�룬��elementΪnullptr������ʲô������
    if (elements)
    {
        for (string* p = first_free; p != elements; /* �� */)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}
StrVec::StrVec(const StrVec& s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
StrVec::~StrVec() { free(); }
StrVec& StrVec::operator =(const StrVec& s)
{
    auto data = alloc_n_copy(s.begin(), s.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void StrVec::reallocate()
{
    // ���ǽ������С�������ڴ�ռ�
    auto newcapacity = size() ? 2 * size() : 1;
    // �������ڴ�
    auto newdata = alloc.allocate(newcapacity);
    //auto dest = newdata;
    auto dest = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), newdata);
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}