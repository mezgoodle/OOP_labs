#pragma once
class Shape
{
	protected:
		long xs1, ys1, xs2, ys2;
	public:
		void Set(long x1, long y1, long x2, long y2);
		virtual void Show(HDC) = 0;
	};
};

//---визначення методу Set---
void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}