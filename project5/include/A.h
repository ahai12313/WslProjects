#ifndef A_H
#define A_H


template<typename T, typename U>
struct AA {};


template<typename T>
struct AA<T, T> {}; 


template<typename T>
struct AA<T, int> {};

template<typename T>
struct AA<int, T> {};

#endif