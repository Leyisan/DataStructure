#ifndef _LINEARLIST_H_
#define _LINEARLIST_H_

enum bool {false, true};
template <class T>
class LinearList
{
    public:
        LinearList();               //���캯��
        ~LinearList();              //��������
        virtual int Size()const = 0;    //���������
        virtual int Search()const = 0;  //�����
        virtual int Locate(int i)const = 0; //�ڱ�����������ֵ X
        virtual bool getData(int i, T& x) const = 0;    //ȡ�� i �������ֵ
        virtual void setData(int i, T& x) = 0;          //�޸ĵ� i �������ֵΪ x
        virtual bool Insert(int i, T& x) = 0;           //�ڵ� i ���������� x
        virtual bool Remove(int i, T& x) = 0;           //ɾ���� i �����ͨ�� x ����
        virtual bool IsEmpty()const = 0;                //�жϱ��
        virtual bool IsFull()const = 0;                 //�жϱ���
        virtual void Sort() = 0;                        //����
        virtual void input() = 0;                       //����
        virtual void output() = 0;                      //���
        virtual LinearList<T> operator=(LinearList<T>& L) = 0;  //����
}