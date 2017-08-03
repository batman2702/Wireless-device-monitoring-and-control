#ifndef uart0_h
#define uart0_h

extern void uart0_init(void); 
extern void uart0_tx(char ch);  
extern void uart0_str(char *);
extern char uart0_rx(void);
extern void uart0_int(unsigned int);
extern void uart0_float(float);


#endif

