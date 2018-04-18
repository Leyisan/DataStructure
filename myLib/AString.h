#ifndef _ASTRING_H_
#define _ASTRING_H_
#define defaultSize = 128;

class AString
{
public:
    AString(int sz = defaultSize);          //���캯��������һ����󳤶�Ϊsz��ʵ�ʳ���Ϊ0���ַ���
    AString(const char* init);              //���캯��������һ����󳤶�ΪmaxSize,��init��ʼ�������ַ�������
    AString(const AString& ob);             //���ƹ��캯������һ�����е��ַ�������ob����һ�����ַ���
    ~AString() {delete []ch;}               //�����������ͷŶ�̬����Ĵ��ռ䲢�������ַ�������
    int Length()const {return curLength;}   //�������ش�*this��ʵ�ʳ���
    AString& operator() {int pos, int len}; 
    //��0 <= pos < maxSize �� 0 <= len �� pos+len < maxSizeʱ�����ڴ�*this�д�pos��ָ��
    //λ�ÿ�ʼ����ȡlen���ַ�����Ӵ�����
    int operator == (AString& ob)const {return strcmp(ch,ob.ch) == 0;}
    //���Ƿ���ȡ�����*this��ob��ȣ���������1������������0��
    int operator != (AString& ob)const {return strcmp(ch,ob.ch) != 0;}
    //���Ƿ񴮲��ȡ�����*this��ob���ȣ��򷵻�1.
    int operator !() const {return curLength == 0;}
    //���Ƿ񴮿ա�����Ϊ�գ��򷵻�1�����򷵻�0
    AString& operator = (AString& ob);      //��ob��ֵ����ǰ��*this
    AString& operator+= (AString& ob);      //��length(*this) + length(ob) < maxSize,��Ѵ�ob����*this���档
    char& operator [](int i);               //ȡ*this�ĵ�i���ַ�
    int Find(AString& pat)const;    
    //����pat�봮*this�е�ĳ���Ӵ�ƥ�䣬�������ص�1��ƥ��ʱ�Ӵ��ڴ�*this��
    //��λ�á�����patΪ�ջ��ڴ�*this��û��ƥ���Ӵ�����������-1��
    int Find(AString& pat, int k)const;

private:
    char *ch;           //���������
    int curLength;      //����ʵ�ʳ���
    int maxSize;        //����������󳤶�
};


#endif