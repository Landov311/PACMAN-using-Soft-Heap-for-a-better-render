#include <iostream>
#include "softheap.h"
#include <cstdlib> // For std::rand() and std::srand()
#include <ctime>
#include <chrono>
#include <stdio.h>
#include "fibonacci_heap.h"
using namespace std;

//void display_menu(soft_heap *h){
//  int option;
//  bool exit_menu = true;
//  while(exit_menu){
//  cout<<"Select option: ";
//  cin >> option;
//  switch(option){
//    case 0:
//      h->reset_explorer();
//      h->print_headers();
//      break;
//    case 1:
//      h->explorer_next();
//      h->print_headers();
//      break;
//    case 2:
//      h->explorer_prev();
//      h->print_headers();
//      break;
//    case 3:
//      h->print_queue();
//      break;
//    case 4:
//      h->Nexplore_next();
//      h->print_queue();
//      break;
//    case 5:
//      h->Nexplore_child();
//      h->print_queue();
//      break;
//    case 6:
//      h->print_Node_information();
//      h->reset_Nexplorer();
//      break;
//    case 7:
//      exit_menu = false;
//      break;
//    default:
//      cout<<"Invalid option"<<endl;
//
//  }
//  }
//}
//void mini_menu(soft_heap *h){
//  int option;
//  cout<<"Select option: ";
//  cin >> option;
//  switch(option){
//    case 1:
//      int value;
//      cout<<"value to insert: ";
//      cin>>value;
//      h->insert(value);
//      cout<<endl;
//      break;
//    case 2:
//      cout<<"min: "<<h->deletemin()<<endl<<endl;
//      break;
//    case 3:
//    cout<<"min: "<<h->findmin()<<endl<<endl;
//    break;
//    case 4:
//      cout<<"----Display soft-heap----"<<endl
//          <<"Options:                 "<<endl
//          <<"¯¯¯¯¯¯¯¯                 "<<endl
//          <<"0. Display headers       "<<endl
//          <<"1. Go to next header     "<<endl
//          <<"2. Go to prev header     "<<endl
//          <<"3. Display soft queue    "<<endl
//          <<"4. Go to next node       "<<endl
//          <<"5. Go to child node      "<<endl
//          <<"6. Display node content  "<<endl
//          <<"7. Exit                  "<<endl
//          <<"------------------------"<<endl;
//      h->reset_explorer();
//      display_menu(h);
//      break;
//    default:
//      cout<<"invalid option"<<endl;
//
//  }
//}



int main() {
  soft_heap *h = new soft_heap(0.2);
//  cout<<"-----Test soft-heap-----"<<endl
//    <<"Options:                "<<endl
//    <<"¯¯¯¯¯¯¯¯                "<<endl
//    <<"1. Insert               "<<endl
//    <<"2. deleteMin            "<<endl
//    <<"3. FindMin              "<<endl
//    <<"4. Display              "<<endl
//    <<"------------------------"<<endl;
//  while(true)
//    mini_menu(h);
    FibonacciHeap<int>* hola= new FibonacciHeap<int>();
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Insertar un millón de datos
    const int NUM_DATOS = 1000000;

    auto com=std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_DATOS; ++i) {
        int x = std::rand();
        h->insert(x);
        h->findmin();
    }
    auto term = std::chrono::high_resolution_clock::now();
    auto durac=std::chrono::duration_cast<std::chrono::microseconds>(term - com);
    cout<<"tiempo de insercion del Soft_heap:" << durac.count()<<endl;

    auto start = std::chrono::high_resolution_clock::now();
    cout<<h->findmin()<<" ";
    h->deletemin();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Tiempo de hallar el minimo del Soft_heap: " << duration.count() << " microsegundos" << std::endl;
    cout<<endl<<endl;


    com=std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_DATOS; ++i) {
        int x = std::rand();
        hola->insert(x);
    }
    term = std::chrono::high_resolution_clock::now();
     durac=std::chrono::duration_cast<std::chrono::microseconds>(term - com);
    cout<<"tiempo de insercion del fibonacci_heap es de :" << durac.count()<<endl;

    auto starta = std::chrono::high_resolution_clock::now();
    cout<<hola->getMinimum()<<" ";
    hola->removeMinimum();
    auto enda = std::chrono::high_resolution_clock::now();


    auto durationa = std::chrono::duration_cast<std::chrono::microseconds>(enda - starta);

    std::cout << "Tiempo de insercion del fibonacci_heap: " << durationa.count() << " microsegundos" << std::endl;
    for(int i=0; i<10000; i++){
        h->deletemin();
        //h->findmin();
    }

    /*
    h->insert(15);
    h->insert(9);
    h->insert(8);
    h->insert(4);
    h->insert(7);
    h->insert(11);
    cout<<"min: "<<h->deletemin()<<endl;
    cout<<"min: "<<h->deletemin()<<endl;
    cout<<"min: "<<h->deletemin()<<endl;
    h->insert(3);
    h->insert(64);
    h->insert(39);
    cout<<"min: "<<h->deletemin()<<endl;
    h->insert(24);
    h->print_headers();
    h->explorer_next();
    h->print_queue();
    h->explorer_next();
    h->print_headers();
    h->Nexplore_next();
    h->print_queue();
    */
    cout<<endl;
    soft_heap* a= new soft_heap(2);
    a->insert(3);
    a->insert(2);
    a->insert(22);
    a->insert(10);
   // a->deletemin();
    cout<<a->findmin();
    a->deletemin();
    cout<<endl;
    cout<<a->findmin();
    a->deletemin();
    cout<<a->findmin();
    //if(a->emp()) cout<<"Tu lista está vacía wasssa :p";
//    cout<<a->findmin();
  return 0;
}