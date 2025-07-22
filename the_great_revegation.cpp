#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
 
int N, M, answer;
int grasst[100001];
vector<int> same[100001], diff[100001];
bool impossible;
 
void visit(int x, int v)
{
  grasst[x] = v;
  for (auto n : same[x]) {
    if (L[n] == 3-v) {
    	impossible = true; 	
	}
    if (L[n] == 0){
    	visit(n, v);
	}
  }
  for (auto n : diff[x]) {
    if (L[n] == v) {
    	impossible = true; 
	}
    if (L[n] == 0) {
    	visit(n, 3-v);
	}
  }  
}
 
int main(void)
{
  ifstream fin ("revegetate.in");
  fin >> N >> M;
  for (int i=0; i<M; i++) {
    int a, b;
    string s;
    fin >> s >> a >> b;
    if (s=="S") { 
		same[a].push_back(b); same[b].push_back(a); 
	}
    if (s=="D") { 
		diff[a].push_back(b); diff[b].push_back(a); 
	}
  }
 
  for (int i=1; i<=N; i++) {
  	if (!grasst[i]) { 
	  	visit(i,1); answer++; 
	  }
  }

  
  ofstream fout ("revegetate.out");
  if (impossible) fout << "0\n";
  else {
    fout << "1";
    for (int i=0; i<answer; i++) fout << "0";
    fout << "\n";
  }
  return 0;
}
