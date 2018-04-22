#include <iostream>
#include <map>
#include <string>

using namespace std;

const double EPS = 1e-6;

/*
 * Encoder works with the following Parameters:
 * 	1-Source Set & its size.
 * 	2-Probabilities.
 * 	3-Message.
 * And returns a tag
 *
 * Decoder works with the following Parameters:
 * 	1-Source Set & its size.
 * 	2-Probabilities.
 * 	3-Tag.
 * and returns the message
 */

string encode(char*, int, double*, string);
string decode(char[], int, double[], string);
string toBinaryString(double);

map<char, int> indexOf;

int main() {
	int n, type;
	do {
		cout << "Enter the Operation Code [1=Encoding, 2=Decoding, otherwise=Exit] : ";
		cin >> type;
		if(type != 1 && type != 2)	break;
		cout << "Enter the size of the Source Set: ";
		cin >> n;
		char* sourceSet = new char[n+1];				//One based
		double* probabilities = new double[n+1];
		string input, output;			//Either tag or message

		cout << "Enter " << n << " Element representing the Source Set: ";
		for(int i = 1 ; i <= n ; ++i) {
			cin >> sourceSet[i];
			indexOf[sourceSet[i]] = i;
		}
		cout << "Enter " << n << " Real Number representing the Corresponding Probabilities: ";
		for(int i = 1 ; i <= n ; ++i)
			cin >> probabilities[i];
		if(type == 1){			//Encoding
			cout << "Enter the Message to be Encoded: ";
			cin >> input;
			output = encode(sourceSet, n, probabilities, input);
		}else{							//Decoding
			cout << "Enter the Tag to be Decoded: ";
			cin >> input;
			output = decode(sourceSet, n, probabilities, input);
		}
		cout << output << endl;

		delete [] sourceSet;
		delete [] probabilities;
	}while(1);
	cout << "Thank you :D" << endl;
	return 0;
}

string encode(char* sourceSet, int n, double* probabilities, string message){
	double prevl = 0, prevu = 1, l, u;
	double F[n+1] = {};				//probability density function
	string ret = "";
	for(int i = 1 ; i <= n ; ++i)
		F[i] = F[i-1] + probabilities[i];

	for(int i = 0 ; i < n ; ++i){
		l = prevl + (prevu - prevl) * F[indexOf[message[i]] - 1];
		u = prevl + (prevu - prevl) * F[indexOf[message[i]]];
		while(l<0.5 && u<0.5 || l>0.5 && u>0.5){
			if(u < 0.5){
				ret += '0';
				u *= 2.0;
				l *= 2.0;
			}
			if(l > 0.5){
				ret += '1';
				u = 2.0*(u-0.5);
				l = 2.0*(l-0.5);
			}
		}
		prevu = u;
		prevl = l;
	}
	return ret + toBinaryString(0.5);
}

string decode(char sourceSet[], int n, double probabilities[], string tag){

}

string toBinaryString(double tag){
	cout << tag << endl;
	string ret = "";
	for(double i = 0.5 ; tag > EPS ; i *= 0.5){
		if(tag >= i)	ret += '1', tag -= i;
		else ret += '0';
	}
	return ret;
}