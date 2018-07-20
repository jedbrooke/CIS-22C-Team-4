
#include <iostream> 
#include <thread>
#include <chrono>


using namespace std;

void print(){
	cout << '#';
	cout << flush;
}

void printProgBar( int percent, string message){
  std::string bar;

  for(int i = 0; i < 50; i++){
    if( i < (percent/2)){
      bar.replace(i,1,"=");
    }else if( i == (percent/2)){
      bar.replace(i,1,"_");
    }else{
      bar.replace(i,1," ");
    }
  }

  std::cout<< "\r" "[" << bar << "] ";
  std::cout.width( 3 );
  std::cout<< percent << "% " << message << std::flush;
}


int main (){
	cout << "writing files..." << endl;
	for(int i = 0; i <= 100; i++){
		if(  i < 50 ){
			printProgBar(i,"Writing Products");
		} else {
			printProgBar(i,"Writing Customers");
		}
		if( i < 60 and i > 49){
			this_thread::sleep_for(chrono::milliseconds(50));
		} else {
			this_thread::sleep_for(chrono::milliseconds(10));
		}
		
	}
	cout << endl;
}

