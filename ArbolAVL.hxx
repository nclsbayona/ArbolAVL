#include "ArbolAVL.h"
#include <iostream>

template <class T>
ArbolAVL<T>::ArbolAVL(NodoAVL<T> *&head){
    this->head=head;
}

template <class T>
ArbolAVL<T>::ArbolAVL(T data){
    this->head=new NodoAVL<T>(data);
}

template <class T>
ArbolAVL<T>::ArbolAVL(){
    this->head=NULL;
}

template <class T>
ArbolAVL<T>::~ArbolAVL(){
    if (this->head){
        delete this->head;
        this->head=NULL;
    }
}
        
template <class T>
NodoAVL<T>* ArbolAVL<T>::getHead(){
    return this->head;
}

template <class T>
void ArbolAVL<T>::setHead(NodoAVL<T>*& head){
    this->head=head;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::insertNode(NodoAVL<T>*& node){
    if (!this->head){
        this->head=node;
        return node;
    }
    
    else if (this->insertNode(this->head, node)){
        this->balance(node);
        return node;
    }
    else
        return NULL;
}

template <class T>
bool ArbolAVL<T>::insertNode(NodoAVL<T>* toCompare, NodoAVL<T>*& node){
    if (toCompare->getData()==node->getData())
        return false;
    else if (toCompare->getData()>node->getData()){
        if (!toCompare->getLeft()){
            toCompare->setLeft(node);
            return true;
        } else
            return this->insertNode(toCompare->getLeft(), node);
    }
    else if (toCompare->getData()<node->getData()){
        if (!toCompare->getRight()){
            toCompare->setRight(node);
            return true;
        } else
            return this->insertNode(toCompare->getRight(), node);
    }
    return true;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::insertNode(T node){
    NodoAVL<T>* c=new NodoAVL<T>(node);
    NodoAVL<T>* nod=this->head;
    if (!nod){
        this->setHead(c);
        return c;
    }
    while (nod!=NULL){
        if (nod->getData()>node){
            if (nod->getLeft())
                nod=nod->getLeft();
            else{
                nod->setLeft(c);
                nod=NULL;
            }
        }
        else if (nod->getData()<node){
            if (nod->getRight())
                nod=nod->getRight();
            else{
                nod->setRight(c);
                nod=NULL;
            }
        }
        else{
            c=NULL;
            nod=NULL;
        }
    }
    this->balance(c);
    return c;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::searchNodeFather(NodoAVL<T>* searching){
    NodoAVL<T>* node=this->head;
    if (!node)
        return node;
    if (node->getData()==searching->getData())
        return node;
    bool enc=false;
    while (!enc){
        if (!(node->getLeft()||node->getRight()))
            return NULL;
        if ((node->getData()<searching->getData()&&!node->getRight()))
            return NULL;
        if ((node->getData()>searching->getData()&&!node->getLeft()))
            return NULL;
        if ((node->getData()<searching->getData()&&node->getRight())){
            if (node->getRight()->getData()==searching->getData())
                enc=true;
            else
                node=node->getRight();
        }
        else if ((node->getData()>searching->getData()&&node->getLeft())){
            if (node->getLeft()->getData()==searching->getData())
                enc=true;
            else
                node=node->getLeft();
        }
    }
    return node;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::searchNodeFather(T searching){
    NodoAVL<T>* node=this->head;
    if (!node)
        return node;
    if (node->getData()==searching)
        return node;
    bool enc=false;
    while (!enc){
        if (!(node->getLeft()||node->getRight()))
            return NULL;
        if ((node->getData()<searching&&!node->getRight()))
            return NULL;
        if ((node->getData()>searching&&!node->getLeft()))
            return NULL;
        if ((node->getData()<searching&&node->getRight())){
            if (node->getRight()->getData()==searching)
                enc=true;
            else
                node=node->getRight();
        }
        else if ((node->getData()>searching&&node->getLeft())){
            if (node->getLeft()->getData()==searching)
                enc=true;
            else
                node=node->getLeft();
        }
    }
    return node;
}

template <class T>
bool ArbolAVL<T>::removeNode(NodoAVL<T>*& node){
    NodoAVL<T>*padre=this->searchNodeFather(node);
    if (!(node->getRight()||node->getLeft())){
        if (padre->getRight()==node){
            delete node;
            node=NULL;
            padre->setRight(node);
        }
        else {
            delete node;
            node=NULL;
            padre->setLeft(node);
        }     
    }
    else if ((!node->getRight())&&(node->getLeft()))
        this->removeNodeGreater(node);
    else
        this->removeNodeMinor(node);
    this->balance(padre);
    return true;
}

template <class T>
bool ArbolAVL<T>::removeNode(T node){
    NodoAVL<T>*padre=this->searchNodeFather(node);
    if (!padre)
        return 0;
    //std::cout<<"Eliminación starting\n"<<padre->toString()<<"\n";
    NodoAVL<T>*nodo;
    if (padre==this->head&&this->head->getData()==node)
            nodo=padre;
    else if (padre->getLeft()&&padre->getLeft()->getData()==node)
            nodo=padre->getLeft();
    else
        nodo=padre->getRight();
    if (!(nodo->getRight()||nodo->getLeft())){
        if (padre->getRight()==nodo){
            delete nodo;
            nodo=NULL;
            padre->setRight(nodo);
        }
        else {
            delete nodo;
            nodo=NULL;
            padre->setLeft(nodo);
        }    
    }
    else if ((!nodo->getRight())&&(nodo->getLeft()))
        this->removeNodeGreater(nodo);
    else
        this->removeNodeMinor(nodo);
    this->balance(padre);
    //std::cout<<"Eliminación afterwards\n"<<padre->toString()<<"\n";
    return true;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::removeNodeMinor(NodoAVL<T>*& node){
    return node->removeSubMinor();
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::removeNodeGreater(NodoAVL<T>*& node){
    return node->removeSubGreater();
}

template <class T>
std::string ArbolAVL<T>::printTree(){
    if (this->head)
        return "Tree\n"+this->head->toString()+"\n";
    else
        return "No head";
}

template <class T>
std::string ArbolAVL<T>::inOrder(bool string){
    if (!this->head)
        return "No...";
    return this->head->inOrder(true);        
}

template <class T>
std::list<NodoAVL<T>*> ArbolAVL<T>::inOrder(){
    if (!this->head)
        return (*new std::list<NodoAVL<T>*>);
    return this->head->inOrder();        
}

template <class T>
std::string ArbolAVL<T>::preOrder(){
    if (!this->head)
        return "No...";
    return this->head->preOrder();        
}

template <class T>
std::string ArbolAVL<T>::postOrder(){
    if (!this->head)
        return "No...";
    return this->head->postOrder();        
}

template <class T>
int ArbolAVL<T>::height(){
    if (!this->head)
        return -1;
    return this->head->height();
}

template <class T>
std::string ArbolAVL<T>::levelOrder(){
    if (!this->head)
        return "No...";
    std::list<NodoAVL<T>*> nextLevel;
    std::string levels="";
    nextLevel.push_back(this->getHead());
    for (typename std::list<NodoAVL<T>*>::iterator it=nextLevel.begin(); it!=nextLevel.end(); advance(it, 1)){
        try{
            if ((*it)->getData()!=""){
                levels+=(*it)->toString(true);
                if ((*it)->getLeft())
                    nextLevel.push_back((*it)->getLeft());
                if ((*it)->getRight())
                    nextLevel.push_back((*it)->getRight());
            }
        }
        catch (...){}
    }
    return levels;
}

template <class T>
bool ArbolAVL<T>::balanced(){
    if (!this->head)
        return 1;
    return (this->nodeBalanced(this->head));
}

template <class T>
bool ArbolAVL<T>::nodeBalanced(NodoAVL<T>* node){
    if (node->getLeft()||node->getRight()){
        if (!node->getLeft())
            if (1+node->getRight()->height()>1)
                return 0;
        if (!node->getRight())
            if (1+node->getLeft()->height()>1)
                return 0;
        if (node->getLeft()&&node->getRight())
            if (node->getLeft()->height()-node->getRight()->height()<-1||node->getLeft()->height()-node->getRight()->height()>1)
                return 0;
    }
    return 1;
}

template <class T> 
bool ArbolAVL<T>::balance(NodoAVL<T>*& node){
    if (this->balanced())
        return 1;
    NodoAVL<T>* ft=this->searchNodeFather(node);
    NodoAVL<T>* lastFather=NULL;
    NodoAVL<T>* toAc=NULL;
    NodoAVL<T>* fath=NULL;
    while (ft!=lastFather){
        if (!this->nodeBalanced(ft)){
            //std::cout<<"Hay que arreglar "<<ft->toString()<<"\n";
            if (ft->getLeft()&&!ft->getRight()){
                if (!ft->getLeft()->getRight()){
                    toAc=ft->rightRotation();
                    //std::cout<<"Tiene izquierdo y no derecho\n";
                    if (ft==this->head){
                        this->setHead(toAc);
                    } else {
                        fath=this->searchNodeFather(ft);
                        if (fath->getLeft()==ft)
                            fath->setLeft(toAc);
                        else
                            fath->setRight(toAc);
                    }
                }
                else{
                    toAc=ft->composedRotation1();
                    //std::cout<<toAc<<'A'<<'\n';
                    //std::cout<<"Tiene izquierdo, derecho\n";
                    if (ft==this->head){
                        this->setHead(toAc);
                    }else{
                        fath=this->searchNodeFather(ft);
                        if (fath->getLeft()==ft)
                            fath->setLeft(toAc);
                        else
                            fath->setRight(toAc);
                    }
                }
            }
        
            else if (!ft->getLeft()&&ft->getRight()){
                if (ft->getRight()){
                    if (!ft->getRight()->getLeft()){
                        toAc=ft->leftRotation();
                        //std::cout<<"Tiene izquierdo y no derecho\n";
                        if (ft==this->head){
                            this->setHead(toAc);
                        } else {
                            fath=this->searchNodeFather(ft);
                            if (fath->getLeft()==ft)
                                fath->setLeft(toAc);
                            else
                                fath->setRight(toAc);
                        }
                    }
                    else{
                        toAc=ft->composedRotation2();
                        //std::cout<<toAc<<'A'<<'\n';
                        //std::cout<<"Tiene izquierdo, derecho\n";
                        if (ft==this->head){
                            this->setHead(toAc);
                        } else{
                            fath=this->searchNodeFather(ft);
                            if (fath->getLeft()==ft)
                                fath->setLeft(toAc);
                            else
                                fath->setRight(toAc);
                        }
                    }
                }
            }
            else{
                //Tiene izq y derecho
                //Izq más alto
                if (ft->getLeft()->height()-ft->getRight()->height()>1){
                    //std::cout<<"Caso de izquierdo más alto\n";
                    if (!ft->getLeft()->getRight()||ft->getLeft()->getLeft()->height()-ft->getLeft()->getRight()->height()>0){
                       fath=this->searchNodeFather(ft);
                        toAc=ft->rightRotation();
                        if (ft==this->head){
                            this->setHead(toAc);
                        } else{
                            if (fath->getLeft()==ft)
                                fath->setLeft(toAc);
                            else
                                fath->setRight(toAc);
                        }
                    }
                    else{
                       fath=this->searchNodeFather(ft);
                        toAc=ft->composedRotation1();
                        if (ft==this->head){
                            this->setHead(toAc);
                        } else{
                            if (fath->getLeft()==ft)
                                fath->setLeft(toAc);
                            else
                                fath->setRight(toAc);
                        }
                    }
                } else if (ft->getLeft()->height()-ft->getRight()->height()<1){
                    //Derecho más alto
                    char n;
                    std::cout<<"Caso de derecho más alto\n";
                    if (!ft->getRight()->getLeft()){
                        fath=this->searchNodeFather(ft);
                        toAc=ft->leftRotation();
                        if (ft==this->head){
                            this->setHead(toAc);
                        } else{
                            if (fath->getLeft()==ft)
                                fath->setLeft(toAc);
                            else
                                fath->setRight(toAc);
                        }
                    }
                    else{
                        fath=this->searchNodeFather(ft);
                        toAc=ft->composedRotation2();
                        if (ft==this->head){
                            this->setHead(toAc);
                        } else{
                            if (fath->getLeft()==ft)
                                fath->setLeft(toAc);
                            else
                                fath->setRight(toAc);
                        }  
                    }
                }
            }
            //std::cout<<"Despues de arreglos para balancear\n"<<this->searchNodeFather(ft)->toString()<<"\n";
        }
        lastFather=ft;
        ft=this->searchNodeFather(ft);
    }
    //std::cout<<"Antes de salir del metodo\n"<<node->toString()<<"\n";
    return 1;
}
