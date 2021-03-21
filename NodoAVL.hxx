#include "NodoAVL.h"
//#include <iostream>
template <class T>
T NodoAVL<T>::getData(){
    return this->data;
}

template <class T>
NodoAVL<T>::NodoAVL(T data){
    this->left=NULL;
    this->right=NULL;
    this->data=data;
}

template <class T>
NodoAVL<T>::~NodoAVL(){
    if (this->left)
        delete this->left;
    if (this->right)
        delete this->right;
}

template<class T>
NodoAVL<T>* NodoAVL<T>::getLeft(){
    return this->left;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::getRight(){
    return this->right;
}

template <class T>
void NodoAVL<T>::setData(T data){
    this->data=data;
}

template <class T>
void NodoAVL<T>::setLeft(NodoAVL<T>*& left){
    this->left=left;
}

template <class T>
void NodoAVL<T>::setRight(NodoAVL<T>*& right){
    this->right=right;
}

template <class T>
int NodoAVL<T>::compareTo(T data){
    if(this->data>data)
        return 1;
    else if(this->data<data) 
        return-1;
    else
        return 0;
}

template <class T>
int NodoAVL<T>::compareTo(NodoAVL<T>*& c){
    if(this->data>c->getData())
        return 1;
    else if(this->data<c->getData()) 
        return-1;
    else
        return 0;
}

template <class T>
std::string NodoAVL<T>::toString(int level, std::string car){
    std::string ret="";
    for (int i=0; i<level; i++)
        ret+="\t\t";
    ret+=car;
    ret+=this->toString(true);
    ret+="\n";
    if (this->right!=NULL)
        ret+=this->right->toString(level+1, "Right: ");
    ret+="\n\n";
    if (this->left!=NULL)
        ret+=this->left->toString(level+1, "Left: ");
    ret+='\n';
    return ret;
}

template <class T>
std::string NodoAVL<T>::toString(bool unique){
    std::string ret="- ";
    ret+="\'";
    try{
        ret+=this->getData();
    } catch (...){
        ret+=this->getData();
    }
    ret+="\'";
    ret+=" ";
    return ret;
}

template <class T>
std::string NodoAVL<T>::inOrder(bool string){
    std::string ret="";
    if (this->left!=NULL)
        ret+=this->left->inOrder(true);
    ret+=this->toString(true);
    if (this->right!=NULL)
        ret+=this->right->inOrder(true);
    return ret;        
}

template <class T>
std::list<NodoAVL<T>*> NodoAVL<T>::inOrder(){
    std::list<NodoAVL<T>*> ret;
    std::list<NodoAVL<T>*> ret2;
    if (this->left!=NULL){
        ret2=this->left->inOrder();
        for (typename std::list<NodoAVL<T>*>::iterator it=ret2.begin(); it!=ret2.end(); advance(it,1))
            ret.push_back((*it));
    }
    ret.push_back(this);
    if (this->right!=NULL){
        ret2=this->right->inOrder();
        for (typename std::list<NodoAVL<T>*>::iterator it=ret2.begin(); it!=ret2.end(); advance(it,1))
            ret.push_back((*it));
    }
    return ret;        
}

template <class T>
std::string NodoAVL<T>::preOrder(){
    std::string ret="";    
    ret+=this->toString(true);
    if (this->left!=NULL)
        ret+=this->left->preOrder();
    if (this->right!=NULL)
        ret+=this->right->preOrder();
    return ret;        
}

template <class T>
std::string NodoAVL<T>::postOrder(){
    std::string ret="";
    if (this->left!=NULL)
        ret+=this->left->postOrder();
    if (this->right!=NULL)
        ret+=this->right->postOrder();
    ret+=this->toString(true);
    return ret;        
}

template <class T>
NodoAVL<T>* NodoAVL<T>::subMinor(){
    NodoAVL<T>* ret=this;
    if (!this->right)
        return ret;
    ret=this->right;
    while (ret->left)
        ret=ret->left;
    return ret;        
}

template <class T>
NodoAVL<T>* NodoAVL<T>::subGreater(){
    NodoAVL<T>* ret=this;
    if (!this->left)
        return ret;
    ret=this->left;
    while (ret->right)
        ret=ret->right;
    return ret; 
}

template <class T>
NodoAVL<T>* NodoAVL<T>::removeSubMinor(){
    NodoAVL<T>* ret=this;
    NodoAVL<T>* ret2=NULL;
    if (!this->right)
        return ret2;
    ret=this->right;
    if (!ret->left){
        this->right=ret->right;
        this->data=ret->data;
        ret=NULL;
        return ret;
    }
    while (ret->left->left)
        ret=ret->left;
    ret2=ret->left;
    ret->left=ret->left->right;
    this->data=ret2->getData();
    return ret2;     
}

template <class T>
NodoAVL<T>* NodoAVL<T>::removeSubGreater(){
    NodoAVL<T>* ret=this;
    NodoAVL<T>* ret2=NULL;
    if (!this->left)
        return ret2;
    ret=this->left;
    if (!ret->right){
        this->left=ret->left;
        this->data=ret->data;
        ret=NULL;
        return ret;
    }
    while (ret->right->right)
        ret=ret->right;
    ret2=ret->right;
    ret->right=ret->right->left;
    this->data=ret2->getData();
    return ret2;
}

template <class T>
int NodoAVL<T>::height(int acu){
    if (!(this->left||this->right))
        return acu;
    int height=acu;
    if (this->left)
        height=this->left->height(acu+1);
    if (this->right)
        if (this->right->height(acu+1)>height)
            height=this->right->height(acu+1);
    return height;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::composedRotation1 (){
    //std::cout<<"Aplicando LRR: "<<this->toString()<<'\n';
    NodoAVL<T>* temp=this->getLeft();
    NodoAVL<T>* temp2=temp->leftRotation();
    this->setLeft(temp2);
    return this->rightRotation();
}

template <class T>
NodoAVL<T>* NodoAVL<T>::composedRotation2 (){
    //std::cout<<"Aplicando RLR: "<<this->toString()<<'\n';
    NodoAVL<T>* temp=this->getRight();
    if (!temp)
        return NULL;
    NodoAVL<T>* temp2=temp->rightRotation();
    this->setRight(temp2);
    return this->leftRotation();
}

template <class T>
NodoAVL<T>* NodoAVL<T>::leftRotation (){
    //std::cout<<"Aplicando LR: "<<this->toString()<<'\n';
    NodoAVL<T>* temp=this->getRight();
    if (!temp)
        return NULL;
    NodoAVL<T>* temp2=temp->getLeft();
    NodoAVL<T>* temp3=this;
    this->setRight(temp2);
    temp->setLeft(temp3);
    return temp;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::rightRotation (){
    //std::cout<<"Aplicando RR: "<<this->toString()<<'\n';
    NodoAVL<T>* temp=this->getLeft();
    //std::cout<<"Temp: "<<temp->toString()<<'\n';
    if (!temp)
        return NULL;
    NodoAVL<T>* temp2=temp->getRight();
    NodoAVL<T>* temp3=this;
    this->setLeft(temp2);
    temp->setRight(temp3);
    //std::cout<<"Temp: "<<temp->toString()<<'\n';
    return temp;
}
