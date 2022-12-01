#include<stdio.h>
#include<iostream>
#include<string.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;
int NoofTask;
vector<vector<int> >Task;
int execution[1000];
int deadline[1000];
int pperiod[1000];
int PeriodsLCM=1;

char help[255];
int i,j,h;
float f;
int Gcd(int a, int b)
{
    if (a == 0)
        return b;
    return Gcd(b % a, a);
}
void GetProcess(){
	cout<<"Enter the no of Task\n";
	cin>>NoofTask;
	for(int i=0;i<NoofTask;i++){
		vector<int> temp;
		cout<<"Enter the execution time of Task "<<i+1<<"\n";
		cin>>execution[i];
		cout<<"Enter the deadline of Task "<<i+1<<"\n";
		cin>>deadline[i];
		cout<<"Enter the period of Task "<<i+1<<"\n";
		cin>>pperiod[i];
		temp.push_back(execution[i]);
		temp.push_back(deadline[i]);
		temp.push_back(pperiod[i]);
		Task.push_back(temp);
	}
	for(int i=0;i<NoofTask;i++){
		cout<<"Task "<<i+1<<"\n";
		cout<<"Execution Time : "<<execution[i]<<"\n";
	}
}
 



void getPeriodsLCM()
{
	int help[1000];
	for(i=0 ; i<NoofTask; i++)
	{
		help[i] = pperiod[i];
	}
	int h = 0;
	int theLowestValueInHelp;
	int theLowestValueIndex;
	while(h == 0)
	{
		h = 1;
		theLowestValueInHelp = help[0];
		theLowestValueIndex = 0;
		
		for(i=0 ; i<NoofTask; i++)
		{
			if(theLowestValueInHelp != help[i])
			{
				h = 0;
				if(theLowestValueInHelp>help[i])
				{
					theLowestValueInHelp = help[i];
					theLowestValueIndex = i;
					
				}
				
			}	
		}
		if(h == 0)
		{
			help[theLowestValueIndex] = theLowestValueInHelp + pperiod[theLowestValueIndex];
		}	
	}
	PeriodsLCM = help[0];
	printf("We Can Schedule That Real System In %d Units(%d is the Lcm of our processes periods)",PeriodsLCM,PeriodsLCM);
	
}
float schedulability()
{
	float Condition = 0;
	float x,y;
	printf("\n The Sum Of :");
	for(i=0 ; i<NoofTask ; i++)
	{
		x = execution[i];
		y = pperiod[i];
		Condition = Condition + (x/y);
		printf(" (%d/%d) ",execution[i],pperiod[i]);
	}
	printf("is equal : %f", Condition);
	return Condition;
}

void schedule()
{
	int earliestDeadline;
	int earliestDeadlineIndex;
	int schedulingTable[PeriodsLCM];
	int remainsCapacity[1000];
	int nextDeadline[1000];
	int processOnlineNewPeriod[1000];
	for(i=0 ; i<NoofTask ; i++)
	{
		nextDeadline[i] = deadline[i];
		remainsCapacity[i] = execution[i];
		processOnlineNewPeriod[i] = 0;
	}
	// scheduling time milestone...
	for(i=0; i<PeriodsLCM; i++)
	{
		cout<<"("<<i<<" "<<i+1<<")"<<endl;
			
			//getting the earliest deadline
			earliestDeadline = PeriodsLCM;
			earliestDeadlineIndex = -1;
			for(j=0 ; j<NoofTask ; j++)
			{
				 if(remainsCapacity[j] > 0)
				 {
				 	
				 	if(earliestDeadline > nextDeadline[j])
				 	{
				 		
				 		earliestDeadline = nextDeadline[j];
				 		earliestDeadlineIndex = j;
					 }
				 }
			}
			cout<<"     [exc = "<<earliestDeadlineIndex<<"]"<<endl;
			remainsCapacity[earliestDeadlineIndex]--;
			
			//get the next deadline distance	
			for(j=0 ; j<NoofTask ; j++)
			{
				
				 if(processOnlineNewPeriod[j] == (pperiod[j] - 1 ) )
				 {
				 	nextDeadline[j] =  deadline[j];
				 	remainsCapacity[j] = execution[j];
				 	processOnlineNewPeriod[j] = 0;
				 }
				 else
				 {
				 	if(nextDeadline[j] >0)
				 	{
				 		nextDeadline[j]--;
					 }
					 else
					 {
					 	if(remainsCapacity[j] > 0)
					 	{
					 		cout<<"\nthe process" <<j<< "has no chance to complete its Capacity"<<endl;

						 }
					 }
				 	 processOnlineNewPeriod[j]++; 
				 }
				 
				 
			}
	}


}

int main()
{   GetProcess();
	getPeriodsLCM();
	
	
	
	cout<<"Schedulability Test :\n";
	f = schedulability();
	if(f <= 1)
	{
		cout<<"\n This Real Time System Is Schedulable because %f <= 1"<<f<<endl;
		schedule();
	}
	else
	{
		cout<<"\nThis Real Time System Is Not Schedulable because %f > 1"<<f<<endl;
		
	}
}
