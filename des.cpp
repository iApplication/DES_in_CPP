#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
void Decode();
void Encode();
void keyBuild(int *keychar);                                     //create key array
void keyCreate(int *midkey2,int movebit,int i);         //call by keyBuild
void F(int *rData,int *key);                                       //F function
void Expand(int *rData,int *rDataP);                        //Expand function
void ExchangeS(int *rDataP,int *rData);                   //S-diagram change
void ExchangeP(int *rData);                                    //P change
void FillBin(int *rData,int n,int s);                             // data to binary;call by S-Diagram change function
void InitialPermutation(int *plaintext_64bit);
void print_byte(char *text_16byte);
void Hex2Bit(char *text_byte,int *text_bit,int n);    //change into bit,n为bit的位数
void Bit2Hex(char *text_byte,int* text_bit,int n);    //change into hex,n为bit的位数
void RoundEncode(int n);
int IP1[]={58, 50, 42, 34, 26, 18, 10, 2,
           60, 52, 44, 36, 28, 20, 12, 4,    //initial change
           62, 54, 46, 38, 30, 22, 14, 6,
           64, 56, 48, 40, 32, 24, 16, 8,
           57, 49, 41, 33, 25, 17, 9,  1,
           59, 51, 43, 35, 27, 19, 11, 3,
           61, 53, 45, 37, 29, 21, 13, 5,
           63, 55, 47, 39, 31, 23, 15, 7,
 };
int IP2[]={40, 8, 48, 16, 56, 24, 64, 32,
           39, 7, 47, 15, 55, 23, 63, 31,    //opp initial change
           38, 6, 46, 14, 54, 22, 62, 30,
           37, 5, 45, 13, 53, 21, 61, 29,
           36, 4, 44, 12, 52, 20, 60, 28,
           35, 3, 43, 11, 51, 19, 59, 27,
           34, 2, 42, 10, 50, 18, 58, 26,
           33, 1, 41, 9, 49, 17, 57, 25
 };
int s[][4][16]={{                                                                              //S-diagram array
                 {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                 {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                 {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                 {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
                 },
                {
                 {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                 {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                 {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                 {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
                },
                {
                 {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                 {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                 {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                 {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
                },
                {
                 {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                 {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                 {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                 {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
                },
                {
                 {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                 {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                 {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                 {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
                },
                {
                 {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                 {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                 {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                 {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
                },
                {
                 {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                 {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                 {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                 {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
                },
                {
                 {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                 {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                 {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                 {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
                }
};
int Ex[48]={  32,1,2,3,4,5,                                                               //Expand array
              4,5,6,7,8,9,
              8,9,10,11,12,13,
              12,13,14,15,16,17,
              16,17,18,19,20,21,
              20,21,22,23,24,25,
              24,25,26,27,28,29,
              28,29,30,31,32,1
 };
int P[32]={16,7,20,21,29,12,28,17,                                                               //P-change
           1,15,23,26,5,18,31,10,
           2,8,24,14,32,27,3,9,
           19,13,30,6,22,11,4,25
 };
int PC1[56]={57,49,41,33,25,17,9,                                                //PC-1 in keyBuild
             1,58,50,42,34,26,18,
             10,2,59,51,43,35,27,
             19,11,3,60,52,44,36,
             63,55,47,39,31,23,15,/////
             7,62,54,46,38,30,22,
             14,6,61,53,45,37,29,
             21,13,5,28,20,12,4
 };
int PC2[48]={14,17,11,24,1,5,3,28,                                                     //PC-2 in keyBuild
             15,6,21,10,23,19,12,4,
             26,8,16,7,27,20,13,2,
             41,52,31,37,47,55,30,40,
             51,45,33,48,44,49,39,56,
             34,53,46,42,50,36,29,32
 };

int LSi[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int subkey_bit[16][48];
char subkey_byte[16][16];
char str[8];  //明文
char plaintext_16byte[16];
int plaintext_64bit[64];
char ciphertext_16byte[16];
int ciphertext_64bit[64];
char key_16byte[16];
int key_64bit[64];
int mode;  //来区分是加密还是解密
int main()                 //main function
{
    Encode();
    system("pause");
    Decode();
    system("pause");
    return 0;
}
void InitialPermutation(int *plaintext_64bit)
{
    int temptext[64];
    for(int i=0;i<64;i++)
        temptext[i]=plaintext_64bit[i];
    for(int i=0;i<64;i++)
        temptext[i]=plaintext_64bit[IP1[i]-1];
    for(int i=0;i<64;i++)
        ciphertext_64bit[i]=temptext[i];
    Bit2Hex(ciphertext_16byte,temptext,64);
    cout<<"初始置换后："<<endl;
    print_byte(ciphertext_16byte);
}

void print_byte(char *text_16byte)
{
    cout<<"    L[0]=";
    for(int i=0;i<16;i++)
    {
        cout<<text_16byte[i];
        if(i==7)
            cout<<"   R[0]=";
    }
    cout<<endl;
}

void Hex2Bit(char *text_byte,int *text_bit,int n)    //change into bit,n为bit的位数
{
    int length=n/4;
    int temptext[length];
    for(int i=0;i<length;i++)
    {
        if(text_byte[i]>='a'&&text_byte[i]<='f')
            temptext[i]=text_byte[i]-'a'+10;
        else if(text_byte[i]>='0'&&text_byte[i]<='9')
            temptext[i]=text_byte[i]-'0';
    }
    for(int i=0;i<length;i++)
    {
        for(int j=3;j>=0;j--)
        {
            text_bit[i*4+j]=temptext[i]%2;
            temptext[i]/=2;
        }
    }
}
void Bit2Hex(char *text_byte,int* text_bit,int n)    //change into hex,n为bit的位数
{
    int length=n/4;
    int temptext[length];
    for(int i=0;i<length;i++)
    {
        temptext[i]=text_bit[i*4+0]*8;
        temptext[i]+=text_bit[i*4+1]*4;
        temptext[i]+=text_bit[i*4+2]*2;
        temptext[i]+=text_bit[i*4+3]*1;
    }
    for(int i=0;i<length;i++)
    {
        if(temptext[i]>=0&&temptext[i]<=9)
            text_byte[i]=temptext[i]+'0';
        else if(temptext[i]>=10&&temptext[i]<=15)
            text_byte[i]=(temptext[i]-10)+'a';
    }
}

void keyBuild(int *keychar)   //create key array
{
    int i,j,k;
    int movebit[]={1,1,2,2,2,2,2,2,
                   1,2,2,2,2,2,2,1};
    int midkey2[56];
    int midkey[64];
	int key[56];
	for(k=0;k<56;k++)
	{
      midkey2[k]=keychar[PC1[k]-1];
	}
	printf("\n");
    for(i=0;i<16;i++)                   //密钥按照移位表循环左移,i代表轮数
	{

      keyCreate(midkey2,movebit[i],i);
	}
}
// midkey2是pc-1置换后的56bit密钥，movebit为左移的位数，n为第几轮
void keyCreate(int *midkey2,int movebit,int n)  //create key
{
    int i,temp[4];
    temp[0]=midkey2[0];
    temp[1]=midkey2[1];
    temp[2]=midkey2[28];
    temp[3]=midkey2[29];
   if(movebit==2)      //左移两位的算法
   {
       for(i=0;i<26;i++)
	   {
         midkey2[i]=midkey2[i+2];
         midkey2[i+28]=midkey2[i+30];
       }
       midkey2[26]=temp[0];
	   midkey2[27]=temp[1];
       midkey2[54]=temp[2];
	   midkey2[55]=temp[3];
   }
     else                     //左移一位的算法
     { for(i=0;i<27;i++)
	 {
        midkey2[i]=midkey2[i+1];
        midkey2[i+28]=midkey2[i+29];
       }
       midkey2[27]=temp[0];midkey2[55]=temp[2];
     }
	 //pc-2置换后变成48位
	 printf("第%d次pc-2置换子密钥结果(48bit): subkey[%d] = ",n+1,n+1);
    for(i=0;i<48;i++)
	{
      subkey_bit[n][i]=midkey2[PC2[i]-1];
	}
    Bit2Hex(subkey_byte[n],subkey_bit[n],48);
    cout<<subkey_byte[n];
    cout<<endl;
}


void RoundEncode(int n)  //第n轮加密
{
    int lData[32],rData[32];
    int rDataE[48];
    for(int i=0;i<32;i++)
        lData[i]=ciphertext_64bit[i];
    for(int i=0;i<32;i++)
        rData[i]=ciphertext_64bit[i+32];
    if(mode==1)
        cout<<"*******第"<<n+1<<"轮加密*******";
    else if(mode==2)
        cout<<"*******第"<<16-n<<"轮解密*******";
    Expand(rData,rDataE);
    for(int i=0;i<48;i++)     //取异或
        rDataE[i]=rDataE[i]^subkey_bit[n][i];
    ExchangeS(rDataE,rData);  //S盒变换
    ExchangeP(rData);         //P置换
    for(int i=0;i<32;i++)      //取异或
        rData[i]=rData[i]^lData[i];
    for(int i=0;i<32;i++)
        ciphertext_64bit[i]=ciphertext_64bit[i+32];
    for(int i=0;i<32;i++)
        ciphertext_64bit[i+32]=rData[i];
}
void F(int *rData,int *key)     //F function
{
    int i,rDataP[48];
    Expand(rData,rDataP);    //将明文右半部分进行E扩展，扩展成48位的A
    cout<<endl<<"E扩展后与48位密钥异或"<<endl;
    for(i=0;i<48;i++)
	{
      rDataP[i]=rDataP[i]^key[i];    //将进行完E扩展的A与key1异或
	  cout<<rDataP[i];
    }

    ExchangeS(rDataP,rData);  //S盒变换
    ExchangeP(rData);
}
void Expand(int *rData,int *rDataP) //E扩展  将明文右半部分进行E扩展，扩展成48位
{
    int i;
    char temp[12];
	cout<<endl<<"E扩展"<<endl<<"    二进制：";
    for(i=0;i<48;i++)
	{
      rDataP[i]=rData[Ex[i]-1];
	  cout<<rDataP[i];
	}
	cout<<endl<<"    十六进制：";
	Bit2Hex(temp,rDataP,48);
    for(int i=0;i<12;i++)
        cout<<temp[i];
}
void ExchangeS(int *rDataP,int *rData){          //S盒变换
    int i,n,linex,liney;
    linex=liney=0;
    for(i=0;i<48;i+=6)
	{
        n=i/6; //printf("%10d\n",(rDataP[i]<<1));
        linex=(rDataP[i]<<1)+rDataP[i+5];
        liney=(rDataP[i+1]<<3)+(rDataP[i+2]<<2)+(rDataP[i+3]<<1)+rDataP[i+4];

        FillBin(rData,n,s[n][linex][liney]);

    }
    cout<<endl<<"S-盒运算"<<endl;
    cout<<"    二进制:";
    for(i=0;i<32;i++)
    {
        printf("%d",rData[i]);
    }
    cout<<endl<<"    十六进制：";
    char temp[8];
    Bit2Hex(temp,rData,32);
    for(int i=0;i<8;i++)
        cout<<temp[i];
}
void FillBin(int *rData,int n,int s)   // data to binary;call by S-Diagram change function
{
    int temp[4],i;
    for(i=0;i<4;i++)
	{
        temp[i]=s%2;
        s=s/2;
     }
    for(i=0;i<4;i++)
	{
        rData[n*4+i]=temp[3-i];
	}
}
void ExchangeP(int *rData)
{                            //P change
    int i,temp[32];
    for(i=0;i<32;i++)
      temp[i]=rData[i];
    cout<<endl<<"p-置换"<<endl<<"    二进制：";
    for(i=0;i<32;i++)
	{
      rData[i]=temp[P[i]-1];
	  printf("%d",rData[i]);
	}
	cout<<endl<<"    十六进制：";
	char temp2[8];
	Bit2Hex(temp2,rData,32);
	for(int i=0;i<8;i++)
        cout<<temp2[i];

}
void Encode()
{
    mode=1;//表示加密
    cout<<"请输入16个要加密的字符："<<endl;
    for(int i=0;i<16;i++)
        cin>>plaintext_16byte[i];
    Hex2Bit(plaintext_16byte,plaintext_64bit,64);
    cout<<"输入明文的二进制为："<<endl;
    for(int i=0;i<64;i++)
        cout<<plaintext_64bit[i];
    cout<<endl;

    cout<<endl<<"请输入密钥(16个字符):"<<endl;
    for(int i=0;i<16;i++)
        cin>>key_16byte[i];
    Hex2Bit(key_16byte,key_64bit,64);
    cout<<"输入密钥二进制为："<<endl;
    for(int i=0;i<64;i++)
        cout<<key_64bit[i];
    cout<<endl;
    InitialPermutation(plaintext_64bit);

    Hex2Bit(key_16byte,key_64bit,64);
    keyBuild(key_64bit);

    for(int i=0;i<16;i++)
    {
        RoundEncode(i);
        cout<<endl;
        Bit2Hex(ciphertext_16byte,ciphertext_64bit,64);
        cout<<"轮输出"<<endl;
        int round=i+1;
        cout<<"    L["<<round<<"]=";
        for(int i=0;i<16;i++)
        {
            if(i==8)
                cout<<"    R["<<round<<"]=";
            cout<<ciphertext_16byte[i];
        }
        cout<<endl;
    }
    int temp[64];   //逆初始置换
    for(int i=0;i<64;i++)
        temp[i]=ciphertext_64bit[i];
    for(int i=0;i<32;i++)
        ciphertext_64bit[i]=temp[i+32];
    for(int i=0;i<32;i++)
        ciphertext_64bit[i+32]=temp[i];

    for(int i=0;i<64;i++)
        temp[i]=ciphertext_64bit[i];
    for(int i=0;i<64;i++)
        ciphertext_64bit[i]=temp[ IP2[i]-1  ];
    Bit2Hex(ciphertext_16byte,ciphertext_64bit,64);

    cout<<"加密后密文为："<<ciphertext_16byte;
}
void Decode()
{
    mode=2;//表示解密
    cout<<endl<<"请输入解密密钥(16个字符):"<<endl;
    for(int i=0;i<16;i++)
        cin>>key_16byte[i];
    Hex2Bit(key_16byte,key_64bit,64);
    cout<<"输入密钥二进制为："<<endl;
    for(int i=0;i<64;i++)
        cout<<key_64bit[i];
    cout<<endl;
    InitialPermutation(ciphertext_64bit);
    for(int i=15;i>=0;i--)
    {
        RoundEncode(i);
        cout<<endl;
        Bit2Hex(ciphertext_16byte,ciphertext_64bit,64);
        cout<<"轮输出"<<endl;
        int round=16-i;
        cout<<"    L["<<round<<"]=";
        for(int i=0;i<16;i++)
        {
            if(i==8)
                cout<<"    R["<<round<<"]=";
            cout<<ciphertext_16byte[i];
        }
        cout<<endl;
    }

    int temp[64];   //逆置换
    for(int i=0;i<64;i++)
        temp[i]=ciphertext_64bit[i];
    for(int i=0;i<32;i++)
        ciphertext_64bit[i]=temp[i+32];
    for(int i=0;i<32;i++)
        ciphertext_64bit[i+32]=temp[i];

    for(int i=0;i<64;i++)
        temp[i]=ciphertext_64bit[i];
    for(int i=0;i<64;i++)
        ciphertext_64bit[i]=temp[ IP2[i]-1  ];
    Bit2Hex(ciphertext_16byte,ciphertext_64bit,64);

    cout<<"解密后明文为："<<ciphertext_16byte;
}
