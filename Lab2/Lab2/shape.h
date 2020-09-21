class Shape {
protected:
	long xs1, ys1, xs2, ys2;
	COLORREF color;
	BOOL isFill;
public:
	void Set(long, long, long, long);
	void SetColor(COLORREF);
	void SetFill(BOOL);
	virtual void Show(HDC) = 0;
};

class PointShape : public Shape
{
	void Show(HDC);
};

class LineShape : public Shape
{
	void Show(HDC);
};

class RectShape : public Shape
{
	void Show(HDC);
};

class EllipseShape : public Shape
{
	void Show(HDC);
};
