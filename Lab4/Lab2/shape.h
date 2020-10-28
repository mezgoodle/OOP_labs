class Shape {
protected:
	long xs1, ys1, xs2, ys2;
public:
	~Shape();
	void Set(long, long, long, long);
	virtual void Show(HDC) = 0;
	virtual Shape* Copy() = 0;
};

class PointShape : public Shape
{
	void Show(HDC);
	virtual Shape* Copy();
};

class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Copy();
};

class RectShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Copy();
};

class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Copy();
};

class PointLineShape : public LineShape, public EllipseShape {
public:
	void Show(HDC);
	virtual Shape* Copy();
};

class CubeShape : public RectShape, public LineShape {
public:
	void Show(HDC);
	virtual Shape* Copy();
};
