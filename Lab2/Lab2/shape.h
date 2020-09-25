class Shape // Shape class for figures
{
protected:
	long xs1, ys1, xs2, ys2;
public:
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC) = 0;
};

class PointShape : public Shape
{
public:
	void Show(HDC);
};

class LineShape : public Shape
{
public:
	void Show(HDC);
};

class RectShape : public Shape
{
public:
	void Show(HDC);
};

class EllipseShape : public Shape
{
public:
	void Show(HDC);
};