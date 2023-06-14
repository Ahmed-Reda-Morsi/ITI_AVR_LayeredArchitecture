/*
 *  @Author: Ahmed Reda Morsi.
 */ 


#ifndef BITMATH_H
#define BITMATH_H

// functions macros
#define SET_BIT(VAR,BITNO) ((VAR) |= (1<<(BITNO)))// set 1
#define CLEAR_BIT(VAR,BITNO) ((VAR) &= ~(1<<(BITNO))) // set 0
#define TOGGLE_BIT(VAR,BITNO) ((VAR) ^= (1<<(BITNO)) )// toggle
#define GET_BIT(VAR,BITNO)  (((VAR)>>(BITNO))&0x01) // get  pin 
/*
void SeT_BiT(volatile uint8_t* Port,uint8_t PinNumber){
    (*Port)|= (1<<PinNumber);
}

void ToG_BiT(volatile uint8_t* Port,uint8_t PinNumber){
    (*Port) ^= 1<<PinNumber;
}

void ClR_BiT(volatile uint8_t* Port,uint8_t PinNumber){
    (*Port) &= ~(1<<PinNumber);
}

uint8_t  GeT_BiT(volatile uint8_t* Port,uint8_t PinNumber){
    return(((*Port)>>PinNumber)&0x01);
}*/

#endif