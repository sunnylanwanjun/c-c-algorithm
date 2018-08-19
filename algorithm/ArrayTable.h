#ifndef __ARRAYTABLE_H
#define __ARRAYTABLE_H
#define MAX_ARRAY_DIM 8
template<class Elem>
struct ArrayTable{
	Elem *base;
	int   dim;
	int  *bounds; //���ά��
	int  *constants;//���ά�ȳ˻�
	/*
	��j1 => ��1ά
	j2 => ��2ά
	j3 => ��3ά
	...
	b1 => ��1ά���ݸ���
	b2 => ��2ά���ݸ���
	...
	�ڶ�ά������£�
	0 1 2  3
	4 5 6  7
	8 9 10 11
	Ҳ�ɱ�ʾΪ
	{[0,1,2,3],[4,5,6,7],[8,9,10,11]}
	���ݼ�����
	b1 = 3 
	b2 = 4
	�ù�ʽ��ʾ
	Addr(j1,j2) = Addr(0,0) + (j1*b2+j2)*L,����L��ʾ����Ԫ����ռ�ռ�
	Addr��ʾj1��j2�����ڵĵ�ַ
	����ά������£�
	{[(1,2,3),(4,5,6)],[(7,8,9),(1,2,3)],[(7,8,9),(1,2,3)],[(7,8,9),(1,2,3)]}
	b1 = 4
	b2 = 2
	b3 = 3
	Addr(j1,j2,j3) = Addr(0,0,0) + (j1*b2*b3 + j2*b3 + j3)*L
	�ƹ㵽nά������
	Addr(j1,j2,...,jn) = Addr(0,0,...,0) + 
	[ (j1*b2*b3*...*bn) +
	  (j2*b3*b4*...*bn) +
	  ...
	  ...
	  ...
	  (jn-1*bn) +
	  jn
	]*L
	*/
	ArrayTable(int dim,...){
		assert(dim <= MAX_ARRAY_DIM);
		bounds = new int[dim];
		va_list va;
		va_start(va,dim);
		int totalSize = 1;
		for (int i = 0; i < dim; i++){
			bounds[i] = va_arg(va, int);
			totalSize *= bounds[i];
		}
		va_end(va);
		constants = new int[totalSize];
		constants[totalSize - 1] = 1;
		for (int i = totalSize-2; i >= 0; i--){
			constants[i] *= constants[i+1];
		}
	}
	~ArrayTable(){
		delete[] base;
		delete[] bounds;
		delete[] constants;
	}
	int Locate(va_list va){
		int pos = 1;
		int offset = 0;
		for (int i = 0; i < dim; i++){
			pos = va_arg(va, int);
			offset += constants[i] * pos;
		}
		va_end(va);
		return offset;
	}
	void Value(Elem* e,...){
		va_list va;
		va_start(va,e);
		*e = base[Locate(va)];
	}
	void Assign(Elem* e, ...){
		va_list va;
		va_start(va, e);
		base[Locate(va)] = *e;
	}

};

//n�׶Գƾ�����±��Ӧ��ϵ�Ƶ�
/*
�����±�
11 12 13 14
21 22 23 24
31 32 33 34
41 42 43 44

����
21 12
13 31
������
������
�Գ�λ���ϵ�ֵ��ͬ

�������������±�
0
1 2
3 4 5
6 7 8 9
�������ɾ����±꣬�Ƴ������±�
�۲��֪��������ȷ���˸����ж��ٸ�����
���3�У���3 4 5
��ô��0+1+2+3=6��Ҳ����˵�����Ƴ�ÿһ�е����һ�����������һ������ȥ�����Ϳ��Եõ����׵����֣��ܽ�ʽ������
(1+i)*i/2-i,�����׼��������Ϳ���֪��������һά�����±�Ĺ�ϵ�����£�
(1+i)*i/2-i+j-1 = (i-1)/2+j-1 ���������ǵĹ�ʽ
���������ǣ��ɶԳƹ�ϵ��֪
(j-1)/2+i-1,�ܽ�����,��kΪ�����±�
��i>=jʱ����k=(i-1)/2+j-1
��i<jʱ����k=(j-1)/2+i-1
*/
//ϡ�������Գƾ���ͬ��ϡ�������û�й����ˣ�����ʹ����Ԫ�����ѹ���洢
template<class Elem>
struct Triple{
	int i, j;
	Elem e;
};
#define TSMAXSIZE 12500
template<class Elem>
struct TSMatrix{
	Triple data[TSMAXSIZE+1];
	int mu, nu, tu;
};
#endif