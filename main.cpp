#include <iostream>

using namespace std;

///PERSONA
class Persona{
    private:
        string nombre;
        string prioridad;
    public:
        Persona();
        ~Persona();
        Persona(string, string);
        string getNombre();
        string getPrioridad();
};
Persona::Persona(string _nombre, string _prioridad){
    nombre=_nombre;
    prioridad=_prioridad;
}
Persona::Persona(){}
Persona::~Persona(){}
string Persona::getNombre(){
    return nombre;
}
string Persona::getPrioridad(){
    return prioridad;
}
///NODO
class Nodo{
    private:
        Persona persona;
    public:
        Nodo *sgte;
        Nodo(Persona);
        ~Nodo();
        Persona getPersona();
};
Nodo::Nodo(Persona _persona){
    persona=_persona;
    sgte=NULL;
}
Nodo::~Nodo(){}
Persona Nodo::getPersona(){
    return persona;
}
///COLA
class Cola{
    private:
        Nodo *primero,*ultimo;
        int cantNodos;
    public:
        Cola();
        ~Cola();
        bool Empty();
        void Push(Persona);
        void Pop();
        Persona Front();
        Persona Back();
        int Size();
};
Cola::Cola(){
    primero=ultimo=NULL;
    cantNodos=0;
}
Cola::~Cola(){}
bool Cola::Empty(){
    return primero==NULL;
}
void Cola::Push(Persona persona){
    Nodo *nuevoNodo=new Nodo(persona), *auxCola=primero;
    if(Empty()){
        primero=ultimo=nuevoNodo;
        cantNodos++;
    }
    else{
        while(auxCola->sgte!=NULL)
            auxCola=auxCola->sgte;
        auxCola->sgte=ultimo=nuevoNodo;
        cantNodos++;
    }
}
void Cola::Pop(){
    Nodo *nodoBorrar=primero;
    if(Empty())
        cout<<"La cola no contiene elementos"<<endl;
    else{
        primero=primero->sgte;
        delete(nodoBorrar);
        cantNodos--;
    }
}
Persona Cola::Front(){
    return primero->getPersona();
}
Persona Cola::Back(){
    return ultimo->getPersona();
}
int Cola::Size(){
    return cantNodos;
}

void mostrarCola(Cola &cola){
    Cola aux;

    ///MOSTRANDO COLA
    while(!cola.Empty()){
        cout<<"Nombre cliente: "<<cola.Front().getNombre()<<"       Prioridad Cliente: "<<cola.Front().getPrioridad()<<endl;
        aux.Push(cola.Front());
        cola.Pop();
    }

    ///LLENANDO COLA
    while(!aux.Empty()){
        cola.Push(aux.Front());
        aux.Pop();
    }
}
void cambiarDeCola(Cola &normal, Cola &especial){
    Cola aux;

    ///RECORRIENDO LA COLA PRINCIPAL
    while(!normal.Empty()){
        if(normal.Front().getPrioridad() == "maxima"){
            especial.Push(normal.Front());
            normal.Pop();
        }
        else{
            aux.Push(normal.Front());
            normal.Pop();
        }
    }

    ///LLENANDO LA COLA NORMAL
    while(!aux.Empty()){
        normal.Push(aux.Front());
        aux.Pop();
    }
}


int main()
{
    Cola colaBanco;
    Cola colaBancoEspecial;

    ///PERSONAS QUE LLEGAN AL BANCO
    Persona cliente1("Fabian", "normal");
    Persona cliente2("Lucho", "normal");
    Persona cliente3("Pancho", "maxima");
    Persona cliente4("Piter", "normal");
    Persona cliente5("Sancho", "maxima");
    Persona cliente6("Manucho", "maxima");

    ///LLENANDO COLA
    colaBanco.Push(cliente1);
    colaBanco.Push(cliente2);
    colaBanco.Push(cliente3);
    colaBanco.Push(cliente4);
    colaBanco.Push(cliente5);
    colaBanco.Push(cliente6);

    ///MOSTRANDO COLA
    mostrarCola(colaBanco);

    ///CAMBIANDO DE COLA
    cambiarDeCola(colaBanco, colaBancoEspecial);

    ///MOSTRANDO AMBAS COLAS
    cout<<endl;
    cout<<"Cola normal del banco:"<<endl;
    mostrarCola(colaBanco);
    cout<<endl;
    cout<<"Cola especial del banco:"<<endl;
    mostrarCola(colaBancoEspecial);

    return 0;
}
