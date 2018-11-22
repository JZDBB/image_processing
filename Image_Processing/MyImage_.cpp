#include "StdAfx.h"
#include "MyImage_.h"


MyImage_::MyImage_(void)
{
	m_pBits=NULL;
}


MyImage_::~MyImage_(void)
{

	if ( m_pBits!=NULL)
	{
		int h=m_CImage.GetHeight();
		for   (int   i=0;   i<2;   i++)   
		{          
			for   (int   j=0;   j<h;   j++)         
			{   

				delete[] m_pBits[i][j];   
				m_pBits[i][j]=NULL;
			}
		}
		for (int   i=0;   i<2;   i++)
		{
			delete[] m_pBits[i];  
			m_pBits[i]=NULL;
		}
		delete[]  m_pBits;
		m_pBits=NULL;
	}
}

HRESULT MyImage_::Load(_In_z_ LPCTSTR pszFileName) 
{
	m_CImage.Load(pszFileName);
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ
	int bits = m_CImage.GetBPP();

	/*������ά���鲢��m_CImage���ƽ���ά����*/
	m_pBits= (BYTE***)new   BYTE**[3];   
	for(int i=0;i<3;i++)  
	{ 
		m_pBits[i] = (BYTE**)new  BYTE*[h];
	}   
	for(int i=0; i<3; i++)   
	{          
		for   (int   j=0;   j<h;   j++)         
		{   

			m_pBits[i][j]=new BYTE[w];   
		}
	}

	/*��m_CImage���ƽ���ά����*/
	if ((bits == 24)|| (bits == 32))
	{
		for (int j=0;j<h;j++)
		{
			for (int k=0;k<w;k++)
			{
				m_pBits[0][j][k] = psrc[j*nrow + k * 3];//B
				m_pBits[1][j][k] = psrc[j*nrow + k * 3 + 1];//G
				m_pBits[2][j][k] = psrc[j*nrow + k * 3 + 2];//R
			}
		}
	}
	else
	{
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				m_pBits[0][j][k] = psrc[j*nrow + k];//B
				m_pBits[1][j][k] = psrc[j*nrow + k];//G
				m_pBits[2][j][k] = psrc[j*nrow + k];//R
			}
		}
	}
	

	/*������ά���鲢��m_CImage���ƽ���ά����*/
	return( S_OK );//Ϊ����CImge���Load��������ֵ��ͬ
}
// HRESULT MyImage_::Load(_In_z_ LPCTSTR pszFileName) 
//{
//	m_CImage.Load(pszFileName);
//
//}

BOOL  MyImage_::Draw(
	_In_ HDC hDestDC,
	_In_ int xDest,
	_In_ int yDest,
	_In_ int nDestWidth,
	_In_ int nDestHeight) const 
{
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ
	/*����ά���鸴�ƽ�m_CImage*/
	int bits = m_CImage.GetBPP();

	if ((bits == 24)||(bits == 32))
	{
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				psrc[j*nrow + k * 3] = m_pBits[0][j][k];//B
				psrc[j*nrow + k * 3 + 1] = m_pBits[1][j][k];//G
				psrc[j*nrow + k * 3 + 2] = m_pBits[2][j][k];//R

			}
		}
	}
	else
	{
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				psrc[j*nrow + k * 3] = m_pBits[0][j][k];
			}
		}
	}

	
	/*����ά���鸴�ƽ�m_CImage*/

	return m_CImage.Draw(hDestDC,xDest, yDest,nDestWidth, nDestHeight);//����CImage��Draw;
}
bool MyImage_::IsNull() const 
{
	return m_CImage.IsNull();
}

void MyImage_::Destroy() 
{
	m_CImage.Destroy();
}

int MyImage_::GetWidth() const 
{
	return m_CImage.GetWidth();
}
int MyImage_::GetHeight() const
{
	return m_CImage.GetHeight();
}

int MyImage_::GetBPP() const
{
	return m_CImage.GetBPP();
}

int MyImage_::GetPitch() const
{
	return m_CImage.GetPitch();
}


//void MyImage_::GetBits() const
//{
//	return m_CImage.GetBits();
//}



BOOL  MyImage_::Draw(
	_In_ HDC hDestDC,
	_In_ int xDest,
	_In_ int yDest) const
{
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ
	/*����ά���鸴�ƽ�m_CImage*/
	int bits = m_CImage.GetBPP();

	if ((bits == 24) || (bits == 32))
	{
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				psrc[j*nrow + k * 3] = m_pBits[0][j][k];//B
				psrc[j*nrow + k * 3 + 1] = m_pBits[1][j][k];//G
				psrc[j*nrow + k * 3 + 2] = m_pBits[2][j][k];//R

			}
		}
	}
	else
	{
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				psrc[j*nrow + k] = m_pBits[0][j][k];
			}
		}
	}
	/*����ά���鸴�ƽ�m_CImage*/
	return m_CImage.Draw(hDestDC,xDest,yDest);
}

HRESULT MyImage_::Save(
	_In_z_ LPCTSTR pszFileName,
	_In_ REFGUID guidFileType) const
{
	if(m_CImage.IsNull()) return 0;
	int w=m_CImage.GetWidth();
	int h=m_CImage.GetHeight();
	int nrow=m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С
	BYTE *psrc=(BYTE *)m_CImage.GetBits();//���m_CImage���һ�е����ص�ַ

	int bits = m_CImage.GetBPP();

	if ((bits == 24) || (bits == 32))
	{
		for (int j = 0; j < h; j++)
		{

			for (int k = 0; k < w; k++)
			{
				psrc[j*nrow + k * 3] = m_pBits[0][j][k];//B
				psrc[j*nrow + k * 3 + 1] = m_pBits[1][j][k];//G
				psrc[j*nrow + k * 3 + 2] = m_pBits[2][j][k];//R

			}
		}
	}
	else
	{
		for (int j = 0; j < h; j++)
		{

			for (int k = 0; k < w; k++)
			{
				psrc[j*nrow + k] = m_pBits[0][j][k];//B
			}
		}
	}

	
	return m_CImage.Save(pszFileName,guidFileType);

}



void MyImage_::calcHistogram(void)//ֱ��ͼͳ��
{
	BYTE *lpSrc;	//ָ��Դͼ��ָ��
	int w = GetWidth();
	int h = GetHeight();
	int gray[256] = {0};	//ÿ���Ҷ�ֵͳ��
	int nrow = m_CImage.GetPitch();//���m_CImageÿһ�����ص�RGB��ռ�õĴ洢�ռ�Ĵ�С

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			BYTE value = m_pBits[0][i][j];
			gray[value] ++;
		}
	}
	
	for (int k = 0; k < 256; k++)
	{
		arr[k] = gray[k] / (w*h*1.0f);
		//Normalization
	}
}
