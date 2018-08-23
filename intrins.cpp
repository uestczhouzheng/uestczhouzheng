#include "intrins.h"  

//循环左移n位  
uchar _crol(uchar tmp, uchar n)
{
	while (n--)
	{
		tmp = _crol_bit(tmp);
	}
	return tmp;
}
//循环左移1位  
uchar _crol_bit(uchar tmp)
{
	return (tmp << 1) | (tmp >> 7);
}
//循环右移n位  
uchar _cror(uchar tmp, uchar n)
{
	while (n--)
	{
		tmp = _cror_bit(tmp);
	}
	return tmp;
}
//循环右移1位  
uchar _cror_bit(uchar tmp)
{
	return (tmp >> 1) | (tmp << 7);
}
//循环移位（旋转）  
void _rota(uchar tmp, uchar *temp)
{
	for (int i = 0; i < 8; i++)
	{
		*temp = _cror(tmp, i);
		temp++;
	}
}
//找到最小值  
uchar _min(uchar *tmp)
{
	uchar min = *tmp;
	for (int i = 0; i < 8; i++)
	{
		tmp++;
		if (min > *tmp)
		{
			min = *tmp;
		}
	}
	return min;
}
