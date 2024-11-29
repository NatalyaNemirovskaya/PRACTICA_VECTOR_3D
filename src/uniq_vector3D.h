#include <iostream>
#include <memory>

class Uniq_Vector3D
{
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

          

            coord(const coord& other):x_(other.x_), y_(other.y_), z_(other.z_){
                    std::cout << "Copy coord "<< std::endl;

            }

            coord(coord&& other):x_(std::move(other.x_)), y_(std::move(other.y_)), z_(std::move(other.z_)){
                std::cout << "move coord "<< std::endl;
            }

            ~coord(){
                //std::cout << "Coord destroyed" << std::endl;
            } // деструктор


        };
        
         std::unique_ptr<coord[]> m_array = nullptr; // массив координат
         std::size_t sz = 0 ; // реальный размер массива
         std::size_t cap = 8 ; //выделено памяти



         // перевыделение памяти
         void reserve(size_t n);


public:
    Uniq_Vector3D() = default; // конструктор по умолчанию

    Uniq_Vector3D(double x, double y, double z); // конструктор с параметрами

    Uniq_Vector3D(const Uniq_Vector3D &) = delete;  //конструктор копирования удален

    Uniq_Vector3D(Uniq_Vector3D && other); //конструктор копирования перемещением

    

    Uniq_Vector3D& operator= (Uniq_Vector3D& other) = delete; // копирующий оператор =

    Uniq_Vector3D& operator= (Uniq_Vector3D&& other); // перемещающий оператор =

   //заполнение n элементов initializer_list
   void resize_Vector(size_t n, std::initializer_list<double> il);

   //удаление последнего элемента
   void pop_back();

    //получить размер
    size_t get_sz() const;

    coord get_crd(size_t n) const; // получить координаты по индексу

    //вывести координаты , лежеащие по адресу m_array+n
    void print_coord(size_t n);

    void push_coord(double x, double y, double z); //добавить элемент в конец массива

    ~Uniq_Vector3D() = default; //деструктор дефолтный

    coord&  operator[](std::size_t pos); // перегрузка оператора []

    const coord&  operator[](std::size_t pos) const; // перегрузка оператора [] const

     friend std::ostream &operator << (std::ostream &out, const coord &v); //перегрузка оператора <<
     


};


