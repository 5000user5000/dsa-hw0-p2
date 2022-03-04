#include<stdio.h>
#include <string.h>
#include<stdlib.h> 
#include <stdbool.h> //�ϥ�bool,c++�O�������� 
//using namespace std;

//����n�Ϊ��ۭq�q��ƫŧi,main�~��� 
int findNext(int board[25][25],int rowClue[25][13],int colClue[25][13],int row,int col);
bool Recur(int board[25][25],int rowClue[25][13],int colClue[25][13],int row,int col,int total);
bool valid(int board[25][25],int rowClue[25][13],int colClue[25][13],int row,int col);
bool isFull(int board[25][25],int row,int col,int total);
void cleandown(int board[25][25],int row,int col,int cell);

int main()
{
	int row,col,a=0,b=0,clue=0,total=0; 
	int rowClue[25][13]={0},colClue[25][13]={0};//�̦h��12��,���L�o�˷|�ܳ·�,�h�@�ӳƥΦbfindNext���|���X�d��,�w�]��0,���Τ]�i�ϥ���0 
	int board[25][25]={0};//�]��1 * 25�]�� ,�w�]0 
	bool justCall;//�u�O���I�srecur 
	
	scanf("%d",&row);
	scanf("%d",&col);

	//row clue
	for(int i=0;i<row;i++)
	{
	 scanf("%d",&clue);
	 for(int j=0;j<clue;j++)
	 {
	  
	  scanf("%d",&rowClue[i][j]);//�C��clue�ɤ~���|�~�����e�� 
	  total+=rowClue[i][j];//�p��®��,��K����T�{�O�_����®� 
	 }
	 
	}
	
	//col clue
	for(int i=0;i<col;i++)
	{
	 scanf("%d",&clue);
	
	 for(int j=0;j<clue;j++)
	 {
	  
	  scanf("%d",&colClue[i][j]);//�C��clue�ɤ~���|�~�����e�� 
	 }
	
	}
	
	justCall=Recur(board,rowClue,colClue,row,col,total);
	
	
	return 0;
}

bool Recur(int board[25][25],int rowClue[25][13],int colClue[25][13],int row,int col,int total)
{
   int cell;
   bool succeed;
   if(isFull(board,row,col,total))//�T�{��S 
   {
   	if(valid(board,rowClue,colClue,row,col))//���Ī��� 
   	{
	   //���L 
	   for(int i=0;i<row;i++)
	   {
	   	for(int j=0;j<col;j++)
	   	{
	   		if(board[i][j]==1)printf("o");//��"",''�|�X�� 
	   		else printf("_");
		   }
		printf("\n");//���� 
	   }
	   
	   
	   //return true;
	   exit(0);//��������{���N�����~��]��L�`���F 
	} 
   	else 
	   return false;
   } 
   
   else{
   	cell=findNext(board,rowClue,colClue,row,col);//��U�@�� 
   	if(cell==-1)return false;
   	board[cell/col][cell% col]=1;//�W�� 
   	succeed = Recur(board,rowClue,colClue,row,col,total);//���j 
   	
   	if(succeed)return true;//���G�S�γB,�]���p�G���\�N����exit �S���nreturn 
   	
   	cleandown(board,row,col,cell);//�M�z
	board[cell/col][cell% col]= -1;//���,��next���|��o 
	succeed = Recur(board,rowClue,colClue,row,col,total);
   	
	if(succeed)return true;
   	//memset(board, 0, sizeof board);//�M��,�ϥ�string.h 
   	//cell=-2;  make cell empty���G���� 
   	
	return false;
   }


} 

//�Ĥ@row�ݨ�U�@��row ,return next�n���lindex 
int findNext(int board[25][25],int rowClue[25][13],int colClue[25][13],int row,int col)
{
	    int rowclueNum,breakout=0,k=0,clue;
		for(int i=0;i<row;i++)//�T���j�� 
		{
			clue=0;//�k�s(��)
			k=0; 
			while(rowClue[i][clue]>0)
			{
				
				rowclueNum = rowClue[i][clue]; 
				for(int j=k;j<col;j++)
			    {
				  if(board[i][j]==0&&rowclueNum>0)return i*col+j;//���0~24 
							
				  if(board[i][j]==1)
				  {
					rowclueNum--;
					breakout=j;//��j�ӵ���
				                   }
			      if(rowclueNum==0)break;
	            
				}
				k =breakout+2;
				clue++;
			}
					
		}
		return -1;//���S��,�i��O��(�z�פW�񺡷|�Q�ˬdfull,�ҥH���|���񺡪����p)�άO�L�k�� 
}

bool valid(int board[25][25],int rowClue[25][13],int colClue[25][13],int row,int col) 
{
    int breakout =0,k=0,colclueNum,clue=0;
	for(int i=0;i<col;i++)
	{
		clue=0;//���s�k0 (��)
		k=0; 
		while(colClue[i][clue]>0)//���l�O����row�W�h,�ҥH�u�n�ˬdcol���L�ŦX�N�n 
		{
		  
		  
		  colclueNum = colClue[i][clue]; 
		  for(int j=k;j<row;j++)
		  {
			
							
		    if(board[j][i]==1)//board[row][col]
		    {
				colclueNum--;
				breakout=j;//��j�ӵ���
				if(j<24&& colclueNum>0 && board[j+1][i]!=1) return false;//�p�G�O�s����,�ӫ᭱�S���´N���F,<24�O��out of range          
			  
			  
			  }
			
			if(colclueNum>0&&j==row-1)return false;//�p�G�����o���,�٥�����,�N�O���~ 
			
			if(colclueNum<=0) 
			{ 
			  if(j<24&&board[j+1][i]>0)return false;//�p�G�U�@��ӪŮ�o���Ʀr�N����~ ,and ensure no out of range
			  if(colclueNum<0) return false;//�i��o��S��,�����´N�|<0 
			  break;
	          }
	          
	        
		  }
		  k =breakout+2;//�[2,�]�ťճB�w�ˬd ,���U�@��i��ª����� 
		  
		  clue++;
			
		}
		
			
		
		
	}
	return true;
	
	
	
}

bool isFull(int board[25][25],int row,int col,int total)//�ǥѭp��®��`�ƽT�{�O�_���,�u�O�C�����n�]�@�� ,�Ӹ귽 
{
	int sum=0;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
		   if(board[i][j]>0)sum++;	
		}
	}
	if(sum==total)return  true;
	else return false;
	
}
void cleandown(int board[25][25],int row,int col,int cell)//�M�z�᭱��cell 
{
    
    //int i = cell/col;//row
    //int j = cell%col;//col
    for(int i = cell/col;i<row;i++)
    {
        for(int j = cell%col;j<col;j++)
        {
            board[i][j]=0;
        }
    }
    
}

