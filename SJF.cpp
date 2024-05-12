#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;	//	进程ID 
    int ArrivalTime;	//创建时间 
    int BurstTime;  //运行时间 
};//定义一个程序结构体 

struct SJF{
    struct Process *processes;
    int numProcesses;

    double AvgWaitingTime;
    double (*SJF_Scheduling)(struct SJF *); 
    void (*InputFromOutside)(struct SJF *, int);
    void (*SortProcessesByBurstTime)(struct SJF *);
};//定义一个SJF结构体 

void SortProcessesByBurstTime(struct SJF *S) {
    struct Process Process1;
    for (int i = 0; i < S->numProcesses - 1; i++) {
        for (int j = i + 1; j < S->numProcesses; j++) {
            if (S->processes[i].BurstTime > S->processes[j].BurstTime) {
                Process1 = S->processes[i];
                S->processes[i] = S->processes[j];
                S->processes[j] = Process1;
            }
        }
    }
}//定义一个根据运行时间对进程排序的函数  

double SJF_Scheduling(struct SJF *S){
    double WaitingTime = 0;
    int CompletionTime = 0;

    for (int i = 0; i < S->numProcesses; i++) {
        CompletionTime = (CompletionTime > S->processes[i].ArrivalTime ? CompletionTime : S->processes[i].ArrivalTime) + S->processes[i].BurstTime;
        WaitingTime += (CompletionTime - S->processes[i].ArrivalTime - S->processes[i].BurstTime) > 0 ? (CompletionTime - S->processes[i].ArrivalTime - S->processes[i].BurstTime) : 0;
    }
    S->AvgWaitingTime = WaitingTime / S->numProcesses;
    return S->AvgWaitingTime;	
}//定义一个用于实现SJF调度算法的函数，用他计算出平均等待时间，并返回这个值

void InputFromOutside(struct SJF *S, int n) {
    S->processes = (struct Process *)malloc(n * sizeof(struct Process));
    S->numProcesses = n;

    for (int i = 0; i < n; i++) {
        printf("进程ID是 %d\n", i + 1);
        printf("输入创建时间: ");
        scanf("%d", &S->processes[i].ArrivalTime);
        printf("输入运行时间: ");
        scanf("%d", &S->processes[i].BurstTime);
        S->processes[i].pid = i + 1;
    }
    S->SortProcessesByBurstTime(S); // 调用排序函数对进程按照执行时间排序

    double avgWaitingTime = SJF_Scheduling(S);
    printf("平均等待时间是 %f\n", avgWaitingTime);

    free(S->processes);
}//定义一个函数，用于从外部输入进程的到达时间和执行时间，并计算出平均等待时间。 

int main() {
	struct SJF S;
    S.SJF_Scheduling = &SJF_Scheduling;//给S的SJF_Scheduling函数指针赋值，使其指向SJF_Scheduling函数 
    S.InputFromOutside = &InputFromOutside;//给S的InputFromOutside函数指针赋值，使其指向InputFromOutside函数
    S.SortProcessesByBurstTime = &SortProcessesByBurstTime; //给S的SortProcessesByBurstTime函数指针赋值，使其指向SortProcessesByBurstTime函数
    
    printf("请输入进程:");
    int ProNum;
    printf("输入进程数量: ");
    scanf("%d", &ProNum);
	S.InputFromOutside(&S, ProNum);
	return 0;
}

