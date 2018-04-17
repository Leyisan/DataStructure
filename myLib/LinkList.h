#ifndef _LINKEDLIST_h_
#define _LINKEDLIST_H_

#include<iostream.h>

template <class T>      //List���ǰ������
class List;



template <class T>
class LinkNode
{
    typedef LinkNode<T>* nPTR;

public:
    friend class List<T>;
    LinkNode(nPTR node = NULL):link(node){ };
    LinkNode(T dat,nPTR node = NULL):data(dat),link(node){ };

private:
    T data;
    nPTR link;
};

template <class T>
class List
{
    typedef LinkNode<T> node;
    typedef LinkNode<T>* nPTR;

public:
    List(){first = new node;};
    List(const T&x){first = new node(x);}
    List(List<T>& L);
    ~List(){makeEmpty();}               //��������
    void makeEmpty();                   //��������Ϊ�ձ�
    int Length()const;                  //��������ĳ���
    nPTR getHead()const{return first;}  //���ظ���ͷ����ַ
    nPTR Search(T x);                   //����������x��Ԫ��
    nPTR Locate(int i);                 //������i��Ԫ�صĵ�ַ
    bool getData(int i,T& x)const;      //ȡ����i��Ԫ�ص�ֵ
    void setData(int i,T x);           //��x�޸ĵ�i��Ԫ�ص�ֵ
    bool Insert(int i,T x);         //�������
    bool Remove(int i,T& x);            //ɾ��������ͨ��x����
    bool IsEmpty()const                 //�б�շ񣿿��򷵻�true
    { return first->link == NULL?true:false;}
    bool IsFull()const {return false;}  //�б����񣿲����򷵻�false
    void Sort();                        //����
    void input();                       //����
    void output();                      //���
    List<T>& operator=(List<T>& L);     //���غ�������ֵ

private:
    nPTR first;
};

template <class T>
List<T>::List(List<T>& L)               
//���ƹ��캯��
{
    T value;
    nPTR srcptr = L.getHead();          //�����Ƶı�ĸ���ͷ����ַ
    nPTR destptr = first = new node;    
    while (scrptr->link != NULL)        //�����㸴��
    {
        value = srcptr->link->data;
        destptr->link = new node(value);    
        destptr = destptr->link;
        srcptr = srcptr->link;
        destptr->link = NULL;
    }
}

template <class T>
void List<T>::makeEmpty()            
//��������Ϊ�ձ�
{
    nPTR q;
    while(first->link != NULL)          //��������ʱ��ɾȥ�������н��
    {
        q = first->link;
        first->link = q->link;          //���汻ɾ��㣬������ժ�¸ý��
        delete q;
    }
}

template <class T>
int List<T>::Length()const          
//���������ͷ���ĵ�����ĳ���
{
    nPTR = first->link; int count = 0;
    while (p != NULL)
    {
        p = p->link; count++;
    }
    return count;
}

template <class T>            
LinkNode<T>* List<T>::Search(T x)      
//�ڱ�������������x�Ľ�㡣�����ɹ�ʱ���������ظý���ַ��
{
    LinkNode<T>* current = first->link;
    while(current != NULL)
        if (current->data == x) break;      //ѭ���Һ�x�Ľ��
        else current = current->link;
    return current;
}

template <class T>
LinkNode<T>* List<T>::Locate(int i)
//��λ���������ر��е�i��Ԫ�صĵ�ַ
{
    if (i<0) return NULL;           //����������
    LinkNode<T>* current = first; int k = 0;    
    while (current != NULL && k < i)        //ѭ���ҵ�i�����
    {
        current = current->link; k++;
    }
    return current;                         //���ص�i������ַ��������NULL����ʾiֵ̫��
}

template <class T>
bool List<T>::getData(int i,T& x)const
//ȡ�������е�i��Ԫ�ص�ֵ
{
    if (i<=0) return NULL;                  //i̫С
    nPTR current = Locate(i);
    if (current == NULL) return false;      //i̫��
    else {x = current->data; return false;}
}

template <class T>
void List<T>::setData(int i,T x)
//�������е�i��Ԫ�ظ�ֵx
{
    if(i<=0) return NULL;
    nPTR current = Locate(i);
    if (current == NULL) return;
    else current->data = x;
}

template <class T>
bool List<T>::Insert(int i,T x)
//����Ԫ��x�����������е�i�����֮��
{
    nPTR current = Locate(i);
    if (current == NULL) return false;
    nPTR newNode = new node(x);
    if (newNode == NULL) {cerr << "�洢�������"<<endl; exit(1);}
    newNode->link = current->link;          //������current֮��
    current->link = newNode;
    return true;                            //����ɹ�
}

template <class T>
bool List<T>::Remove(int i,T& x)
//�������еĵ�i��Ԫ��ɾȥ��ͨ�������Ͳ���x���ظ�Ԫ�ص�ֵ
{
    nPTR current = Locate(i-1);
    if (current == NULL || current->link == NULL) return false;         //ɾ�����ɹ�
    nPTR del = current->link;           //��������������ɾ��������ժ��
    current->link = del->link;
    x = del->data; delete del;          //ȡ����ɾ����е�����ֵ
    return true;
}

template <class T>
void List<T>::input()
//����������뺯��
{
    int n;
    T x;
    nPTR ptr = first;
    cout << "����������Ԫ�ظ�����";
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cout << "#"<<i<<":";
        cin >> x;
        while(ptr->link != NULL)
        {
            ptr = ptr->link;
        }
        ptr->link = new node(x);
    }
}

template <class T>
void List<T>::output()
//���������������������������������ݰ��߼�˳���������Ļ��
{
    nPTR current = first->link;
    while (current != NULL)
    {
        cout<<current->data<<endl;
        current = current->link;
    }
}

template <class T>
List<T>& List<T>::operator =(List<T>& L)
//���غ�������ֵ��������ʽ��A=B������A�ǵ��ô˲�����List����B����������е�
//�����Ͳ���L��ϵĲ���
{
    T value;
    nPTR srcptr = L.getHead();          //�����Ʊ�ĸ���ͷ����ַ
    nPTR destptr = first = new node;
    while (srcptr->link != NULL)        //�����㸴��
    {
        value = srcptr->link->data;
        destptr->link = new node(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
    return *this;
}

#endif