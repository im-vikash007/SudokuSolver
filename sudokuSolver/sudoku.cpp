#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<cstdio>
using namespace std;
class Greeting{ // abstract class for greeting message
  protected:
  virtual void atStart()=0;  // message to display at start
  virtual void atEnd()=0;   //message to display at end
  virtual void duringProcess(){}; //message to show when application is busy in performing task
  virtual void instruction(){}; // specific message regarding uses of application (like input formate)
};
class Sudoku{ // abstract class for sudoku solver
  protected:
   int inputBoard[9][9]; //to take input by user
   int outputBoard[9][9];// solved board where possible answer stored
   virtual bool isBoardValid()=0; //checking initial board provided by user is valid or not
   virtual bool checkRow(int,int)=0;   //traversing row and marked existing no.
   virtual bool checkColumn(int,int)=0;//traversing column and marked existing no.
   virtual bool checkBox(int,int)=0; //traversing each 3*3 box and marked existing no.
   virtual bool canPlace(int,int)=0; //to find whether we can place a specific no. at current postion or not
   virtual bool Solver(int,int)=0;// method which solve the problem  
};
class Message:public Greeting{
      public:
            void atStart(){
              cout<<"\n";
              cout<<"\t\t****************        WELCOME TO SUDOKU SOLVER      **************** \n";
              cout<<"\t\t                        Created by: Vikash Kumar       \n";
              cout<<"\t\t   for any query you can reach to us through gmail: vikashkr.iot@gmail.com \n";
              cout<<"\t\t                        Press any key to contnue       \n";
            } 
            void atEnd(){
               cout<<"\t\t************      THANKS FOR USING THIS APPLICATION       ************\n";
               cout<<"\t\t  for any query you can reach to us through gmail: vikashkr.iot@gmail.com \n";
               unsigned int microsecond = 1000000;
               usleep(microsecond);//sleeps for 1 second
            }
            void duringProcess(){
                 cout<<"please wait......\n\n";
            }
            void instruction(){
                 cout<<"\t\t please follow below instruction that help us to solve your puzzle \n";
                 cout<<"\t\t 1: input should be of integer type\n";
                 cout<<"\t\t 2: at empty place provide -1 as input\n";
                 cout<<"\t\t 3: provide sudoku element in row wise fashion\n\n";
                 cout<<" Waiting for input.... \n\n";
            }
            void inValidBoardMessage(){
                 cout<<"\n\t Your provided sudoku is inValid \n";
                 cout<<"\t please provide valid sudoku \n\n\n";
            }
};
class SudokuSolver:public Sudoku{
      protected:
      bool present[10]; //helping to check validity in can place method of sudoku
      public:
      SudokuSolver(){
          memset(present,0,sizeof present); 
      };
      bool checkRow(int r,int c){ //checking row validity
           for(int i=0;i<9;i++){
              int curr=outputBoard[r][i];
              if(curr==-1)continue;
              if(present[curr]==1)return 0;
              present[curr]=1;
           }
           memset(present,0,sizeof present);
           return 1;
      }
      bool checkColumn(int r,int c){ //checking column validity
           for(int i=0;i<9;i++){
              int curr=outputBoard[i][c];
              if(curr==-1)continue;
              if(present[curr]==1)return 0;
              present[curr]=1;
           }
           memset(present,0,sizeof present);
           return 1;
      }
      bool checkBox(int r,int c){ //checking 3*3 boxes
           r=(r/3)*3;
           c=(c/3)*3;
           for(int i=r;i<r+3;i++){
             for(int j=c;j<c+3;j++){
              int curr=outputBoard[i][j];
              if(curr==-1)continue;
              if(present[curr]==1)return 0;
              present[curr]=1;
             }
           }
           memset(present,0,sizeof present);
           return 1;
      }
      bool isBoardValid(){
           for(int i=0;i<9;i++) //checking row
           {
             if(checkRow(i,0)==0)return 0;
           }
           for(int i=0;i<9;i++)//checking column
           {
              if(checkColumn(0,i)==0)return 0;
           }
           for(int i=0;i<9;i+=3){
              for(int j=0;j<9;j+=3){
                 if(checkBox(i,j)==0)return 0;
              }
           }
        return 1;
      }
      bool canPlace(int r,int c){ //checking whether we can place number at given postion or not
           memset(present,0,sizeof present);
           bool f1=checkRow(r,c);
           bool f2=checkColumn(r,c);
           bool f3=checkBox(r,c);
           memset(present,0,sizeof present);
           return f1&&f2&&f3; 
      }
      bool Solver(int r,int c){

           for(int i=r;i<9;i++){
             for(int j=c;j<9;j++){
                 int curr=outputBoard[i][j];
                 if(curr!=-1)continue;
                 for(int p=1;p<10;p++){ // trying all possible  numbers
                     outputBoard[i][j]=p;
                     if(canPlace(i,j)==0) continue;
                     if(Solver(0,0)==1)return 1;
                 }
                 outputBoard[i][j]=-1;//again put initial value as blank
                 return 0;//backtrack due to wrong earlier decision
             }
           }
           return 1;//when we finished one possible solution of board
      }
};

class App:public Message,public SudokuSolver{
      public:
      App(){ 
         atStart();  
         pauseDisplay();
      }
      void displayResult(){
         cout<<"\t sudoku to solve \n";
         for(int i=0;i<9;i++){
           cout<<"\t ";
           for(int j=0;j<9;j++){
            cout<<inputBoard[i][j]<<" ";
           }
           cout<<endl;
         }
         cout<<"\t solved sudoku \n";
         for(int i=0;i<9;i++){
           cout<<"\t ";
           for(int j=0;j<9;j++){
            cout<<outputBoard[i][j]<<" ";
           }
           cout<<endl;
         }
      }
      void pauseDisplay(){
         char temp=getchar();//to pause the display
         system("clear");
      }
      void appMessege(){
          cout<<"\n";
          cout<<"\t please enter one of the choice given below \n";
          cout<<"\t 1:To Continue enter 1\n";
          cout<<"\t 2:To Quit enter 0 \n";
      }
      void takeInput(){
          for(int i=0;i<9;i++){
             for(int j=0;j<9;j++){
                cin>>inputBoard[i][j];
                outputBoard[i][j]=inputBoard[i][j];
             }
           }
      }
      bool solve(){
           return Solver(0,0);
      }
      bool Run(){
           bool choice=1;
           while(choice){
               instruction();
               takeInput();
               if(isBoardValid()==0){
                 memset(present,0,sizeof present);
                 inValidBoardMessage();
                // pauseDisplay();
                 continue;
               }
               else{
                 duringProcess();
                 solve();
                 displayResult();
                 appMessege();
               }
               cin>>choice;
               system("clear");
           }
           atEnd();//displaying message at end
      }
};
int main(){
    App ob1;
    ob1.Run();
  
return 0;
}
