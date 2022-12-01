#include <bits/stdc++.h>

using namespace std;

class Processtask{
    public:
    int execution_time;
    int timeperiod;
};
bool comp(const Processtask& lhs, const Processtask& rhs)
{
  if(lhs.timeperiod!=rhs.timeperiod)
    return lhs.timeperiod<rhs.timeperiod;
  else
   return lhs.execution_time <rhs.execution_time;
}
float calculateU(Processtask *task,int n){
    float U=0.0; //  intialise the float variable 
    for (int i = 0; i < n; i++) 
        U+=(float)task[i].execution_time/task[i].timeperiod;
    return U;
}
float Kvalue(int n){
    return (float)n*(pow(2,(float)1/n)-1);
}
int main(){
    int n;
    cout<<"Enter the no of processes for schedulabliity : ";
    cin>>n;
    Processtask task[n];
    for(int i=0;i<n;i++){
        cout<<"Enter exectution time of task "<<i+1<<" : ";
        cin>>task[i].execution_time;
        cout<<"Enter Total time Period of task "<<i+1<<" : ";
        cin>>task[i].timeperiod;
    }

    sort(task,task+n,comp); //Sort in priority

    float U= calculateU(task,n);
    float K = Kvalue(n);
    //cout<<K<<endl;
    if(U>1){
        cout<<"Not schedulable by Test Nessecity";
        return 0;
    }
    if(U<K){
         cout<<"Schedulable by Test 2";
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        cout<<"Running precise test for Process P( "<<task[i].execution_time<<" , "<<task[i].timeperiod<<" )\n";
        float r0=0,r1=0;  
        for (int j = 0; j <= i; j++)
        {
            r0+=task[j].execution_time;
        }
        cout<<"R0 is "<<r0<<endl;
        while (true)
        {
            r1=task[i].execution_time;
            
            for (int x = i-1; x>=0; x--)
            {
                r1+=ceil((float)r0/task[x].timeperiod)*task[x].execution_time;
            }
            //cout<<r1<<endl;
            if(r0==r1 && r0<=task[i].timeperiod){
                  cout<<"Schedulable\n";
                  break;
            }
            else if (r1>task[i].timeperiod){
                cout<<"Not Schedulable\n";
                break;
            }
            else r0=r1;
            
        }
        
        
    }
}