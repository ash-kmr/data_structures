#include <iostream>
#include <string>
#include <fstream>
#include "name_map.hpp"
#include "number_map.hpp"
using namespace std;

int main(){
	Number_Map<long, int> n(743);
	Name_Map<string, string> m(2531);
	while(1){
		cout << "Please​ ​ enter​ ​ 1 ​ ​ to​ ​ know​ ​ balance​ ​ of​ ​ a ​ ​ phone​ ​ number​ ​ and​ ​ 2 ​ ​ to​ ​ know​ ​ meaning​ ​ of​ ​ a ​ ​ name​ and 3 to quit\n";
		int i;
		cin >> i;
		if(i == 1){
			cout << "Please​ enter Number ";
			long num;
			cin >> num;
			cout << "Number = " << num << " , " << "Balance  = " << n.find(num)<<endl;
			cout << endl;
		}
		else if(i == 2){
			cout << "Please enter Name ";
			string name;
			cin >> name;
			cout << "Name = " << name << " , "<< "Meaning = "<< m.find(name)<<endl;
			cout << endl;
		}
		else{
			break;
		}
	}
}