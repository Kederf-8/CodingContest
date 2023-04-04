#include <iostream>
#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");
#define B 0
#define R 1

template <class H>
class Nodo
{
public:
    Nodo<H> *sx, *dx, *p;
    H key;
    bool color;
    Nodo(H key) : key(key), sx(NULL), dx(NULL), p(NULL), color(R) {}
};

template <class H>
class RBT
{
private:
    Nodo<H> *root;

    void _inorder(Nodo<H> *n)
    {
        if (n != NULL)
        {
            _inorder(n->sx);
            char c;
            if (n->color == B)
                c = 'B';
            else
                c = 'R';
            out << "(" << n->key << " " << c << ") ";
            _inorder(n->dx);
        }
    }
    void _postorder(Nodo<H> *n)
    {
        if (n != NULL)
        {
            _postorder(n->sx);
            _postorder(n->dx);
            char c;
            if (n->color == B)
                c = 'B';
            else
                c = 'R';
            out << "(" << n->key << " " << c << ") ";
        }
    }
    void _preorder(Nodo<H> *n)
    {
        if (n != NULL)
        {
            char c;
            if (n->color == B)
                c = 'B';
            else
                c = 'R';
            out << "(" << n->key << " " << c << ") ";
            _preorder(n->sx);
            _preorder(n->dx);
        }
    }

public:
    RBT() : root(NULL) {}

    void trapianta(Nodo<H> *x, Nodo<H> *y)
    { // trapiantare i nodi x e y
        if (x->p == NULL)
            root = y; // se x non ha padre allora y diventa root
        else if (x->p->dx == x)
            x->p->dx = y; // se il padre ha come figlio destro x allora il destro diventa y
        else
            x->p->sx = y; // altrimenti il contrario

        if (y != NULL)
            y->p = x->p; // se y è diverso da NULL il padre di y sarà lo stesso di x
    }

    void rleft(Nodo<H> *x)
    {
        if (x != NULL)
        {
            Nodo<H> *y = x->dx;
            if (y != NULL)
            {
                x->dx = y->sx;
                if (x->dx != NULL)
                    x->dx->p = x;
            }
            trapianta(x, y);
            y->sx = x;
            x->p = y;
        }
    }

    void rright(Nodo<H> *x)
    {
        if (x != NULL)
        {
            Nodo<H> *y = x->sx;
            if (y != NULL)
            {
                x->sx = y->dx;
                if (x->sx != NULL)
                    x->sx->p = x;
            }
            trapianta(x, y);
            y->dx = x;
            x->p = y;
        }
    }

    void insert_fixup(Nodo<H> *nuovo)
    {
        if (nuovo->p != NULL && nuovo->p->color == B)
            return; // caso padre nero ritorna
        if (root == nuovo)
        { // caso di un nodo si cambia colore perchè è la radice
            nuovo->color = B;
            return;
        }
        Nodo<H> *padre = nuovo->p;
        Nodo<H> *nonno = padre->p;
        Nodo<H> *zio = nonno->dx;
        if (nonno->dx == padre)
            zio = nonno->sx; // controllo per vedere chi è lo zio dx o sx

        if (zio != NULL && zio->color == R)
        { // caso zio rosso padre rosso
            zio->color = B;
            padre->color = B;
            nonno->color = R;
            insert_fixup(nonno);
            return;
        }

        if (nonno->sx == padre)
        { // caso nodo rosso figlio destro con padre rosso
            if (padre->dx == nuovo)
            {
                rleft(padre);
                padre = nuovo;     // adesso il padre è il nuovo nodo
                nuovo = padre->sx; // il figlio sinistro di padre diventa nuovo
                // invertendo le posizioni si registra l'inversione di ruoli
            }
            rright(nonno); // si ruota a destra sul nonno
            nonno->color = R;
            padre->color = B;
            return;
        }
        else
        { // caso nodo rosso figlio sinistro con padre rosso
            if (padre->sx == nuovo)
            {
                rright(padre);
                padre = nuovo;
                nuovo = padre->dx;
            }
            nonno->color = R;
            padre->color = B;
            rleft(nonno);
            return;
        }
    }

    void insert(H x)
    {
        Nodo<H> *nuovo = new Nodo<H>(x);
        Nodo<H> *r = root;
        Nodo<H> *tmp = NULL;
        while (r != NULL)
        {            // se già ci sono nodi e quindi la radice non è nulla entra nel ciclo
            tmp = r; // conserviamo il valore della radice/padre
            if (x >= r->key)
                r = r->dx; // si scende per posizionare il nodo
            else
                r = r->sx;
            // si ritorna indietro con r che sarà sceso di un livello
            // arriverà a destinazione quando incontra una foglia null che è la posizione
            // che dovrà prendere
        }
        nuovo->p = tmp; // il padre di nuovo sarà tmp che è il nodo padre della foglia null
        if (tmp == NULL)
            root = nuovo; // caso in cui non ci sono nodi quindi r sopra era uguale a null al primo ciclo
        else if (x >= tmp->key)
            tmp->dx = nuovo; // si fa l'ultimo controllo per vedere se
        else
            tmp->sx = nuovo; // posizionare nuovo a dx o sx
        insert_fixup(nuovo); // si fixano eventuali errori di colore.
    }

    void preorder()
    {
        _preorder(root);
    }
    void postorder()
    {
        _postorder(root);
    }
    void inorder()
    {
        _inorder(root);
    }
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        string type;
        in >> type;
        int n;
        in >> n;
        string stampa;
        in >> stampa;
        if (type == "int")
        {
            RBT<int> *t = new RBT<int>();
            for (int j = 0; j < n; j++)
            {
                int a;
                in >> a;
                t->insert(a);
            }
            if (stampa == "preorder")
                t->preorder();
            else if (stampa == "inorder")
                t->inorder();
            else
                t->postorder();
            out << endl;
        }
        else
        {
            RBT<double> *t = new RBT<double>();
            for (int j = 0; j < n; j++)
            {
                double a;
                in >> a;
                t->insert(a);
            }
            if (stampa == "preorder")
                t->preorder();
            else if (stampa == "inorder")
                t->inorder();
            else
                t->postorder();
            out << endl;
        }
    }
}