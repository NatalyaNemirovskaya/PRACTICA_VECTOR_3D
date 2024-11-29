#include <iostream>
#include <memory>
#include <new>


class Vector3D {

private:

// структура для хранения координат
 struct coord
    {
        /* data */
        double x_ = 0; // координата х
        double y_ = 0; // координата у
        double z_ = 0; // координата z

        // конструктор без параметров
        coord(){
           // std::cout << "Created new coord without parametres" << std::endl;
        }

        //конструктор с параметрами
        coord(double x, double y, double z):x_(std::move(x)), y_(std::move(y)), z_(std::move(z)){
               std::cout << "Created new move coord with parametres" << std::endl;
        }
       
        coord(const coord& other):x_(other.x_), y_(other.y_), z_(other.z_) 
        {
                std::cout << "Copy coord "<< std::endl;

       }
              
        
        coord(coord&& other):x_(std::move(other.x_)), y_(std::move(other.y_)), z_(std::move(other.z_)){
            
            std::cout << "move coord "<< std::endl;

        }
       
       

        
       ~coord(){
            std::cout << "Coord destroyed" << std::endl;
        } // деструктор


        friend std::ostream &operator << (std::ostream &out, const coord &v)
        {
            {
                out << "{" << v.x_ << ","
                           << v.y_ << ","
                           << v.z_ << "}";
            }

            return out;
        }


    };

    coord* m_array = nullptr; // массив координат
    std::size_t sz = 0 ; // реальный размер массива
    std::size_t cap = 8 ; //выделено памяти

     // перевыделение памяти
     void reserve(std::size_t n);


public:


  //конструктор без параметров
    Vector3D();

    //конструктор с параметрами
    Vector3D(double x, double y, double z);

    //конструктор копирования
    Vector3D(const Vector3D & other) ;

    //оператор присваивания копированием
    Vector3D& operator= (const Vector3D &other);

    //конструктор перемещения
    Vector3D (Vector3D&& other);

    //оператор присваивания перемещением
     Vector3D& operator= (Vector3D&& other);

    //добавление элемента
     void push_coord(double x, double y, double z);

     
     //заполнение массива одинаковыми данными 
     void resize_Vector(size_t n, std::initializer_list<double> il);

    //деструктор
     ~Vector3D();

     void pop_back();

    coord get_crd(size_t n) const; // получить координаты по индексу

    // void set(size_t i, const coord& c);


    coord&  operator[](std::size_t pos); // перегрузка оператора []

    const coord&  operator[](std::size_t pos) const; // перегрузка оператора [] const

    //вывод на печать
    void print_coord(size_t n);

    //перегрузка оператора <<
    friend std::ostream &operator << (std::ostream &out, const Vector3D &v)
    {
        volatile auto sz = v.get_sz();
        if (v.m_array  == nullptr){
             out << "Massiv is nulptr" << std::endl << std::endl;
             return out;
        }
        for(int i=0; i<sz; ++i) 
        {
            out << v.m_array[i] << std::endl;
        }

        return out;
    }


    // возвращение размера массива
    size_t get_sz() const;

};




