#include "AString.h"

AString::AString(int sz)    //�����캯��
{
    maxSize = sz;
    ch = new char[maxSize+1];
    if (ch == NULL) {cerr << "Allocation Error\n";exit(1);}
    curLength = 0; ch[0] = '\0';
}

AString::AString(const char *init)  //�����캯��
{
    int len = strlen(init);
    maxSize = (len>defaultSize)?len:defaultSize;
    ch = new char[maxSize+1];
    if (ch == NULL) { cerr << "Allocation Error\n"; exit(1);}
    curLength = len;
    strcpy(ch,init);
}

AString::AString(const AString& ob){    //�����ƹ��캯��
    maxSize = ob.maxSize;
    ch = new char[maxSize+1];
    if (ch == NULL) {cerr << "�洢����ʧ��\n"; exit(1);}
    curLength = ob.curLength;
    strcpy(ch,ob.ch);
}

AString AString::operator() (int pos, int len){ //���Ӵ�
    AString temp;
    if (pos < 0 || pos+len-1>=maxSize || len<0){
        temp.curLength = 0; temp.ch[0] = '\0';
    }
    else{
        if (pos+len-1 >= curLength) len = curLength-pos;
        temp.curLength = len;
        for (int i = 0, j = pos; i < len; i++,j++) temp.ch[i] = ch[j];
        temp.ch[len] = '\0';
    }
    return temp;
}

AString& AString::operator=(const AString& ob){     //�����ز���������ֵ
    if (&ob != this){
        delete[]ch;
        ch = new char[ob.maxSize];                  //���·���
        if (ch == NULL) {cerr << "�洢����ʧ��!\n"; exit(1);}
        curLength = ob.curLength;
        strcpy(ch,ob.ch);
    }
    else cout << "�ַ�������ֵ����\n";
    return *this;
}

AString& AString::operator+=(const AString& ob){    //�����ز�����������
    char *temp = ch;                //�ݴ�ԭ������
    int n = curLength + ob.curLength;   //����������
    int m = (maxSize >= n)? maxSize:n;  
    ch = new char[m];
    if (ch == NULL) {cerr << "�洢�����\n"; exit(1);}
    maxSize = m; curLength = n;
    strcpy(ch,temp);                    //����ԭ������
    strcat(ch,ob.ch);                   //����ob������
    delete []temp; return *this;
}

AString& AString::operator+= (const AString& ob){   //�����ز�����������
    char *temp = ch;                    //�ݴ�ԭ������
    int n = curLength+ob.curLength;     //����������
    int m = (maxSize >= n)?maxSize:n;
    ch = new char[m];
    if (ch == NULL) {cerr << "�洢�����\n"; exit(1);}
    maxSize = m;    curLength = n;
    strcpy(ch,temp);                    //����ԭ������
    strcat(ch,ob.ch);                   //����ob������
    delete []temp;  return *this;
}

char AString::operator[] (int i){       //�����ز�����ȡ��ǰ��*this�ĵ�i���ַ�
    if (i < 0 || i >= curLength)
    { cout << "�ַ����±곬�磡\n"; exit(1);}
    return ch[i];
}

int AString::Find(AString& pat, int k)const{
    //�ڵ�ǰ����Ŀ��*this���дӵ�k���ַ���ʼѰ��ģʽpat�ڵ�ǰ����ƥ���λ�á�����
    //��ǰ����*this�����Ҳ����봮patƥ����Ӵ�����������-1�����򷵻�pat�ڵ�ǰ
    //����*this���е�һ��ƥ���λ��
    int i,j;
    for (i = k; i <= curLength - pat.curLength; i++) {  //���˱Ƚ�
        for (j = 0; j < pat.curLength; j++)
            //��ch[i]��ʼ���Ӵ���ģʽpat.ch���бȽ�
            if (ch[i+j]!=pat.ch[j]) break;
            if (j == pat.curLength) return i;           //patɨ���꣬ƥ��ɹ�
    }
    return -1;                              //patΪ�ջ�*this���Ҳ�����
}