template<class T>
void Tprint(T t) {
    fmt::print("one\n");
}

template<class T, class V>
void Tprint(T t, V v) {
    fmt::print("Two\n");
}