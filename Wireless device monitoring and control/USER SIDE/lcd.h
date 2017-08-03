#ifndef _lcd_h_
#define _lcd_h_

extern void init_lcd(void);
extern void char_lcd(char);
extern void str_lcd(char *);
extern void int_lcd(unsigned int);
extern void float_lcd(float);
extern void cmd_lcd(char);
extern void write_lcd(char);


#endif
