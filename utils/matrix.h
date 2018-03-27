#ifndef MATRIX_H
#define MATRIX_H

#include <utility>

template <typename T>
class Matrix
{
public:
    Matrix();
    explicit Matrix(int n, int m);
    Matrix(const Matrix &origin);
    Matrix(Matrix &&origin);
    virtual ~Matrix();
    Matrix& operator=(const Matrix &origin);
    Matrix& operator=(Matrix &&origin);

    int rowCount() const { return N; }
    int columnCount() const { return M; }

    bool hasData() const { return data; }
    void resize(int newN, int newM);
    void clear();

    void divideRow(int row, T divider);
    void addRow(int row_to, int row_what, T multiplier);

    Matrix &operator+=(const Matrix &other);
    Matrix &operator*=(const Matrix &other);

    Matrix operator+(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;

    T operator()(int i, int j) const;
    T &operator()(int i, int j);

    //Array<T> operator*(const Array<T> &other) const;

protected:
    T **data;
    int N, M;
};

template <typename T>
Matrix<T>::Matrix() :  data(nullptr), N(0), M(0)
{
}

template <typename T>
Matrix<T>::Matrix(int n, int m) : N(n), M(m)
{
    data = new T*[N];
    for (int i = 0; i < N; i++)
    {
        data[i] = new T[M];
        for (int j = 0; j < M; j++)
            data[i][j] = 0;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix &origin)
{
    M = origin.M;
    N = origin.N;
    data = new T*[N];
    for (int i = 0; i < N; i++)
    {
        data[i] = new T[M];
        for (int j = 0; j < M; j++)
            data[i][j] = origin.data[i][j];
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix &&origin)
{
    N = origin.N;
    M = origin.M;
    data = origin.data;
    origin.data = nullptr;
    origin.N = origin.M = 0;
}

template <typename T>
Matrix<T>::~Matrix()
{
    for (int i = 0; i < N; i++)
        delete[] data[i];
    delete[] data;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &origin)
{
    M = origin.M;
    N = origin.N;
    data = new T*[N];
    for (int i = 0; i < N; i++)
    {
        data[i] = new T[M];
        for (int j = 0; j < M; j++)
            data[i][j] = origin.data[i][j];
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> &&origin)
{
    N = origin.N;
    M = origin.M;
    data = std::move(origin.data);
    origin.data = nullptr;
    origin.N = origin.M = 0;
    return *this;
}

template <typename T>
void Matrix<T>::resize(int newN, int newM)
{
    if (hasData())
        clear();

    data = new T*[newN];
    for (int i = 0; i < newN; i++)
        data[i] = new T[newM];
    N = newN;
    M = newM;
}

template <typename T>
void Matrix<T>::clear()
{
    for (int i = 0; i < N; i++)
        delete[] data[i];
    delete[] data;
    data = nullptr;
    N = M = 0;
}

template <typename T>
void Matrix<T>::divideRow(int row, T divider)
{
    for (int i = 0; i < M; i++)
        data[row][i] /= divider;
}

template <typename T>
void Matrix<T>::addRow(int row_to, int row_what, T multiplier)
{
    for (int i = 0; i < M; i++)
        data[row_to][i] += multiplier*data[row_what][i];
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other)
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            data[i][j] += other.data[i][j];
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other)
{
    *this = *this * other;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
{
    Matrix<T> result(N, M);
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const
{
    Matrix<T> result;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < other.M; j++)
            for(int k = 0; k < M; k++)
                result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
}

template <typename T>
T Matrix<T>::operator()(int i, int j) const
{
    return data[i][j];
}

template <typename T>
T &Matrix<T>::operator()(int i, int j)
{
    return data[i][j];
}

template <typename T>
class Array
{
public:
    Array() : _data(nullptr), N(0) { }
    Array(int n) : N(n) { _data = new T[N]; }
    Array(const Array &origin);
    Array(Array &&origin);
    ~Array() { delete[] _data; }

    int size() const { return N; }
    const T* data() const { return _data; }

    void clear() { delete[] _data; }
    void resize(int n) { if (_data) clear; _data = new T[n]; }
    void transform(const Matrix<T> &m);
    Array getTransformed(const Matrix<T> &m);

    Array slice(int begin, int size);

    Array& operator=(const Array &origin);
    Array& operator=(Array &&origin);

    T operator[](int i) const;
    T &operator[](int i);

protected:
    T *_data;
    int N;
};

template <typename T>
Array<T>::Array(const Array &origin)
{
    N = origin.N;
    _data = new T[N];
    for (int i = 0; i < N; i++)
        _data[i] = origin._data[i];
}

template <typename T>
Array<T>::Array(Array &&origin)
{
    N = origin.N;
    _data = std::move(origin._data);
    origin._data = nullptr;
    origin.N = 0;
}

template <typename T>
void Array<T>::transform(const Matrix<T> &m)
{
    *this = this->getTransformed(m);
}

template <typename T>
Array<T> Array<T>::getTransformed(const Matrix<T> &m)
{
    Array<T> result(m.rowCount());
    for (int i = 0; i < m.rowCount(); i++)
    {
        result._data[i] = 0;
        for (int j = 0; j < m.columnCount(); j++)
            result._data[i] += m(i, j) * _data[j];
    }
    return result;
}

template <typename T>
Array<T> Array<T>::slice(int begin, int size)
{
    Array<T> result(size);
    for (int i = 0; i < size; i++)
        result[i] = this->operator[](i+begin);
    return result;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T> &origin)
{
    N = origin.N;
    _data = new T[N];
    for (int i = 0; i < N; i++)
        _data[i] = origin._data[i];
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T> &&origin)
{
    N = origin.N;
    _data = origin._data;
    origin._data = nullptr;
    origin.N = 0;
    return *this;
}

template <typename T>
T Array<T>::operator[](int i) const
{
    return _data[i];
}

template <typename T>
T &Array<T>::operator[](int i)
{
    return _data[i];
}
#endif // MATRIX_H
