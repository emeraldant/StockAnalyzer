#include <iostream>
using namespace std;
const int Total_Days = 1000; // Amount of Data: Preferably at least 1000
double stock_prices[Total_Days*2];
double big[Total_Days*2];
double small[Total_Days*2];
double diff[Total_Days*2];
string sig[Total_Days*2];
int dist[Total_Days*2]; //dist from last strong signal

void readData(){ // Put the data in here
	for(int i = 1; i <= Total_Days-1; i++){
		stock_prices[i] = 1000-double(i*i); 
	}
	for(int i = Total_Days-50; i <= Total_Days; i++) stock_prices[i] = 1000;
}
double getConfidence(int Day){
	return 50+100/(double(dist[Day]+2));
}
void OutputBuyOrSell(int Day){
	cout << "Day " << Day << "\n";
	cout << sig[Day] << "\n"; 
	cout << "Confidence: " << getConfidence(Day) << "%" << "\n\n\n"; // Confidence formula goes from 50-100%
}
int main() {
	int AverageWindowSmall = 50, AverageWindowBig = 200; // Set these to how long the averages are
	if(AverageWindowSmall > AverageWindowBig) swap(AverageWindowSmall, AverageWindowBig);
	readData();
	for(int i = AverageWindowBig+1; i <= Total_Days; i++){ // gets long averages
		double total = 0;
		for(int j = 0; j < AverageWindowBig; j++){
			total+=stock_prices[i-j];
		}
		big[i] = total/double(AverageWindowBig);
	}
	
	for(int i = AverageWindowSmall+1; i <= Total_Days; i++){ // gets short averages
		double total = 0;
		for(int j = 0; j < AverageWindowSmall; j++){
			total+=stock_prices[i-j];
		}
		small[i] = total/double(AverageWindowSmall);
	}
	for(int i = AverageWindowBig+1; i <= Total_Days; i++){ // gets difference in averages
		diff[i] = small[i]-big[i];
		//cout << diff[i] << " ";
	}
	for(int i = AverageWindowBig+4; i <= Total_Days; i++){ // when there's a crossover
		if(diff[i] >= 0 && diff[i-1] <= 0){
			sig[i] = "buy";
		}
		else if(diff[i] <= 0 && diff[i-1] >= 0){
			sig[i] = "sell";
		}
		else sig[i] = "hold";
	}
	for(int i = AverageWindowBig+5; i <= Total_Days; i++){ // Time since last crossover (calculate confidence based on this)
		if(sig[i] == "hold"){
			sig[i] = sig[i-1];
			dist[i] = dist[i-1]+1;
		}
		else dist[i] = 0;
	}
	OutputBuyOrSell(Total_Days);
	
	/*for(int i = AverageWindowBig+10; i <= Total_Days; i++){
		OutputBuyOrSell(i);
	}*/
	return 0;
}