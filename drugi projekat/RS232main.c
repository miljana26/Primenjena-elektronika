#include <stdio.h>
#include <stdlib.h>
#include<p30fxxxx.h>
#include "Tajmeri.h"
#include "adc.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);

unsigned char tempRX1,tempRX2;
unsigned int napred = 0;

void initUART1(void)
{
    U1BRG=0x0040;//ovim odredjujemo baudrate

    U1MODEbits.ALTIO=1;//biramo koje pinove koristimo za komunikaciju osnovne ili alternativne

    IEC0bits.U1RXIE=1;//omogucavamo rx1 interupt

    U1STA&=0xfffc;

    U1MODEbits.UARTEN=1;//ukljucujemo ovaj modul

    U1STAbits.UTXEN=1;//ukljucujemo predaju
}

void initUART2(void)
{
    U2BRG=0x0040;//ovim odredjujemo baudrate

    IEC1bits.U2RXIE=1;//omogucavamo rx1 interupt

    U2STA&=0xfffc;

    U2MODEbits.UARTEN=1;//ukljucujemo ovaj modul

    U2STAbits.UTXEN=1;//ukljucujemo predaju
}


unsigned int stanje = 0;
unsigned int buf [6];
void __attribute__((__interrupt__)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX1=U1RXREG;
                
} 


int n=0;
void __attribute__((__interrupt__)) _U2RXInterrupt(void) 
{
    IFS1bits.U2RXIF = 0;
    tempRX2=U2RXREG;

    if(tempRX2 != 0 ){
        buf[n]=tempRX2;
        tempRX2 = 0;
        
        if(n < 5){
            n++;
            buf[n] = 0;
        
        }
        else n = 0;
    }
    
    provera();
    
    
} 

void provera(){
    
    if(buf[0]=='S' && buf[1]=='T' && buf[2]=='A' && buf[3]=='N' && buf[4]=='I' && buf[5] == '\0' && stanje != 0 ){
                stanje = 0;
                RS232_putst2("Robot je stao");
                WriteUART2(13);
            }

}

void WriteUART1(unsigned int data)
{
	  while(!U1STAbits.TRMT);

    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

void WriteUART2(unsigned int data)
{
	  while(!U2STAbits.TRMT);

    if(U2MODEbits.PDSEL == 3)
        U2TXREG = data;
    else
        U2TXREG = data & 0xFF;
}

void RS232_putst1(register const char *str)
{

    while((*str)!=0){
    
        WriteUART1(*str);
        str++;
    } 
}

void RS232_putst2(register const char *str)
{

    while((*str)!=0){
    
        WriteUART2(*str);
        str++;
    } 
}

void WriteUART1dec2string(unsigned int data)
{
	unsigned char temp;

	temp=data/1000;
	WriteUART1(temp+'0');
	data=data-temp*1000;
	temp=data/100;
	WriteUART1(temp+'0');
	data=data-temp*100;
	temp=data/10;
	WriteUART1(temp+'0');
	data=data-temp*10;
	WriteUART1(data+'0');
}

void WriteUART2dec2string(unsigned int data)
{
	unsigned char temp;

	temp=data/1000;
	WriteUART2(temp+'0');
	data=data-temp*1000;
	temp=data/100;
	WriteUART2(temp+'0');
	data=data-temp*100;
	temp=data/10;
	WriteUART2(temp+'0');
	data=data-temp*10;
	WriteUART2(data+'0');
}

int stoperica1,stoperica2,stoperica3,stoperica4,stoperica5;
void __attribute__((__interrupt__)) _T1Interrupt(void)
{
   	TMR1 =0;
    stoperica1++;
    IFS0bits.T1IF = 0;
}

void __attribute__((__interrupt__)) _T2Interrupt(void)
{

   	TMR2 =0;
    stoperica2++;
    IFS0bits.T2IF = 0;
}

void __attribute__((__interrupt__)) _T3Interrupt(void)
{

   	TMR3 =0;
    stoperica3++;
    IFS0bits.T3IF = 0;
}

unsigned int slanje1 = 0;
unsigned int slanje2 = 0;
unsigned int vreme1 = 0;
unsigned int vreme2 = 0;
void __attribute__((__interrupt__)) _T4Interrupt(void)
{

   	TMR4 =0;
    stoperica4++;
    if(PORTBbits.RB1 == 1  && slanje1 == 1){
        stoperica4 = 0;
        slanje1 = 2;
    }
    if(PORTBbits.RB1 == 0 && slanje1 == 2) {
        vreme1 = stoperica4;
        slanje1 = 3;
        T4CONbits.TON = 0;
    }
    if(stoperica4 > 9999 && slanje1 == 1 && PORTBbits.RB1 == 0){
        vreme1 = 9999;
        slanje1 = 3;
        T4CONbits.TON = 0;
    }
    IFS1bits.T4IF = 0;
}

void __attribute__((__interrupt__)) _T5Interrupt(void)
{

   	TMR5 =0;
    stoperica5++;
    if(PORTBbits.RB3 == 1  && slanje2 == 1){
        stoperica5 = 0;
        slanje2 = 2;
    }
    if(PORTBbits.RB3 == 0 && slanje2 == 2) {
        vreme2 = stoperica5;
        slanje2 = 3;
        T5CONbits.TON = 0;
    }
    if(stoperica5 > 9999 && slanje2 == 1 && PORTBbits.RB3 == 0){
        vreme2 = 9999;
        slanje2 = 3;
        T5CONbits.TON = 0;
    }
    IFS1bits.T5IF = 0;
}

void Delay_us (int vreme)//funkcija za kasnjenje u us
	{
		while(stoperica1 < vreme);   
	}

void Delay_ms (int vreme)//funkcija za kasnjenje u milisekundama
	{
        T3CONbits.TON = 1;
		while(stoperica3 < vreme);
        T3CONbits.TON = 0;
        //stoperica3 = 0;

	}

unsigned int sirovi0;
unsigned int temp0; 
void __attribute__((__interrupt__)) _ADCInterrupt(void) 
{
    sirovi0=ADCBUF0;//sharp
	temp0=sirovi0;

    IFS0bits.ADIF = 0;
    
} 

void sharp()
{
    if(sirovi0 > 1700 && napred == 0)    
        napred = 1;
    
    if(sirovi0 < 1700 && napred == 1)
       napred = 0;
}

unsigned int x1, x2;
int izr1 = 0;
int izr2 = 0;

void ultra1(){

    switch (slanje1) {
        case 0:
            stoperica1 = 0;
            T1CONbits.TON = 1;
            LATBbits.LATB0 = 1;
            Delay_us(2);
            LATBbits.LATB0 = 0;
            T1CONbits.TON = 0;
            slanje1 = 1;
            T4CONbits.TON = 1;
            stoperica4 = 0;
            break;
            
        case 3:
            
            x1 = (int)((float)(340 * ((float)((float)vreme1/100))) / 2);
            izr1 = 1;
            slanje1 = 0;
            break;
            
        default:
            break;    
    }
            
}

void ultra2(){

    switch (slanje2) {
        case 0:
            stoperica1 = 0;
            T1CONbits.TON = 1;
            LATBbits.LATB2 = 1;
            Delay_us(2);
            LATBbits.LATB2 = 0;
            T1CONbits.TON = 0;
            slanje2 = 1;
            T5CONbits.TON = 1;
            stoperica5 = 0;
            break;
            
        case 3:
            x2 = (int)((float)(340 * ((float)((float)vreme2/100))) / 2);
            izr2 = 1;
            slanje2 = 0;
            break;
            
        default:
            break;        
    }            
}

void desni_stani (){
    LATBbits.LATB11 = 0;
    LATBbits.LATB12 = 0;
}

void levi_stani (){
    LATFbits.LATF0 = 0;
    LATFbits.LATF1 = 0;
}

void pauza (){
    levi_stani();
    desni_stani();
    Delay_ms(500);
    stoperica3 = 0;
}

void pauza_desni (){
    desni_stani();
    Delay_ms(500);
    stoperica3 = 0;
}

void desni_napred (){
    LATBbits.LATB11 = 1;
    LATBbits.LATB12 = 0;
}

void desni_nazad (){
    LATBbits.LATB11 = 0;
    LATBbits.LATB12 = 1;
}


void levi_napred (){
    LATFbits.LATF0 = 0;
    LATFbits.LATF1 = 1;
}

void levi_nazad (){
    LATFbits.LATF0 = 1;
    LATFbits.LATF1 = 0;
}

unsigned int mode = 1;
int x;

int main(int argc, char** argv) {
    
    initUART1();
    initUART2();
    ADCinit();
    ADCON1bits.ADON=1;
    ConfigureADCPins();
    Init_T1();
    Init_T2();
    Init_T3();
    Init_T4();
    Init_T5();
    
    TRISBbits.TRISB0=0; //izlazni pin B0
    TRISBbits.TRISB2=0; //izlazni pin B2
    
    TRISBbits.TRISB1=1;//ulazni pin B1
    ADPCFGbits.PCFG1=1;// digitalni B1
    TRISBbits.TRISB3=1;//ulazni pin B3
    ADPCFGbits.PCFG3=1;// digitalni B3
    
    TRISDbits.TRISD0=0; //izlaz za pwm1
    TRISDbits.TRISD1=0; //izlaz za pwm2
    
    OC1CONbits.OCM=0b110; 
    OC2CONbits.OCM=0b110; 
    
    //koristi se tajmer2
    OC1CONbits.OCTSEL = 0;   
    OC2CONbits.OCTSEL = 0; 
    T2CONbits.TON = 1; 
 
    OC1R = 0;  
    OC2R = 0;  
    OC1RS = 360;   
    OC2RS = 360;  
    
    //za levu stranu
    TRISBbits.TRISB11=0; //izlazni pin B11
    TRISBbits.TRISB12=0; //izlazni pin B12
    
    //za desnu stranu
    TRISFbits.TRISF0=0; //izlazni pin F0
    TRISFbits.TRISF1=0; //izlazni pin F1
    
 
    levi_stani();
    desni_stani();
    

	while(1)
	{

            if(buf[0]=='K' && buf[1]=='R' && buf[2]=='E' && buf[3]=='N' && buf[4]=='I' && buf[5] == '\0' && stanje != 1){
                stanje = 1;
                RS232_putst2("Robot krece");
                WriteUART2(13);
            }
            
            if (stanje){
                
                sharp();
                while(izr1 != 1 || izr2 !=1){
                ultra1();
                ultra2();
                }
                ultra1();
                ultra2();
                
                WriteUART1dec2string(x1);
                WriteUART1(13);
                WriteUART1dec2string(x2);
                WriteUART1(13);
                WriteUART1(13);
                
                switch(mode){
                    case 1:
                        
                        if(x1 > x2 && (x1 - x2) > 1){
                            desni_napred();
                            levi_nazad();
                        }

                        if(x1 < x2 && (x2 - x1) > 1){
                            desni_nazad();
                            levi_napred();
                        }
                        
                        if((x1 > x2 && (x1 - x2) <= 1) ||(x1 < x2 && (x2 - x1) <= 1)){
                            desni_stani();
                            levi_stani();
                            RS232_putst2("Postavljen prema desnoj ivici");
                            WriteUART2(13);
                            Delay_ms(1500);
                            stoperica3 = 0;
                            mode = 2;
                            RS232_putst2("Ide pravo");
                            WriteUART2(13);
                        }
                        break;
                        
                    case 2:
                        OC1RS = 400;
                        OC2RS = 365;
                        desni_napred();
                        levi_napred();

                        if(napred == 1){
                            OC1RS = 405;
                            OC2RS = 380;
                            pauza();
                            levi_nazad();
                            desni_napred();
                            RS232_putst2("Skrece levo");
                            WriteUART2(13);
                            Delay_ms(980);
                            stoperica3 = 0;
                            RS232_putst2("Skrenuo je levo");
                            WriteUART2(13);
                            desni_stani();
                            levi_stani();
                            Delay_ms(1030);
                            stoperica3 = 0;
                            mode = 1;
                            OC1RS = 360;
                            OC2RS = 360;
                        }

                        if(x2 > x1 && (x2 - x1) > 250 && napred == 0){
                            OC1RS = 340;
                            OC2RS = 380;
                            stoperica3 = 0;
                            Delay_ms(100);
                            stoperica3 = 0;
                            pauza();
                            levi_napred();
                            desni_nazad();
                            RS232_putst2("Skrece desno");
                            WriteUART2(13);
                            Delay_ms(1530);
                            stoperica3 = 0;
                            pauza;
                            levi_napred();
                            desni_napred();
                            while(x1 > 400){
                                
                                ultra1();
                                ultra2();
                            }
                            
                            Delay_ms(1000);
                            stoperica3 = 0;
                            RS232_putst2("Skrenuo je desno");
                            WriteUART2(13);
                            mode = 1;
                            OC1RS = 360;
                            OC2RS = 360;
                        }
                        
                        break;

                        
                    default:
                        break;
                }
                
                }else{
                    levi_stani();
                    desni_stani();
                }
                
            
            
            
            

    }//od whilea

    return (EXIT_SUCCESS);
}

