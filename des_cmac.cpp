#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<iostream>
using namespace std;
void keyBuild(int *keychar);                                     //create key array
void keyCreate(int *midkey2,int movebit,int i);         //call by keyBuild
void F(int *rData,int *key);                                       //F function
void Expand(int *rData,int *rDataP);                        //Expand function
void ExchangeS(int *rDataP,int *rData);                   //S-diagram change
void ExchangeP(int *rData);                                    //P change
void FillBin(int *rData,int n,int s);                             // data to binary;call by S-Diagram change function
void InitialPermutation(int *plaintext_64bit);
void Hex2Bit(char *text_byte,int *text_bit,int n);    //change into bit,nΪbit��λ��
void Bit2Hex(char *text_byte,int* text_bit,int n);    //change into hex,nΪbit��λ��
void RoundEncode(int n);
void cmac();
void Encode_cmac();
void k1_k2_create();
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
int PC1[56]={57,49,41,33,25,17,9,                                       //PC-1 in keyBuild
             1,58,50,42,34,26,18,
             10,2,59,51,43,35,27,
             19,11,3,60,52,44,36,
             63,55,47,39,31,23,15,
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
char plaintext_16byte[16];
int plaintext_64bit[64];
char ciphertext_16byte[16];
int ciphertext_64bit[64];
char key_16byte[16];
int key_64bit[64];
int mode;  //�������Ǽ��ܻ��ǽ���
string plaintext_cmac;
int k1[64];
char k1_byte[16];
int k1_temp[65];
int k2[64];
char k2_byte[16];
int k2_temp[66];
int main()                 //main function
{
    cmac();
    system("pause");
    return 0;
}
void cmac()
{
    cout<<"��������Կ(16���ַ�):"<<endl;
    for(int i=0;i<16;i++)
        cin>>key_16byte[i];
    Hex2Bit(key_16byte,key_64bit,64);

    k1_k2_create();

    cout<<"����������(���Դ���16���ַ�)��"<<endl;
    cin>>plaintext_cmac;
    int length=plaintext_cmac.size();
    cout<<"�����ַ��ĳ���Ϊ��"<<length<<endl;
    for(int i=0;i<64;i++)
        //ciphertext_64bit��ʼ����Ϊ0���Ա��һ�����ciphertext_64bit��ʱ��û��ȡ������
        ciphertext_64bit[i]=0;
    if(length%16==0)//���������ַ��������������������ķ��鳤�ȣ������´���
    {
        int i;
        for(i=0;i<length/16-1;i++)    //ע������Ҫ-1
        {
            for(int j=0;j<16;j++)
                plaintext_16byte[j]=plaintext_cmac[j+i*16];
            Hex2Bit(plaintext_16byte,plaintext_64bit,64);
            for(int j=0;j<64;j++)
                plaintext_64bit[j]=plaintext_64bit[j]^ciphertext_64bit[j];
            Encode_cmac();
            cout<<"��"<<i+1<<"����ܺ�����Ϊ��"<<ciphertext_16byte<<endl;
        }
        for(int j=0;j<16;j++)
            plaintext_16byte[j]=plaintext_cmac[j+i*16];
        Hex2Bit(plaintext_16byte,plaintext_64bit,64);
        for(int j=0;j<64;j++)
            plaintext_64bit[j]=plaintext_64bit[j]^ciphertext_64bit[j];


        for(int j=0;j<64;j++)
            plaintext_64bit[j]=plaintext_64bit[j]^k1[j];//�൱����K1����ˣ�����

        Encode_cmac();
        cout<<"��"<<i+1<<"����ܺ�����Ϊ��"<<ciphertext_16byte<<endl;
    }
    else if(length%16!=0)//���������ַ������Ȳ����������ķ��鳤�ȣ������´���
    {
        int i;
        for(i=0;i<length/16;i++)   //ע�����ﲻ-1�����һ�������ͬ��
        {
            for(int j=0;j<16;j++)
                plaintext_16byte[j]=plaintext_cmac[j+i*16];
            Hex2Bit(plaintext_16byte,plaintext_64bit,64);
            for(int j=0;j<64;j++)
                plaintext_64bit[j]=plaintext_64bit[j]^ciphertext_64bit[j];
            Encode_cmac();
            cout<<"��"<<i+1<<"����ܺ�����Ϊ��"<<ciphertext_16byte<<endl;
        }

        //���漸�����һ�������Ҫ��ͬ�ĵط�����������100...000�����
        for(int j=0;j<length%16;j++)
            plaintext_16byte[j]=plaintext_cmac[j+i*16];
        plaintext_16byte[length%16]='8';//��8=1000
        for(int j=length%16+1;j<16;j++)
            plaintext_16byte[j]='0';

        Hex2Bit(plaintext_16byte,plaintext_64bit,64);
        for(int j=0;j<64;j++)
            plaintext_64bit[j]=plaintext_64bit[j]^ciphertext_64bit[j];

        for(int j=0;j<64;j++)
            plaintext_64bit[j]=plaintext_64bit[j]^k2[j];;//�൱����K2����ˣ�����

        Encode_cmac();
        cout<<"��"<<i+1<<"����ܺ�����Ϊ��"<<ciphertext_16byte<<endl;
    }
}
void Encode_cmac()
{
    InitialPermutation(plaintext_64bit);

    Hex2Bit(key_16byte,key_64bit,64);
    keyBuild(key_64bit);

    for(int i=0;i<16;i++)
    {
        RoundEncode(i);
        Bit2Hex(ciphertext_16byte,ciphertext_64bit,64);
    }
    int temp[64];   //���ʼ�û�
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
}
void k1_k2_create()   //���ڲ���k1��k2
{
    for(int i=0;i<64;i++)
        plaintext_64bit[i]=0;
    Encode_cmac();//��E(K,0^n)����
    cout<<"L=E(K,0^n)="<<ciphertext_16byte<<endl;
    Hex2Bit(ciphertext_16byte,ciphertext_64bit,64);
    cout<<"L=E(K,0^n)������Ϊ��";
    for(int i=0;i<64;i++)
        cout<<ciphertext_64bit[i];
    cout<<endl;

    for(int i=0;i<64;i++)//��k1��k2����ֵ��ΪL��ֵ
    {
        k1[i]=ciphertext_64bit[i];
        k2[i]=ciphertext_64bit[i];
    }

    for(int i=0;i<64;i++)
        k1_temp[i]=k1[i];
    k1_temp[64]=0;//k1_tempΪk1����x���ֵ��
    //if(k1_temp[0]==0)
    //����Ҫ����������ȡx^64+x^4+x^3+1 ȡ�࣬�����λ��x^64Ϊ0��ʱ��k1���䣬���Բ��ô���
    if(k1_temp[0]==1)
    {//ȡx^64+x^4+x^3+1 ȡ��
        k1_temp[0]=k1_temp[0]^1;
        k1_temp[60]=k1_temp[60]^1;
        k1_temp[61]=k1_temp[61]^1;
        k1_temp[63]=k1_temp[63]^1;
        k1_temp[64]=k1_temp[64]^1;
    }
    for(int i=0;i<64;i++)
        k1[i]=k1_temp[i+1];//��ʱk1=L*x
    Bit2Hex(k1_byte,k1,64);
    cout<<"K1="<<k1_byte<<endl;

    for(int i=0;i<64;i++)
        k2_temp[i]=k2[i];
    k2_temp[64]=0;
    k2_temp[65]=0;//k2_tempΪk2����x^2���ֵ��
    if(k2_temp[0]==1)
    {
        k2_temp[0]=k2_temp[0]^1;
        k2_temp[60]=k2_temp[60]^1;
        k2_temp[61]=k2_temp[61]^1;
        k2_temp[63]=k2_temp[63]^1;
        k2_temp[64]=k2_temp[64]^1;
    }
    if(k2_temp[1]==1)
    {
        k2_temp[1]=k2_temp[1]^1;
        k2_temp[61]=k2_temp[61]^1;
        k2_temp[62]=k2_temp[62]^1;
        k2_temp[64]=k2_temp[64]^1;
        k2_temp[65]=k2_temp[65]^1;
    }
    for(int i=0;i<64;i++)
        k2[i]=k2_temp[i+2];//��ʱk2=L*x^2
    Bit2Hex(k2_byte,k2,64);
    cout<<"K2="<<k2_byte<<endl;

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
}
void Hex2Bit(char *text_byte,int *text_bit,int n)    //change into bit,nΪbit��λ��
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
void Bit2Hex(char *text_byte,int* text_bit,int n)    //change into hex,nΪbit��λ��
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
    for(i=0;i<16;i++)                   //��Կ������λ��ѭ������,i��������
	{

      keyCreate(midkey2,movebit[i],i);
	}
}
// midkey2��pc-1�û����56bit��Կ��movebitΪ���Ƶ�λ����nΪ�ڼ���
void keyCreate(int *midkey2,int movebit,int n)  //create key
{
    int i,temp[4];
    temp[0]=midkey2[0];
    temp[1]=midkey2[1];
    temp[2]=midkey2[28];
    temp[3]=midkey2[29];
   if(movebit==2)      //������λ���㷨
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
     else                     //����һλ���㷨
     { for(i=0;i<27;i++)
	 {
        midkey2[i]=midkey2[i+1];
        midkey2[i+28]=midkey2[i+29];
       }
       midkey2[27]=temp[0];midkey2[55]=temp[2];
     }
	 //pc-2�û�����48λ
    for(i=0;i<48;i++)
	{
      subkey_bit[n][i]=midkey2[PC2[i]-1];
	}
    Bit2Hex(subkey_byte[n],subkey_bit[n],48);
}


void RoundEncode(int n)  //��n�ּ���
{
    int lData[32],rData[32];
    int rDataE[48];
    for(int i=0;i<32;i++)
        lData[i]=ciphertext_64bit[i];
    for(int i=0;i<32;i++)
        rData[i]=ciphertext_64bit[i+32];
    Expand(rData,rDataE);
    for(int i=0;i<48;i++)     //ȡ���
        rDataE[i]=rDataE[i]^subkey_bit[n][i];
    ExchangeS(rDataE,rData);  //S�б任
    ExchangeP(rData);         //P�û�
    for(int i=0;i<32;i++)      //ȡ���
        rData[i]=rData[i]^lData[i];
    for(int i=0;i<32;i++)
        ciphertext_64bit[i]=ciphertext_64bit[i+32];
    for(int i=0;i<32;i++)
        ciphertext_64bit[i+32]=rData[i];
}
void F(int *rData,int *key)     //F function
{
    int i,rDataP[48];
    Expand(rData,rDataP);    //�������Ұ벿�ֽ���E��չ����չ��48λ��A
    for(i=0;i<48;i++)
	{
      rDataP[i]=rDataP[i]^key[i];    //��������E��չ��A��key1���
    }
    ExchangeS(rDataP,rData);  //S�б任
    ExchangeP(rData);
}
void Expand(int *rData,int *rDataP) //E��չ  �������Ұ벿�ֽ���E��չ����չ��48λ
{
    int i;
    char temp[12];
    for(i=0;i<48;i++)
	{
      rDataP[i]=rData[Ex[i]-1];
	}
	Bit2Hex(temp,rDataP,48);
}
void ExchangeS(int *rDataP,int *rData){          //S�б任
    int i,n,linex,liney;
    linex=liney=0;
    for(i=0;i<48;i+=6)
	{
        n=i/6; //printf("%10d\n",(rDataP[i]<<1));
        linex=(rDataP[i]<<1)+rDataP[i+5];
        liney=(rDataP[i+1]<<3)+(rDataP[i+2]<<2)+(rDataP[i+3]<<1)+rDataP[i+4];
        FillBin(rData,n,s[n][linex][liney]);

    }
    char temp[8];
    Bit2Hex(temp,rData,32);
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
    for(i=0;i<32;i++)
      rData[i]=temp[P[i]-1];
	char temp2[8];
	Bit2Hex(temp2,rData,32);
}
