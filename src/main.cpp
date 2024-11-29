#include "vector_3d.h"
#include "uniq_vector3D.h"
#include <iostream>

 using namespace std;

//заполнить массив нулями
void Resize_nl(shared_ptr<Uniq_Vector3D> &p){
   auto t = {0.0, 0.0, 0.0};
   p->resize_Vector(p->get_sz(), t);
    
}

int main()
{
  

{

{   cout << "Created massiv v1" << endl;
    Vector3D v1(2, 3, 4);
    cout << "Created massiv v2" << endl;
   Vector3D v2;
   
   v1.print_coord(0); //печатаем содержимое 1 элемента
   cout << "Add item to v2" << endl;
   v1.push_coord(2.3, 3.0, 5.5); //добавляем координаты
   v1.print_coord(1); //печатаем содержимое 2 элемента
   v1.print_coord(2); //печатаем содержимое 3 элемента ОШИБКА!!!


   v2.push_coord(1.0, 2.0, 3.0);
   v2.print_coord(0);
   std::cout << "size of arrays v2 " << v2.get_sz() << std::endl;
}
   Vector3D v3;
   cout << "v3" <<v3 << endl << endl;
   Vector3D v4(3, 5, 8);
   v4.push_coord(2.3, 3.0, 5.5);

    v4.push_coord(7.3, 4.0, 6.5);
   cout << "v4 " <<v4 << endl;
   v3 = v4;
   // присвоение v3 v4
   cout << "v3 after operator = " <<v3 << endl << endl;

   // конструктор копирования
   Vector3D v5(v4);
  // v5[0] = {0,0,0};
   cout << "v5 " <<v5 << endl << endl;

  
  
  // move copy
   Vector3D v6(std::move(v5));
   cout << "v6" <<v6 << endl << endl;
   cout << "v5 " <<v5 << endl << endl;
   cout << " v6 resize" << endl;
    auto c = {1.0 ,2.0 ,3.0};
    v6.resize_Vector(6, c);

    cout << v6[5]<< endl;
    cout <<v6.get_sz() << endl << endl;

    
    

   int arr[sizeof(Vector3D)];

   Vector3D *vecptr = new (&arr) Vector3D[4];

   for (auto i = 4; i--;) 
      for (auto it = rand() % 10; it--; vecptr[i].push_coord(rand() % 20, rand() % 20, rand() % 20)) ;

   for (auto i = 4; i--; cout << i[vecptr])
      ;

   auto t = vecptr[0].get_crd(0); // получение данных

   t.x_ = 2;
   t.y_ = 2;
   t.z_ = 2;
   cout << "NEW ONE" << endl;
   cout << t << endl;
   cout << vecptr[0].get_crd(0) << endl; // не изменяет!
  // присваивающее копирование
   Vector3D v7;
   v7 = std::move(v6);
   cout << "size of v7 = " << v7.get_sz() << endl;
   cout << "size of v6 = " << v6.get_sz() << endl << endl;

}
   //------------------------------Uuniq_vector3D-------------------------------------------
   cout <<""<< endl;
   Uniq_Vector3D uv1(3 ,2, 6);
   uv1.push_coord(2, 3, 5 );

   cout << uv1[0] << endl;
   cout << uv1[1] << endl;
   cout << uv1.get_sz() << endl;
   uv1.pop_back();

   cout << uv1[1] << endl;
   cout << uv1.get_sz() << endl;
   uv1.print_coord(2);
   uv1.print_coord(0);

   Uniq_Vector3D uv2;
   auto y ={1.2, 2.3, 3.0};
   uv2.resize_Vector(12, y);
    cout << uv2.get_sz() << endl;
    cout << uv2[11] << endl;
   uv2.print_coord(11);
   
   Uniq_Vector3D uv3(std::move(uv2));
   cout << uv2.get_sz() << endl;
   cout << uv3.get_sz() << endl;




   
   auto shp = make_shared<Uniq_Vector3D>(1,2,3);
   cout << "Size of shp = " << shp->get_sz()<< endl;
   shp->push_coord(0.2,0.3,2.5);
   cout << "Size of shp = " << shp->get_sz()<< endl;
   shp->print_coord(0);
   shp->print_coord(1);
   auto shp1 = shp;
   cout << "Size of shp1 = " << shp1->get_sz()<< endl;


   Resize_nl(shp1); // заполнить нулями
   cout << "Size of shp1 = " << shp1->get_sz()<< endl;
   shp->print_coord(0);
   shp->print_coord(1);
   auto t = shp->operator[](0);
   cout << " x= " << t.x_ << endl;
   cout << " y= " << t.y_<< endl;
   cout << " z= " <<  t.z_<<  endl; 
   

   return 0;
}
