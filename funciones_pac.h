//
// Created by lvera on 14/07/2024.
//

#ifndef SOFT_HEAP_PROYECTO_FUNCIONES_PAC_H
#define SOFT_HEAP_PROYECTO_FUNCIONES_PAC_H
#include <algorithm>
#include "fibonacci_heap.h"
#include <unordered_map>
#include <limits>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
ALLEGRO_BITMAP *pac;
ALLEGRO_BITMAP *comi;
ALLEGRO_BITMAP *enemi;
ALLEGRO_BITMAP *muerte;
ALLEGRO_DISPLAY* display;
ALLEGRO_BITMAP *wall_bitmap;
int dir = 4;
int px = 5 * 32, py = 5 * 32;
int fdir=0;
int _x=32*3, _y=32*3;
int apx, apy;
const int TILE_SIZE = 32;
int display_width = 24 * TILE_SIZE;
int display_height = 13 * TILE_SIZE;
char mapa[13][25] = {
        "XXXX XXXXXXXXXXXXXXXXXXX",
        "X     ooo oooo  ooooo  X",
        "Xo   XXXX XXXX XXXXX   X",
        "Xo     X               X",
        "Xo     X   XX    X     X",
        "Xo    oo    ooo  X     X",
        "X   XXXX XXXXXXX XXXX  X",
        "X   X  oooooooooo   X  X",
        "XX  X XX  XXXXX  XX X XX",
        "    X               X   ",
        "X  XX   X  XXX  X  XX  X",
        "X     ooX   ooo X  oo  X",
        "XXXX XXXXXXXXXXXXXXXXXXX"
};

struct casilla{
    int x;
    int y;
    casilla(int xx, int yy){
        x=xx;
        y=yy;
    }
};



bool game_over(){
    for (int y = 0; y < 13; ++y) {
        for (int x = 0; x < 24; ++x) {
            if (mapa[y][x] == 'o') {
                return true;
            }
        }
    }
    return false;
}

void draw_ghost(){
    al_draw_bitmap_region(enemi, 0, 0, 30, 30, _x, _y, 0);
}
void pac_death(){
    if(py==_y and px==_x || (_x==apx and _y==apy )){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        for (int j=7; j>=0;j--){
            al_flip_display();
            al_draw_bitmap_region(muerte, j * 33, 0, 33, 33, px, py, 0);
            al_rest(0.04);
        }
        _y=32;
        _x=32;
        px=32*5;
        py=32*5;
        dir=4;
    }
}
void move_g(){
    draw_ghost();
    pac_death();
}

vector<pair<int, int>> get_neighbors(int x, int y) {
    vector<pair<int, int>> neighbors;
    int row = y / TILE_SIZE;
    int col = x / TILE_SIZE;

    if (row > 0 && mapa[row - 1][col] != 'X')
        neighbors.emplace_back(x, y - TILE_SIZE);

    if (row < 12 && mapa[row + 1][col] != 'X')
        neighbors.emplace_back(x, y + TILE_SIZE);

    if (col > 0 && mapa[row][col - 1] != 'X')
        neighbors.emplace_back(x - TILE_SIZE, y);

    if (col < 24 && mapa[row][col + 1] != 'X')
        neighbors.emplace_back(x + TILE_SIZE, y);

    return neighbors;
}
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2; // Simplemente combino los hashes
    }
};
void dijkstra(vector<casilla>& wa, int gx, int gy) {
    unordered_map<pair<int, int>, pair<int, int>, pair_hash> parent;
    unordered_map<pair<int, int>, int, pair_hash> distances;
    unordered_map<pair<int, int>, bool, pair_hash> visited;

    // Inicialización de distancias y visitados
    for (const auto& par : wa) {
        pair<int, int> f(par.x, par.y);
        distances[f] = 200000;
        visited[f] = false;
    }

    pair<int, int> fa(gx, gy);
    distances[fa] = 0;

    auto* np=new  soft_heap(0.002);

    np->insert(0);
    int nohay = 0;
    while (true) {
        nohay++;
        //if (empty(a)) break;
        int current_dist = np->deletemin();

        pair<int, int> current_node(-1, -1);
        // Encontrar el nodo con la distancia mínima no visitado
        for (const auto& par : distances) {
            if (par.second == current_dist && !visited[par.first]) {
                current_node = par.first;
                break;
            }
        }

        if(nohay==135) break;
        if (current_node.first == -1 && current_node.second == -1) {
            break;
        }

        visited[current_node] = true;

        // Obtener vecinos
        vector<pair<int, int>> lista_vecinos = get_neighbors(current_node.first, current_node.second);

        for (const auto& vecino : lista_vecinos) {
            pair<int, int> vecino_casilla(vecino.first, vecino.second);
            int nueva_distancia = distances[current_node] + 32;

            if (distances.find(vecino_casilla) != distances.end() && nueva_distancia < distances[vecino_casilla]) {
                distances[vecino_casilla] = nueva_distancia;
                parent[vecino_casilla] = current_node;
                np->insert( nueva_distancia);
            }
        }
    }
    // Recuperar el camino más corto y establecer _x y _y
    pair<int, int> pm(px, py);
    int conf = distances[pm];
    while (conf != 32) {
        pm = parent[pm];
        conf = distances[pm];
        if(conf==0) break;
    }
    if(conf==0){
        if(fdir==0){
            if(mapa[_y/32][(_x-32)/32]!='X') _x-=32;
            else fdir= rand()%3;
        }
        else if(fdir==1){
            if(mapa[_y/32][(_x+32)/32]!='X') _x+=32;
            else fdir= rand()%3;
        }
        else if(fdir==2){
            if(mapa[(_y-32)/32][(_x)/32]!='X') _y-=32;
            else fdir= rand()%3;
        }
        else if(fdir==3){
            if(mapa[(_y+32)/32][(_x)/32]!='X') _y+=32;
            else fdir= rand()%3;
        }
        if (_x<=-32) {_x=24 * TILE_SIZE;}
        else if (_x >= 24 * TILE_SIZE) _x=0;
        if (_y<=-32) {_y=13 * TILE_SIZE;}
        else if (_y >= 13 * TILE_SIZE) _y=0;
    }
    else {
        _x = pm.first;
        _y = pm.second;
    }
}


#endif //SOFT_HEAP_PROYECTO_FUNCIONES_PAC_H
