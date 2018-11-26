//
// Created by yqi on 11/26/18.
//

#ifndef FFT_COMPLEX_HPP
#define FFT_COMPLEX_HPP

#endif //FFT_COMPLEX_H
template <class T>
class complex
{
private:
    T real;
    T imag;
public:
    complex(){real=0;imag=1;}
    complex(T r,T i):real(r),imag(i){}
    complex(const complex &tmp):real(tmp.real),imag(tmp.imag){}
    void set_real(T r);
    void set_imag(T i);
    void set_complex(T r,T i);
    T get_real() const;
    T get_imag() const;
    complex& operator+=(const complex &tmp);
    complex& operator+=(const T r);
    complex& operator-=(const complex &tmp);
    complex& operator-=(const T r);
    complex& operator=(const complex &tmp);
    complex& operator=(const T r);
    bool operator==(const complex &tmp) const;
    bool operator>=(const complex &tmp) const;
    bool operator<=(const complex &tmp) const;
    bool operator!=(const complex &tmp) const;
    bool operator>(const complex &tmp) const;
    bool operator<(const complex &tmp) const;
    T operator!();
    friend complex operator+(const complex &tmp,const complex &temp);
    friend complex operator+(const complex &tmp,const T r);
    friend complex operator+(const T r,const complex &tmp);
    friend complex operator-(const complex &tmp,const complex &temp);
    friend complex operator-(const complex &tmp,const T r);
    friend complex operator-(const T r,const complex &tmp);
    friend complex operator*(const complex &tmp,const complex &temp);
    friend complex operator*(const complex &tmp,const T r);
    friend complex operator*(const T r,const complex &tmp);
    friend complex operator/(const complex &tmp,const complex &temp);
    friend complex operator/(const complex &tmp,const T r);
    friend complex operator/(const T r,const complex &tmp);
//    friend istream& operator>>(istream &is ,complex &tmp);
//    friend ostream& operator<<(ostream &os,const complex &tmp);
};
template<class T>
void complex<T>::set_real(T r)
{
	real = r;
}

template <class T>
void complex<T>::set_imag(T i)
{
	imag = i;
}

template <class T>
void complex<T>::set_complex(T r, T i)
{
	real = r;
	imag = i;
	return;
}

template <class T>
inline T complex<T>::get_real() const
{
	return(real);
}

template <class T>
inline T complex<T>::get_imag() const
{
	return(imag);
}

template <class T>
inline complex<T>& complex<T>::operator+=(const complex<T>& tmp)
{
	real += tmp.real;
	imag += tmp.imag;
	return *this;
}

template <class T>
inline complex<T>& complex<T>::operator+=(T r)
{
	real += r;
	return *this;
}

template <class T>
inline complex<T>& complex<T>::operator-=(const complex<T>& tmp)
{
	real -= tmp.real;
	imag -= tmp.imag;
	return *this;
}

template <class T>
inline complex<T>& complex<T>::operator-=(T r)
{
	real -= r;
	return *this;
}

template <class T>
inline complex<T>& complex<T>::operator=(const complex<T>& tmp)
{
	real = tmp.real;
	imag = tmp.imag;
	return *this;
}

template <class T>
inline complex<T>& complex<T>::operator=(T r)
{
	real = r;
	imag = 0;
	return *this;
}

template <class T>
inline complex<T> operator+(const complex<T> &tmp, const complex<T> &temp)
{
	complex<T> result;
	result.real = tmp.real + temp.real;
	result.imag = tmp.imag + temp.imag;
	return result;
}

template <class T>
inline complex<T> operator+(const complex<T> &tmp, const T r)
{
	complex<T> result;
	result.real = tmp.real + r;
	result.imag = tmp.imag;
	return result;
}

template <class T>
inline complex<T> operator+(const T r, const complex<T> &tmp)
{
	complex<T> result;
	result.real = r + tmp.real;
	result.imag = tmp.imag;
	return result;
}

template <class T>
inline complex<T> operator-(const complex<T> &tmp, const complex<T> &temp)
{
	complex<T> result;
	result.real = tmp.real - temp.real;
	result.imag = tmp.imag - temp.imag;
	return result;
}

template <class T>
inline complex<T> operator-(const complex<T> &tmp, const T r)
{
	complex<T> result;
	result.real = tmp.real - r;
	result.imag = tmp.imag;
	return result;
}

template <class T>
inline complex<T> operator-(const T r, const complex<T> &tmp)
{
	complex<T> result;
	result.real = r - tmp.real;
	result.imag = 0 - tmp.imag;
	return result;
}

template <class T>
inline complex<T> operator*(const complex<T> &tmp, const complex<T>& temp)
{
	complex<T> result;
	result.real = temp.real*tmp.real - temp.imag*tmp.imag;
	result.imag = temp.real*tmp.imag + temp.imag*tmp.real;
	return result;
}

template <class T>
inline complex<T> operator*(const complex<T> &tmp, const T r)
{
	complex<T> result;
	result.real = tmp.real*r;
	result.imag = tmp.imag*r;
	return result;
}

template <class T>
inline complex<T> operator*(const T r, const complex<T> &tmp)
{
	complex<T> result;
	result.real = r * tmp.real;
	result.imag = r * tmp.imag;
	return result;
}

template <class T>
inline complex<T> operator/(const complex<T> &tmp, const complex<T> &temp)
{
	complex<T> result;
	if (temp.real == 0 && temp.imag == 0)
	{
		runtime_error("error");
		return result;
	}
	result.real = (tmp.real*temp.real + tmp.imag*temp.imag) / (temp.real*temp.real + temp.imag*temp.imag);
	result.imag = (tmp.imag*temp.real - tmp.real*temp.imag) / (temp.real*temp.real + temp.imag*temp.imag);
	return result;
}

template <class T>
inline complex<T> operator/(const complex<T> &tmp, const T r)
{
	complex<T> result;
	if (r == 0)
	{
		runtime_error("error");
		return result;
	}
	result.real = tmp.real / r;
	result.imag = tmp.imag / r;
	return result;
}

template <class T>
inline complex<T> operator/(const T r, const complex<T> &tmp)
{
	complex<T> result;
	if (tmp.real == 0 && tmp.imag == 0)
	{
		throw runtime_error("error");
	}
	result.real = r * tmp.real / (tmp.real*tmp.real + tmp.imag*tmp.imag);
	result.imag = (0 - r * tmp.imag) / (tmp.real*tmp.real + tmp.imag + tmp.imag);
	return result;
}

template <class T>
inline T complex<T>::operator!()
{
	return sqrt(real*real + imag * imag);
}

template <class T>
inline bool complex<T>::operator==(const complex<T> &tmp) const
{
	if (real == tmp.real&&imag == tmp.imag)
		return true;
	else
		return false;
}

template <class T>
inline bool complex<T>::operator!=(const complex<T> &tmp) const
{
	if (*this == tmp)
		return false;
	else
		return true;
}

template <class T>
inline bool complex<T>::operator>=(const complex<T> &tmp) const
{
	if ((real*real + imag * imag) >= (tmp.real*tmp.real + tmp.imag*tmp.imag))
		return true;
	else
		return false;
}

template <class T>
inline bool complex<T>::operator>(const complex<T> &tmp) const
{
	if ((real*real + imag * imag) > (tmp.real*tmp.real + tmp.imag*tmp.imag))
		return true;
	else
		return false;
}

template <class T>
inline bool complex<T>::operator<=(const complex<T> &tmp) const
{
	if ((real*real + imag * imag) <= (tmp.real*tmp.real + tmp.imag*tmp.imag))
		return true;
	else
		return false;
}

template <class T>
inline bool complex<T>::operator<(const complex<T> &tmp) const
{
	if ((real*real + imag * imag) < (tmp.real*tmp.real + tmp.imag*tmp.imag))
		return true;
	else
		return false;
}
