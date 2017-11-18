#ifndef MAVLTREE_H
#define MAVLTREE_H
#include <string>

using namespace std;
class node2{
    private:
        int place;
        int key;
        int size;
        string val;
        node2* left;
        node2* right;
        node2* parent;
        int height;
        friend class MAVLTree;
};
class node{
    private:
        int place;
        int key;
        string val;
        node* left;
        node* right;
        node* parent;
        int height;
        friend class MAVLTree;
};

class MAVLTree
{
    public:
        MAVLTree();                                 //Initialize the ADT
     	int size() const;	                        // number of elements
    	bool isEmpty() const;	                    // is the queue empty?
        void insert(const int k, string s);         //insert key k,s into the tree
        void insert(const int p,const int k, string s);
        int max(int a, int b);
        int getheight(node* r);
        int getheight(node2* r);
        int getdiff(node* n);
        int getdiff(node2* n);
        node* rRotate(node* y);
        node2* rRotate(node2* y);
        node* lRotate(node* x);
        node2* lRotate(node2* x);
        void balance(node* x);
        void balance(node2* x);
        void traverse(node* tmp);
        void traverse(node2* tmp);
        int getsize(node2* r);
        void decsize(node2* x);
        void traversal();
        void remove(const int k);                  //remove k from the tree, if exists
        void deleter2(const int p);                  //remove k from the tree, if exists
        string search(const int k);                 //search for key k in the tree
        void delete_by_place(int i);                //Delete from the entry at the  ith place (as determined by the order of insertion)
        int get_place(int k);                       //Return the place (which is determined by the order of insertion), if x does not exist, return -1

    private:
        int counter;
        int place;
        node* root;
        node2* root2;
};

#include <algorithm>
#include <iostream>
#include <queue>
#include <fstream>
MAVLTree::MAVLTree()
{
    root = NULL;
    root2 = NULL;
    counter = 0;
    place = 1;
    ifstream entries;
    entries.open("entries.txt");
    int k;
    string val;
    while(entries){
        entries >> k >> val;
        if(!entries) break;
        insert(k, val);
    }
}
int MAVLTree::getheight(node* r){
    if(r!=NULL) return r->height;
    else return 0;
}
int MAVLTree::getheight(node2* r){
    if(r!=NULL) return r->height;
    else return 0;
}
int MAVLTree::max(int a, int b){
    if(a>b) return a;
    else return b;
}
node* MAVLTree::rRotate(node* y){
    node* x = new node;
    x = y->left;
    node*z = new node;
    z = y->left->right;
    x->right = y;
    x->parent = y->parent;
    if(y!=NULL)y->parent = x;
    y->left = z;
    if(z!=NULL)z->parent = y;
    y->height = max(getheight(y->right),getheight(y->left))+1;
    x->height = max(getheight(x->right),getheight(x->left))+1;
    return x;
}
node2* MAVLTree::rRotate(node2* y){
    node2* x = new node2;
    x = y->left;
    node2*z = new node2;
    z = y->left->right;
    x->right = y;
    x->parent = y->parent;
    if(y!=NULL)y->parent = x;
    y->left = z;
    if(z!=NULL)z->parent = y;
    y->height = max(getheight(y->right),getheight(y->left))+1;
    y->size = getsize(y->left)+getsize(y->right)+1;
    x->height = max(getheight(x->right),getheight(x->left))+1;
    x->size = getsize(x->left)+getsize(x->right)+1;
    return x;
}
node* MAVLTree::lRotate(node* x){
    node* y = new node;
    y = x->right;
    node* z = new node;
    z = x->right->left;
    y->left = x;
    y->parent = x->parent;
    if(x!=NULL)x->parent = y;
    x->right = z;
    if(z!=NULL)z->parent = x;
    x->height = max(getheight(x->left),getheight(x->right))+1;
    y->height = max(getheight(y->left),getheight(y->right))+1;
    return y;
}
node2* MAVLTree::lRotate(node2* x){
    node2* y = new node2;
    y = x->right;
    node2* z = new node2;
    z = x->right->left;
    y->left = x;
    y->parent = x->parent;
    if(x!=NULL)x->parent = y;
    x->right = z;
    if(z!=NULL)z->parent = x;
    x->height = max(getheight(x->left),getheight(x->right))+1;
    x->size = getsize(x->left)+getsize(x->right)+1;
    y->height = max(getheight(y->left),getheight(y->right))+1;
    y->size = getsize(y->left)+getsize(y->right)+1;
    return y;
}
void MAVLTree::insert(const int k, string s){
    if(root == NULL){
        root = new node;
        root->parent = NULL;
        root->key = k;
        root->val = s;
        root->place = place;
        place++;
        root->left = NULL;
        root->right = NULL;
        int p = place-1;
        //cout << p << " " << k << " " << s << endl;
        insert(p,k,s);
        return;
    }
    node* temp = new node;
    temp = root;
    while(1){
        if(k < temp->key){
            if(temp->left == NULL) break;
            temp = temp->left;
        }else{
            if(temp->right == NULL) break;
            temp = temp->right;
        }
    }
    node* newnode = new node;
    newnode->key = k;
    newnode->val = s;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = temp;
    newnode->height = 1;
    newnode->place = place;
    place++;
    if(k < temp->key) temp->left = newnode;
    else temp->right = newnode;
    balance(temp);
    int p = place-1;
    //cout << p << " " << k << " " << s <<endl;
    insert(p, k, s);
    return;
}

void MAVLTree::insert(const int p, const int k, string s){
    //cout << p << " " << k << " " << s << endl;
    if(root2 == NULL){
        root2 = new node2;
        root2->parent = NULL;
        root2->key = k;
        root2->val = s;
        root2->size = 1;
        root2->place = p;
        root2->left = NULL;
        root2->right = NULL;
        //cout << root2->place << " " << root2->key << " " << root2->val <<endl;
        return;
    }
    node2* temp = new node2;
    temp = root2;
    while(1){
        if(p < temp->place){
            if(temp->left == NULL) break;
            temp = temp->left;
        }else{
            if(temp->right == NULL) break;
            temp = temp->right;
        }
    }
    node2* newnode = new node2;
    newnode->key = k;
    newnode->val = s;
    newnode->place = p;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->size = 1;
    newnode->parent = temp;
    newnode->height = 1;
    if(p < temp->place) temp->left = newnode;
    else temp->right = newnode;
    balance(temp);
    return;
}
void MAVLTree::remove(const int k){
    if(root == NULL) return;
    if(root->left == NULL && root-> right == NULL && k == root->key){
        int p = root->place;
        root = NULL;
        deleter2(p);
        return;
    }
    node* temp = new node;
    temp = root;
    while(1){
        if(k < temp->key){
            temp = temp->left;
        }
        else if(k > temp->key){
            temp = temp->right;
        }
        else{
            break;
        }
    }
    int p = temp->place;
    if(temp->right == NULL && temp->left == NULL){
        node* t = new node;
        t = temp->parent;
        if(temp == t->left) t->left = NULL;
        else t->right = NULL;
        if(t!=NULL) balance(t);
    }
    else if(temp->left == NULL && temp->right !=NULL){
        temp->key = temp->right->key;
        temp->val = temp->right->val;
        temp->place = temp->right->place;
        temp->left = temp->right->left;
        temp->right = temp->right->right;
        balance(temp);
    }
    else if(temp->right == NULL && temp->left != NULL){
        temp->key = temp->left->key;
        temp->val = temp->left->val;
        temp->place = temp->left->place;
        temp->right = temp->left->right;
        temp->left = temp->left->left;
        balance(temp);
    }
    else{
        node* t = new node;
        t = temp->right;
        while(t->left!=NULL){
            t = t->left;
        }
        temp->key = t->key;
        temp->val = t->val;
        temp->place = t->place;
        if(t == t->parent->left && t->right == NULL){
            t->parent->left = NULL;
        }else{
            if(t->right!=NULL){
                t->key = t->right->key;
                t->val = t->right->val;
                t->place = t->right->place;
                t->left = t->right->left;
                t->right = t->right->right;
                balance(t);
            }else{
                temp->right = NULL;
            }
        }
        balance(temp);
    }
    deleter2(p);
}
void MAVLTree::deleter2(const int p){
    if(root2 == NULL) return;
    if(root2->left == NULL && root2->right == NULL && p == root2->place){
        root2 = NULL;
        return;
    }
    node2* temp = new node2;
    temp = root2;
    //traverse(root2);
    //cout << "to delete "<< p <<endl;
    //cout << "initial root size " << root2->size <<endl;
    while(1){
        if(p < temp->place){
            temp = temp->left;
        }
        else if(p > temp->place){
            temp = temp->right;
        }
        else{
            break;
        }
    }
    if(!(temp->left != NULL && temp->right != NULL)){
    //cout << "this is key "<< temp->key << endl;
        decsize(temp);
        //cout << "changed root2 size "<< root2->size <<endl;
        temp = root2;
        //cout << root2->key << " here"<<endl;;
        //traverse(root2);
        while(1){
            if(p < temp->place){
                temp = temp->left;
            }
            else if(p > temp->place){
                temp = temp->right;
            }
            else{
                break;
            }
        }
    }
    //cout << "final root2 size " << root2->size <<endl;
    if(temp->right == NULL && temp->left == NULL){
        node2* t = new node2;
        t = temp->parent;
        if(temp == t->left) t->left = NULL;
        else t->right = NULL;
        if(t!=NULL) {
            balance(t);
        }
    }
    else if(temp->left == NULL && temp->right !=NULL){
        temp->key = temp->right->key;
        temp->place = temp->right->place;
        //cout << "new temp place " << temp->place <<endl;
        temp->val = temp->right->val;
        temp->left = temp->right->left;
        temp->right = temp->right->right;
        balance(temp);
    }
    else if(temp->right == NULL && temp->left != NULL){
        temp->key = temp->left->key;
        temp->place = temp->left->place;
        temp->val = temp->left->val;
        temp->right = temp->left->right;
        temp->left = temp->left->left;
        balance(temp);
    }
    else{
        node2* t = new node2;
        t = temp->right;
        while(t->left!=NULL){
            t = t->left;
        }
        temp->key = t->key;
        temp->val = t->val;
        temp->place = t->place;
        decsize(t);
        t = temp->right;
        while(t->left!=NULL){
            t = t->left;
        }
        //cout << "new temp place " << temp->place <<endl;
        if(t == t->parent->left && t->right == NULL){
            t->parent->left = NULL;
        }else{
            if(t->right!=NULL){
                t->key = t->right->key;
                t->place = t->right->place;
                t->size = t->right->size;
                t->val = t->right->val;
                t->left = t->right->left;
                t->right = t->right->right;
                balance(t);
            }else{
                temp->right = NULL;
            }
        }
        balance(temp);
    }
}
void MAVLTree::decsize(node2* x){
    node2* temp = new node2;
    temp = x;
    if(temp->parent!=NULL)temp = temp->parent;
    while(temp!= NULL){
        temp->size -= 1;
        //cout << "new size " << temp->size <<endl;
        root2 = temp;
        if(temp->parent == NULL) break;
        temp = temp->parent;
    }
    //cout <<"hey " << root2->size <<endl;
}

void MAVLTree::balance(node* x){
    if(x == NULL){
        return;
    }
    x->height = 1+ max(getheight(x->right), getheight(x->left));
    if(x->left == NULL && x->right == NULL) return;
    int b;
    b = getheight(x->left)-getheight(x->right);
    if(b > 1 && getdiff(x->left) >=0){
        x = rRotate(x);
        if(x->parent!=NULL){
            if(x->key > x->parent->key) x->parent->right = x;
            else x->parent->left = x;
        }
        if(x->parent == NULL) root = x;
        return balance(x->parent);
    }
    if(b < -1 && getdiff(x->right) <=0){
        x = lRotate(x);
        if(x->parent!=NULL){
            if(x->key > x->parent->key) x->parent->right = x;
            else x->parent->left = x;
        }
        if(x->parent == NULL) root = x;
        return balance(x->parent);
    }
    if(b > 1 && getdiff(x->left) < 0){
        x->left = lRotate(x->left);
        if(x!=NULL){
            if(x->left->key > x->key) x->left->parent->right = x->left;
            else x->left->parent->left = x->left;
        }
        x = rRotate(x);
        if(x->parent!=NULL){
            if(x->key > x->parent->key) x->parent->right = x;
            else x->parent->left = x;
        }
        if(x->parent == NULL) root = x;
        return balance(x->parent);
    }
    if(b < -1 && getdiff(x->right) >0){
        x->right = rRotate(x->right);
        if(x!=NULL){
            if(x->right->key > x->key) x->right->parent->right = x->right;
            else x->right->parent->left = x->right;
        }
        x = lRotate(x);
        if(x->parent!=NULL){
            if(x->key > x->parent->key) x->parent->right = x;
            else x->parent->left = x;
        }
        if(x->parent == NULL) root = x;
        return balance(x->parent);
    }
    if(x->parent == NULL) root = x;
    return balance(x->parent);
}
int MAVLTree::getsize(node2* r){
    if(r == NULL) return 0;
    else return r->size;
}
void MAVLTree::balance(node2* x){
    if(x == NULL){
        return;
    }
    x->size = getsize(x->left) + getsize(x->right) + 1;
    x->height = 1+ max(getheight(x->right), getheight(x->left));
    if(x->left == NULL && x->right == NULL) return;
    int b;
    //if(x->size == 4) cout <<"found the culprit fo askznldfasSjcnzlxnvd.,smxn";

    b = getheight(x->left)-getheight(x->right);
    if(b > 1 && getdiff(x->left) >=0){
        x = rRotate(x);
        if(x->parent!=NULL){
            if(x->place > x->parent->place) x->parent->right = x;
            else x->parent->left = x;
        }
        if(x->parent == NULL) root2 = x;
        return balance(x->parent);
    }
    if(b < -1 && getdiff(x->right) <=0){
        x = lRotate(x);
        if(x->parent!=NULL){
            if(x->place > x->parent->place) x->parent->right = x;
            else x->parent->left = x;
        }
        if(x->parent == NULL) root2 = x;
        return balance(x->parent);
    }
    if(b > 1 && getdiff(x->left) < 0){
        x->left = lRotate(x->left);
        if(x!=NULL){
            if(x->left->place > x->place) x->left->parent->right = x->left;
            else x->left->parent->left = x->left;
        }
        x = rRotate(x);
        if(x->parent!=NULL){
            if(x->place > x->parent->place) x->parent->right = x;
            else x->parent->left = x;
        }
        if(x->parent == NULL) root2 = x;
        return balance(x->parent);
    }
    if(b < -1 && getdiff(x->right) >0){
        x->right = rRotate(x->right);
        if(x!=NULL){
            if(x->right->place > x->place) x->right->parent->right = x->right;
            else x->right->parent->left = x->right;
        }
        x = lRotate(x);
        if(x->parent!=NULL){
            if(x->place > x->parent->place) x->parent->right = x;
            else x->parent->left = x;
        }
        if(x->parent == NULL) root2 = x;
        return balance(x->parent);
    }
    if(x->parent == NULL) root2 = x;
    return balance(x->parent);
}

void MAVLTree::traversal(){
    node* tmp = new node;
    tmp = root;
    traverse(tmp);
    node2* tmp2 = new node2;
    tmp2 = root2;
    //cout << root2->size <<endl;
    //if(root2->size == 4)cout << "found the cul[osd;lfjsnmd;lgvkn";
    traverse(tmp2);
}
int MAVLTree::getdiff(node* r){
    if(r == NULL) return 0;
    else return getheight(r->left) - getheight(r->right);
}
int MAVLTree::getdiff(node2* r){
    if(r == NULL) return 0;
    else return getheight(r->left) - getheight(r->right);
}
void MAVLTree::traverse(node* tmp){
    queue<node*> q;
    q.push(tmp);
    while(!q.empty()){
        node* temp = new node;
        temp = q.front();
        q.pop();
        if(temp->left!=NULL) q.push(temp->left);
        if(temp->right!= NULL) q.push(temp->right);
        cout << temp->key <<" " << temp->place<<endl;
    }
    cout <<endl;
}
void MAVLTree::traverse(node2* tmp){
    queue<node2*> q;
    q.push(tmp);
    cout << "place tree\n";
    while(!q.empty()){
        node2* temp = new node2;
        temp = q.front();
        q.pop();
        if(temp->left!=NULL) q.push(temp->left);
        if(temp->right!= NULL) q.push(temp->right);
        cout << temp->place <<" " << temp->key <<" "<< temp->size<<endl;
    }
}

void MAVLTree::delete_by_place(int p){
    node2* temp = new node2;
    temp = root2;
    if(p > temp->size) return;
    int csize = 0;
    while(1){
        if(p > getsize(temp->left)+1){
            csize += getsize(temp->left) + 1;
            p -= getsize(temp->left) + 1;
            if(temp->right!=NULL) temp = temp->right;
        }else if(p < getsize(temp->left) + 1){
            if(temp->left!= NULL)temp = temp->left;
        }else{
            break;
        }
    }
    int j = temp->key;
    //cout << "key found :: "<< temp->key << " corresponding place :: "<< temp->place<<endl;
    remove(j);
}
int MAVLTree::get_place(int k){
    node* tmp = new node;
    tmp = root;
    while(1){
        if(k < tmp->key){
            tmp = tmp->left;
        }
        else if(k > tmp->key){
            tmp = tmp->right;
        }
        else{
            break;
        }
    }
    int p = tmp->place;
    //cout << "temp->place :: " << p <<endl;
    node2* temp = new node2;
    temp = root2;
    int csize = 0;
    while(1){
        if(p > temp->place){
            csize += getsize(temp->left) + 1;
            if(temp->right!=NULL) temp = temp->right;
        }else if(p < temp->place){
            if(temp->left!= NULL)temp = temp->left;
        }else{
            csize += getsize(temp->left) +1;
            break;
        }
    }
    //cout << "found correct place :: "<< csize <<endl;
    return csize;
}
string MAVLTree::search(const int k){
    node* tmp = new node;
    tmp = root;
    while(1){
        if(k < tmp->key){
            tmp = tmp->left;
        }
        else if(k > tmp->key){
            tmp = tmp->right;
        }
        else{
            break;
        }
    }
    return tmp->val;
}


#endif // MAVLTREE_H