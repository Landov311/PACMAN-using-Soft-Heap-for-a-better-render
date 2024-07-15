#include <iostream>
using namespace std;

struct ILCELL {
    int key;
    ILCELL *next;


    ILCELL() : next(nullptr){}
    ILCELL(int value) : key(value), next(nullptr){}
};

struct NODE {
    int ckey, rank;
    NODE *next, *child;
    ILCELL *il, *il_tail;

    NODE() : rank(0), next(nullptr), child(nullptr), il(nullptr), il_tail(nullptr){}
    NODE(int value) : ckey(value), rank(0), next(nullptr), child(nullptr), il(nullptr), il_tail(nullptr){}
};

struct HEAD {
    NODE *queue;
    HEAD *next, *prev, *suffix_min;
    int rank;
};

class soft_heap{
private:
    HEAD *header, *tail, *explorer;
    NODE *Nexplorer;
    int r;

public:
    soft_heap() : header(nullptr), tail(nullptr), explorer(nullptr), Nexplorer(nullptr), r(0){}
    soft_heap(int value){
        header = new HEAD;
        tail = new HEAD;
        tail->rank = 255; //Inf
        header->next = tail;
        tail->prev = header;
        explorer = header;
        Nexplorer = nullptr;
        r = value;
    }

    void insert(int value){
        NODE *q;
        ILCELL *l;
        l = (ILCELL*)malloc(sizeof(ILCELL));
        l->key = value;
        l->next = nullptr;

        q = new NODE();
        q->rank = 0;
        q->ckey = value;
        q->il = l;
        q->il_tail = l;
        meld(q);
    }

    void meld(NODE *q){
        HEAD *h, *prevhead, *tohead = header->next;
        NODE *top, *botton;
        while (q->rank > tohead->rank){
            tohead = tohead->next;
        }
        prevhead = tohead->prev;
        while (q->rank == tohead->rank){
            if(tohead->queue->ckey > q->ckey){
                top = q;
                botton = tohead->queue;
            }
            else{
                top = tohead->queue;
                botton = q;
            }
            q = new NODE();
            q->ckey = top->ckey;
            q->rank = top->rank + 1;
            q->child = botton;
            q->next = top;
            q->il = top->il;
            q->il_tail = top->il_tail;
            tohead = tohead->next;
        }
        if(prevhead == tohead->prev){
            h = new HEAD();
        }
        else{
            h = prevhead->next;
        }
        h->queue = q;
        h->rank = q->rank;
        h->prev = prevhead;
        h->next = tohead;
        prevhead->next = h;
        tohead->prev = h;
        fix_minlist(h);
    }

    void fix_minlist(HEAD *h){
        HEAD *tmpmin;
        if (h->next == tail){
            tmpmin = h;
        }
        else{
            tmpmin = h->next->suffix_min;
        }
        while(h != header){
            if (h->queue->ckey < tmpmin->queue->ckey){
                tmpmin = h;
            }
            h->suffix_min = tmpmin;
            h = h->prev;
        }
    }

    NODE *sift(NODE *v){
        NODE *tmp;
        v->il = nullptr;
        v->il_tail = nullptr;
        if(v->next == nullptr && v->child == nullptr){
            v->ckey = 255;
            return v;
        }
        v->next = sift(v->next);
        if(v->next->ckey > v->child->ckey){
            tmp = v->child;
            v->child = v->next;
            v->next = tmp;
        }
        v->il = v->next->il;
        v->il_tail = v->next->il_tail;
        v->ckey = v->next->ckey;
        if(v->rank > r && (v->rank % 2 == 1 || v->child->rank < v->rank-1)){
            v->next = sift(v->next);
            if(v->next->ckey > v->child->ckey){
                tmp = v->child;
                v->child = v->next;
                v->next = tmp;
            }
            if(v->next->ckey != 255 && v->next->il != nullptr){
                v->next->il_tail->next = v->il;
                v->il = v->next->il;
                if(v->il_tail == nullptr){
                    v->il_tail = v->next->il_tail;
                }
                v->ckey = v->next->ckey;
            }
        }
        if(v->child->ckey == 255){
            if(v->next->ckey == 255){
                v->child = nullptr;
                v->next = nullptr;
            }
            else{
                v->child = v->next->child;
                v->next = v->next->next;
            }
        }
        return v;
    }
    int deletemin() {
        NODE *tmp;
        int min;
        HEAD *h = header->next->suffix_min;

        if(h->queue->il== NULL) 
        while (h->queue->il == nullptr) {
            tmp = h->queue;

            // Realiza un sifteo en la cola para mantener las propiedades del montículo
            h->queue = sift(h->queue);

            // Verifica si la cola quedó vacía después del sifteo
            if (h->queue->ckey == 255) {  // Si la cola está vacía
                h->prev->next = h->next;
                h->next->prev = h->prev;
                h = h->prev;
            }

            fix_minlist(h);  // Asegura que suffix_min se actualice correctamente

            // Si no hay elementos en la lista principal, indica que está vacía
            if (header->next == tail) {
                //cout << "Empty List" << endl;
                return 0;
            }

            // Actualiza h para apuntar al siguiente suffix_min
            h = header->next->suffix_min;
        }

        // Cuando se encuentra un elemento válido en la lista de elementos
        if (h->queue->il != nullptr) {
            min = h->queue->il->key;  // Obtiene la clave mínima de la lista de elementos
            h->queue->il = h->queue->il->next;  // Avanza al siguiente elemento en la lista de elementos
            if (h->queue->il == nullptr) {
                h->queue->il_tail = nullptr;
            }
            return min;
        } else {
            cout << "Error: Element not found" << endl;
            return -1;  // or another value indicating an error
        }
    }


    int findmin(){
        NODE *tmp;
        int min, childcount;
        HEAD *h = header->next->suffix_min;
        while (h->queue->il == nullptr){
            tmp = h->queue;
            childcount = 0;
            while(tmp->next != nullptr){
                tmp = tmp->next;
                childcount++;
            }
            if(childcount< h->rank/2){
                h->prev->next = h->next;
                h->next->prev = h->prev;
                fix_minlist(h->prev);
                tmp = h->queue;
                while(tmp->next != nullptr){
                    meld(tmp->child);
                    tmp = tmp->next;
                }
            }
            else{
                h->queue = sift(h->queue);
                if(h->queue->ckey == 255){
                    h->prev->next = h->next;
                    h->next->prev = h->prev;
                    h = h->prev;
                }
                fix_minlist(h);
            }
            if( header->next->suffix_min == nullptr){
                //cout<< "Empty List" << endl;
                return 0;
            }
            h = header->next->suffix_min;
        }
        min = h->queue->il->key;
        return min;
    }

    void print_headers() {
        HEAD *current = header->next;
        HEAD *tmpcurrent = header->next;
        if((header->next == nullptr)&&(explorer != header)){
            explorer = header;
        }
        if(explorer == header){
            cout << "  ↓   " << endl;
        }
        else{
            cout << "      ";
            while(tmpcurrent != explorer){
                cout << "      ";
                tmpcurrent = tmpcurrent->next;
            }
            cout << "     ↓"<<endl;
        }

        cout << "HEADER";
        while (current != tail){
            cout << " ←-→ "<<current->rank;
            current = current->next;
        }
        cout << " ←-→ TAIL" << endl;
    }
    void print2Dutil(NODE *root, int space) {
        if (root == nullptr)
            return;

        // Increase distance between levels
        space += 9;

        // Process right child first
        print2Dutil(root->child, space);

        // Print current node after space
        // count
        cout << endl;
        for (int i = 9; i < space; i++)
            cout << " ";
        if(root == Nexplorer){
            cout <<"→"<<root->ckey << "\n";
        }
        else{
            cout <<" "<<root->ckey << "\n";
        }

        // Process left child
        print2Dutil(root->next, space);
    }
    void print_queue() {
        NODE *current = explorer->queue;
        if(current == nullptr){
            cout << "Empty queue" << endl;
            return;
        }
        cout << "Queue:" << endl;
        print2Dutil(current, 0);

    }
    void print_il() {
        ILCELL *tmp = Nexplorer->il;
        if(tmp == nullptr){
            cout<<"item-list: empty"<<endl;
            return;
        }
        cout<<"item-list: ";
        while(tmp != nullptr){
            cout << tmp->key << ", ";
            tmp = tmp->next;
        }
        cout << endl;
    }
    void explorer_next() {
        if(explorer->next == nullptr){
            cout<<"out of border"<<endl;
            return;
        }
        else{
            explorer = explorer->next;
            Nexplorer = explorer->queue;
        }

    }

    void explorer_prev() {
        if(explorer->prev == nullptr){
            cout<<"out of border"<<endl;
            return;
        }
        else{
            explorer = explorer->prev;
            Nexplorer = explorer->queue;
        }
    }

    void Nexplore_next(){
        if(Nexplorer->next == nullptr){
            cout<<"you are in a leaf!!!"<<endl;
            return;
        }
        else{
            Nexplorer = Nexplorer->next;
        }
    }

    void Nexplore_child(){
        if(Nexplorer->child == nullptr){
            cout<<"you are in a leaf!!!"<<endl;
            return;
        }
        else{
            Nexplorer = Nexplorer->child;
        }
    }
    void print_Node_information(){
        cout<<"key: "<<Nexplorer->ckey<<endl;
        cout<<"rank: "<<Nexplorer->rank<<endl;
        print_il();

    }
    void reset_explorer(){
        explorer = header;
        Nexplorer = nullptr;
    }
    void reset_Nexplorer(){
        Nexplorer = explorer->queue;
    }
};
