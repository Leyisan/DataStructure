#include <iostream.h>
#include <stdlib.h>
const int DefaultSize = 100;
#define zero 0


template <class T>
class Trituple                      //��Ԫ����Trituple
{
    public:
        Trituple() {row = col = 0; value = zero;}
        Trituple(Trituple<T>& t){row = t.row; col = t.col; value = t.value;}
        int row, col;               //����Ԫ�ص��кš��к�
        T value;                    //����Ԫ�ص�ֵ
};

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

template <class T>
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
SparseMatrix<T> SparseMatrix<T>::Transpose()
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
SparseMatrix<T> SparseMatrix<T>::Add(SparseMatrix<T>& b){
//����ϡ�����A��*thisָʾ����B���������е�b����ӣ������Result��
    SparseMatrix<T> Result;          //����������Ԫ����
    if (Rows != b.Rows || Cols != b.Cols){
        cout << "Incompatible matrices" << endl;//����������һ��
        return Result;
    }
    int i = 0, j = 0, index_a,index_b; Result.Terms = 0;
    while (i < Terms && j < b.Terms){
        index_a = Cols * smArray[i].row + smArray[i].col;
        index_b = Cols * b.smArray[j].row + b.smArray[j].col;
        if (index_a < index_b) {                //smArray[i]��b.smArray[j]ǰ
            Result.smArray[Result.Terms] = smArray[i];
            i++;
        }
        else if (index_a > index_b) {           //smArray[i]��b.smArray[j]��
            Result.smArray[Result.Terms] = b.smArray[i];
            j++;
        }
        else {                                  //smArray[i]��b.smArray[j]����ͬλ��
            Result.smArray[Result.Terms] = smArray[i];
            Result.smArray[Result.Terms].value = smArray[i].value + b.smArray[j].value;
            i++; j++;
        }
        Result.Terms++;
    }
    //����ʣ��Ԫ��
    for(; i < Terms; i++){
        Result.smArray[Result.Terms] = smArray[i];
        Result.Terms++;
    }
    for(; j < b.Terms; j++){
        Result.smArray[Result.Terms] = b.smArray[i];
        Result.Terms++;
    }
    return Result;
}   


template <class T>
SparseMatrix<T> SparseMatrix<T>::Multiply(SparseMatrix<T>& b){
    //����ϡ�����a(*thisָʾ)��b(�������е�b)��ˣ������Result��
    SparseMatrix<T> result;        //����������Ԫ���
    if (Cols != b.Rows){
        cerr << "Incompatible matrices" << endl;    //A������B��������
        return result;                              //���ؿվ���
    }
    if (Terms == maxTerms || b.Terms == maxTerms){
        cerr << "One additional space in a or b needed" << endl;
        return result;                              //�ռ䲻�㣬���ؿվ���
    }
    int *rowSize = new int[b.Rows];                 //����b���з���Ԫ�ظ���
    int *rowStart = new int[b.Rows+1];              //����b��������Ԫ�鿪ʼλ��
    T *temp = new T[b.Cols];                        //�ݴ�ÿһ�м�����
    int i, Current, LastInResult, RowA, ColA, ColB;
    for (i = 0; i < b.Rows; i++) rowSize[i] = 0;
    for (i = 0; i < b.Terms; i++) rowSize[b.smArray[i].row]++;
    rowStart[0] = 0;                                //B��i�з���Ԫ�ؿ�ʼλ��
    for (i = 1; i <= b.Rows; i++)
        rowStart[i] = rowStart[i-1] + rowSize[i-1];
    Current = 0; LastInResult = -1;                  //aɨ��ָ�뼰result��ָ��
    while (Current < Terms){                        //����result�ĵ�ǰ��temp
        RowA = smArray[Current].row;                //��ǰ�е��к�
        for (i = 0; i < b.Cols; i++) temp[i] = 0;
        while (Current < Terms && smArray[Current].row == RowA){
            ColA = smArray[Current].col;            //����A��ǰɨ�赽Ԫ�ص��к�
            for (i = rowStart[ColA]; i < rowStart[ColA+1]; i++){
                ColB = b.smArray[i].col;            //����B�����Ԫ�ص��к�
                temp[ColB] += smArray[Current].value * b.smArray[i].value;
            }                                       //A��RowA����B��ColB�����
            Current++;
        }
        for (i = 0; i < b.Cols; i++)
            if (temp[i] != 0) {                     //��temp�еķ���Ԫ��ѹ����result��ȥ
                LastInResult++;
                result.smArray[LastInResult].row = RowA;
                result.smArray[LastInResult].col = i;
                result.smArray[LastInResult].value = temp[i];
            }
    }
    result.Rows = Rows; result.Cols = b.Cols;
    result.Terms = LastInResult+1;
    delete []rowSize; delete []rowStart; delete []temp;
    return result;
};
