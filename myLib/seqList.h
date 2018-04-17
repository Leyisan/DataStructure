#include <iostream.h>
#include <stdlib.h>

const int defaultSize = 100;
template <class T>
class SeqList
{
    protected:
        T *data;        //�������
        int maxSize;    //�������ɱ��������
        int last;       //��ǰ�Ѵ��������λ�ã���0��ʼ��
        void reSize(int newSize);   //�ı�data����ռ�Ĵ�С
    public:
        SeqList(int sz = defaultSize);      //���캯��
        SeqList(SeqList<T>& L);             //���ƹ��캯��
        ~SeqList(){delete[] data;}          //��������
        int Size()const{return maxSize;}    //������������ɱ������
        int Length()const{return last + 1;} //�������
        int Search(T& x)const;              //���� x �ڱ���λ�ã��������ر������
        int Locate(int i)const;             //��λ�� i ������������ر������
        bool getData(int i, T& x)const      //ȡ��i�������ֵ
        { if(i > 0 && i <= last+1)  {x = data[i-1]; return true;}   else return false;}
        void setData(int i, T& x)           //�� x �޸ĵ� i �������ֵ
        { if(i > 0 && i <= last+1)  data[i-1] = x;}
        bool Insert(int i, T& x);           //����x �ڵ�i������֮��
        bool Remove(int i,T& x);            //ɾ����i�����ͨ��x���ر����ֵ
        bool IsEmpty(){return (last == -1)?true:false;}
                                            //�жϱ�շ񣬿��򷵻�true;
        bool IsFull(){return (last == maxSize-1)?true:false;}
                                            //�жϱ��������򷵻�true;
        void input();                       //����
        void output();                      //���
        SeqList<T> operator=(SeqList<T>& L);    //�����帳ֵ

};

template <class T>
SeqList<T>::SeqList(int sz)             //���캯����ͨ��ָ������sz��������ĳ���
{
    if (sz > 0)
    {
        maxSize = sz; last = -1;            //�ñ��ʵ�ʳ���Ϊ��
        data = new T[maxSize];              //����˳���洢����
        if (data == NULL)                   //��̬����ʧ��
        { cerr << "�洢����ʧ�ܣ�" << endl; exit(1);}
    }
}

template <class T>
SeqList<T>::SeqList(SeqList<T>& L)          //���ƹ��캯�����ò������и���������˳����ʼ���½���˳���
{
    maxSize = L.Size(); last = L.Length()-1; T value;
    data = new T[maxSize];                  //����˳���洢����
    if (data == NULL)                       //��̬����ʧ��
    { cerr << "�洢�������" << endl; exit(1);}
    for (int i = 1; i <= last+1; i++)
    {L.getData(i,value); data[i-1] = value;}
}

template <class T>
void SeqList<T>::reSize(int newSize)    //˽�к���������˳���Ĵ洢����ռ��С���������Ԫ�ظ���Ϊ newSize��
{
    if (newSize <= 0)
    { cerr << "��Ч�������С" << endl; return;}
    if (newSize != maxSize)             //����������
    {
        T* newarray = new T[newSize];
        if (newarray == NULL)
        { cerr << "�洢�������"<< endl; exit(1);}
        int n = last+1;                
        T *srcptr = data;               //Դ�����׵�ַ
        T *destptr = newarray;          //Ŀ�������׵�ַ
        while(n--) *destptr++ = *destptr++;     //����
        delete []data;
        data = newarray; maxSize = newSize;
    }
}

template <class T>
int SeqList<T>::Search(T &x)const       //�����������ڱ���˳�����������ֵ x ��ƥ��ı���ҵ��򷵻ظñ����ǵڼ���Ԫ�ء�
{
    for (int i = 0; i <= last; i++)     //˳������
        if (data[i] == x) return i+1;   //�����ɹ�
    return 0;
}

template <class T>
int SeqList<T>::Locate(int i)const      //��λ���������ص�i�������λ�ã�����������0����ʾ��λʧ��
{
    if (i >= 1&& i <= last+1) return i;
    else return 0;
}

template <class T>
bool SeqList<T>::Insert(int i, T& x)     
//����Ԫ��x���뵽���е�i��0<=i<=last+1��������֮�󡣺������ز���ɹ�����Ϣ��������ɹ��򷵻�true��i = 0������ģ�ʵ�����ǲ��뵽��һ��Ԫ��λ��
{
    if (last == maxSize-1) return false;        //���������ܲ���
    if (i <0 || i > last+1) return false;       //����i���������ܲ���
    for (int j = last; j >= i; j--)
        data[j+1] = data[j];                    //���κ��ƣ��ճ���i��λ��
    data[i] = x;                                //����
    last++;
    return true;
}

template <class T>
bool SeqList<T>::Remove(int i, T& x)
//�ӱ���ɾ����i(1<=i<=last+1)�����ͨ�������Ͳ���x����ɾ����Ԫ��ֵ����������ɾ��
//�ɹ�����Ϣ����ɾ���ɹ��򷵻�true�����򷵻�false
{
    if (last == -1) return false;               //��գ�����ɾ��
    if (i < 1 || i > last+1) return false;      //����i����������ɾ��
    x = data[i-1];                              //���汻ɾ����ֵ
    for (int j = i; j <= last; j++)
        data[j-1] = data[j];                    //����ǰ�ƣ��
    last--;                                     //���λ�ü�1
    return true;                                //ɾ���ɹ�    
}

template <class T>
void SeqList<T>::input()            //�ӱ�׼��������������룬����˳���
{
    while(1){
        cout << "��ʼ����˳������������Ԫ�ظ�����";
        cin >> last;
        if (last <= maxSize-1) break;
        cout << "��Ԫ�ظ����������󣬷�Χ���ܳ���" << maxSize - 1 << endl;
    }
    for (int i = 0; i < last; i++)
    { cout <<"#"<< i+1 <<":"; cin >> data[i];}
}

template <class T>
void SeqList<T>::output()
{
    cout << "˳���ǰԪ�ص����λ��Ϊ��" << last << endl;
    for (int i = 0; i < last; i++)
        cout << "#" << i+1 << ":" << data[i] << endl;
}