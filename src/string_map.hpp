#define CANTCHAR 256
#include <stack>



template <typename T>
string_map<T>::string_map(){
    _size = 0;
    raiz = new Nodo;
    raiz->siguientes = new Nodo*[CANTCHAR];

    for(int i = 0; i < CANTCHAR; i++){
        raiz->siguientes[i] = nullptr;
    }
    raiz->definicion = nullptr;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } 

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    delete raiz;
    _size = d.size();

    raiz = copiarNodos(d.raiz);
}

template <typename T>
typename string_map<T>::Nodo * string_map<T>::copiarNodos(Nodo *nodoACopiar) {
    if (nodoACopiar == nullptr){
        return nodoACopiar;
    }
    Nodo* nuevoNodo = new Nodo;

    if(nodoACopiar->definicion == nullptr){
        nuevoNodo->definicion = nullptr;
    }
    else{
        nuevoNodo->definicion = new T;
        *(nuevoNodo->definicion) = *(nodoACopiar->definicion);
    }
    nuevoNodo->siguientes = new Nodo*[CANTCHAR];

    for(int i = 0; i < CANTCHAR; i++){
        nuevoNodo->siguientes[i] = copiarNodos(nodoACopiar->siguientes[i]);
    }
    return nuevoNodo;
}

template <typename T>
string_map<T>::~string_map(){
    delete raiz;
    raiz = nullptr;
    _size = 0;
}

//

template <typename T>
string_map<T>::Nodo::~Nodo() {

    delete definicion;
    for(int i = 0; i < CANTCHAR; i++){
        delete (siguientes[i]);
    }
    delete[] siguientes;
}


template <typename T>
T& string_map<T>::operator[](const string& clave){

    Nodo* nodoActual = raiz;

    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        if(nodoActual->siguientes[pos] == nullptr){

            nodoActual->siguientes[pos] = new Nodo;
            nodoActual->siguientes[pos]->definicion = nullptr;
            nodoActual->siguientes[pos]->siguientes = new Nodo*[CANTCHAR];

            for(int j = 0; j < CANTCHAR; j++){
                nodoActual->siguientes[pos]->siguientes[j] = nullptr;
            }
        }

        nodoActual = nodoActual->siguientes[pos];
    }

    if(nodoActual->definicion == nullptr){
        nodoActual->definicion = new T;
        _size++;
    }
    return *(nodoActual->definicion);
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    Nodo* nodoActual = raiz;

    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        nodoActual = nodoActual->siguientes[pos];

        if(nodoActual == nullptr){
            return 0;
        }
    }
    if(nodoActual->definicion == nullptr){
        return 0;
    }

    return 1;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* nodoActual = raiz;

    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        nodoActual = nodoActual->siguientes[pos];
    }
    return nodoActual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* nodoActual = raiz;

    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        nodoActual = nodoActual->siguientes[pos];
    }
    return nodoActual->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    std::stack<std::pair<Nodo*, int>> padres;
    Nodo* nodoActual = raiz;
    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);
        padres.emplace(nodoActual, pos);

        nodoActual = nodoActual->siguientes[pos];
    }
    delete nodoActual->definicion;
    nodoActual->definicion = nullptr;

    _size--;

    while(!padres.empty()){
        nodoActual = padres.top().first;
        int vinoDe = padres.top().second;

        if(sonHijosNulos(nodoActual->siguientes[vinoDe])){
            delete nodoActual->siguientes[vinoDe];
            nodoActual->siguientes[vinoDe] = nullptr;
        }
        padres.pop();
    }
}

template <typename T>
bool string_map<T>::sonHijosNulos(Nodo *nodoARevisar) {
    bool sonNulos = true;
    for(int i = 0; i < CANTCHAR; i++){
        if(nodoARevisar->siguientes[i] != nullptr){
            sonNulos = false;
            break;
        }
    }

    return sonNulos;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}