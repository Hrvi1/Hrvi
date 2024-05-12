#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;	//	����ID 
    int ArrivalTime;	//����ʱ�� 
    int BurstTime;  //����ʱ�� 
};//����һ������ṹ�� 

struct SJF{
    struct Process *processes;
    int numProcesses;

    double AvgWaitingTime;
    double (*SJF_Scheduling)(struct SJF *); 
    void (*InputFromOutside)(struct SJF *, int);
    void (*SortProcessesByBurstTime)(struct SJF *);
};//����һ��SJF�ṹ�� 

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
}//����һ����������ʱ��Խ�������ĺ���  

double SJF_Scheduling(struct SJF *S){
    double WaitingTime = 0;
    int CompletionTime = 0;

    for (int i = 0; i < S->numProcesses; i++) {
        CompletionTime = (CompletionTime > S->processes[i].ArrivalTime ? CompletionTime : S->processes[i].ArrivalTime) + S->processes[i].BurstTime;
        WaitingTime += (CompletionTime - S->processes[i].ArrivalTime - S->processes[i].BurstTime) > 0 ? (CompletionTime - S->processes[i].ArrivalTime - S->processes[i].BurstTime) : 0;
    }
    S->AvgWaitingTime = WaitingTime / S->numProcesses;
    return S->AvgWaitingTime;	
}//����һ������ʵ��SJF�����㷨�ĺ��������������ƽ���ȴ�ʱ�䣬���������ֵ

void InputFromOutside(struct SJF *S, int n) {
    S->processes = (struct Process *)malloc(n * sizeof(struct Process));
    S->numProcesses = n;

    for (int i = 0; i < n; i++) {
        printf("����ID�� %d\n", i + 1);
        printf("���봴��ʱ��: ");
        scanf("%d", &S->processes[i].ArrivalTime);
        printf("��������ʱ��: ");
        scanf("%d", &S->processes[i].BurstTime);
        S->processes[i].pid = i + 1;
    }
    S->SortProcessesByBurstTime(S); // �����������Խ��̰���ִ��ʱ������

    double avgWaitingTime = SJF_Scheduling(S);
    printf("ƽ���ȴ�ʱ���� %f\n", avgWaitingTime);

    free(S->processes);
}//����һ�����������ڴ��ⲿ������̵ĵ���ʱ���ִ��ʱ�䣬�������ƽ���ȴ�ʱ�䡣 

int main() {
	struct SJF S;
    S.SJF_Scheduling = &SJF_Scheduling;//��S��SJF_Scheduling����ָ�븳ֵ��ʹ��ָ��SJF_Scheduling���� 
    S.InputFromOutside = &InputFromOutside;//��S��InputFromOutside����ָ�븳ֵ��ʹ��ָ��InputFromOutside����
    S.SortProcessesByBurstTime = &SortProcessesByBurstTime; //��S��SortProcessesByBurstTime����ָ�븳ֵ��ʹ��ָ��SortProcessesByBurstTime����
    
    printf("���������:");
    int ProNum;
    printf("�����������: ");
    scanf("%d", &ProNum);
	S.InputFromOutside(&S, ProNum);
	return 0;
}

