#include<iostream>
#include<string>
using namespace std;

struct Nodo{
    int val;
    Nodo* next;
    Nodo* previus;
};

class circuit{
    private:
        Nodo* nodoAct;

    public:
        circuit(){
            nodoAct = NULL;
        }

        int value(){
            if (this->nodoAct == NULL){
                cout << "Segmentation fault in circuit" << endl;
                return -1;
            };
            return (this->nodoAct)->val;
        }

        void addNextValue(int val){
            Nodo *nodo =(Nodo*) malloc(sizeof(Nodo));
            nodo->val = val;

            if (this->nodoAct == NULL){    
                nodo->previus = nodo;
                nodo->next = nodo;
            }else{
                ((this->nodoAct)->next)->previus = nodo;
                nodo->next = (this->nodoAct)->next;
                (this->nodoAct)->next = nodo;
                nodo->previus = this->nodoAct;
            }

            this->nodoAct = nodo;
        }

        void next(){this->nodoAct = (this->nodoAct)->next;}

        void previus(){this->nodoAct = (this->nodoAct)->previus;}

        void erase(){
            if(this->nodoAct == NULL) return;

            if((this->nodoAct)->next == (this->nodoAct)){
                free(this->nodoAct);
                this->nodoAct = NULL;
                return;
            }

            Nodo* previus = (this->nodoAct)->previus;
            Nodo* next = (this->nodoAct)->next;
            previus->next = next;
            next->previus = previus;

            Nodo* th = this->nodoAct;
            (this->nodoAct) = (this->nodoAct)->next;
            free(th);
        }

        void deletCircuit(){
            while(this->nodoAct != NULL){
                this->erase();
            }
        }
};

int main(){
    circuit a = circuit();
    a.erase(); //No deberia presentar problemas

    a.addNextValue(1);
    if(a.value() != 1){ //Es para revisar la el primer agregar
        cout << "Ay un error al agregar el primer valor" << endl;
        return 1;
    }
    a.erase();
    if(a.value() != -1){
        cout << "Un solo elemento se elimina mal" << endl;
        return 1;
    }
    else{
        cout << "Si dice 'Segmentation fault in circuit'. Entonces esta funcionando correctamente  \n";
    }

    a.addNextValue(1);
    a.addNextValue(2);
    a.addNextValue(3);
    a.previus(); // dejamos a en "2"
    if (a.value() != 2){
        cout << "Mal ejecutado la funcion" << endl;
        return 1;
    }
    a.erase(); //Borramos 2
    
    if(a.value() != 3){
        cout << "No deberia ser distinto de 3" << endl;
        return 1;
    }
    a.next();

    if(a.value() != 1){
        cout << "Ay un error en el next" << endl;
        return 1;
    }

    a.next();

    if(a.value() != 3){
        cout << "El circulo se ronpio" << endl;
    }
    
    a.deletCircuit();
    if(a.value() != -1){
        cout << "Hay un error al eliminar todo el circuito" << endl;
        return 1;
    }
    else{
        cout << "Si dice 'Segmentation fault in circuit'. Entonces esta funcionando correctamente  \n";
    }

}
