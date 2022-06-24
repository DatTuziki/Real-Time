// OKE
#pragma config FOSC = HS   // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF    // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF   // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF  // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF   // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
// CONFIG2
#pragma config BOR4V = BOR40V // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF

//#pragma config CONFIG1 = 0x2CD4
//#pragma config CONFIG2 = 0x0700

// LCD module connections
#define LCD_RS RE0
#define LCD_EN RE2
#define LCD_D4 RD4
#define LCD_D5 RD5
#define LCD_D6 RD6
#define LCD_D7 RD7
#define LCD_RS_DIR TRISE0
#define LCD_EN_DIR TRISE2
#define LCD_D4_DIR TRISD4
#define LCD_D5_DIR TRISD5
#define LCD_D6_DIR TRISD6
#define LCD_D7_DIR TRISD7
// End LCD module connections

#include <xc.h>
#define _XTAL_FREQ 8000000
#define Baud_rate 9600
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "LCD.h" // include LCD driver source file


struct date
{
  int day, month, year;
};

struct time
{
  int hour, minute, second;
  struct date d;
};

// Kiem tra nam nhuan
int IsLeapYear(int y);

// tao lap ngay thang nam
struct date setdate(int d, int m, int y);
// tao lap ngay thang nam gio phut giay
struct time settime(int year, int month, int day, int hour, int minute, int second);

// hien thi ngay thang nam
void displaydate(struct date d);
// hien thi ngay thang nam gio phut giay
void displaytime(struct time t);

// chinh lai ngay thang nam cho chuan
void formatdate(struct date *this);
// chinh lai ngay thang nam gio phut giay cho chuan
void formattime(struct time *this);

// cong ngay hien tai voi mot so
void adddate(struct date *this, int a);
void addtime(struct time *this, int a);

int IsLeapYear(int y)
{
  if (y % 4 == 0)
  {
    while (y % 100 == 0)
    {
      if (y % 400 == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
    return 1;
  }
  else
  {
    return 0;
  }
}

struct date setdate(int d, int m, int y)
{
  struct date s1;
  s1.day = d;
  s1.month = m;
  s1.year = y;
  return s1;
}

struct time settime(int year, int month, int day, int hour, int minute, int second)
{
  struct time s1;
  s1.d = setdate(day, month, year);
  s1.hour = hour;
  s1.minute = minute;
  s1.second = second;
  return s1;
}

void displaydate(struct date d)
{
  formatdate(&d);
  printf("%d / %d / %d", d.day, d.month, d.year);
}

void displaytime(struct time t)
{
  formattime(&t);
  printf("%d / %d / %d\n", t.d.day, t.d.month, t.d.year);
  printf("%d gio %d phut %d giay", t.hour, t.minute, t.second);
}

void formatdate(struct date *this)
{
p:;
  if (this->month <= 12)
  {
    switch (this->month)
    {
    case 1:
      if (this->day > 31)
      {
        this->day = this->day - 31;
        this->month++;
        goto p;
      }
      break;
    case 2:
      if (IsLeapYear(this->year))
      {
        if (this->day > 29)
        {
          this->day = this->day - 29;
          this->month++;
          goto p;
        }
      }
      else
      {
        if (this->day > 28)
        {
          this->day = this->day - 28;
          this->month++;
          goto p;
        }
      }
      break;
    case 3:
      if (this->day > 31)
      {
        this->day = this->day - 31;
        this->month++;
        goto p;
      }
      break;
      ;
    case 4:
      if (this->day > 30)
      {
        this->day = this->day - 30;
        this->month++;
        goto p;
      }
      break;
    case 5:
      if (this->day > 31)
      {
        this->day = this->day - 31;
        this->month++;
        goto p;
      }
      break;
    case 6:
      if (this->day > 30)
      {
        this->day = this->day - 30;
        this->month++;
        goto p;
      }
      break;
    case 7:
      if (this->day > 31)
      {
        this->day = this->day - 31;
        this->month++;
        goto p;
      }
      break;
    case 8:
      if (this->day > 31)
      {
        this->day = this->day - 31;
        this->month++;
        goto p;
      }
      break;
    case 9:
      if (this->day > 30)
      {
        this->day = this->day - 30;
        this->month++;
        goto p;
      }
      break;
    case 10:
      if (this->day > 31)
      {
        this->day = this->day - 31;
        this->month++;
        goto p;
      }
      break;
    case 11:
      if (this->day > 30)
      {
        this->day = this->day - 30;
        this->month++;
        goto p;
      }
      break;
    case 12:
      if (this->day > 31)
      {
        this->day = this->day - 31;
        this->month++;
        goto p;
      }
      break;
    }
  }
  if (this->month > 12)
  {
    this->year++;
    this->month = this->month - 12;
    goto p;
  }
}

void formattime(struct time *this)
{
  int ND = 0;
  while (this->second >= 60)
  {
    this->second = this->second - 60;
    this->minute++;
  }
  while (this->minute >= 60)
  {
    this->minute = this->minute - 60;
    this->hour++;
  }
  while (this->hour >= 24)
  {
    this->hour = this->hour - 24;
    ND++;
  }
  adddate(&this->d, ND);
  formatdate(&this->d);
}

void adddate(struct date *this, int a)
{
  this->day = this->day + a;
  formatdate(this);
}

void addtime(struct time *this, int a)
{
  this->second = this->second + a;
  formattime(this);
}

void UART_initialize(void)
{
  // cau hinh chan uart
  TRISCbits.TRISC6 = 0; // TX Pin set as output
  TRISCbits.TRISC7 = 1; // RX Pin set as input

  SPBRG = ((_XTAL_FREQ / 16) / Baud_rate) - 1;
  BRGH = 1; // baudrate toc do cao

  SYNC = 0; // Asynchronous
  SPEN = 1; // cho phep cong noi tiep

  TXEN = 1; // cho phep truyen
  CREN = 1; // cho phep nhan

  // chon che do truyen nhan 8 bits
  TX9 = 0;
  RX9 = 0;
}

void UART_sendChar(char bt)
{
  while (!TXIF)
    ;         // lam tre he thong khi bo dem TX dang trong
  TXREG = bt; // ghi gia tri truyen vao thanh ghi TXREG
}

char UART_getChar()
{
  if (OERR) // check Error
  {
    CREN = 0; // If error -> Reset
    CREN = 1; // If error -> Reset
  }

  while (!RCIF)
    ; // lam tre he thong khi bo dem RX dang trong
  return RCREG;
}

void UART_sendString(char *str)
{
  while (*str)
  {
    UART_sendChar(*str++);
  }
}

void UART_getString(char *str, int len)
{
  for (int i = 0; i < len; i++)
  {
    str[i] = UART_getChar();
  }
}
char text[20], TEXT[20];
unsigned int Count = 0;

void main(void)
{
    UART_initialize();
    int CHECK=0;
    char check;
    mark:;
    check = UART_getChar();
    if(check!='s')
    {
        goto mark;
    }
    CHECK++;
    if(CHECK < 3)
    {
        goto mark;
    }
  TRISE1 = 0;
  RE1 = 0;
  ANSEL = ANSELH = 0x00;
  TMR1 = 3035;
  T1CONbits.TMR1CS = 0;
  T1CONbits.T1CKPS1 = 1;
  T1CONbits.T1CKPS0 = 1;
  T1CONbits.T1SYNC = 1;
  T1CONbits.TMR1ON = 1;

  OSCCON = 0X70;      // set internal oscillator to 8MHz
  LCD_Begin();        // initialize LCD module
  LCD_Cmd(LCD_CLEAR); // clear the whole screen

  struct time t;

  char get_value;
  int count = 0;

p:;
//update handshake two step
  //LCD_Cmd(LCD_CLEAR);
  UART_sendChar('u');
  get_value = UART_getChar();
  if (get_value != 'y')
    goto p;
  char UP[17];
  UART_getString(UP, 17);
  count++;
  if (count < 2)
    goto p;
  int dd=(UP[0] - '0') * 10 + (UP[1] - '0');
  int month=(UP[2] - '0') * 10 + (UP[3] - '0');
  int yy=(UP[4] - '0') * 1000 + (UP[5] - '0')*100+(UP[6] - '0') * 10 + (UP[7] - '0');
  if(yy==1970)
  {
      goto p;
  }
  int hh = (UP[8] - '0') * 10 + (UP[9] - '0');
  int mm = (UP[10] - '0') * 10 + (UP[11] - '0');
  int ss = (UP[12] - '0') * 10 + (UP[13] - '0');

  t = settime(yy, month, dd, hh, mm, ss);
  int updateTime = 3600;
  while (1)
  {
    if (PIR1bits.TMR1IF == 1)
    {
      PIR1bits.TMR1IF = 0;
      TMR1 = 3035;
      Count++;
      if (Count == 4)
      {
        Count = 0;
        updateTime--;
        if(updateTime==0)
        {
            goto p;
        }
        addtime(&t, 1);
        sprintf(TEXT, "%c%c%c %02d/%02d/%04d      ",UP[14],UP[15],UP[16], t.d.day, t.d.month, t.d.year);
        sprintf(text, "%02dh %02dm %02ds         ", t.hour, t.minute, t.second);
        LCD_Goto(1,1);
        LCD_Print("Real-time Clock     ");
        LCD_Goto(1,2);
        LCD_Print(TEXT);
        LCD_Goto(1, 3);
        LCD_Print(text);
        LCD_Goto(1, 4);
        LCD_Print("GMT+7 HCMC VietNam  ");
      }
    }
  }
}
// End of code.
