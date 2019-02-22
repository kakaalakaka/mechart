/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CMATHLIBME_H__
#define __CMATHLIBME_H__
#pragma once
#include "..\\..\\stdafx.h"

namespace MeLib
{
	struct LPDATA
	{
	public:
		LPDATA()
		{
		};
		double lastvalue;
		double first_value;
		int mode;
		double sum;
	};

	class CMathLibMe
	{
	public:
		static void M001(int index, int n, double s, double m, double high, double low, double hhv, double llv, 
			int last_state, double last_sar, double last_af, int *state, double *af, double *sar);
		static double M002(double value, double *listForAvedev, int listForAvedev_length, double avg);
		static double M003(int index, int n, double value, struct LPDATA last_MA);
		static double M004(int index, int n, double value, struct LPDATA last_SUM);
		static double M005(int n, int weight, double value, double lastWMA);
		static double M006(int n, double value, double lastEMA);
		static double M007(double *list, int length, double avg,  double standardDeviation);
		static double GetMin(double *list, int length);
		static double GetMax(double *list, int length);
		static double M010(double *list, int length);
		static double M011(double *list, int length);
		static int M012(double min, double max, int yLen, int maxSpan, int minSpan, int defCount, double *step, int *digit);
		static void M013(int index, double close, double p, double *sxp, int *sxi, double *exp, int *exi, int *state, int *cStart, int *cEnd, double *k, double *b);
		static void M014(double *list, int length, float *k, float *b);
		static double M015(double close, double lastSma, int n, int m);
		static void M105(int x1, int y1, int x2, int y2, int *x, int *y, int *w, int *h);
		static double M106(float x1,  float y1,  float x2,  float y2,  float oX,  float oY);
		static void M107(float x1,  float y1,  float x2,  float y2,  float oX,  float oY,  float *k,  float *b);
		static void M108(float width,  float height,  float *a,  float *b);
		static bool M109(float x, float y, float oX, float oY, float a, float b);
		static void M110(float x1, float y1, float x2, float y2, float x3, float y3, float *oX, float *oY, float *r);
		static int M112(int index);
		static void M124(float x1, float y1, float x2, float y2, float x3, float y3, float *x4, float *y4);
		static double M129(int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec, int tm_msec);
		static void M130(double num, int *tm_year, int *tm_mon, int *tm_mday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_msec);
		static int M131();
		static void M132(RECT *bounds, SIZE *parentSize, SIZE *oldSize, bool anchorLeft, bool anchorTop, bool anchorRight, bool anchorBottom);
		static void M133(RECT *bounds, RECT *spaceRect, SIZE *cSize, int dock);
		static void M135(int layoutStyle, RECT *bounds, PADDING *padding, PADDING *margin, int left, int top, int width, int height, int tw, int th, POINT *headerLocation);
		static void M137(int resizePoint, int *left, int *top, int *right, int *bottom, POINT *nowPoint, POINT *startMousePoint);
		static bool IsLineVisible(int indexTop, int indexBottom, int cell, int floor, int lineHeight, double visiblePercent);
	};
}
#endif