bit oldstate;
bit active_player;

//**  Configuration :
//      7Seg = Bit
//        a  =  2      |  0
//        b  =  3      |  1
//        c  =  6      |  2
//        d  =  5      |  3
//        e  =  4      |  4
//        f  =  1      |  5
//        g  =  0      |  6
//       dip =  7      |  u
//**

const unsigned int _pA=0b00000001;
const unsigned int _pB=0b00000010;
const unsigned int _pC=0b00000100;
const unsigned int _pD=0b00001000;
const unsigned int _pE=0b00010000;
const unsigned int _pF=0b00100000;
const unsigned int _pG=0b01000000;
const unsigned int _pH=0b10000000;

//**
//  Number to 7-Seg:
//**
unsigned char Display(unsigned char no){
    unsigned char Pattern;
    unsigned char SEGMENT[]={
		0xFF&(~_pG)&(~_pH),              // 0 = All but G and H
		_pB|_pC,                         // 1 = B and C
		0xFF&(~_pC)&(~_pF)&(~_pH),       // 2 = All but C, F and H
		0xFF&(~_pE)&(~_pF)&(~_pH),       // 3 = All but E, F and H
		_pB|_pC|_pF|_pG,                 // 4 = B, C, F and G
		0xFF&(~_pB)&(~_pE)&(~_pH),       // 5 = All but B, E and H
		0xFF&(~_pB)&(~_pH),              // 6 = All but B and H
		_pA|_pB|_pC,                     // 7 = A, B and C
		0xFF&(~_pH),                     // 8 = All but H
		0xFF&(~_pE)&(~_pH),              // 9 = All but H
    };
    Pattern=SEGMENT[no];
    return(Pattern);
}

//**
//  Number to Dice:
//**
int Dice(int v){
    switch(v){
		case 1: return 0x10; //0b00010000
		case 2: return 0x22; //0b00100010
		case 3: return 0x98; //0b10011000
		case 4: return 0xAA; //0b10101010
		case 5: return 0xBA; //0b10111010
		case 6: return 0xEE; //0b11101110
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
	//**
	//  Oscillator Configuration:
	//  0b0
	//  - 4 MHz (110)
	//  - Primary system clock (1)
	//  - Stable frequency (1)
	//  - System clock : Internal RC (10)
	//  - Total : 0b01101110
	//**
	OSCCON=0x6E;

	//**
	//  Comparator Configuration:
	//  Disable all
	//  - Total : 0b00000111;
	//**
	CMCON=0x07;

	//**
	//  A/D Configuration:
	//  0b
	//  Left Justified (1)
	//  A/D Clock divide by 2 disabled (0)
	//  VRef - = VSS (0)
	//  VRef + = VDD (0)
	//  - All Digital (1111)
	//  - Total : 0b10001111;
	//**
	ADCON1=0x8F;

	//**
	//  PORT Directions
	//  - Output:
	//    + PORTA
	//    + PORTC
	//    + PORTD
	//  - Input:
	//    + PORTB [RB7]
	//**
	TRISA = 0x00;
	TRISB = 0x80;
	TRISC = 0x00;
	TRISD = 0x00;

	//**
	//  Main Program
	//**
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