#ifndef TF_H
#define TF_H

template <class T>
void swap(T &a, T& b)
{
    T c = a;
    a = b;
    b = c;
}

#endif