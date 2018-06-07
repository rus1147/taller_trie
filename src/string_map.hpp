template <typename T>
string_map<T>::string_map(){
    raiz=NULL;
    int size=0;
}
template <class T>
string_map<T>::Nodo::~Nodo() {
    delete siguientes;
}
template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    string_map<T> actual=d;
    return actual;
}

template <typename T>
string_map<T>::~string_map(){
    if(raiz!=NULL){
        delete raiz;
    }
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    if(raiz!=NULL){
        if(count(clave)==1){
            return buscarSignificado(clave);
        }
    } else{
        
    }
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if(raiz!=NULL){
        Nodo* aux=raiz;
        ///defino un int para contar la cantidad de iteraciones del for, cuando se cumple la guarda del if.
        int i=0;
        for(int j=0;j<clave.size();j++){
            int indice= int(clave[j]);  ///casteo a int para verificar que el char este en el indice
            if(aux->siguientes[indice]!=NULL){
                aux=aux->siguientes[indice];
                i=j;
            }
            ///se itera i-tamdeclave veces, verificando que el indice del vector siguiente, tenga dicho valor entero definido

        }
        if(i==clave.size()){
            return 1;
        }
    }
    return 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // COMPLETAR
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
}

template <typename T>
int string_map<T>::size() const{

}

template <typename T>
bool string_map<T>::empty() const{
    return raiz==NULL;
}
template <typename T>
T string_map<T>::buscarSignificado(const string& clave) const{
    if(raiz!=NULL){
        Nodo* aux=raiz;
        ///defino un int para contar la cantidad de iteraciones del for, cuando se cumple la guarda del if.
        int i=0;
        T sig;
        for(int j=0;j<clave.size();j++){
            int indice= int(clave[j]);  ///casteo a int para verificar que el char este en el indice
            if(aux->siguientes[indice]!=NULL){
                aux=aux->siguientes[indice];
                i=j;
                sig=aux->siguientes[indice]->definicion;
            }
            ///se itera i-tamdeclave veces, verificando que el indice del vector siguiente, tenga dicho valor entero definido

        }
        if(i==clave.size()){
            return sig;
        } /*else{
            Nodo*nuevo= new Nodo;
            aux->siguientes= reinterpret_cast<Nodo **>(nuevo);
        }*/
    }
    return NULL;

}