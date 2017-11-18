#include <iostream>
#include <string>
#include "mavl.hpp"
using namespace std;

int main(){
	MAVLTree m;
	while(1){
		int i;
		cout <<"Please enter 1 to insert, 2 to delete by key, 3 to get the place of a key, and 4 to delete by place of​ key and press 5 to quit\n";
		cin >> i;
		if(i == 1){
			int k;
			string s;
			cout << "input key ";
			cin >> k;
			cout << "input value ";
			cin >> s;
			m.insert(k,s);
		}
		else if(i == 2){
			int k;
			cout << "input key to delete ";
			cin >> k;
			m.remove(k);
		}
		else if(i == 3){
			int k;
			cout << "input key to get place of ";
			cin >> k;
			cout << "the place is " << m.get_place(k) <<endl;
		}
		else if(i == 4){
			int k;
			cout << "which place do you want to delete ";
			cin >> k;
			m.delete_by_place(k);
		}
		else{
			break;
		}
	}
}