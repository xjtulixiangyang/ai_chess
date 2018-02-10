#include "../base/base.h"
#include <memory.h> 
#include "logger.h"
#ifndef TIMER_RECORD_H
#define TIMER_RECORD_H


/**
 *   ���ڼ�¼ÿһ��ģ��ʹ�õ�ʱ��.
 */

#define MAX_TIMER 50
#define MAX_TIMER_NAME 256

#define MOVE_INDEX 0
#define EVALUATE_INDEX 1
#define CAPMOVE_INDEX 2
#define NOCAPMOVE_INDEX 3
#define SEARCH_INDEX 4
#define SEARCHQUIESC_INDEX 5 

#define CHASED_BY_INDEX 6

struct TimerStruct {
	char timerNames[MAX_TIMER][MAX_TIMER_NAME]; // ���ڴ洢timer������
	int timerCnt; // ���ڴ洢timer����Ŀ 

	int timerCount[MAX_TIMER]; // �����õĴ���

	int64_t timerTime[MAX_TIMER]; // �����õ���ʱ��

	int64_t startTimes[MAX_TIMER]; // ��ʼ��ʱ��. ��Ȼ���� endTime��Ӧ.

	void StartRecord(int index ){
		startTimes[index] = GetTime();
	}

	void EndRecord(int index){
	    int64_t endTime = GetTime();
	    timerCount[index] ++;
	    timerTime[index] += endTime - startTimes[index];
	}

	void init(){
	    timerCnt = 0;

	    // ��Ҫ���м�¼ʱ��ĺ���. 
	    const char* names[] = {
		"genmoves",
		"evaluate",
		"genCapMoves",
		"genNoCapMoves",
		"allSearch",
		"SearchQuiesc",
		"ChasedBy"
	    };
	    for(int i = 0; i < sizeof(names)/ sizeof(char*); i++){
            fflush(stdout);
		    timerCount[i] = 0;
		    timerTime[i] = 0;
		    timerCnt += 1;
		    strcpy( timerNames[i], names[i]);
	    }
	}

	void PrintLn(){
	    for(int i = 0; i < timerCnt; i++){
		    if(getLogger()->opened){
		        getLogger()->logger("use time %s, call cnt %d, use time %.3f\n", timerNames[i], timerCount[i], timerTime[i] / 1000.0);
                printf("use time %s, call cnt %d, use time %.3f\n", timerNames[i],
			    timerCount[i], timerTime[i] / 1000.0);
	        fflush(stdout);	
            }
		    
			
	    }
	}
	void Reset(){
	    memset(timerCount, 0, sizeof(timerCount) );
        memset(timerTime, 0, sizeof(timerTime));
	}
};

extern TimerStruct Timer;

#define INIT_TIME()    {Timer.init();}
#define START_TIME(x)  {Timer.StartRecord(x);}
#define END_TIME(x) {Timer.EndRecord(x);}

#define OUTPUT_TIME() {Timer.PrintLn();}

#define RESET_TIME() {Timer.Reset();}

#endif
