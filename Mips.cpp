#include "stdafx.h"
#include "Memory.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <conio.h>

	
using std::string;
using std::getline;

using namespace std;

class MIPS
{
public:
	
	Memory Memoria;// Objeto para acessar os métodos da memória
		
	///////////// DEFINIÇÃO DOS MÈTODOS///////////

void load()
	{
        unsigned long int instruction;
		int cont=1;
		char end[400],palavra[33];//Aqui é a palavra que está no arquivo;
	    PC=1;
		ciclos=0;
		ifstream leitura; //objeto de leitura de arquivo.
		
		cout<<"Entre com o endereco onde esta localizado o arquivo que sera lido.\nExemplo:\"C:/exemplo/teste.txt\""<<endl;
		cin>>end;
		
        leitura.open(end); // abertura de arquivo.
        if(!leitura.is_open( ))  // Saber se o arquivo foi aberto.
        {
		  system("cls");
          cout<<"\t\t\tERROR!! CODE:0x001";
          leitura.clear( ); //reseta o objeto leitura, para limpar memória do sistema
          _getch();
		  exit(0);
        }
	   
	    system("cls");
	    cout<<"\t\t\tArquivo aberto com sucesso!"<<endl;
		cout<<"\nPressione qualquer tecla para que seu codigo seja processado";
		getch();
        while(leitura.getline(palavra,33))//lê o arquivo, os 32 bits até o \n e armazena em palavra, até o fim do arquivo
        {
             instruction=strtoul(palavra,NULL,2);//converte de string para unsigned long int.
             Memoria.write(cont,instruction);
			 cont+=4;
			 ciclos++;
	    }
       leitura.close();
	}
void fetch()
{
	unsigned long int instruction;
	instruction=Memoria.read(PC);
	itoa(instruction,IR,2);
	PC+=4;
}
void complementar()
{
	int i,qtd;
	char comp_zeros[33];
	qtd=strlen(IR);

	for(i=0;i<=32;i++)
	{
	  comp_zeros[i]=NULL;
    }

	i=0;
	while(qtd<32)
	{
	   comp_zeros[i]='0';
	   qtd++;
	   i++;
	}

	strcat(comp_zeros,IR);
			  
	for(i=0;i<=32;i++)
	{
      IR[i]=comp_zeros[i];
    }
}
void decode()
{
	unsigned int qtd;
	qtd=strlen(IR);
	if(qtd<32)
	{
      complementar();
    }
	if(qtd>32)
	{
    		system("cls");
 			printf("ERRO CODE:0x004");
			_getch();
			exit(0);
	}
	string s;
    s=IR;
          

	enum opcodes
	{
      LW=35,
      SW=43,
	};

	enum funct
	{
      ADD=32,
      MUL=24,
      DIV=26,
      SUB=34,
	};
    unsigned int opcodeDEC;
	s.copy(opcode,6,0);
	opcode[6]=NULL;
	opcodeDEC=strtoul(opcode,NULL,2);

	if(opcodeDEC!=35 && opcodeDEC!=43 && opcodeDEC!=0)
	{
		system("cls");
		cout<<"ERRO CODE:0x005";
		_getch();
		exit(0);
	}

	unsigned int functDEC;
    s.copy(Funct,6,26);
	Funct[6]=NULL;
    functDEC=strtoul(Funct,NULL,2);
	
	switch (opcodeDEC)
	{
	   case LW:
		    s.copy(rs,5,6);
			rs[5]=NULL;
		
			s.copy(rt,5,11);
			rt[5]=NULL;

			s.copy(rd,5,16);
			rd[5]=NULL;
			
			break;
	   case SW:
		    
		    s.copy(rs,5,6);
			rs[5]=NULL;
		
			s.copy(rt,5,11);
			rt[5]=NULL;

			s.copy(rd,16,16);
			rd[16]=NULL;


		    break;

	   case 0:
		
		   if(functDEC==32)
		   {
				s.copy(rs,5,6);
				rs[5]=NULL;
				
				s.copy(rt,5,11);
				rt[5]=NULL;

				s.copy(rd,5,16);
				rd[5]=NULL;

				s.copy(sa,5,21);
				sa[5]=NULL;
		   }
		   if(functDEC==24)
		   {
			    s.copy(rs,5,6);
				rs[5]=NULL;
				
				s.copy(rt,5,11);
				rt[5]=NULL;

				s.copy(rd,5,16);
				rd[5]=NULL;

				s.copy(sa,5,21);
				sa[5]=NULL;
		   }
		   if(functDEC==26)
		   {
			    s.copy(rs,5,6);
				rs[5]=NULL;
				
				s.copy(rt,5,11);
				rt[5]=NULL;

				s.copy(rd,5,16);
				rd[5]=NULL;

				s.copy(sa,5,21);
				sa[5]=NULL;
		   }
		   if(functDEC==34)
		   {
			    s.copy(rs,5,6);
				rs[5]=NULL;
				
				s.copy(rt,5,11);
				rt[5]=NULL;

				s.copy(rd,5,16);
				rd[5]=NULL;

				s.copy(sa,5,21);
				sa[5]=NULL;
		   }
		   if(functDEC != 32 && functDEC!=24 && functDEC!=26 && functDEC!=34)                                        
		   {	
				system("cls");
				cout<<"ERRO CODE:0x006";
				_getch();
				exit(0);
			}
		   break;
		}
	}
void execute()
{
	enum opcodes
	{
      LW=35,
      SW=43,
	};
	enum funct
	{
      ADD=32,
      MUL=24,
      DIV=26,
      SUB=34,
	};

	unsigned long int end;
	
	unsigned long int opcodeDEC;
	opcodeDEC=strtoul(opcode,NULL,2);
	
	unsigned long int FunctDEC;
    FunctDEC=strtoul(Funct,NULL,2);
	
	switch (opcodeDEC)
	{
	   case SW:
		    
		    end=strtoul(rd,NULL,2);
			Memoria.write(end,$t0);
		    
			break;

	   case 0:
			   
		   if(FunctDEC==32)// ADD
		   {
				$s0=strtoul(rs,NULL,2);
				$s1=strtoul(rt,NULL,2);

				$t0=$s0+$s1;				
				_ltoa($t0,rd,2);
		   }
		   if(FunctDEC==24)//MUL
		   {
			    $s1=strtoul(rs,NULL,2);
				$s2=strtoul(rt,NULL,2);
			    
				for(int i=1;i<=$s2;i++)
			    {
				   $t0+=$s1;
			    }
				_itoa($t0,rd,2);
 		   }

		   if(FunctDEC==26)//DIV
		   {
			    $s1=strtoul(rs,NULL,2);
				$s2=strtoul(rt,NULL,2);
			    HI=0;
				if($s1<$s2)
				{
					system("cls");
					printf("ERRO CODE:0x002");
				    _getch();
					exit(0);
				}
				$t0=$s1;
				for(;;)
				{
					$t0-=$s2;
					HI++;
					if($t0<=1)
					break;
				}
				itoa(HI,rd,2);
				$t0=HI;
		   }
		   if(FunctDEC==34)//SUB
		   {
			    $s0=strtoul(rs,NULL,2);
				$s1=strtoul(rt,NULL,2);
				$t0=$s0-$s1;
				if($t0<=0)
				{
					system("cls");
					printf("ERROR CODE:0x003");
				    _getch();
					exit(0);
				}

				_itoa($t0,rd,2);
			
		   }
		   break;
	}
								
}
void dump_memory(int inic, int fim)
{
	int i;
	unsigned long int data;
	i=inic;
	while (i<=fim)
	{
		data=Memoria.read(inic);
		if(data==3435973836)
		{
			Memoria.write(inic,0);
			data=Memoria.read(inic);
			cout<<"\n"<<inic<<" - "<<data<<"\n";
		}
		if(data>1000 && data<3435973836)
		{
			cout<<"\n"<<inic<<" - "<<data<<" [instrucao em memoria]"<<endl;
		}
		if(data>0 && data<1000)
		{
			cout<<"\n"<<inic<<" - "<<data<<" [dado]\n";
		}
		inic++;
		i++;
		
	}
	_getch();
	menu();
}
void dump_regs()
{	
		int opc;
		system("cls");
		unsigned int opcodeDEC;
		opcodeDEC=strtoul(opcode,NULL,2);
		
		if(opcodeDEC==43)
		{
			std::cout<<"\nOpcode= "<<opcode
			<<"\nrd[address]= "<<rd
			<<endl;
			cout<<"\nSelecione a opcao desejada:\n1-Para Ver o endereco em decimal\n2-Voltar ao menu principal\n3-Sair do programa ";
			cin>>opc;
			if(opc==1)
			{
				unsigned int rdDEC;
				rdDEC=strtoul(rd,NULL,2);
				cout<<"\nrd[address]= "<<rdDEC
					<<endl;
				getch();
				menu();
			}
			if(opc==2)
			{		
				menu();
			}
			if(opc==3)
			{
				system("cls");
				cout<<"\t\tObrigado por usar o simulador de arquitetura Mips Basic\n\t\t    Developed by: Renato Fernandes e Ivan Lopes";
				_getch();
				exit(0);
			}
		}
		else
		{	
			std::cout<<"\nOpcode= "<<opcode
			<<"\n$s0= "<<rs
			<<"\n$s1= "<<rt
			<<"\n$t0= "<<rd
			<<"\nFunct= "<<Funct
			<<endl;
		}
		
		cout<<"\nSelecione a opcao desejada:\n1-Para Ver o resultado em decimal\n2-Voltar ao menu principal\n3-Sair do programa ";
		cin>>opc;
		if(opc==1)
		{
			unsigned int rsDEC,rtDEC,rdDEC,saDEC,functDEC,opcodeDEC;
			rsDEC=strtoul(rs,NULL,2);
			rtDEC=strtoul(rt,NULL,2);
			rdDEC=strtoul(rd,NULL,2);
			functDEC=strtoul(Funct,NULL,2);
			opcodeDEC=strtoul(opcode,NULL,2);

			cout<<"\nOpcode= "<<opcodeDEC
			<<"\n$s0= "<<rsDEC
			<<"\n$s1= "<<rtDEC
			<<"\n$st= "<<rdDEC
			<<"\nFunct= "<<functDEC
			<<endl;
			_getch();
			menu();
		}
			if(opc==2)
			{		
				menu();
			}
			if(opc==3)
			{
				system("cls");
				cout<<"\t\tObrigado por usar o simulador de arquitetura Mips Basic\n\t\t    Developed by: Renato Fernandes e Ivan Lopes";
				_getch();
				exit(0);
			}

}
int menu()
{
	int opc;
	system("cls");
	cout<<"\t\t\t Operacao realizada com sucesso!!\n\nPressione a opcao desejada: ";
	cout<<"\n1-Para ver os registradores\n2-Ver memoria\n3-Sair do Programa\n";
	cin>>opc;
	if(opc==1)
	{
		dump_regs();
	}
	if(opc==2)
	{
		int inicial,final;
		system("cls");
		cout<<"Entre com a posicao inicial de memoria a ser lida: ";
		cin>>inicial;
		cout<<"Entre com a posicao final de memoria a ser lida: ";
		cin>>final;
		dump_memory(inicial,final);
	}
	if(opc==3)
	{
		system("cls");
		cout<<"\t\tObrigado por usar o simulador de arquitetura Mips Basic\n\t\t    Developed by: Renato Fernandes e Ivan Lopes";
		return 0;
	}
}
void step()
{
	fetch();
	decode();
	execute();
}
void run()
	{	
		while(ciclos>0)	
		{
			step();
			ciclos--;
		}
	}

	//REGISTRADORES
	unsigned long int $s0,$s1,$s2,$s3;
	unsigned long int $t0,$t1,$t2,$t3;
	
	int HI;
	char opcode[7];
    char rd[16];
    char rs[6];
    char rt[6];
    char sa[6];
    char Funct[7];
	int ciclos;
	char IR[33];
    int PC;
};

int main()
{
	MIPS Obj;
	int opc;
	cout<<"\t\t\tBem Vindo ao Simulador de arquitetura MIPS\n\n";
	Obj.load();
	Obj.run();
	Obj.menu();
	return 0;
}
