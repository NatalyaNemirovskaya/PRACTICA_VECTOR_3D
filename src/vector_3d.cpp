#include <iostream>
#include "vector_3d.h"
#include <memory>
#include <new>



Vector3D::Vector3D()
{   
    m_array = reinterpret_cast<coord *>(new int8_t[cap * sizeof(coord)]);
    //auto pointer = new int8_t[cap * sizeof(coord)]; // выделение памяти под 8 элементов без конструктора Placement-new;
   // m_array = new (pointer) coord[cap];
   // new (m_array) coord();

    std::cout << "M_array created without parametres" << std::endl;
}


Vector3D::Vector3D(double x, double y, double z)
{
    // выделение памяти под 8 элементов без конструктора Placement-new
    m_array = reinterpret_cast<coord *>(new int8_t[cap * sizeof(coord)]);
    new (m_array) coord(std::move(x), std::move(y), std::move(z)); // создание coord
    std::cout << "M_array created with parametres" << std::endl;
    sz += 1; // реально занято памяти
}

Vector3D::coord &Vector3D::operator[](std::size_t pos)
{
    return *(m_array + pos); // возвращаем по индексу структуру
}

const Vector3D::coord &Vector3D::operator[](std::size_t pos) const
{
    return *(m_array + pos); // возвращаем по индексу структуру
}

// конструктор копирования
Vector3D::Vector3D(const Vector3D &other)
{
    cap = other.cap;
    sz = other.sz;
    m_array = reinterpret_cast<coord *>(new int8_t[(cap) * sizeof(coord)]);
    for (size_t i = 0; i < sz; ++i)
    {

        new (m_array + i) coord(other.m_array[i]);
    }
    std::cout << "Constructor copy" << std::endl;
}

// конструктор перемещения
Vector3D::Vector3D(Vector3D &&other) : m_array(other.m_array)
{

    cap = other.cap;
    sz = other.sz;
    other.m_array = nullptr;
    other.cap = 8;
    other.sz = 0;

    std::cout << "Move copy" << std::endl;
}

//оператор присваивания копированием
Vector3D& Vector3D::operator= (const Vector3D &other){
    if (&other == this)
        return *this;
    //создать массив размера other неиницилизированный
    coord *array = reinterpret_cast<coord *>(new int8_t[other.cap * sizeof(coord)]);
    // заполняем массив элементами из other
    for (size_t i = 0; i < other.sz; ++i)
    {
        new (array + i) coord(other.get_crd(i));
    }
    // очистить старый массив
    for (size_t i = 0; i < sz; ++i) // освобождение памяти
    {
        (m_array + i)->~coord();
    }

    delete[] reinterpret_cast<int8_t *>(m_array);

    m_array = array; // указатель на созданный массив
    cap = other.cap;
    sz = other.sz;
    std::cout << "operator =" << std::endl;
    return *this;
}

// оператор присваивания перемещением
Vector3D &Vector3D::operator=(Vector3D &&other)
{
    if (&other == this)
        return *this;
    for (size_t i = 0; i < sz; ++i) // очищаем
    {
        (m_array + i)->~coord();
    }

    m_array = other.m_array; // указатель  массив other
    cap = other.cap;
    sz = other.sz;
    other.m_array = nullptr;
    other.cap = 0;
    other.sz = 0;
    return *this;
}

Vector3D::~Vector3D(){
    delete  m_array;
    std::cout << "M_array destroyed" << std::endl;
}



// перевыделение памяти
void Vector3D::reserve(size_t n)
{
    // выделение памяти под новый массив
    coord *arr = reinterpret_cast<coord *>(new int8_t[n * sizeof(coord)]);
    for (size_t i = 0; i < sz; ++i) // копирование из старого массива
    {
        // new (arr + i) coord(m_array[i]);
          new (arr + i) coord(std::move(m_array[i])); // переместить элементы в новый массив
    }
    /*
    for (size_t i = 0; i < sz; ++i) // освобождение памяти
    {
        (m_array + i)->~coord();
    }
    */
    delete[] reinterpret_cast<int8_t *>(m_array);

    m_array = arr; // указатель на созданный массив

    cap = n; // емкость массива
}

void Vector3D::push_coord(double x, double y, double z)
{
    if (sz == cap)
        reserve(2 * cap);
     //new (m_array+sz) coord(x, y, z);
     new (m_array +sz)  coord(std::move(x), std::move(y), std::move(z));
    ++sz;
}

void Vector3D::pop_back()
{
    --sz;
    (m_array + sz)->~coord();
}

Vector3D::coord Vector3D::get_crd(size_t n) const
{
    if (n >= sz)
    {
        std::cout << "ERROR" << std::endl;
        return this->m_array[sz - 1];
        ;
    }
    return this->m_array[n];
}

//вывести на печать n-ый элемент массива
void Vector3D::print_coord(size_t n)
{
    if (n >= this->sz)
    {
        std::cout << "Error  Massiv have  " << sz << " items" << std::endl;
        return;
    }
    std::cout << "Coords: " << n << " item " << std::endl;

    std::cout << "x= " << m_array[n].x_ << " "
              << "y= " << m_array[n].y_ << " "
              << "z= " << m_array[n].z_ << " "
              << std::endl;
}

// получить размер массива
size_t Vector3D::get_sz() const
{
    return this->sz;
}


void Vector3D::resize_Vector(size_t n, std::initializer_list<double> il)
{
    if (n > cap) {
        coord *arr = reinterpret_cast<coord *>(new int8_t[n * sizeof(coord)]); //выделить новый массив
        m_array = arr;
        for (size_t i = 0; i < sz; ++i) // освобождение памяти
           {
                  (m_array + i)->~coord();
            }
   
         delete[] reinterpret_cast<int8_t *>(m_array);
         cap = n;

    }
       // reserve(n);
    for (auto i = 0; i < n; ++i) // заполнение массива 
    {
        new (m_array + i) coord(*(il.begin()), *(il.begin() + 1), *(il.begin() + 2));
    }
    sz = n;
    
}
