#include <iostream>
#include <time.h>

using namespace std;

//4
struct errmsg{
	int i;
	errmsg(int ii) {i=ii;}
};

void thrower(){
	throw errmsg(15);
}

void toCatchAThrower(){
	try{
		thrower();
	} catch (errmsg e){
		cout << "Errno " << e.i << " detected!" << endl;
	}
	
}
//end4

//5
struct depthErr{
	int level;
	depthErr(int i){level = i;}
};

void recursionCatch(int depth, int height=0){
	if (!depth) throw depthErr(height);
	else height++;
	recursionCatch(depth-1,height);
}
//end5

//6
struct throwing{
	int t;
	throwing(int tt){ t = tt; }
};
int returnOrThrow(int arg, bool ret){
	if (ret)
		return arg;
	else
		throw throwing(arg);
}

int main() {
	//4
	//toCatchAThrower();
	//5
	//try{
	//	recursionCatch(5);
	//} catch (depthErr e){
	//	cerr << "error caught at depth: " << e.level << endl;
	//}
	//6

	//method 1: returns only
	clock_t launch = clock();
	for (int i = 0; i<100000; i++){
		int x = returnOrThrow(i,true);
	}
	clock_t done = clock();
	double diff = (done - launch) / double (CLOCKS_PER_SEC);
	cout << "Time for 100k returns only is: " << diff << " seconds." << endl;
	//method 2: throw only: no print
	clock_t launch2 = clock();
	for (int i=0; i<1000; i++){
		try{
			returnOrThrow(i,false);
		} catch (throwing e) {
			//cerr << "The argument: " << e.t << " was thrown!" << endl;
		}
	}
	clock_t done2 = clock();
	double diff2 = (done2-launch2) / double(CLOCKS_PER_SEC);
	cout << "Time for 100k throws only is ROUGHLY (linearly interpolated): " << diff2*100 << " seconds." << endl;
	return 0;
}