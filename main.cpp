#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,char> > > allStates(2000);
vector<set<string> > output(2000);
vector<int> fail(2000,-1);
vector<int> myqueue;
int newstate=0;

int findMyqueue(int toBeFound){
	vector<int>::iterator it=myqueue.begin();
	for(;it!=myqueue.end();++it){
		if(*it == toBeFound) return 1;
	}
	if(it==myqueue.end()) return -1;

	return -1;
}

void printqueue(){
	cout<<"The queue is ";
	vector<int>::iterator it=myqueue.begin();
	for(;it!=myqueue.end();++it){
		cout<<*it<<" ";
	}
	cout<<""<<endl;
}

int find(int state,char a){
	vector<pair<int,char> >::iterator it;
	for(it=allStates[state].begin();it!=allStates[state].end();++it){
		if(it->second == a){
			return it->first;
		}
	}
	if(it==allStates[state].end()){
		return -1;
	}

	return -1;
}

void procedure(string s){
	int state=0,j=0;
	while(find(state,s[j])!=-1)
	{
		state=find(state,s[j]);
		j+=1;
		//cout<<"the character is "<<s[j]<<endl;
	}
	for(int p=j;p < (signed)s.length();++p){
		newstate+=1;
		allStates[state].push_back(make_pair(newstate,s[p]));
		state=newstate;
	}
	output[state].insert(s);
}

void failure(){
	int state;
	vector<pair<int,char> >::iterator it=allStates[0].begin();
	for(;it!=allStates[0].end();++it){
		//cout<<"it->first is "<<it->first<<endl;
		if(findMyqueue(it->first) == -1){
			if(it->first==0) continue;
			myqueue.push_back(it->first);
			fail[it->first]=0;
		}
	}
	//printqueue();
	while(myqueue.begin()!=myqueue.end()){
		//cout<<"inside the while loop"<<endl;
		//printqueue();
		int currentState=*(myqueue.begin());
		//cout<<"current state is "<<currentState<<endl;
		myqueue.erase(myqueue.begin());
		vector<pair<int,char> >::iterator it=allStates[currentState].begin();
		for(;it!=allStates[currentState].end();++it){
			//cout<<"inside the for loop"<<endl;
			if(findMyqueue(it->first) == -1){
				myqueue.push_back(it->first);
				state=fail[currentState];
			}
			while(find(state,it->second)== -1){
				//cout<<"it->first is "<<it->first<<" ans it->second is "<<it->second<<endl;
				//cout<<"state is "<<state<<endl;
				//cout<<"fail[state] is "<<fail[state]<<endl;
				state=fail[state];
				//cout<<"inside the 2nd "<<endl;
			}
			//cout<<"out of the while ans the state is "<<state<<endl;
			//cout<<"fail of "<<it->first<<" is "<<find(state,it->second)<<endl;
			fail[it->first]=find(state,it->second);
			output[it->first].insert(output[fail[it->first]].begin(),output[fail[it->first]].end());
		}
	}
}

void solve(string s){
    //cout<<"Called with string s as "<<s<<endl;
	int state=0;
	for(int i=0;i<(signed)s.length();++i){
		while(find(state,s[i])== -1){
			state=fail[state];
		}
		state=find(state,s[i]);
		//cout<<"After the while loop"<<endl;
		if(output[state].begin()!=output[state].end()){
			cout<<i<<endl;
			set<string>::iterator it=output[state].begin();
			for(;it!=output[state].end();++it){
				cout<<*it<<endl;
			}
		}
	}
}

int main(){
	string s;
	fstream myfile ("biblio.txt");
	/*cout<<"the output of all the states are as follows"<<endl;
	vector<set<string> >::iterator ot;
	set<string>::iterator inIt;
	int dummycount=0;
	for(ot=output.begin();ot!=output.end();++ot){
		cout<<"state is "<<++dummycount<<endl;
		for(inIt=ot->begin();inIt!=ot->end();++inIt){
			cout<<*inIt<<endl;
		}
		cout<<"-----------------"<<endl;
	}
	*/

	while(myfile >> s){
		string::iterator it=s.begin();
		//cout<<"string s is "<<s<<endl;
		for(;it!=s.end();++it){
			if(ispunct(*it)) s.erase(it);
		}
		//cout<<"string s is "<<s<<endl;
		procedure(s);
	}
	for(int i=97;i<=122;i++){
		if(find(0,i)==-1){
			allStates[0].push_back(make_pair(0,i));
		}
	}

	//fail[0]=0;
	output[0].erase(output[0].begin(),output[0].end());
	failure();
	myfile.close();

	fstream searchFile ("search.txt");
	while(searchFile >> s){
		string::iterator it=s.begin();
		//cout<<"string s is "<<s<<endl;
		for(;it!=s.end();++it){
			if(ispunct(*it)) s.erase(it);
		}
		solve(s);
	}
	searchFile.close();
	/*cout<<"the size of zeroth state is "<<output[0].size()<<endl;
	cout<<"Printing all the node value"<<endl;

	int count=0;
	vector<vector<pair<int,char> > >::iterator it;
	vector<pair<int,char> >::iterator pt;
	for(it=allStates.begin();it!=allStates.end();++it){
		cout<<"count is "<<count++<<endl;
		for(pt=it->begin();pt!=it->end();++pt){
			cout<<pt->first<<" "<<pt->second<<endl;
		}
		cout<<"-----------------------"<<endl;
	}
	*/



	/* THIS PART NEEDS TO BE UNCOMMENTED LATER .DONE JUST TO RUN MATCHING MACHINE


	cout<<"the output of all the states are as follows"<<endl;
	vector<set<string> >::iterator ot;
	set<string>::iterator inIt;
	int dummycount=0;
	for(ot=output.begin();ot!=output.end();++ot){
		cout<<"state is "<<++dummycount<<endl;
		for(inIt=ot->begin();inIt!=ot->end();++inIt){
			cout<<*inIt<<endl;
		}
		cout<<"-----------------"<<endl;
	}
	//
	//cout<<allStates[0][0].first<<endl;
	cout<<"the below is the final calculated failure function"<<endl;
	vector<int>::iterator failit=fail.begin();
	for(;failit!=fail.end();++failit){
			cout<<*failit<<" ";
	}
	*/
	return 0;
}


