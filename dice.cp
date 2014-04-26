#line 1 "C:/Users/Dan/Desktop/USB/Documents/Projects/Pic Tools/Published Projects/Dice/dice.c"
bit oldstate;
bit active_player;
#line 16 "C:/Users/Dan/Desktop/USB/Documents/Projects/Pic Tools/Published Projects/Dice/dice.c"
const unsigned int _pA=0b00000001;
const unsigned int _pB=0b00000010;
const unsigned int _pC=0b00000100;
const unsigned int _pD=0b00001000;
const unsigned int _pE=0b00010000;
const unsigned int _pF=0b00100000;
const unsigned int _pG=0b01000000;
const unsigned int _pH=0b10000000;




unsigned char Display(unsigned char no){
 unsigned char Pattern;
 unsigned char SEGMENT[]={
 0xFF&(~_pG)&(~_pH),
 _pB|_pC,
 0xFF&(~_pC)&(~_pF)&(~_pH),
 0xFF&(~_pE)&(~_pF)&(~_pH),
 _pB|_pC|_pF|_pG,
 0xFF&(~_pB)&(~_pE)&(~_pH),
 0xFF&(~_pB)&(~_pH),
 _pA|_pB|_pC,
 0xFF&(~_pH),
 0xFF&(~_pE)&(~_pH),
 };
 Pattern=SEGMENT[no];
 return(Pattern);
}




int Dice(int v){
 switch(v){
 case 1: return 0x10;
 case 2: return 0x22;
 case 3: return 0x98;
 case 4: return 0xAA;
 case 5: return 0xBA;
 case 6: return 0xEE;
 }
}

unsigned char Number(int Lim, int Y){
 unsigned char Result;
 static unsigned int Y;

 Y=(Y*32719+3)%32749;
 Result=((Y%Lim)+1);
 return Result;
}

unsigned char i,Seed=1;
int j;
int tmp;
int score1;
int score2;
int tmp_score;

void main(){









 OSCCON=0x6E;






 CMCON=0x07;
#line 105 "C:/Users/Dan/Desktop/USB/Documents/Projects/Pic Tools/Published Projects/Dice/dice.c"
 ADCON1=0x8F;










 TRISA = 0x00;
 TRISB = 0x80;
 TRISC = 0x00;
 TRISD = 0x00;




 active_player=0;
 score1=score2=0;

 while(1){
 if(active_player==0){
 PORTA=2;
 tmp_score=score1;
 }
 else{
 PORTA=1;
 tmp_score=score2;
 }
 PORTC=Display(score1);
 PORTB=Display(score2);
 if (PORTB.B7==0){
 i=Number(6,seed);
 tmp=Dice(i);
 PORTD=tmp;
 Delay_ms(2000);
 PORTD=0x00;
 Delay_ms(250);
 tmp_score=i+tmp_score;
 if(active_player==0){
 score1=tmp_score;
 }
 else{
 score2=tmp_score;
 }
 PORTC=Display(score1);
 PORTB=Display(score2);
 PORTD=tmp;
 Delay_ms(250);
 PORTD=0x00;
 Delay_ms(250);
 PORTD=tmp;
 Delay_ms(250);
 PORTD=0x00;
 Delay_ms(500);
 if(score1>9){
 for(j=0; j<3; j++){
 PORTA=0;
 Delay_ms(250);
 PORTA=2;
 Delay_ms(250);
 }
 active_player=0;
 score1=score2=0;
 }
 if(score2>9){
 for(j=0; j<3; j++){
 PORTA=0;
 Delay_ms(250);
 PORTA=1;
 Delay_ms(250);
 }
 active_player=0;
 score1=score2=0;
 }
 if(active_player==0){
 active_player=1;
 }
 else{
 active_player=0;
 }
 }
 }
}
