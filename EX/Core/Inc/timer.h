/*
 * timer.h
 *
 *  Created on: 7 Sep 2023
 *      Author: duvan
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

extern int timer1_flag;
void setTimer1(int duration);

extern int timer2_flag;
void setTimer2(int duration);

extern int timer3_flag;
void setTimer3(int duration);

extern int timer4_flag;
void setTimer4(int duration);


void timerRun();

#endif /* INC_TIMER_H_ */
