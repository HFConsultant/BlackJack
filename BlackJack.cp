/*
*BlackJack: Analyzes Player Strategies
*Joel Gravestock
*/


#include <stdlib.h>
#include <time.h>
#include <iostream.h>

const int Continue=1;
const int Game_Over=0;

int Psum=0;
int Hsum=0;
int hwin=0;
int pwin=0;
int draw=0;
int luck=0;
int pstrat=0;
int series=1;
int Deck[52]={0};
int Di=0;
int Phand[8]={0};
int Pi=0;
int Hhand[8]={0};
int Hi=0;
int Ptotal=0;
int Htotal=0;
int Dtotal=0;
int PStotal=0;
int Ltotal=0;


void Fill_Deck();
void Shuffle();
void Deal();
int After_Deal();
int PStrategy();
int PStrategy2();
int HStrategy();
void Evaluate();
void Display_Results();
void HCard_Count();
void PCard_Count();
void PCard_Count2();
void Analysis();

int main()
	{
	int seed=clock();
	srand(seed);
	Fill_Deck();
	for(series=1;series<=10;series++)
		{
		draw=0;
		hwin=0;
		pwin=0;
		luck=0;
		pstrat=0;
		for(int game=1;game<=1000;game++)
			{
			Shuffle();
			Deal();
			if(After_Deal())
				{
				if(PStrategy())
					if(HStrategy())
						Evaluate();
				}
			else
				luck++;
			}
			
		Ptotal+=pwin;
		Htotal+=hwin;
		Dtotal+=draw;
		PStotal+=draw;
		Ltotal+=luck;
		
		}
	Analysis();	
	return 0;
	}
	
	
	
void Fill_Deck()
	{
	for(int i=0;i<52;i++)
		{
		int cd=(i+1)%13+1;
		if(cd>9)
			Deck[i]=10;
		else if(cd==1)
			Deck[i]=11;
		else
			Deck[i]=cd;		
		}
	}
	
	
	
	
void Shuffle()
	{
	for(int i=0;i<52;i++)
		{
		int random=rand()%52;
		int Hold;
		Hold=Deck[i];
		Deck[i]=Deck[random];
		Deck[random]=Hold;
		}
	}
	
	

void Deal()
	{
	for(int i=0;i<8;i++)
		{
		Phand[i]=0;
		Hhand[i]=0;
		}
	Pi=0;
	Hi=0;
	Di=0;
	Phand[Pi++]=Deck[Di++];
	Hhand[Hi++]=Deck[Di++];
	Phand[Pi++]=Deck[Di++];
	Hhand[Hi++]=Deck[Di++];
	}
	
	
	
int After_Deal()
	{
	int Result=0;
	HCard_Count();
	PCard_Count();
	if(Psum==21&&Hsum==21)
		draw++;
	else if(Hsum==21)
		hwin++;
	else if(Psum==21)
		pwin++;
	else
		Result=Continue;
	return Result;
	}
	
	
	
int PStrategy()
	{
	int Result=1;
	while(Psum<17)
		{
		Phand[Pi++]=Deck[Di++];
		PCard_Count();
		}
	if(Psum>21)
		{
		Result=0;
		hwin++;
		}
	return Result;
	}



int PStrategy2()
	{
	int Ace=0;
	int Result=1;
	
	for(int i=0;Phand[i]==0;i++)
		{
		if(Phand[i]==11)
			Ace=i;
		while(Psum<18&&Phand[Ace]==11)
			{
			Phand[Pi++]=Deck[Di++];
			PCard_Count2();
			if(Psum>21)
				{
				Phand[Ace]=1;
				PCard_Count2();
				}
			}
		if(Phand[Ace]==11)	
			if(Psum==18&&Hhand[3]>8)
				{
				Phand[Pi++]=Deck[Di++];
				PCard_Count2();
				if(Psum>21)
					{
					Phand[Ace]=1;
					PCard_Count2();
					}
				 }
		}	
		
	while(Psum<12)
		{
		Phand[Pi++]=Deck[Di++];
		PCard_Count();
		}
	if(Psum==12)
		if(Hhand[3]<4&&Hhand[3]>6)
			{
			Phand[Pi++]=Deck[Di++];
			PCard_Count();
			}
	if(Hhand[3]>6)
		while(Psum>12&&Psum<17)
			{
			Phand[Pi++]=Deck[Di++];
			PCard_Count();
			}
	if(Psum>21)
		{
		hwin++;
		Result=0;
		}										
	return Result;
	}
	
	
int HStrategy()
	{
	int Result=1;
	while(Hsum<17&&Hsum<Psum)
		{
		Hhand[Hi++]=Deck[Di++];
		HCard_Count();
		}
	if(Hsum>21)
		{
		Result=0;
		pwin++;
		pstrat++;
		}
	return Result;
	}
	
	
	
void Evaluate()
	{
	if(Psum==Hsum)
		draw++;
	else if(Psum>Hsum)
		{
		pwin++;
		pstrat++;
		}
	else
		hwin++;
	}
	
	
	
void Display_Results()
	{
	cout<<"Series:   "<<series<<endl;
	cout<<"House wins:   "<<hwin<<endl;
	cout<<"Player wins:   "<<pwin<<endl;
	cout<<"Pushes:   "<<draw<<endl;
	cout<<"Lucky wins:   "<<luck<<endl;
	cout<<"Wins from player strategy:   "<<pstrat<<endl;
	}
	
	
	
	
void HCard_Count()
	{
	int True=0;
	int Ace=0;
	
	do
		{
		for(int i=0;i<8;i++)
	  		{
	  		Hsum=0;
	  		True=0;
			Ace=0;
			Hsum+=Hhand[i];
			if(Hhand[i]==11)
				{
				True=1;
				Ace=i;
				}
			}																				
	  	if(True&&Hsum>21)
	  		{
	  		Hhand[Ace]=1;
	  		for(int j=0;j<8;j++)
	  			{
	  			Hsum=0;
	  			Hsum+=Hhand[j];
	  			}
	  		}
	  	}		
	while(True);
	}
	
	
	
void PCard_Count()
	{
	int True=0;
	int Ace=0;
	
	do
		{
		for(int i=0;i<8;i++)
	  		{
	  		Psum=0;
	  		True=0;
			Ace=0;
			Psum+=Phand[i];
			if(Phand[i]==11)
				{
				True=1;
				Ace=i;
				}
			}																				
	  	if(True&&Psum>21)
	  		{
	  		Phand[Ace]=1;
	  		for(int j=0;j<8;j++)
	  			{
	  			Psum=0;
	  			Psum+=Phand[j];
	  			}
	  		}
	  	}		
	while(True);
	}

	
	
	
void PCard_Count2()
	{
	Psum=0;
	for(int i=0;i<8;i++)
		Psum+=Phand[i];
	}		
	
	
	
void Analysis()
	{
	int Games=Ptotal+Htotal+Dtotal;
	cout<<"There were "<<Games<<" games played."<<endl;
	cout<<"Player won "<<Ptotal%Games/100<<"% of the time, or a total of ";
	cout<<Ptotal<<" games."<<endl;	 				
	cout<<"Of those wins, "<<PStotal%Ptotal/100<<"%, or "<<PStotal;
	cout<<" of them, incorporated the players strategy."<<endl;
	cout<<Ltotal%Games/100<<"%, or "<<Ltotal<<" of the games, ended after the deal."<<endl;
	cout<<Dtotal%Games/100<<"%, or "<<Dtotal<<" of the games, were a push."<<endl;
	}