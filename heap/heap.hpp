#ifndef HEAP_H
#define HEAP_H
#include <iostream>
using namespace std;
template<typename E, typename C> class Heap;
template<typename E, typename C>
class node{
    public:
    protected:

    private:
        node<E,C>* left;
        node<E,C>* right;
        node<E,C>* parent;
        E data;
        friend class Heap<E,C>;
};
template <typename E, typename C>
class Heap
{
    public:
        void swap(node<E,C>* n,node<E,C>* m);
        Heap(const Heap& hp);
        Heap(); //Constructor
        int size() const;                   // number of elements
        bool isEmpty() const;               // is the queue empty?
        void insert(const E& e);                // insert element
        const E& min() const;       // minimum element
        void removeMin();           // remove minimum
        Heap<E,C>* mergeHeaps(Heap A);
        void buildHeap(const E A[], int n);
        void heapify(E arr[], int n, int i);
        E* heaparray();
        void called(node<E,C>*, E*);
        void heapifyup(node<E,C>* e);
        void updatelast(node<E,C>* t);
        void heapifydown(node<E,C>* e);
        node<E,C>* createtree(E arr[], int i, int n,node<E,C>* elem, node<E,C>*par);
    protected:

    private:
        node<E,C>* root;
        node<E,C>* last;
        E* arr;
        int sizer;
        int ci;
        E mini;
        C cmp;
};
template <typename E, typename C>
Heap<E,C>::Heap(){
    sizer = 0;
    ci = 0;
}
template <typename E, typename C>
void Heap<E,C>::swap(node<E,C>* n, node<E,C>* m){
    E e = n->data;
    n->data = m->data;
    m->data = e;
}
template <typename E, typename C>
Heap<E,C>::Heap(const Heap& hp){
    root = hp.root;
    last = hp.last;
    int s = hp.size();
    arr = new E[s];
    sizer = hp.sizer;
    ci = hp.ci;
    mini = hp.mini;

}
template <typename E, typename C>
int Heap<E,C>::size() const{
    return sizer;
}
template <typename E, typename C>
bool Heap<E,C>::isEmpty() const{
    if (sizer == 0) return 1;
    else return 0;
}
template <typename E, typename C>
void Heap<E,C>::insert(const E& e){
    sizer++;
    node<E,C>* temp = new node<E,C>;
    if(sizer == 1){
        E* a = new E;
        a[0] = e;
        buildHeap(a,1);
        return;
    }
    temp->data = e;
    int i = 0;
    while(1){
        if(last == root && !i){
            while(1){
                if(last->left == NULL){
                    last->left = temp;
                    temp->parent = last;
                    last = temp;
                    break;
                }
                last = last->left;
            }
            break;
        }
        if(!i && last == last->parent->left){
            i = 1;
            last = last->parent;
            if(last->right == NULL){
                last->right = temp;
                temp->parent = last;
                last= last->right;
                break;
            }
            else last = last->right;
            continue;
        }
        if(i){
            if(last->left == NULL){
                last->left = temp;
                temp->parent = last;
                last = temp;
                break;
            }
            last = last->left;
            continue;
        }
        if(!i){
            last = last->parent;
            continue;
        }
    }
    heapifyup(last);
}
template <typename E, typename C>
void Heap<E,C>::heapifyup(node<E,C>* last){
    node<E,C>* temp = new node<E,C>;
    temp = last;
    while(last!=root){
        if(cmp(last->data,last->parent->data)){
            swap(last, last->parent);
        }
        last = last->parent;
    }
    last = temp;
}
template <typename E, typename C>
void Heap<E,C>::removeMin(){
    sizer--;
    if(sizer == 0){
        root->left = NULL;
        root->right = NULL;
        return;
    }
    swap(root, last);
    node<E,C>* t = new node<E,C>;
    t = last;
    if(t->parent->right!=NULL && t->parent->right == t) last = t->parent->left;
    else updatelast(t);
    if(t == t->parent->left) t->parent->left = NULL;
    else t->parent->right = NULL;
    heapifydown(root);
}
template <typename E, typename C>
void Heap<E,C>::updatelast(node<E,C>* t){
    node<E,C>* tmp = new node<E,C>;
    tmp = t;
    int i = 0;
    while(1){
        if(!i){
            if(t == root){
                while(t->right!=NULL){
                    t = t->right;
                    if(t->right == NULL)break;
                }
                break;
            }
            if(t!= root && t->parent->left == t){
                t = t->parent;
                continue;
            }
            if(t!= root &&t->parent->right == t){
                i = 1;
                t = t->parent->left;
                continue;
            }
        }
        if(i){
            if(t->right != NULL){
                t = t->right;
                continue;
            }else{
                break;
            }
        }
    }
    last = t;
    t = tmp;
}
template <typename E, typename C>
E* Heap<E, C>::heaparray(){
    E* arr = new E[sizer];
    called(root, arr);
    return arr;
}
template <typename E, typename C>
void Heap<E,C>::called(node<E,C>* temp, E* arr){
    if(temp == NULL){
        return;
    }
    arr[ci]= temp->data;
    ci++;
    called(temp->left, arr);
    called(temp->right, arr);
}
template <typename E, typename C>
void Heap<E,C>::heapifydown(node<E,C>* root){
    node<E,C>* temp = new node<E,C>;
    temp = root;
    while(root!=NULL && !(root->left == NULL && root->right == NULL)){
        if((root->left!=NULL && !cmp(root->data,root->left->data)) && (root->right == NULL || cmp(root->data,root->right->data))){
            swap(root, root->left);
            root = root->left;
            continue;
        }
        if((root->right != NULL && !cmp(root->data,root->right->data)) && (root->left == NULL || cmp(root->data,root->left->data))){
            swap(root, root->right);
            root = root->right;
            continue;
        }
        if((root->right!= NULL && !cmp(root->data, root->right->data)) && (root->left!=NULL && !cmp(root->data,root->left->data))){
            if(cmp(root->left->data,root->right->data)){
                swap(root, root->left);
                root = root->left;
                continue;
            }
            else{
                swap(root, root->right);
                root = root->right;
                continue;
            }
        }
        break;
    }
    root = temp;
}
template <typename E, typename C>
const E& Heap<E,C>::min() const{
    //cout << "data is " <<root->data<<endl;
    return root->data;
}
template <typename E, typename C>

void Heap<E,C>::heapify(E arr[], int n, int i){
    int rootelem = i;
    int lft = 2*i + 1;
    int rgt = 2*i + 2;
    if (lft < n && cmp(arr[lft],arr[rootelem]))
        rootelem = lft;
    if (rgt < n && cmp(arr[rgt],arr[rootelem]))
        rootelem = rgt;
    if (rootelem != i)
    {
        E e = arr[i];
        arr[i] = arr[rootelem];
        arr[rootelem]  =e;
        heapify(arr, n, rootelem);
    }
}

template <typename E, typename C>

void Heap<E,C>::buildHeap(const E A[],int n){
    E arr[n];
    sizer = n;
    for(int i = 0; i < n; i++){
        arr[i] = A[i];
    }
    for(int i  =n/2 -1; i >=0; i--){
            heapify(arr, n, i);
    }
    node<E,C>* tempo = new node<E,C>;
    last = NULL;
    createtree(arr,0, n, tempo, NULL);
}
template <typename E, typename C>
node<E,C>* Heap<E,C>::createtree(E arr[], int i, int n, node<E,C>* elem, node<E,C>*par){
    if(i>n-1){
        elem = NULL;
        return NULL;
    }node<E,C>*temp = new node<E,C>;
    temp->data = arr[i];
    temp->parent = par;
    elem = temp;
    if(i == n-1){
        last = elem;
    }
    elem->left = createtree(arr,2*i+1, n, elem->left, elem);
    elem->right = createtree(arr,2*i+2, n, elem->right, elem);
    root = elem;
    return elem;
}
template <typename E, typename C>
Heap<E,C>* Heap<E,C>::mergeHeaps(Heap h){
    int s2 = h.size();
    E* arr = new E[s2];
    E* arr2 = new E[sizer];
    arr2 = heaparray();
    arr = h.heaparray();
    int s = s2+sizer;
    E mergear[s];
    for(int i = 0; i < s; i++){
        if(i < s2) mergear[i] = arr[i];
        else mergear[i] = arr2[i-s2];
    }
    buildHeap(mergear, s);
    ci = 0;
}

#endif // HEAP_H
