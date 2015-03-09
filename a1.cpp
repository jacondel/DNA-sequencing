#include <fstream> 
#include <iostream>
#include <math.h>
int main(int argc, char* argv[] ){
	if( argc < 2 ){
		std::cout<<"no file name"<<std::endl;
		return -1;
	}

	std::fstream f;

	f.open(argv[1]); // open file specified by argv[1]

	if( !f ) {
		std::cout<<"file does not exist"<<std::endl; 
		return -1;
	}
	
	std::string s;
	//grab k and m
	int k=0;
	int m=0;
	f>>k;
	f>>m;
	std::string* strArray=new std::string[m];//m indicates how many sequences are in the file	
	int currentIndex=0;
	
	
	if(k<3 || k>10 || m<2){
		std::cout<<"error"<<std::endl;
		delete[] strArray;
		return -1;
	}


	while( true ){
		f >> s;
		if(f.eof()){break;}
		if(currentIndex>=m){
			std::cout<<"error"<<std::endl;//more lines than indicated
			delete[] strArray;
			return -1;
		}
		strArray[currentIndex]=s;
		currentIndex++;
		//std::cout << s;
		//std::cout << "\n"; // *adds a line break
	}
	
	if(currentIndex<m){  // less lines than indicated
		std::cout<<"error"<<std::endl;
		delete[] strArray;
		return -1;
	}
	
	
	int* kmerArray= new int[(int)pow(4,k)]; //max number of kmers is 4^k
	for(int i=0;i<pow(4,k);i++){
		kmerArray[i]=0;
	}	
	int base4=0;
	for(int i=0;i<m;i++){//travese array of strings
		std::string whole=strArray[i];
		std::string sub;
		if(whole.size()>=(unsigned)k){
		for(int j=0;unsigned(j)<=whole.size()-k;j++){ //traverse whole string  
			sub=whole.substr(j,k);//grab substring
			//std::cout<<"substring: "<<sub<<std::endl;
			for(int l=0;unsigned(l)<unsigned(sub.size());l++){//taverse substring
				//convert to base 4;i
				if(sub.at(l)=='A'){base4+=(int)0*pow(4,sub.size()-1-l);}
				if(sub.at(l)=='C'){base4+=(int)1*pow(4,sub.size()-1-l);}
				if(sub.at(l)=='G'){base4+=(int)2*pow(4,sub.size()-1-l);}
				if(sub.at(l)=='T'){base4+=(int)3*pow(4,sub.size()-1-l);}
			}
			//std::cout<<"adding to kmer: "<< base4<<std::endl;
			kmerArray[base4]+=1;//increment kmerArray at that entry
			base4=0;
		}
		}
		//find all substrings of length k-  convert to base 4 - increcrement kmerarray for that entry
	}
	std::string reconstruct;
	std::string converted="";
	int power=0;
	int rem=0;
	for(int i=0;i<pow(4,k);i++){
		if(kmerArray[i]!=0){
			//std::cout<<"index: "<<i<<" value "<<kmerArray[i]<<std::endl;
			for(int j=0;j<k;j++){ // reconstruct kmer based on index valuei
				power=(int)pow(4,k-j-1);
				rem=(i/power)%4;		
				if(rem==0){reconstruct+="A";}
				if(rem==1){reconstruct+="C";}
				if(rem==2){reconstruct+="G";}
				if(rem==3){reconstruct+="T";}
			}
			std::cout<<reconstruct<<" "<<kmerArray[i]<<std::endl;
			reconstruct="";
		}
	}
	 

	f.close();
	delete[] kmerArray;
	delete[] strArray;
	return 0;
}
