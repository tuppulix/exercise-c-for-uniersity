#include <iostream>
#include <cmath>
using namespace std;

class Shape{

    double virtual getarea()= 0;

};


class Triangolo: public Shape{
    float b;
    float l;
    float h;
public:
    Triangolo(float b=0,float l=0, float h=0){
        this->b=b;
        this->l=l;
        this->h=h;
    }

    void setbase(float b){this->b=b;}
    void setlato(float l){this->l=l;}
    void setaltezza(float h){this->h=h;}

    double getarea(){
        return l*h;
    }


    bool operator < (Triangolo g){
        if(this->getarea()<g.getarea())
            return true;

        else
            return false;
    }

    friend
    ostream& operator<<(ostream& out, Triangolo& t){
        out<<"base: "<<t.b<<"\n"<<"altezza: "<<t.h<<"\n"<<"lato: "<<t.l<<"\n"<<"area: "<<t.getarea()<<endl;
        return out;
    }

};

class Rettangolo: public Shape{
    float b;
    float h;
public:
    Rettangolo(float b=5, float h=3){
        this->b=b;
        this->h=h;
    }

    double getarea(){
        return b*h;
    }

    void setbaser(float b){this->b=b;}
    void seth(float h){this->h=h;}

    
    bool operator < (Rettangolo g){
        if(this->getarea()<g.getarea())
            return true;

        else
            return false;
    }

    friend
    ostream& operator<<(ostream& out, Rettangolo& t){
        out<<"base: "<<t.b<<"\n"<<"altezza: "<<t.h<<"\n"<<"area: "<<t.getarea()<<endl;
        return out;
    }

};

class Circonferenza: public Shape{
    float r;
public:
    Circonferenza(float r=4){
        this->r=r;
    }
    

    void setraggio(float n){
         r=n;
    }

    double getarea(){
        return (2*M_PI)*r;
    }

    bool operator < (Circonferenza g){
        if(this->getarea()<g.getarea())
            return true;

        else
            return false;
    }

    friend
    ostream& operator<<(ostream& out, Circonferenza& t){
        out<<"raggio: "<<t.r<<"\n"<<"area: "<<t.getarea()<<endl;
        return out;
    }
};

template <class T>
class Nodo{
public:
    T val;
    Nodo<T>* parent;
    Nodo<T>* right;
    Nodo<T>* left;

    Nodo(){
        parent=nullptr;
        right=nullptr;
        left=nullptr;
    }
};

template <class T>
class BST {
private:
    Nodo<T>* root;

    void inOrder(Nodo<T>* p){
      if(p!=nullptr){
        inOrder(p->left);
        cout << p->val;
        cout<<endl;
        inOrder(p->right);
        
     }
    }
    

public:

        BST():root(nullptr){
             root=NULL;
        }

    void Insert(T valore){
        Nodo<T>* nuovo=new Nodo<T>;
        Nodo<T>* x=root, *y=nullptr;

        nuovo->val=valore;
        nuovo->left=nuovo->right=nullptr;

        while(x!=nullptr){
            y=x;
            if(valore<x->val)
                x=x->left;
            else
                x=x->right;
        }
        
        nuovo->parent=y;
        if(y==nullptr)
            root=nuovo;
        else if(valore<y->val)
            y->left=nuovo;
        else
            y->right=nuovo;
    }
    

    void trapianta(Nodo<T>* u, Nodo<T>* v){

        if(u->parent == nullptr) // se u e' la radice
            root = v;
        else if (u == u->parent->left) // se u e' figlio sx di suo padre
            u->parent->left = v;
        else
            u->parent->right = v;
        if(v!=nullptr)
            v->parent = u->parent;
    }

    void cancella(Nodo<T>* z){
     Nodo<T>* y;
        //Caso 1: z ha un solo figlio
        if(z->left == nullptr)
            trapianta(z, z->right); // z non ha figlio sx
        else if(z->right == nullptr)
            trapianta(z, z->left); // z non ha figlio dx
        // altrimenti... caso 3: z ha entrambi i figli
        else{
            y = minimo(z->right); // y sara' il successore di z
            // se y non e' figlio di z devo gestire y.right e z.right
            if(y->parent!=z){ // caso 3 generale
                trapianta(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            trapianta(z,y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
}


    bool cancella(int x){
        Nodo<T>* iter = root;
        // ricerca di un nodo con chiave x
        while((iter!=nullptr) && (x!=iter->val)){
            if(x< iter->val)
                iter = iter->left;
            else
                iter = iter->right;
        }
        if(iter == nullptr)
            return false;
        // chiamo la procedura privata
        cancella(iter);
        return true;
    }

    void inOrder()  {inOrder(root);}
    

    Nodo<T>* minimo(Nodo<T>* x){
        Nodo<T>* nMin =x;
        while(nMin->left != nullptr)
            nMin = nMin->left;
        return nMin;
    }
    
    void inOrdereliminazione(Nodo<T>* p, float j){
      if(p!=nullptr){
        Nodo<T>* iter=nullptr;
        inOrdereliminazione(p->left,j);
        iter=p->right;
        if(p->val.getarea()<j){
        cancella (p);
        }
        cout<<endl;
        inOrdereliminazione(iter,j);
     }
    }

    Nodo<T>* getnodo(){
        return root;

    }
    

};


int main(){

int N;
cout<<"inserisci il numero di elementi di tipo Circonferenza: ";
cin>>N;
cout<<endl;
BST<Circonferenza> cir;
Circonferenza* c= new Circonferenza [N];
    for (int i =0 ; i < N; i++){
        int k;
        cout<<"inserisci i valori della circonferenza di elemento "<<i<<" : ";
        cin>>k;
        c->setraggio(k);
        c[i]=Circonferenza(k);
        cir.Insert(*c);
        cout<<"elemento: "<<i<<" creato."<<endl<<endl;

    }
    cir.inOrder();
        cout<<endl;
    

int M;
cout<<"inserisci il numero di elementi di tipo triangolo: ";
cin>>M;
cout<<endl;
BST<Triangolo> tri;
Triangolo* t=new Triangolo[M];
    for (int i = 0; i < M; i++){
        float b;
        float h;
        float l;
        cout<<"inserisci i valori della base di elemento "<<i<< " : ";
        cin>>b;
        cout<<"inserisci i valori dell' altezza di elemento "<<i<< " : ";
        cin>>h;
        cout<<"inserisci i valori del lato di elemento "<<i<< " : ";
        cin>>l;
        t->setbase(b);
        t->setlato(l);
        t->setaltezza(h);
        t[i]=Triangolo(b,l,h);        
        tri.Insert(*t);
        cout<<"elemento: "<<i<<" creato."<<endl<<endl;
        
    }
    
    tri.inOrder();
        cout<<endl;
    
int K;
cout<<"inserisci il numero di rettangoli: ";
cin>>K;
cout<<endl;
BST<Rettangolo> ret;
Rettangolo* r=new Rettangolo[K];
    for (int i = 0; i <K ; i++){
        float b;
        float h;
        cout<<"inserisci il valore della base di elemento "<<i<< " :";
        cin>>b;
        cout<<"inserisci il valore dell'altezza di elemento "<<i<< " :";
        cin>>h;
        r->setbaser(b);
        r->seth(h);
        r[i]=Rettangolo(b,h);
        ret.Insert(*r);
        cout<<"elemento: "<<i<<" creato"<<endl<<endl;
       
    }
     ret.inOrder();
        cout<<endl;
  


    float a_eliminazione;
    cout<<"inserisci l'area sotto la quale gli oggetti verranno eliminati: ";
    cin>>a_eliminazione;

    cout<<"Circonferenze: "<<endl;
    cir.inOrdereliminazione(cir.getnodo(),a_eliminazione);
    cir.inOrder();
        cout<<endl;
    cout<<"Triangoli: "<<endl;
    tri.inOrdereliminazione(tri.getnodo(),a_eliminazione);
    tri.inOrder();
        cout<<endl;
    cout<<"Rettangolo: "<<endl;
    ret.inOrdereliminazione(ret.getnodo(),a_eliminazione);
    ret.inOrder();
        cout<<endl;
    
}