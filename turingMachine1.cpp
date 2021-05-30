/**
 * This code is for the turing machine 
 * accepting string A^nB^n , example   AAABBB, AABB, AAAAABBBBB
 * where number of A's = number of B's , and A's are before B's
 * 
 * ------------------------------------------------------
 * this code is copyrighted to Bilal Alqudah, PhD (C)
 * @ school of engineering 
 * Al-hussien bin talal University - Maan, Jordan 
 * not allowed to be used for commercial uses. educational only is free.
 * you can contact me @ 
 * www.bilal-qudah.com
 * https://www.ahu.edu.jo/View_Articlear.aspx?type=9&ID=0&drid=302
 * 
**/
#include <iostream>
#include <string>

using namespace std;
int printTabe( char *t, int size ){
for (int i=0; i< size ; i++){
    cout<<*t;
    t++;
}
cout<<endl;
return 1;
}


int initTabe( char *t, int size ){
for (int i=0; i< size ; i++){
    *t='^';
    //cout<<*t;
    t++;
}

for (int i=0; i< size/2 ; i++){
    t--;
}
return 1;
}

int moveHead(char *t, char direction){
    int val=0;
    switch (direction){
    case 'L':
        t++;
        val=-1;
        cout<<" <-- Moving left"<<endl;
        break;
    case 'R':
        t--;
        val=1;
        cout<<" Moving right -->" <<endl;
        break;
    }
return val ;
}


int initInput_AnBnTouring(int n,char *t, int size){
    char *head=t;
    t+=((size/2)-n);
    for(int i=0; i<n; i++){
        *t='A';
        *(t+n)='B';
        t++;
    }
    t=head;
    return ((size/2)-n);

}
bool AnBnMachine(char *root, char *t, int size, int head){
    bool stop=false;
    bool accept=false;
    string state="q0";
    t+=head;
    while (!stop){
        // q0
      if (state=="q0") { 
               printTabe(root,size);
               cout<<"state= "<<state<<"; reading "<<*t<<endl;
               switch(*t){
                case 'A':
                    *t='x';
                    t+=moveHead(t,'R');
                    state="q1";
                    break;
                case 'y':
                    *t='y';
                    t+=moveHead(t,'R');
                    state="q3";
                    break;
                default:
                    stop=true;
             };
             

     }

     else if (state=="q1"){
        cout<<"state= "<<state<<"; reading "<<*t<<endl;
        printTabe(root,size);
        switch(*t){
            case 'y':
                *t='y';
                t+=moveHead(t,'R');
                state="q1";
                break;
             case 'A':
                *t='A';
                t+=moveHead(t,'R');
                state="q1";
                break; 
             case 'B':
                *t='y';
                t+=moveHead(t,'L');
                state="q2";
                break;
              default:
                stop=true;

        }

     } else if (state=="q2"){
        cout<<"state= "<<state<<"; reading "<<*t<<endl;
        printTabe(root,size);
              switch(*t){
            case 'y':
                *t='y';
                t+=moveHead(t,'L');
                state="q2";
                break;
             case 'A':
                *t='A';
                t+=moveHead(t,'L');
                state="q2";
                break;
            case 'x':
                *t='x';
                t+=moveHead(t,'R');
                state="q0";
                break;
             default:
                stop=true; 

        }  

     } else if (state=="q3") { 
        cout<<"state= "<<state<<"; reading "<<*t<<endl;
        printTabe(root,size);
          switch(*t){
           case 'y':
                *t='y';
                t+=moveHead(t,'R');
                state="q3";
                break;
            case '^':
                *t='^';
                t+=moveHead(t,'L');
                state="q4";
                break;
            default:
                stop=true;
          } 
       }
       else if(state=="q4"){
        cout<<"state= "<<state<<"; reading "<<*t<<endl;
        printTabe(root,size);
                accept=true;
                stop=true;
       }

 
    }

   return accept; 
}
int RejectedInput_AnBnConfigureAndRun(int size, char *tabe){
    // now for the A^nB^n touring machine  
    int n=2;      // how many A's and how many B's you want to have on the input
    int head=initInput_AnBnTouring(n,tabe,size);    // where the input start
    char *root=tabe;                                // root pointer, used for printing 
    printTabe(root,size);
    cout<<"head location ="<<head<<endl;              
    *(tabe+head+1)='B';
    bool result=AnBnMachine(root,tabe,size,head);               // this will run the machine 
    printTabe(root,size);
    return result;
}
bool AcceptedInput_AnBnConfigureAndRun(int size, char *tabe){
    // now for the A^nB^n touring machine  
    int n=3;      // how many A's and how many B's you want to have on the input
    int head=initInput_AnBnTouring(n,tabe,size);    // where the input start
    char *root=tabe;                                // root pointer, used for printing 
    cout<<"head location ="<<head<<endl;              
    bool result= AnBnMachine(root,tabe,size,head);               // this will run the machine 
    printTabe(root,size);
    return result;
}

int main()
{
    char *tabe=new char;   // the input tabe
    int size=30;           // the size of the tabe
    cout<<"\n table init = "<<initTabe(tabe,size)<<endl;  // to fill the tabe with spaces
     cout<<"\n===============  First Accept input Case ==================\n";
     // 1. case for accepted input
     if (AcceptedInput_AnBnConfigureAndRun(size, tabe))
         cout<<"\n Input is Accepted "<<endl;
    else
        cout<<"\n Input is Rejected \n"<<endl;
  


    cout<<"\n=============== Now Rejected Case ==================\n";
    // 2. case for rejected input 
    initTabe(tabe,size);
    if (RejectedInput_AnBnConfigureAndRun(size,tabe))
        cout<<"\n Input is Accepted "<<endl;
    else
        cout<<"\n Input is Rejected \n"<<endl;


    
    return 0;
}
