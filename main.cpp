#include "ArbolAVL.h"
#include <set>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

const int MAX=100;
using namespace std;
template <class T>
bool compare(list<NodoAVL<T>*>lsta, set<T>& RN);
template <class T>
string printRB(set<T>& RN);
template <class T>
void tokenize(char* line, string& operation, T& value);
template <class T>
T decide(string& operation, T& value, set<T>& RN, ArbolAVL<T>& AVL);
int main(int argc, char** argv){
    unsigned t0 = std::clock();
    if (argc>1){
        typedef string T;

        int i=0;
        char* line=new char[MAX];
        T archive_name=argv[1];
        ifstream in(archive_name);
        string operation;
        T id;
        set<T> RN;
        ArbolAVL<T> AVL;
        cout<<archive_name<<' '<<in.is_open()<<'\n';
        if (in.is_open()){
            while (!in.eof()){
                in.getline(line, MAX, '\n');
                if (!strlen(line))
                    continue;
                else{
                    tokenize<T>(line, operation, id);
                    cout<<"\nInsertado "<<decide<T>(operation, id, RN, AVL);
                    cout<<"Van "<<++i<<endl;
                    decide<T>(operation, id, RN, AVL);
                    if (!compare<T>(AVL.inOrder(), RN)||!AVL.balanced()){
                        cout<<"Aquí hay un problema";
                        cin.getline(line, MAX, '\n');
                    }
                }
            }
            in.close();
        }
        cout<<'\n';
        if (!AVL.balanced())
            cout<<"AVL no balanceado"<<'\n';
        if (!compare(AVL.inOrder(), RN))
            cout<<"No son iguales"<<'\n';
        else
            cout<<"Si son iguales"<<'\n';
    }
            
    unsigned t1 = std::clock();
    double calc_time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<"Tiempo de ejecución: "<<calc_time<<" segundos\n";
    return 0;
}

template <class T>
void tokenize(char* line, string& operation, T& value){
    char*ptr=strtok(line, " ");
    operation=ptr;
    ptr=strtok(NULL, "\n");
    value=ptr;
}

template <class T>
T decide(string& operation, T& value, set<T>& RN, ArbolAVL<T>& AVL){
    if (operation=="A"){
        RN.insert(value);
        AVL.insertNode(value);
    }
    
    else if (operation=="E"){
        RN.erase(value);
        AVL.removeNode(value);
    }
        return value;
}

template <class T>
string printRB(set<T>& RN){
    typename set<T>::iterator it=RN.begin();
    string c="";
    while (it!=RN.end()){
        c+="- \'";
        c+=(*it);
        c+=" \' ";
        advance (it,1);
    }
    return c;
}

template <class T>
bool compare(list<NodoAVL<T>*>lsta, set<T>& RN){
    typename list<NodoAVL<T>*>::iterator it=lsta.begin();
    typename set<T>::iterator it2=RN.begin();
    while (it2!=RN.end() && it!=lsta.end()){
        if (*it2!=(*it)->getData())
          return 0;
        advance (it,1);
        advance (it2,1);
    }
    if (it2!=RN.end() || it!=lsta.end())
      return 0;
    return 1;
}
