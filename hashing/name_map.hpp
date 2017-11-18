#ifndef NAME_MAP_H
#define NAME_MAP_H

#include <string>
#include "nodelist.hpp"
template <typename K, typename V>
class Name_Map
{
    public:
        Name_Map(int capacity = 2531);
        int NextPrime(int a);
        bool IsPrime(int a);
        int size() const;
        bool empty() const;
        V& find(K k);
        void put(const K& k, const V& v);
        void erase(const K& k);
    protected:

    private:
        List<K,V>** arr;
        int cap;
        int* collision;
        int divisor;
        int sizer;

};
#include <iostream>
#include <fstream>
template <typename K, typename V>
Name_Map<K,V>::Name_Map(int capacity){
    cap = capacity;
    divisor = cap;
    sizer = 0;
    List<K,V> m;
    collision = new int[12];
    arr = new List<K,V>*[12];
    for(int i = 0; i < 12; i++){
        arr[i] = new List<K,V>[2531];
        collision[i] = 0;
    }
    K name;
    V val;
    int sr = 0;
    int read = 0;
    ifstream file;
    file.open("names.txt");
    while(file){
        read++;
        file >> name;
        if(!file) break;
        getline(file, val);
        put(name, val);
    }/*
    cout << "total read " << read <<endl;
    for(int i = 0; i < 12; i++){
        int c = 0;
        int l = 0;
        for (int j = 0; j < 2531; j++){
            c += arr[i][j].coll;
            if(arr[i][j].coll > sr) sr = arr[i][j].coll;
            l += arr[i][j].lsize;
        }
        //cout << c << " " << l << "    ";
    }
    cout << " i found sr   ::::  " << sr <<endl;
    cout << endl;
    for(int i = 0; i < 12; i++){
        cout << collision[i]<< " ";
    }*/
    ofstream fout;
    fout.open("EntryNumOutput.txt", ios_base::app);
    fout << "\n\nCollisions in Name_Map \n\n";
    fout << "\t\t Division\tMAD\t\tMultiplication\n";
    fout << "Int Casting \t" << collision[9]*100.00/sizer << "\t" << collision[10]*100.00/sizer << "\t" << collision[11]*100.00/sizer<<endl;
    fout << "Comp. Sum \t" << collision[0]*100.00/sizer << "\t" << collision[1]*100.00/sizer << "\t" << collision[2]*100.00/sizer<<endl;
    fout << "Poly. Sum \t" << collision[3]*100.00/sizer << "\t" << collision[4]*100.00/sizer << "\t" << collision[5]*100.00/sizer<<endl;
    fout << "Cyclic Sum \t" << collision[6]*100.00/sizer << "\t" << collision[7]*100.00/sizer << "\t" << collision[8]*100.00/sizer<<endl;

}
template <typename K, typename V>
void Name_Map<K,V>::put(const K& k, const V& v){
    sizer++;
    // 0 component sum + division
    string na = k;
    int c = 0;
    int e = na.length();
    for(int i = 0; i < e; i++){
        char ch = na[i];
        c  = (c + int(ch));
    }
    if(c < 0)c = -c;
    int index = c%divisor;
    if(arr[0][index].head != NULL) collision[0]++;
    arr[0][index].insert(k, v);
    // 1 component sum + MAD
    int a = 2539;
    int b = 2521;
    index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
    if(arr[1][index].head != NULL) collision[1]++;
    arr[1][index].insert(k, v);
    // 2 component sum + Multiplication
    int g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
    index = (g)%2531;
    if(arr[2][index].head != NULL) collision[2]++;
    arr[2][index].insert(k, v);
    // 3 polynomial sum + division
    c = 0;
    a = 33;
    for(int i = 0; i < e; i++){
      c = ((c * a) + int(na[i]));
    }
    if(c < 0)c = -c;
    index = c%divisor;
    //cout << k << " " << index <<endl;
    if(arr[3][index].head != NULL) collision[3]++;
    arr[3][index].insert(k, v);
    // 4 polynomial sum + MAD
    a = 2539;
    b = 2521;
    index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
    if(arr[4][index].head != NULL) collision[4]++;
    arr[4][index].insert(k, v);
    // 5 polynomial sum + Multiplication
    g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
    index = (g)%2531;
    if(arr[5][index].head != NULL) collision[5]++;
    arr[5][index].insert(k, v);
    // 6 cyclic sum + division
    c = 0;
    for(int i = 0; i < e; i++){
        char ch = na[i];
        int s = int(ch);
        c = (c>>27)|(c<<5);
        c = (c + s);
    }
    if(c < 0)c = -c;
    index = c%divisor;
    if(arr[6][index].head != NULL) collision[6]++;
    arr[6][index].insert(k, v);
    // 7 cyclic sum + MAD
    a = 2539;
    b = 2521;
    index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
    //cout << k << " " << index <<endl;
    if(arr[7][index].head != NULL) collision[7]++;
    arr[7][index].insert(k, v);
    // 8 cyclic sum + Multiplication
    g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
    index = (g)%2531;
    if(arr[8][index].head != NULL) collision[8]++;
    arr[8][index].insert(k, v);
    // 9 integer casting + division
    c = 0;
    for(int i = e-1; i >=0; i--){
        if(i<e-4) break;
        int add = na[i];
        if(i%4==0) add = add<<0;
        else if (i%4 == 1) add = add<<8;
        else if (i%4 == 2) add = add<<16;
        else if (i%4 == 3) add = add<<24;
        c += add;
    }
    if(c<0) c = -c;
    index = c%divisor;
    if(arr[9][index].head != NULL) collision[9]++;
    arr[9][index].insert(k, v);
    // 10 integer casting + MAD
    a = 2539;
    b = 2521;
    index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
    if(arr[10][index].head != NULL) collision[10]++;
    arr[10][index].insert(k, v);
    // 11 integer casting + Multiplication
    g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
    index = (g)%2531;
    if(arr[11][index].head != NULL) collision[11]++;
    arr[11][index].insert(k, v);
}
template <typename K, typename V>
void Name_Map<K,V>::erase(const K& k){
    sizer--;
    // 0 component sum + division
    string na = k;
    int c = 0;
    int e = na.length();
    for(int i = 0; i < e; i++){
        char ch = na[i];
        c  = (c + int(ch));
    }
    if(c < 0)c = -c;
    int index = c%divisor;
    arr[0][index].remove(k);
    // 1 component sum + MAD
    int a = 2539;
    int b = 2521;
    index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
    arr[1][index].remove(k);
    // 2 component sum + Multiplication
    int g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
    index = (g)%2531;
    arr[2][index].remove(k);
    // 3 polynomial sum + division
    c = 0;
    a = 33;
    for(int i = 0; i < e; i++){
      c = ((c * a) + int(na[i]));
    }
    if(c < 0)c = -c;
    index = c%divisor;
    //cout << k << " " << index <<endl;
    arr[3][index].remove(k);
    // 4 polynomial sum + MAD
    a = 2539;
    b = 2521;
    index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
    arr[4][index].remove(k);
    // 5 polynomial sum + Multiplication
    g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
    index = (g)%2531;
    arr[5][index].remove(k);
    // 6 cyclic sum + division
    c = 0;
    for(int i = 0; i < e; i++){
        char ch = na[i];
        int s = int(ch);
        c = (c>>27)|(c<<5);
        c = (c + s);
    }
    if(c < 0)c = -c;
    index = c%divisor;
    arr[6][index].remove(k);
    // 7 cyclic sum + MAD
    a = 2539;
    b = 2521;
    index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
    //cout << k << " " << index <<endl;
    arr[7][index].remove(k);
    // 8 cyclic sum + Multiplication
    g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
    index = (g)%2531;
    arr[8][index].remove(k);
    // 9 integer casting + division
    c = 0;
    for(int i = e-1; i >=0; i--){
        if(i<e-4) break;
        int add = na[i];
        if(i%4==0) add = add<<0;
        else if (i%4 == 1) add = add<<8;
        else if (i%4 == 2) add = add<<16;
        else if (i%4 == 3) add = add<<24;
        c += add;
    }
    if(c<0) c = -c;
    index = c%divisor;
    arr[9][index].remove(k);
    // 10 integer casting + MAD
    a = 2539;
    b = 2521;
    index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
    arr[10][index].remove(k);
    // 11 integer casting + Multiplication
    g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
    index = (g)%2531;
    arr[11][index].remove(k);
}
template <typename K, typename V>
V& Name_Map<K,V>::find(K k){
    int imin = 0;
    int cmin = collision[0];
    for(int i = 0; i < 9; i++){
        if(collision[i] < cmin){
            cmin = collision[i];
            imin = i;
        }
    }
    string na = k;
    int c = 0;
    int e = na.length();
    int index;
    int a = 2539;
    int b = 2521;
    if(imin == 0 || imin == 1 || imin == 2){
        c = 0;
        for(int i = 0; i < e; i++){
            char ch = na[i];
            c  = (c + int(ch));
        }
        if(imin == 0){
            index = c%divisor;
            return arr[0][index].findi(k);
        }
        else if(imin == 1){
            index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
            return arr[1][index].findi(k);
        }
        else if(imin == 2){
            int g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
            index = (g)%2531;
            return arr[2][index].findi(k);
        }
    }
    else if(imin == 3 || imin == 4 || imin == 5){
        c = 0;
        a = 33;
        for(int i = 0; i < e; i++){
          c = ((c * a) + int(na[i]));
        }
        if(c<0) c = -c;
        if(imin == 3){
            index = c%divisor;
            //cout << k << " "<< index <<endl;
            return arr[3][index].findi(k);
        }
        else if(imin == 4){
            a = 2539;
            b = 2521;
            index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
            return arr[4][index].findi(k);
        }
        else if(imin == 5){
            int g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
            index = (g)%2531;
            return arr[5][index].findi(k);
        }
    }
    else if(imin >= 6 && imin <= 8){
        c = 0;
        for(int i = 0; i < e; i++){
            char ch = na[i];
            int s = int(ch);
            c = (c>>27)|(c<<5);
            c = (c + s);
        }
        if(c< 0) c = -c;
        if(imin == 6){
            index = c%divisor;
            //cout << index << endl;
            return arr[6][index].findi(k);
        }
        else if(imin == 7){
            a = 2539;
            b = 2521;
            index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
            return arr[7][index].findi(k);
        }
        else if(imin == 8){
            int g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
            index = (g)%2531;
            return arr[8][index].findi(k);
        }
    }
    else if(imin >=9){
        c = 0;
        for(int i = e-1; i >=0; i--){
            if(i<e-4) break;
            int add = na[i];
            if(i%4==0) add = add<<0;
            else if (i%4 == 1) add = add<<8;
            else if (i%4 == 2) add = add<<16;
            else if (i%4 == 3) add = add<<24;
            c += add;
        }
        if(c < 0) c= -c;
        if(imin == 9){
            index = c%divisor;
            return arr[9][index].findi(k);
        }
        else if(imin == 10){
            a = 2539;
            b = 2521;
            index = (((a%divisor)*(c%divisor)%divisor)+b%divisor)%divisor;
            return arr[10][index].findi(k);
        }
        else if(imin == 11){
            int g = (int)(4096*((c*0.6180339887 - (int)(c*0.6180339887))));
            index = (g)%divisor;
            return arr[11][index].findi(k);
        }
    }
}

template <typename K, typename V>
int Name_Map<K,V>::size() const{
    return sizer;
}
template <typename K, typename V>
bool Name_Map<K,V>::empty() const{
    return (sizer == 0);
}


#endif // NAME_MAP_H
