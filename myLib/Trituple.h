#include <iostream.h>
#include <stdlib.h>
const int DefaultSize = 100;

template <class T>
class Trituple                      //��Ԫ����Trituple
{
    public:
        Trituple(Trituple<T>& t){row = t.row; col = t.col; value = t.value;}
        int row, col;               //����Ԫ�ص��кš��к�
        T value;                    //����Ԫ�ص�ֵ
        friend Trituple<T>& operator =(Trituple<T>& x);  //��㸳ֵ
};

template<class T>
Trituple<T>& operator =(Trituple<T>& x)
{
    row = t.row; col = t.col; value = t.value;
}

template <class T>
class SparseMatrix      //ϡ������������
{
    friend ostream& operator << (ostream& out, SparseMatrix<T>& M);
                                    //��Ԫ���������������������
    friend istream& operator >> (istream& in, SparseMatrix<T>& M);
                                    //��Ԫ����������������������
    public:
        SparseMatrix(int maxSize = DefaultSize);        //���캯��
        SparseMatrix(SparseMatrix<T>& x);               //���ƹ��캯��
        ~SparseMatrix() {delete []smArray;}             //��������
        SparseMatrix<T>& operator = (SparseMatrix<T>& x);
        SparseMatrix<T> Transpose();                    //�Ե�ǰϡ��������(*thisָʾ)ִ��ת������
        SparseMatrix<T> FastTranspose();
        SparseMatrix<T> Add(SparseMatrix<T>& b);        //��ǰ����*thisָʾ�������b���
        SparseMatrix<T> Multiply(SparseMatrix<T>& b);   //����ʽc[i][j] = ��(a[i][k]*b[k][j])ʵ�ֵ�ǰ���������b���
    private:
        int Rows,Cols,Terms;
        Trituple<T> *smArray;
        int maxTerms;

};

template <class T>
SparseMatrix<T>::SparseMatrix(int maxSize):maxTerms(maxSize){
    if (maxSize < 1){
        cerr<<"�����ʼ��ֵ��"<<endl; exit(1);}
    smArray = new Trituple<T>[maxSize];
    if (smArray == NULL){
        cerr<< "�洢�����"<< endl; exit(1);}
    Rows = Cols = Terms = 0;
}

SparseMatrix<T>::SparseMatrix(SparseMatrix<T>& x){
    Rows = x.Rows; Cols = x.Cols; Terms = x.Terms;
    maxTerms = x.maxTerms;
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL){
        cerr << "�洢�����"<<endl; exit(1);}
    for (int i = 0; i < Terms; i++) smArray[i] = x.smArray[i];
    //ʹ�ý���Ա����"="ִ�������㸴��
}

template <class T>
ostream& operator << (ostream& out, SparseMatrix<T>& M){
    out << "rows = " << M.Rows << endl;
    out << "cols = " << M.Cols << endl;
    out << "Nonzero terms = " << M.Terms << endl;
    for (int i = 0; i < M.Terms;i++)
        out << "M[" << M.smArray[i].row << "][" << M.smArray[i].col
        << "]=" << M.smArray[i].value << endl;
    return out;
}

template <class T>
istream& operator >> (istream& in, SparseMatrix<T>& M){
    cout << "Enter number of rows, columns, and terms" << endl;
    in >> M.Rows >> M.Cols >> M.Terms;
    if (M.Terms > maxTerms){
        cerr << "number of terms overflow!" <<endl; exit(1);}
    for (int i = 0; i < M.Terms; i++){
        cout << "Enter row, column, and value of term:" << i+1 << endl;
        in >> M.smArray[i].row >> M.smArray[i].col >>
            >> M.smArray[i].value;
    }
    return in;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::transpose()
//��ϡ�����a��*thisָʾ��ת�ã������ϡ�����b�в�ͨ����������
{
    SparseMatrix<T> b(maxTerms);            //����һ��ϡ�������Ķ���b
    b.Rows = Cols;                          //����b������=����a������
    b.Cols = Rows;                          //����b������=����a������    
    b.Terms = Terms;                        //����b�ķ���Ԫ�ظ���
    if (Terms > 0){
        int k,i,CurrentB = 0;               //���λ��ָ��
        for (k = 0; k < Cols; k++)          //���к���ɨ�裬��Cols��
            if (smArray[i].col == k){
                b.smArray[CurrentB].row = k;
                b.smArray[CurrentB].col = smArray[i].row;
                b.smArray[CurrentB].value = smArray[i].value;
                CurrentB++;                 //���ָ���1
            }
    }
    return b;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::FastTranspose(){
//����ת��
    int *rowSize = new int[Cols];               //�������飬ͳ�Ƹ��з���Ԫ�ظ���
    int *rowStart = new int[Cols];              //�������飬Ԥ��ת�ú���д��λ��
    SparseMatrix<T> b(maxTerm);                 //���ת�ý��
    b.Rows = Cols; b.Cols = Rows; b.Terms = Terms;
    if (Terms > 0){
        int i, j;
        for (i = 0; i < Cols; i++) rowSize[i] = 0;
        for (i = 0; i < Terms; i++) rowSize[smArray[i].col]++;
        rowStart[0] = 0;
        for (i = 1; i < Cols; i++)
            rowStart[i] = rowStart[i-1] + rowSize[i-1];
        for (i = 0; i < Terms; i++){            //��a��b����
            j = rowStart[smArray[i].col];       //��i������Ԫ����b��Ӧ��λ��
            b.smArray[j].row = smArray[i].col;  
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;         //rowStart�ĸ�������
        }
    }
    delete []rowSize; delete []rowStart;
    return b;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::Add(SparseMatrix<T> b){
//����ϡ�����A��*thisָʾ����B���������е�b����ӣ������Result��

}