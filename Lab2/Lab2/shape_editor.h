#pragma once
class ShapeObjectsEditor {
	private:

	public:
		ShapeObjectsEditor(void);
		~ShapeObjectsEditor();
		void StartPointEditor(...);
		void StartLineEditor(...);
		void StartRectEditor(...);
		void StartEllipseEditor(...);
		void OnLBdown(HWND);
		void OnLBup(HWND);
		void OnMouseMove(HWND);
		void OnPaint(HWND);
		void OnInitMenuPopup(HWND, WPARAM); //відповідно варіанту завдання
};