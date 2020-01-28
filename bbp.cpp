//g++ -std=c++14 -pthread bbp.cpp 
#include"header.hpp"
int k; 
int th;
std::vector<std::thread> t; // vector de thread
std::vector<std::future<int>> thread_vec_;
std::mutex m;
using namespace std;

// Pi = Somme(i>=0) {[4/(8*i+1) - 2/(8*i+4) - 1/(8*i+5) - 1/(8*i+6)] / 16^i}
long double algo_bbp(int debut, int fin) 
{
  cout<<"(begin, end) = (" << debut << ", "<< fin << ")--------------------------\n";
  long double pi=0.0f;
  m.lock();
  for (int i=0; i<fin; ++i) 
  {
    int d1=8*i+1, q=d1+3, d5=q+1, d6=d5+1;
    pi += (4.0/d1 - 2.0/q - 1.0/d5 - 1.0/d6) / (1ll<<(4*i));
    if(i>=debut)
    {
      cout << "  k = "<<i<< setprecision (30) <<"  |   Pi ="<<pi << "\n"; 
    }
  }
  cout<<endl;
  m.unlock();
  return pi  ;
}

void mult_thread()
{
  int step = k/th;
  int begin = 0; 
  int end = 0; 
  long double a = 0.0;

  for (int r = 0;r <th; ++r)
  {
    begin = end;
    end += step;
    auto m1 = std::async(std::launch::async, algo_bbp, begin, end);
    a += m1.get();
  }
}
int recorder()
{
 cout << "Tapez nombre de décimales k: "; cin >> k;
 cout << "Tapez le nombre de threads th : "; cin >> th;
  cout << "\n";
  clock_t start;
  double duree;
  start = clock();
  
  cout<<"ALGORITHME_BBP:"<<"\n";
  cout<<"valeur precise de PI: PI=3.14159265358979"<<"\n";
  cout<<"Pi = Somme {[4/(8*i+1) - 2/(8*i+4) - 1/(8*i+5) - 1/(8*i+6)] / 16^i}"<<"\n";
  cout << "##################################################\n\n";
  
  mult_thread();
  cout << "##################################################\n";
  
  cout << "_________________________________________________________________\n\n";
	duree = (clock() - start ) / (double) CLOCKS_PER_SEC;
  cout<<"Nombre de Décimale apres la virgule= "<<k<<endl;
  cout<<"Nombre de treads: "<<th<<endl;
  cout<<"durée d'exécution: "<<duree<<endl;
  cout << "_________________________________________________________________\n";
  return 0;
}