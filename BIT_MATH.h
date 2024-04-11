/*
 * BIT_MATH.h
 *
 * Created: 22/10/2023 
 *  Author: ROAA AIMAN 
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define BIT_MATH_H
#define SET_BIT( var , bit) var|=(1<<bit)
#define CLR_BIT( var , bit) var&=~(1<<bit)
#define TOG_BIT( var , bit) var^=(1<<bit)
#define GET_BIT( var , bit) ((var>>bit)&1)



#endif /* BIT_MATH_H_ */
