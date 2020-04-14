//made by ashish bhoya
#include<bits/stdc++.h>
using namespace std;
int i,n;

typedef class ProcesseShed {
public:
	int process_no, arrival_time , burst_time;
} Process;

Process * line[100];
int first = 0, rear = -1, completed = 0, running_time = 0, tq = 6;
int last_first = 0, last_rear = -1;

bool comp(const ProcesseShed& lhs, const ProcesseShed& rhs)
{
return lhs.arrival_time < rhs.arrival_time;
}

void firstact(Process p[], int n) {
int i, j, option;
for (i = 0; i < n; ++i)
 {
   option = 1;
   if (p[i].arrival_time <= running_time && p[i].burst_time > 0)
   {
     if (first == 0)
     line[++rear] = &p[i];
     else
     {
        for (j = last_first; j <= last_rear; ++j)
        {
        if (line[j]->process_no == p[i].process_no)
        option = 0;
         }
        if (option == 1)
        line[++rear] = &p[i];
        }
    }
  }
  for (i = last_first; i <= last_rear; ++i)
  {
    if (line[i]->burst_time > 0)
    line[++rear] = line[i];
  }
}
void implement() {
	if (first-1 == rear) {
		cout<<"CPU idle for 1 second.\n";
		running_time += 1;
	}
	else {
		last_first = first;
		last_rear = rear;
		for (i = first; i <= rear; ++i, ++first)
		{
			if (line[i]->burst_time > tq)
			{
				line[i]->burst_time -= tq;
				running_time += tq;
				cout<<"Process number "<<line[i]->process_no<<"  excuted till "<<running_time<<" seconds.\n";
			}
			else if (line[i]->burst_time > 0)
			{
				running_time += line[i]->burst_time;
				line[i]->burst_time = 0;
				cout<<"Process number "<<line[i]->process_no<<"  excuted till "<<running_time<<" seconds.\n";
				++completed;
			}
		}
	}
}
int main() {
    cout<<"Enter the number of process: ";
    cin>>n;
	Process p[n];
	for (i = 0; i < n; i++) {
		cout<<"\nEnter the arrival time of process "<<i+1<<": ";
		cin>>p[i].arrival_time;
		cout<<"Enter the burst time of process "<<i+1<<": ";
		cin>>p[i].burst_time;
		p[i].process_no = i+1;
	}
	sort(p,p+n,comp);
	while (1) {
		firstact(p, n);
		cout<<"\nIn line: ";
		for (i = 0; i <= rear; ++i) {
			cout<<line[i]->process_no<<" ";
		}
		cout<<"\nfirst = "<<first<<", Rear = "<<rear<<".\n\n";
		implement();

		if (completed == n)
			break;
	}
	int j=1;
	for(i=0;i<=rear;i++)
	{
	 int jmin=i;
	 int jmax=0;
	 int jcoun=0;
	if(line[i]->process_no==j)
	{
	  for(int m=i;m<=rear;m++)
	  {
	   if(line[m]->process_no==j)
	   {
	   if(m>jmax)
	   jmax=m;
	   jcoun++;
	   }

	   }
       int maxtime=jmax*6;
	   int waitin_time=maxtime-line[i]->arrival_time-(jcoun*6);
	   cout<<"The average waiting time of process "<<i<<" is "<<waitin_time<<"\n";
	  }
	  j++;
	}
	return 0;
}
