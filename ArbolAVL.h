#ifndef _ARBOLAVL_H
#define _ARBOLAVL_H
#include "NodoAVL.h"
template <class T>
class ArbolAVL{
    private:
        NodoAVL<T>* head;
        bool insertNode(NodoAVL<T>* toCompare, NodoAVL<T>*& node);
        bool nodeBalanced(NodoAVL<T>* node);
    public:
        bool balanced();
        bool balance(NodoAVL<T>*& node);
        ArbolAVL();
        ArbolAVL(T data);
        ArbolAVL(NodoAVL<T>*& head);
        ~ArbolAVL();
        NodoAVL<T>* getHead();
        void setHead(NodoAVL<T>*& head);
        NodoAVL<T>* insertNode(NodoAVL<T>*& node);
        NodoAVL<T>* insertNode(T node);
        NodoAVL<T>* removeNodeMinor(NodoAVL<T>*& node);
        NodoAVL<T>* removeNodeGreater(NodoAVL<T>*& node);
        bool removeNode(NodoAVL<T>*& node);
        bool removeNode(T node);
        NodoAVL<T>* searchNodeFather(NodoAVL<T>* node);
        NodoAVL<T>* searchNodeFather(T node);
        std::string printTree();
        std::string inOrder(bool string);
        std::list<NodoAVL<T>*> inOrder();
        std::string preOrder();
        std::string postOrder();
        std::string levelOrder();
        int height();
};
#include "ArbolAVL.hxx"
#endif

