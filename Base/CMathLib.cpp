#include "..\\stdafx.h"
#include "..\\include\\Base\\CMathLib.h"

using namespace MeLib;

void CMathLibMe::M001( int index, int n, double s, double m, double high, double low, 
					double hhv, double llv, int last_state, double last_sar, double last_af,
					int *state, double *af, double *sar )
{
	if (index >= n) {
		if (index == n)
		{
			*af = s;
			if (llv < low)
			{
				*sar = llv;
				*state = 1;
			}
			if (hhv > high)
			{
				*sar = hhv;
				*state = 2;
			}
		}
		else
		{
			*state = last_state;
			*af = last_af;
			double* localRefObject = 0;
			if (*state == 1)
			{
				if (high > hhv)
				{
					localRefObject = af;(*localRefObject = *localRefObject + s);
					if (*af > m) {
						*af = m;
					}
				}
				*sar = last_sar + *af * (hhv - last_sar);
				if (*sar < low) {
					*state = 1;
				} else {
					*state = 3;
				}
			}
			else if (*state == 2)
			{
				if (low < llv)
				{
					localRefObject = af;(*localRefObject = *localRefObject + s);
					if (*af > m) {
						*af = m;
					}
				}
				*sar = last_sar + *af * (llv - last_sar);
				if (*sar > high) {
					*state = 2;
				} else {
					*state = 4;
				}
			}
			else if (*state == 3)
			{
				*sar = hhv;
				if (*sar > high) {
					*state = 2;
				} else {
					*state = 4;
				}
				*af = s;
			}
			else if (*state == 4)
			{
				*sar = llv;
				if (*sar < low) {
					*state = 1;
				} else {
					*state = 3;
				}
				*af = s;
			}
		}
	}
}

double CMathLibMe::M002( double value, double *listForAvedev, int listForAvedev_length, double avg )
{
	int i = 0;
	if (listForAvedev_length > 0)
	{
		double sum = abs(value - avg);
		for (i = 0; i < listForAvedev_length; i++) {
			sum += abs(listForAvedev[i] - avg);
		}
		return sum / listForAvedev_length;
	}
	return 0.0;
}

double CMathLibMe::M003( int index, int n, double value, struct LPDATA last_MA )
{
	double sum = 0.0;
	if (last_MA.mode == 0)
	{
		sum = last_MA.sum + value;
	}
	else
	{
		if (index > n - 1)
		{
			sum = last_MA.lastvalue * n;
			sum -= last_MA.first_value;
		}
		else
		{
			sum = last_MA.lastvalue * index;
			n = index + 1;
		}
		sum += value;
	}
	return sum / n;
}

double CMathLibMe::M004( int index, int n, double value, struct LPDATA last_SUM )
{
	double sum = 0.0;
	if (last_SUM.mode == 0)
	{
		sum = last_SUM.sum + value;
	}
	else
	{
		sum = last_SUM.lastvalue;
		if (index > n - 1) {
			sum -= last_SUM.first_value;
		}
		sum += value;
	}
	return sum;
}

double CMathLibMe::M005( int n, int weight, double value, double lastWMA )
{
	return (value * weight + (n - weight) * lastWMA) / n;
}

double CMathLibMe::M006( int n, double value, double lastEMA )
{
	return (value * 2.0 + lastEMA * (n - 1)) / (n + 1);
}

double CMathLibMe::M007( double *list, int length, double avg, double standardDeviation )
{
	int i = 0;
	if (length > 0)
	{
		double sum = 0.0;
		for (i = 0; i < length; i++) {
			sum += (list[i] - avg) * (list[i] - avg);
		}
		return standardDeviation * sqrt(sum / length);
	}
	return 0.0;
}

double CMathLibMe::GetMin( double *list, int length )
{
	double min = 0.0;
	int i = 0;
	for (i = 0; i < length; i++) {
		if (i == 0) {
			min = list[i];
		} else if (min > list[i]) {
			min = list[i];
		}
	}
	return min;
}

double CMathLibMe::GetMax( double *list, int length )
{
	double max = 0.0;
	int i = 0;
	for (i = 0; i < length; i++) {
		if (i == 0) {
			max = list[i];
		} else if (max < list[i]) {
			max = list[i];
		}
	}
	return max;
}

double CMathLibMe::M010( double *list, int length )
{
	int i = 0;
	double sum = 0.0;
	if (length > 0)
	{
		for (i = 0; i < length; i++) {
			sum += list[i];
		}
		return sum / length;
	}
	return 0.0;
}

double CMathLibMe::M011( double *list, int length )
{
	double sum = 0.0;
	int i = 0;
	for (i = 0; i < length; i++) {
		sum += list[i];
	}
	return sum;
}

int CMathLibMe::M012( double min, double max, int yLen, int maxSpan, int minSpan, int defCount, double *step, int *digit )
{
	double sub = max - min;
	int nMinCount = (int)ceil((float)yLen / maxSpan);
	int nMaxCount = (int)floor((float)yLen / minSpan);
	int nCount = defCount;
	double logStep = sub / nCount;
	bool start = false;
	double divisor = 0.0;
	int i = 0;int nTemp = 0;
	*step = 0.0;
	*digit = 0;
	nCount = max(nMinCount, nCount);
	nCount = min(nMaxCount, nCount);
	nCount = max(nCount, 1);
	for (i = 15; i >= -6; i--)
	{
		divisor = pow(10.0, i);
		void* localObject = 0;
		int localInteger1 = 0;
		int localInteger2 = 0;
		if (divisor < 1.0)
		{
			localObject = digit;localInteger1 = *((int*)localObject);
			localInteger2 = *((int*)localObject) = *((int*)localObject) + 1;
		}
		nTemp = (int)floor(logStep / divisor);
		if (start)
		{
			if (nTemp < 4)
			{
				if (*digit <= 0) {
					break;
				}
				localObject = digit;localInteger1 = *((int*)localObject);
				localInteger2 = *((int*)localObject) = *((int*)localObject) - 1; 
				break;
			}
			if ((nTemp >= 4) && (nTemp <= 6))
			{
				nTemp = 5;
				localObject = step;*((double*)localObject) = *((double*)localObject) + nTemp * divisor; 
				break;
			}
			localObject = step;*((double*)localObject) = *((double*)localObject) + 10.0 * divisor;
			if (*digit <= 0) {
				break;
			}
			localObject = digit;localInteger1 = *((int*)localObject);
			localInteger2 = *((int*)localObject) = *((int*)localObject) - 1; 
			break;
		}
		if (nTemp > 0)
		{
			*step = nTemp * divisor + *step;
			logStep -= *step;
			start = true;
		}
	}
	return 0;
}

void CMathLibMe::M013( int index, double close, double p, double *sxp, int *sxi, double *exp, int *exi, int *state, int *cStart, int *cEnd, double *k, double *b )
{
	bool reverse = false;
	bool ex = false;
	if (index == 0)
	{
		*sxp = close;
		*exp = close;
	}
	else if (index == 1)
	{
		if (close >= *exp) {
			*state = 0;
		} else {
			*state = 1;
		}
		*exp = close;
		*exi = 1;
	}
	else
	{
		if (*state == 0)
		{
			if (100.0 * (*exp - close) / *exp > p) {
				reverse = true;
			} else if (close >= *exp) {
				ex = true;
			}
		}
		else if (100.0 * (close - *exp) / *exp > p) {
			reverse = true;
		} else if (close <= *exp) {
			ex = true;
		}
		if (reverse == true)
		{
			if (*state == 1) {
				*state = 0;
			} else {
				*state = 1;
			}
			*k = (*exp - *sxp) / (*exi - *sxi);
			*b = *exp - *k * *exi;
			*cStart = *sxi;
			*cEnd = *exi;
			*sxi = *exi;
			*sxp = *exp;
			*exi = index;
			*exp = close;
		}
		else if (ex == true)
		{
			*exp = close;
			*exi = index;
			*k = (*exp - *sxp) / (*exi - *sxi);
			*b = *exp - *k * *exi;
			*cStart = *sxi;
			*cEnd = *exi;
		}
		else
		{
			*k = (close - *exp) / (index - *exi);
			*b = close - *k * index;
			*cStart = *exi;
			*cEnd = index;
		}
	}
}

void CMathLibMe::M014( double *list, int length, float *k, float *b )
{
	int i = 0;
	double sumX = 0.0;
	double sumY = 0.0;
	double sumUp = 0.0;
	double sumDown = 0.0;
	double xAvg = 0.0;
	double yAvg = 0.0;
	*k = 0.0;
	*b = 0.0;
	if (length > 1)
	{
		for (i = 0; i < length; i++)
		{
			sumX += i + 1;
			sumY += list[i];
		}
		xAvg = sumX / length;
		yAvg = sumY / length;
		for (i = 0; i < length; i++)
		{
			sumUp += (i + 1 - xAvg) * (list[i] - yAvg);
			sumDown += (i + 1 - xAvg) * (i + 1 - xAvg);
		}
		*k = sumUp / sumDown;
		*b = yAvg - *k * xAvg;
	}
}

double CMathLibMe::M015( double close, double lastSma, int n, int m )
{
	return (close * m + lastSma * (n - m)) / n;
}

void CMathLibMe::M105( int x1, int y1, int x2, int y2, int *x, int *y, int *w, int *h )
{
	*x = x1 < x2 ? x1 : x2;
	*y = y1 < y2 ? y1 : y2;
	*w = abs(x1 - x2);
	*h = abs(y1 - y2);
	if (*w <= 0) {
		*w = 4;
	}
	if (*h <= 0) {
		*h = 4;
	}
}

double CMathLibMe::M106( float x1, float y1, float x2, float y2, float oX, float oY )
{
	if (x1 - oX != x2 - oX) {
		return (y2 - oY - (y1 - oY)) / (x2 - oX - (x1 - oX));
	}
	return 0.0;
}

void CMathLibMe::M107( float x1, float y1, float x2, float y2, float oX, float oY, float *k, float *b )
{
	*k = 0.0;
	*b = 0.0;
	if (x1 - oX != x2 - oX)
	{
		*k = (y2 - oY - (y1 - oY)) / (x2 - oX - (x1 - oX));
		*b = y1 - oY - *k * (x1 - oX);
	}
}

void CMathLibMe::M108( float width, float height, float *a, float *b )
{
	*a = width / 2.0;
	*b= height / 2.0;
}

bool CMathLibMe::M109( float x, float y, float oX, float oY, float a, float b )
{
	x -= oX;
	y -= oY;
	if ((a == 0.0) && (b == 0.0) && (x == 0.0) && (y == 0.0)) {
		return true;
	}
	if (a == 0.0) {
		if ((x == 0.0) && (y >= -b) && (y <= b)) {
			return false;
		}
	}
	if (b == 0.0) {
		if ((y == 0.0) && (x >= -a) && (x <= a)) {
			return true;
		}
	}
	if ((x * x / (a * a) + y * y / (b * b) >= 0.8) && (x * x / (a * a) + y * y / (b * b) <= 1.2)) {
		return true;
	}
	return false;
}

void CMathLibMe::M110( float x1, float y1, float x2, float y2, float x3, float y3, float *oX, float *oY, float *r )
{
	*oX = ((y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1) + (y2 - y1) * (y1 * y1 - y3 * y3 + x1 * x1 - x3 * x3)) / (2.0 * (x2 - x1) * (y3 - y1) - 2.0 * (x3 - x1) * (y2 - y1));
	*oY = ((x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1) + (x2 - x1) * (x1 * x1 - x3 * x3 + y1 * y1 - y3 * y3)) / (2.0 * (y2 - y1) * (x3 - x1) - 2.0 * (y3 - y1) * (x2 - x1));
	*r = (float)sqrt((x1 - *oX) * (x1 - *oX) + (y1 - *oY) * (y1 - *oY));
}

int CMathLibMe::M112( int index )
{
	if (index < 1) {
		return 0;
	}
	int i = 0;int result = 0;
	int* vList = new int[index];
	for (i = 0; i <= index - 1; i++) {
		if ((i == 0) || (i == 1)) {
			vList[i] = 1;
		} else {
			vList[i] = (vList[(i - 1)] + vList[(i - 2)]);
		}
	}
	result = vList[(index - 1)];
	delete []vList;
	vList = 0;
	return result;
}

void CMathLibMe::M124( float x1, float y1, float x2, float y2, float x3, float y3, float *x4, float *y4 )
{
	*x4 = x1 + x3 - x2;
	*y4 = y1 + y3 - y2;
}

double CMathLibMe::M129( int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec, int tm_msec )
{
	struct tm t;
	time_t tn;
	t.tm_sec = tm_sec;
	t.tm_min = tm_min;
	t.tm_hour = tm_hour;
	t.tm_mday = tm_mday;
	t.tm_mon = tm_mon - 1;
	t.tm_year = tm_year - 1900;
	tn = mktime(&t);
	return (double)tn + (double)tm_msec / 1000 + 28800;
}

void CMathLibMe::M130( double num, int *tm_year, int *tm_mon, int *tm_mday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_msec )
{
	time_t tn = (_int64)num;
	struct tm* t = gmtime(&tn);
	*tm_sec = t->tm_sec;
	*tm_min = t->tm_min;
	*tm_hour = t->tm_hour;
	*tm_mday = t->tm_mday;
	*tm_mon = t->tm_mon + 1;
	*tm_year = t->tm_year + 1900;
	*tm_msec = (int)((num * 1000 - floor(num) * 1000));
}

int CMathLibMe::M131()
{
	return 0;
}

void CMathLibMe::M132( RECT *bounds, SIZE *parentSize, SIZE *oldSize, bool anchorLeft, bool anchorTop, bool anchorRight, bool anchorBottom )
{
	if (anchorRight && !anchorLeft)
	{
		bounds->left = (bounds->left + parentSize->cx - oldSize->cx);
	}
	if (anchorBottom && !anchorTop)
	{
		bounds->top = (bounds->top + parentSize->cy - oldSize->cy);
	}
	if (anchorRight)
	{
		bounds->right = (bounds->right + parentSize->cx - oldSize->cx);
	}
	if (anchorBottom)
	{
		bounds->bottom = (bounds->bottom + parentSize->cy - oldSize->cy);
	}
}

void CMathLibMe::M133( RECT *bounds, RECT *spaceRect, SIZE *cSize, int dock )
{
	if (dock == DockStyleMe_Bottom)
	{
		bounds->left = spaceRect->left;
		bounds->top = (spaceRect->bottom - cSize->cy);
		bounds->right = spaceRect->right;
		bounds->bottom = spaceRect->bottom;
	}
	else if (dock == DockStyleMe_Fill)
	{
		bounds = spaceRect;
	}
	else if (dock == DockStyleMe_Left)
	{
		bounds->left = spaceRect->left;
		bounds->top = spaceRect->top;
		bounds->right = (bounds->left + cSize->cx);
		bounds->bottom = spaceRect->bottom;
	}
	else if (dock == DockStyleMe_Right)
	{
		bounds->left = (spaceRect->right - cSize->cx);
		bounds->top = spaceRect->top;
		bounds->right = spaceRect->right;
		bounds->bottom = spaceRect->bottom;
	}
	else if (dock == DockStyleMe_Top)
	{
		bounds->left = spaceRect->left;
		bounds->top = spaceRect->top;
		bounds->right = spaceRect->right;
		bounds->bottom = (bounds->top + cSize->cy);
	}
}

void CMathLibMe::M135( int layoutStyle, RECT *bounds, PADDING *padding, PADDING *margin, int left, int top, int width, int height, int tw, int th, POINT *headerLocation )
{

}

void CMathLibMe::M137( int resizePoint, int *left, int *top, int *right, int *bottom, POINT *nowPoint, POINT *startMousePoint )
{
	switch (resizePoint)
	{
	case 0: 
		left = left + nowPoint->x - startMousePoint->x;
		top = top + nowPoint->y - startMousePoint->y;
		break;
	case 1: 
		left = left + nowPoint->x - startMousePoint->x;
		bottom = bottom + nowPoint->y - startMousePoint->y;
		break;
	case 2: 
		right = right + nowPoint->x - startMousePoint->x;
		top = top + nowPoint->y - startMousePoint->y;
		break;
	case 3: 
		right = right + nowPoint->x - startMousePoint->x;
		bottom = bottom + nowPoint->y - startMousePoint->y;
		break;
	case 4: 
		left = left + nowPoint->x - startMousePoint->x;
		break;
	case 5: 
		top = top + nowPoint->y - startMousePoint->y;
		break;
	case 6: 
		right = right + nowPoint->x - startMousePoint->x;
		break;
	case 7: 
		bottom = bottom + nowPoint->y - startMousePoint->y;
	}
}

bool CMathLibMe::IsLineVisible( int indexTop, int indexBottom, int cell, int floor, int lineHeight, double visiblePercent )
{
	if (indexTop < cell)
	{
		indexTop = cell;
	}
	else if (indexTop > floor)
	{
		indexTop = floor;
	}
	if (indexBottom < cell)
	{
		indexBottom = cell;
	}
	else if (indexBottom > floor)
	{
		indexBottom = floor;
	}
	if (indexBottom - indexTop > lineHeight * visiblePercent)
	{
		return true;
	}
	return false;
}
