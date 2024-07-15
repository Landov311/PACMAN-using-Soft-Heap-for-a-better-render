//
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "softheap.h"
#include "fibonacci_heap.h"
#include "funciones_pac.h"
using namespace std;


int main() {
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro!\n");
        return -1;
    }
    if (!al_init_image_addon()) {
        fprintf(stderr, "Failed to initialize Allegro Image Addon!\n");
        return -1;
    }
    comi= al_load_bitmap("C:\\Soft_heap_proyecto\\Images\\Comida.bmp");
    pac = al_load_bitmap("C:\\Soft_heap_proyecto\\Images\\pacman.bmp");
    enemi= al_load_bitmap("C:\\Soft_heap_proyecto\\Images\\enemigo.bmp");
    muerte= al_load_bitmap("C:\\Soft_heap_proyecto\\Images\\muerte.bmp");

    al_convert_mask_to_alpha(pac, al_map_rgb(255, 0, 255)); // 255, 0, 255 es el color rosa en RGB
    al_convert_mask_to_alpha(comi, al_map_rgb(255, 0, 255)); // 255, 0, 255 es el color rosa en RGB
    al_convert_mask_to_alpha(enemi, al_map_rgb(255, 0, 255)); // 255, 0, 255 es el color rosa en RGB
    al_convert_mask_to_alpha(muerte, al_map_rgb(255, 0, 255)); // 255, 0, 255 es el color rosa en RGB

    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(display_width, display_height);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    ALLEGRO_BITMAP* wall_bitmap = al_load_bitmap("C:\\Soft_heap_proyecto\\Images\\roca.bmp");
    if (!wall_bitmap) {
        fprintf(stderr, "Failed to load sprite!\n");
        al_destroy_display(display);
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));


    al_flip_display();
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    ALLEGRO_EVENT ev;
    // Bucle principal del juego
    bool running = true;


    //Generador de casillas
    vector<casilla> grafo;
    for (int y = 0; y < 13; ++y) {
        for (int x = 0; x < 24; ++x) {
            if (mapa[y][x] != 'X') {
                casilla a(x * TILE_SIZE,y* TILE_SIZE);
                grafo.push_back(a);
            }

        }
    }
    while (running && game_over()) {
        apx=px;
        apy=py;
        if(px>0 and px<display_width and py<display_height and py>0){
        dijkstra(grafo,_x,_y);}
        if (!al_is_event_queue_empty(event_queue)) {
            if (al_get_next_event(event_queue, &ev)) {
                if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                    switch (ev.keyboard.keycode) {
                        case ALLEGRO_KEY_UP:
                            dir = 2;
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            dir = 1;
                            break;
                        case ALLEGRO_KEY_DOWN:
                            dir = 3;
                            break;
                        case ALLEGRO_KEY_LEFT:
                            dir = 0;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        if(dir==0) {
            if(mapa[py/32][(px-32)/32] !='X')
            px-=32;
            else dir=4;
        }
        if(dir==1) {
            if(mapa[py/32][(px+32)/32] !='X')
            px+=32;
            else dir=4;
        }
        if(dir==2) {
            if(mapa[(py-32)/32][px/32] !='X')
            py-=32;
            else dir=4;
        }
        if(dir==3) {
            if(mapa[(py+32)/32][px/32] !='X')
            py+=32;
            else dir=4;
        }
         //caaaaaaammmmmmbioooooooo
        if (px<=-32) {px=display_width;}
        else if (px >= display_width) px=0;
        if (py<=-32) {py=display_height;}
        else if (py >= display_height) py=0;

        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Dibujar el mapa
        for (int y = 0; y < 13; ++y) {
            for (int x = 0; x < 24; ++x) {
                if (mapa[y][x] == 'X') {
                    al_draw_bitmap(wall_bitmap, x * TILE_SIZE, y * TILE_SIZE, 0);
                }
                else if (mapa[y][x] == 'o') {
                    al_draw_bitmap(comi, x * TILE_SIZE, y * TILE_SIZE, 0);
                    if(py/32==y && px/32==x){
                        mapa[y][x] = ' ';
                    }
                }
            }
        }
        move_g();
        al_draw_bitmap_region(pac, dir * 33, 0, 33, 33, px, py, 0);
        al_flip_display();
        al_rest(0.023); // Pequeña pausa para controlar la velocidad del bucle
        al_draw_bitmap_region(pac, 4 * 33, 0, 33, 33, px, py, 0);
        al_flip_display();
        al_rest(0.023);

    }

    al_destroy_bitmap(wall_bitmap);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(pac);
    cout<<"You have won, 20 pa tu final";

    return 0;
}
//void dijkstra(vector<casilla>& wa, int gx, int gy) {
//    unordered_map<pair<int, int>, pair<int, int>, pair_hash> parent;
//    unordered_map<pair<int, int>, int, pair_hash> distances;
//    unordered_map<pair<int, int>, bool, pair_hash> visited;
//
//    // Inicialización de distancias y visitados
//    for (const auto& par : wa) {
//        pair<int, int> f(par.x, par.y);
//        distances[f] = 200000;
//        visited[f] = false;
//    }
//
//    // Nodo objetivo
//    pair<int, int> fa(gx, gy);
//    distances[fa] = 0;
//
//    // Crear el soft_heap<int> para manejar las distancias mínimas
//    auto* nn = new soft_heap(2);
//    FibonacciHeap<int>* np= new FibonacciHeap<int>();
//    for(int j=0;j<10000;j++){
//        nn->insert(199999);
//    }
//    np->insert(0); // Insertar la distancia cero para el nodo inicial
//
//    while (true) {
//        //if (np->empty()) break;
//        if(np->isEmpty()) break;
//        int current_dist = np->removeMinimum();
//        //nn->deletemin();
//        pair<int, int> current_node(-1, -1);
//
//        // Encontrar el nodo con la distancia mínima no visitado
//        for (const auto& par : distances) {
//            if (par.second == current_dist && !visited[par.first]) {
//                current_node = par.first;
//                break;
//            }
//        }
//
//        // Si no se encontró ningún nodo válido, terminar
//        if (current_node.first == -1 && current_node.second == -1) {
//            cout << "No hay más nodos válidos." << endl;
//            break;
//        }
//
//        visited[current_node] = true;
//
//        // Obtener vecinos
//        vector<pair<int, int>> lista_vecinos = get_neighbors(current_node.first, current_node.second);
//
//        for (const auto& vecino : lista_vecinos) {
//            pair<int, int> vecino_casilla(vecino.first, vecino.second);
//            int nueva_distancia = distances[current_node] + 32;
//
//            if (distances.find(vecino_casilla) != distances.end() && nueva_distancia < distances[vecino_casilla]) {
//                distances[vecino_casilla] = nueva_distancia;
//                parent[vecino_casilla] = current_node;
//                np->insert(nueva_distancia);
//            }
//        }
//    }
//
//    int conf;
//    //auto *pm= new casilla(px,py);
//    pair<int,int> pm(px,py);
//    conf= distances[pm];
//    while(true){
//        if(conf==32) break;
//        pm=parent[pm];
//        conf=distances[pm];
//    }
//    _x=pm.first;
//    _y=pm.second;
//
//}
