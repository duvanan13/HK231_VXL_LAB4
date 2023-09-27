/*
 * scheduler.c
 *
 *  Created on: Sep 17, 2023
 *      Author: duvan
 */

#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];

unsigned int current_index_task;

void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period =  PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;
		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		current_index_task++;
	}
}

void SCH_Update(void){
    unsigned char Index;
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].pTask){
            if (SCH_tasks_G[Index].Delay == 0) {
                SCH_tasks_G[Index].RunMe += 1;
                if (SCH_tasks_G[Index].Period) {
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }
            } else {
                SCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}

void SCH_Dispatch_Tasks(void){
    unsigned char Index;
    for (Index = 0; Index < SCH_MAX_TASKS; Index++){
        if (SCH_tasks_G[Index].RunMe > 0) {
            (*SCH_tasks_G[Index].pTask)();
            SCH_tasks_G[Index].RunMe -= 1;
            if (SCH_tasks_G[Index].Period == 0)
            {
                SCH_Delete_Task(Index);
            }
        }
    }
}

void SCH_Delete_Task(uint32_t TaskID){
    SCH_tasks_G[TaskID].pTask = 0x0000;
    SCH_tasks_G[TaskID].Delay = 0;
    SCH_tasks_G[TaskID].Period = 0;
    SCH_tasks_G[TaskID].RunMe = 0;
}



