#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

template <class H>
class Node
{
public:
    H key;
    Node<H> *left;
    Node<H> *right;
    Node<H> *parent;

    Node(H k)
    {
        parent = left = right = NULL;
        key = k;
    }
};

template <class H>
class BST
{
public:
    Node<H> *root;

    BST()
    {
        root = NULL;
    }

    BST *insert(H k)
    {
        Node<H> *newNode = new Node<H>(k);
        if (root == NULL)
            root = newNode;
        else
        {
            Node<H> *iter = root;
            Node<H> *prev = nullptr;

            while (iter)
            {
                prev = iter;
                iter = (k < iter->key) ? iter->left : iter->right;
            }

            newNode->parent = prev;

            if (k < prev->key)
                prev->left = newNode;
            else
                prev->right = newNode;
        }
        return this;
    }

    // void leftRotate(Node<H> *node)
    // {
    //     if (!node->right)
    //         return;
        
    // }

    void inorder(Node<H> *node)
    {
        if (node)
        {
            inorder(node->left);
            out << node->key << " ";
            inorder(node->right);
        }
    }

    void preorder(Node<H> *node)
    {
        if (node)
        {
            out << node->key << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node<H> *node)
    {
        if (node)
        {
            postorder(node->left);
            postorder(node->right);
            out << node->key << " ";
        }
    }
};

template <class H>
class Task
{
public:
    Task(int n, int m, string p)
    {
        BST<H> *bst = new BST<H>();

        for (int i = 0; i < n; i++)
        {
            char x;
            in >> x;

            if (x == 'i')
            {
                in >> x; //'n'
                in >> x; //'s'
                in >> x; //':'

                H v;
                in >> v;
                bst->insert(v);
                // out << "Inserisco " << v << ", ";
            }
            if (x == 'c')
            {
                in >> x; //'a'
                in >> x; //'n'
                in >> x; //'c'
                in >> x; //':'

                H v;
                in >> v;
                // bst->remove(v);
                // out << "Rimuovo " << v << ", ";
            }
        }

        for (int i = 0; i < m; i++)
        {
            char x;
            in >> x;

            if (x == 'l')
            {
                in >> x; //'e'
                in >> x; //'f'
                in >> x; //'t'
                in >> x; //':'

                H v;
                in >> v;
                // bst->leftRotation(v);
                // out << "Ruoto a sinistra " << v << ", ";
            }
            if (x == 'r')
            {
                in >> x; //'i'
                in >> x; //'g'
                in >> x; //'h'
                in >> x; //'t'
                in >> x; //':'

                H v;
                in >> v;
                // bst->rightRotation(v);
                // out << "Ruoto a destra " << v << ", ";
            }
        }

        if (p == "inorder")
            bst->inorder(bst->root);
        if (p == "preorder")
            bst->preorder(bst->root);
        if (p == "postorder")
            bst->postorder(bst->root);
        out << endl;
    }
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        string type, printOrder;
        int operations, rotations;

        in >> type;
        in >> operations;
        in >> rotations;
        in >> printOrder;

        if (type == "int")
            Task<int> *t = new Task<int>(operations, rotations, printOrder);
        if (type == "double")
            Task<double> *t = new Task<double>(operations, rotations, printOrder);
    }
    return 0;
}