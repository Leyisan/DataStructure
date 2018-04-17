#include <assert.h>
#include <iostream.h>
#include <stdlib.h>
const int DefaultPQSize = 50;           //���ȼ����������Ĭ�ϳ���

template <class T>
class PQueue
{
    public:
        PQueue(int sz = DefaultPQSize);         //���캯��
        ~PQueue() {delete []pqelements;}        //��������
        bool Insert(const T& x);                //����Ԫ��x���뵽��β
        bool RemoveMin(T& x);                   //������Ԫ��ɾȥ
        bool getFront(T& x)const;               //��ȡ����Ԫ�أ���С����Ȩ����ֵ
        void makeEmpty() {count = 0;}           //�����ȼ�����Ϊ��
        bool IsEmpty()const{                    //�ж��пշ�
            return (count == 0)?true:false;}
        bool IsFull()const                      //�ж�������
        {return (count == maxSize)?true:false;} 
        int getSize()const {return count;}      //�����ȼ�������Ԫ�ظ���
    private:
        T* pqelements;                          //���ȼ���������
        int count;                              //��ǰԪ�ظ��������ȣ�
        int maxSize;                            //������������Ԫ�ظ���
        void adjust();
};

template <class T>
PQueue<T>::PQueue(int sz): maxSize(sz), count(0){
//���캯��������һ��������maxSize��Ԫ�صĿ����ȼ����С�
    pqelements = new T[maxSize];                //�������пռ�
    assert(pqelements != NULL);                 //���ԣ���̬�洢����ɹ����
}

template <class T>
bool PQueue<T>::Insert(const T& x){
//�����ȼ����в�������Ԫ��x���뵽�ö��ж�β�����������
    if (count == maxSize) return false;         //��������������
    pqelements[count++] = x;                    //����x����β
    adjust();                                   //������Ȩ���е���
    return true;
}

template <class T>
void PQueue<T>::adjust(){
//����βԪ�ذ�������Ȩ��С�������ʵ�λ�ã���������Ԫ�ذ�����Ȩ��С��������
    T temp = pqelements[count-1];
    int left = -1,right = count;                //�γɰ�Χ�������Ŀռ䣬���衾-1����count���Ǵ�����С����ֵ��λ��
  /*
    int j;  
    for (j = count-2; j >= 0; j--)
        if (pqelements[j] <= temp) break;       //�����б�temp��С����ȵ�pqelements[j] ����ѭ��
        else pqelements[j+1] = pqelements[j];   //��temp���Ԫ�� pqelements[j] ����
    pqelements[j+1] = temp;                     //���뵽�ʵ�λ��
*/
    
    for(int mid = (left + right)/2; (right-left)>1;)    //����λ��count-1֮ǰ�������Ѿ����򣬶��ֲ��Һ�������λ��
    {
        if (pqelements[mid] < temp)                      //��ֵС�ڲ���ֵ������������С����ֵ
            left = mid;
        else right = mid;                               //������С������
        mid = (left + right)/2;
    }
    for(int i = count-1; i > left+1;i--)                //��������left+1 ~ count-2��ֵ������һ��
        pqelements[i] = pqelements[i-1];
    pqelements[left+1] = temp;                          //������ֵ����left+1
    
}

template <class T>
bool PQueue<T>::RemoveMin(T& x){
//�����ȼ����в����������ظö��о����������Ȩ��ֵ��С��Ԫ�ص�ֵ��ͬʱ����Ԫ��ɾ����
    if(count == 0) return false;                //�����пգ���������false
    x = pqelements[0];
    for(int i = 1; i < count; i++) pqelements[i-1] = pqelements[i];
    count--;                                    //���ȼ�����Ԫ�ظ�����һ
    return true;                                //ɾ���ɹ�������true
}

