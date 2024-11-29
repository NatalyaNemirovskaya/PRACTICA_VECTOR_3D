#include "uniq_vector3D.h"
#include <memory>
#include <iostream>


Uniq_Vector3D::Uniq_Vector3D(double x, double y, double z){

    //создание указателя на 8 
    m_array = std::make_unique<coord[]>(cap);
    //m_array[sz]= coord(std::move(x), std::move(y), std::move(z));  
    //записаны координаты в 1 элемент массива
    m_array[sz].x_ = std::move(x);  
    m_array[sz].y_ =  std::move(y); 
    m_array[sz].z_ =  std::move(z);      
    sz+=1;
    std::cout << "uniq_vector is created" << std::endl;


}



 //конструктор перемещения
Uniq_Vector3D::Uniq_Vector3D(Uniq_Vector3D&& other){
    this->m_array = std::move(other.m_array);
    sz = other.sz;
    cap = other.cap;
    
    other.m_array = nullptr;
    other.sz = 0;
    other.cap = 0;

}

// перемещающий оператор =
Uniq_Vector3D&  Uniq_Vector3D::operator= (Uniq_Vector3D&& other){
    if (&other == this)
        return *this;

    m_array = std::move(other.m_array);
    sz = other.sz;
    cap = other.cap;    
    other.m_array = nullptr;
    other.sz = 0;
    other.cap = 0;
    return *this;

}

void Uniq_Vector3D::resize_Vector(size_t n, std::initializer_list<double> il){
    if (n > cap) {
         std::unique_ptr up = std::make_unique<coord[]>(n);
   
        this->m_array = std::move(up);
        up = nullptr;
    }
    for (auto i = 0; i < n; ++i) // копирование из старого массива
    {
       m_array[i].x_ = *il.begin();
       m_array[i].y_= *(il.begin()+1);
       m_array[i].z_ =  *(il.begin()+2);
    }

    sz = n;
    cap = n;
}

void Uniq_Vector3D::pop_back(){
    --sz;
    m_array[sz].x_ = 0;
    m_array[sz].y_ = 0;
    m_array[sz].z_ = 0;

}

void Uniq_Vector3D::print_coord(size_t n){
     if (n >= sz){
        std::cout << "Error  Massiv have  "  << sz <<" items" << std::endl;
        return;
    }
    std::cout << "Coords: " << n << " item " << std::endl;

    std::cout << "x= " << m_array[n].x_ << " "
              << "y= " << m_array[n].y_ << " "
              << "z= " << m_array[n].z_ << " "
              << std::endl;
}

size_t Uniq_Vector3D::get_sz() const{
    return sz;
    
}

Uniq_Vector3D::coord Uniq_Vector3D::get_crd(size_t n) const
{
    if (n >= sz)
    {
        std::cout << "ERROR" << std::endl;

        return m_array[sz - 1];
    }
    return this->m_array[n];
}

//
void Uniq_Vector3D::push_coord(double x, double y, double z){
    if (sz == cap) {reserve(cap*2);}
     m_array[sz].x_ = std::move(x);   
    m_array[sz].y_ =  std::move(y);  
    m_array[sz].z_ =  std::move(x);   
    sz+=1;
}

void  Uniq_Vector3D::reserve(std::size_t n){
    std::unique_ptr up = std::make_unique<coord[]>(n);
   // std::uninitialized_copy(m_array.get(), m_array.get()+sz, up.get());
    std::uninitialized_move(m_array.get(), m_array.get()+sz, up.get());
    this->m_array = std::move(up);
    up = nullptr;
    cap = n;
    
   

}

// перегрузка оператора []
Uniq_Vector3D::coord&  Uniq_Vector3D::operator[](std::size_t pos){
        return  *(m_array.get()+pos); // возвращаем по индексу структуру
}




const Uniq_Vector3D::coord&  Uniq_Vector3D::operator[](std::size_t pos) const  { // перегрузка оператора [] const
        return  *(m_array.get()+pos); // возвращаем по индексу структуру

}

std::ostream & operator << (std::ostream &out, const Uniq_Vector3D::coord &v)        {
     {

         out << "{" << v.x_ << ","
             << v.y_ << ","
             << v.z_ << "}";
    }

    return out;
}

   