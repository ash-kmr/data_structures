#ifndef NODELIST_H
#define NODELIST_H
#include <iostream>
using namespace std;
template <typename K, typename V> class Name_Map;
template <typename K, typename V> class Number_Map;
template <typename K, typename V> class List;
template <typename K, typename V>
class node{
    public:
    private:
        K name;
        V val;
        node* next;
        friend class Name_Map<K,V>;
        friend class Number_Map<K,V>;
        friend class List<K,V>;
};
template <typename K, typename V>
class List{
    public:
        List();
        void insert(const K& k,const V& v);
        void remove(const K& k);
        V& findi(K& k);
    private:
        node<K,V>* head;
        node<K,V>* tail;
        int lsize;
        int coll;
        friend class Name_Map<K,V>;
        friend class Number_Map<K,V>;
};

template <typename K, typename V>
List<K,V>::List(){
    lsize = 0;
    coll = 0;
    head = new node<K,V>;
    head = NULL;
    tail = NULL;
}
template <typename K, typename V>
void List<K,V>::insert(const K& k,const V& v){
    if(head == NULL){
        head = new node<K,V>;
        head->name = k;
        head->val = v;
        //cout << head->name<<endl;
        head->next = NULL;
        tail = head;
        lsize++;
    }else{
        node<K,V>* temp = head;
        while(temp->next!=NULL){
                if(temp->name == k){
                    temp->val = v;
                    return;
                }
                else temp = temp->next;
        }
        if(temp->name == k){
            temp->val = v;
            return;
        }
        else{
            coll++;
            node<K,V> *newnode = new node<K,V>;
            newnode->name = k;
            newnode->val = v;
            newnode->next = NULL;
            temp->next = newnode;
            //cout << newnode->name<<endl;
            lsize++;
            return;
        }
    }
}
template <typename K, typename V>
void List<K,V>::remove(const K& k){
    node<K,V>* prev = new node<K,V>;
    node<K,V>* curr = new node<K,V>;
    lsize--;
    prev = head;
    curr = head->next;
    if(head->name == k){
        head = head->next;
        return;
    }
    for(int i = 0; i < lsize-1; i++){
        if(curr->name == k){
            prev->next = curr->next;
            break;
        }
        prev = prev->next;
        curr = curr->next;
    }
    return;
}
template <typename K, typename V>
V& List<K,V>::findi(K& k){
    node<K,V>* prev = new node<K,V>;
    node<K,V>* curr = new node<K,V>;
    prev = head;
    curr = head->next;
    if(head->name == k){
        return head->val;
    }
    for(int i = 0; i < lsize-1; i++){
        if(curr == NULL) break;
        if(curr->name == k){
            return curr->val;
            break;
        }
        if(curr->next == NULL) break;
        curr = curr->next;
    }
    cout << " not found\n ";
}
#endif // NODELIST_H