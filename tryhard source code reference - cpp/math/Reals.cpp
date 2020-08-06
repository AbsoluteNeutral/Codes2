#include "Reals.h"

namespace zg {
	float ToRad(float value) { return value * PI180; }
	float ToDeg(float value) { return value * INV_PI180; }

	//float
	//Trigonometric
	float sin	(float x)			{ return std::sinf(x);		}
	float cos	(float x)			{ return std::cosf(x);		}
	float tan	(float x)			{ return std::tanf(x);		}
	float asin	(float x)			{ return std::asinf(x);		}
	float acos	(float x)			{ return std::acosf(x);		}
	float atan	(float x)			{ return std::atanf(x);		}
	float atan2	(float y, float x)	{ return std::atan2f(y, x); }

	//Hyperbolic 
	float sinh	(float x) {	return std::sinh(x);	}
	float cosh	(float x) {	return std::cosh(x);	}
	float tanh	(float x) {	return std::tanh(x);	}
	float asinh	(float x) {	return std::asinh(x);	}
	float acosh	(float x) {	return std::acosh(x);	}
	float atanh	(float x) {	return std::atanh(x);	}

	//Power
	float pow	(float x, float exp)	{ return std::powf(x, exp); }
	float sqrt	(float x)				{ return std::sqrtf(x); }

	//double
	//Exponential and logarithmic
	double sin	(double x)			 { return std::sin(x);		}
	double cos	(double x)			 { return std::cos(x);		}
	double tan	(double x)			 { return std::tan(x);		}
	double asin	(double x)			 { return std::asin(x);		}
	double acos	(double x)			 { return std::acos(x);		}
	double atan	(double x)			 { return std::atan(x);		}
	double atan2(double y, double x) { return std::atan2(y, x); }

	//Hyperbolic 
	double sinh	(double x) { return std::sinh(x);	}
	double cosh	(double x) { return std::cosh(x);	}
	double tanh	(double x) { return std::tanh(x);	}
	double asinh(double x) { return std::asinh(x);	}
	double acosh(double x) { return std::acosh(x);	}
	double atanh(double x) { return std::atanh(x);	}

	//Power
	double pow	(double x, double exp)	{ return std::pow(x, exp); }
	double sqrt	(double x)				{ return std::sqrt(x); }

#pragma region __________________________________________________ExtraExternal	
	float Absolute(float val)	{ return val < 0.0f ? -val : val;	}
	double Absolute(double val)	{ return val < 0.0 ? -val : val;		}

	bool ApproxEqual(float a, float b, float epsilon) {
		return (std::fabs(a - b) < epsilon);
	}
	bool ApproxEqual(double a, double b, double epsilon) {
		return (std::fabs(a - b) < epsilon);
	}

	float Lerp(float start_, float end_, float time_) {
		// Imprecise start_, which does not guarantee v = v1 when t = 1, due to floating-point arithmetic error.
		// This form may be used when the hardware has a native fused multiply-add instruction.
		//return start_ + time_* (end_ - start_);

		// Precise method, which guarantees v = v1 when t = 1.
		float dttmp = 1.0f - time_;
		return dttmp * start_ + time_ * end_;
	}
	double Lerp(double start_, double end_, double time_) {
		//return start_ + time_* (end_ - start_);
		double dttmp = 1.0 - time_;
		return dttmp * start_ + time_ * end_;
	}

	// == Random generator
	float randomf(float value) {
		float bloat = value * 100.0f;
		return (rand() % (int)(bloat + 1) * 1.0f) / 100.0f;
	}
	// == Random Range generator
	float randomRangef(float min, float max) {
		float bloatmin = min * 10.0f;
		float bloatmax = max * 10.0f;
		return (bloatmin + rand() % (int)(bloatmax - bloatmin + 1)) / 10.0f;
	}
	int random1ToMax(int max) {
		return rand() % max + 1;
	}
	int randomRange(int min, int max) {
		max += 1;
		return rand() % (max - min) + min;
	}
	//http://www.rgba.org/articles/sfrand/sfrand.htm
	//Generates between -1 to 1
	static unsigned int mirand = 1;
	float sfrand() {
		unsigned int a;
		mirand *= 16807;
		a = (mirand & 0x007fffff) | 0x40000000;
		return(*((float*)&a) - 3.0f);
	}
	float sfrand(float min, float max) {
		return (sfrand() + 1) / 2 * (max - min) + min;
	}
	float QuinIn(float time, float begin, float final, float duration) {
		if (begin != final)
		{
			if (begin < 0)
			{
				final += begin * -1.0f;
			}
			else
				final -= begin;

			time /= duration;
			return final * time*time + begin;
		}
		else
			return begin;
	};
	float QuinOut(float time, float begin, float final, float duration) {
		if (begin != final)
		{
			if (begin < 0)
			{
				final += begin * -1.0f;
			}
			else
				final -= begin;

			float ts = (time /= duration)*time;
			float tc = ts * time;
			return begin + final * (tc*ts + -5 * ts*ts + 10 * tc + -10 * ts + 5 * time);
		}
		else
			return begin;
	}

	float BounceIn(float time, float begin, float final, float duration) {
		return final - BounceOut(duration - time, 0, final, duration) + begin;
	}

	float BounceOut(float time, float begin, float final, float duration) {
		if ((time /= duration) < (1 / 2.75f)) {
			return final * (7.5625f*time*time) + begin;
		}
		else if (time < (2 / 2.75f)) {
			float postFix = time -= (1.5f / 2.75f);
			return final * (7.5625f*(postFix)*time + .75f) + begin;
		}
		else if (time < (2.5 / 2.75)) {
			float postFix = time -= (2.25f / 2.75f);
			return final * (7.5625f*(postFix)*time + .9375f) + begin;
		}
		else {
			float postFix = time -= (2.625f / 2.75f);
			return final * (7.5625f*(postFix)*time + .984375f) + begin;
		}
	}

	float SmoothDampf(float current, float target, float currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
	{
		smoothTime = MAX2(0.0001f, smoothTime);
		float num = 2.0f / smoothTime;
		float num2 = num * deltaTime;
		float num3 = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
		float num4 = current - target;
		float num5 = target;
		float num6 = maxSpeed * smoothTime;
		num4 = zg::Clamp(num4, -num6, num6);
		target = current - num4;
		float num7 = (currentVelocity + num * num4) * deltaTime;
		currentVelocity = (currentVelocity - num * num7) * num3;
		float num8 = target + (num4 + num7) * num3;
		if (num5 - current > 0.0f == num8 > num5)
		{
			num8 = num5;
			currentVelocity = (num8 - num5) / deltaTime;
		}
		return num8;
	}


#pragma endregion

}//namespace zg
