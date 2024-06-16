#pragma once

/*namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			canvas = this->CreateGraphics();
		}
		void drawAxes(int, int);


	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
	private:
		Graphics^ canvas;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(684, 661);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
	
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		
		
	}
	private: System::Void Form1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		canvas = e->Graphics;
		
		//task2();
		//task3();

	}	

	};
	void MyForm::drawAxes(int x, int y) {
			canvas->Clear(Color::Blue);
			
		}  
	
}*/
#pragma once
#include <cmath>
namespace Project2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			xbegSh = -100;
			ybegSh = Height / 2 - 100 - 35;
			xSh = 0;
			ySh = 0;
			hi = 2;
			angle = 0;
			flour = 0;
			canvas = this->CreateGraphics();
			pen = gcnew Pen(Color::Black);
			timer1->Interval = 100;
			timer1->Enabled = false;
			moving = false;
			rigth = true;
		}

		void drawPoezd();
		void drawBackground();
		void drawSamolet();
		void drawAxes(int, int);
		void task1();
		void task2();
		void task3();

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:
	private:

	private:
		Graphics^ canvas;
		Pen^ pen;
		int xbegSh, ybegSh, xSh, ySh, hi, flour;
		bool moving, rigth;
		float angle;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(608, 546);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->TransparencyKey = System::Drawing::Color::White;
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::Form1_Paint);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::Form1_KeyPress);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		angle = angle + 1;
		if (angle == 360) angle = 0;
		if (flour < 80) {
			flour++;
		}
		if (rigth) {
			xbegSh++;
			ybegSh++;
		}
		else {
			xbegSh--;
			ybegSh--;
		}
		if (xbegSh == this->Width - 200 && rigth) {
			rigth = false;
		}
		if (!rigth && xbegSh == -50) {
			rigth = true;
		}
		Refresh();
	}
	private: System::Void Form1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		canvas = e->Graphics;
		//task1();
		task2();
		//task3();

	}
	private: System::Void Form1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == 'y') {
			System::Media::SoundPlayer^ spl = gcnew System::Media::SoundPlayer();
			spl->SoundLocation = "самолЄт.wav";
			moving = !moving;
			MyForm::Refresh();
			if (moving) {
				spl->Load();
				spl->Play();
			}
			else {
				spl->Stop();
			}
		}
	}
	};

	void MyForm::drawPoezd() {
		canvas->Clear(Color::WhiteSmoke);
		System::Drawing::Brush^ br = Brushes::Black;
		Rectangle wall(100, 199, 200, 100);
		br = Brushes::MediumBlue;
		canvas->FillRectangle(br, wall);
		canvas->DrawRectangle(pen, wall);
		Rectangle wall1(300, 120, 70, 179);
		br = Brushes::MediumBlue;
		canvas->FillRectangle(br, wall1);
		canvas->DrawRectangle(pen, wall1);
		Rectangle wall2(317, 140, 35, 45);
		br = Brushes::CornflowerBlue;
		canvas->FillRectangle(br, wall2);
		canvas->DrawRectangle(pen, wall2);
		Rectangle dop1(240, 300, 40, 40);
		Rectangle dop2(280, 300, 40, 40);
		Rectangle dop3(120, 300, 40, 40);
		Rectangle dop4(200, 300, 40, 40);
		Rectangle dop5(160, 300, 40, 40);
		Rectangle dop6(320, 300, 40, 40);

		br = Brushes::Black;
		canvas->FillEllipse(br, dop2);
		canvas->DrawEllipse(pen, dop2);
		br = Brushes::Black;
		canvas->FillEllipse(br, dop1);
		canvas->DrawEllipse(pen, dop1);
		br = Brushes::Black;
		canvas->FillEllipse(br, dop3);
		canvas->DrawEllipse(pen, dop3);
		br = Brushes::Black;
		canvas->FillEllipse(br, dop4);
		canvas->DrawEllipse(pen, dop4);
		br = Brushes::Black;
		canvas->FillEllipse(br, dop5);
		canvas->DrawEllipse(pen, dop5);
		br = Brushes::Black;
		canvas->FillEllipse(br, dop6);
		canvas->DrawEllipse(pen, dop6);
		br = Brushes::Black;
		array <System::Drawing::Point>^ triangle = gcnew array<Point>(4);
		triangle[0] = Point(120, 200);
		triangle[1] = Point(110, 150);
		triangle[2] = Point(180, 150);
		triangle[3] = Point(170, 200);
		canvas->FillPolygon(br, triangle);
		Rectangle op1(164, 74, 40, 40);
		Rectangle op2(134, 105, 60, 30);
		Rectangle op3(187, 65, 20, 25);
		Rectangle op4(208, 45, 30, 30);
		br = Brushes::Gray;
		canvas->FillEllipse(br, op2);
		canvas->DrawEllipse(pen, op2);
		br = Brushes::Gray;
		canvas->FillEllipse(br, op1);
		canvas->DrawEllipse(pen, op1);
		br = Brushes::Gray;
		canvas->FillEllipse(br, op3);
		canvas->DrawEllipse(pen, op3);
		br = Brushes::Gray;
		canvas->FillEllipse(br, op4);
		canvas->DrawEllipse(pen, op4);
		Rectangle wall3(370, 240, 10, 15);
		br = Brushes::Beige;
		canvas->FillRectangle(br, wall3);
		canvas->DrawRectangle(pen, wall3);
	}

	void MyForm::drawSamolet() {

		canvas->Clear(Color::WhiteSmoke);
		System::Drawing::Brush^ br = Brushes::LightCoral;

		array <System::Drawing::Point>^ triangle = gcnew array<Point>(4);
		triangle[0] = Point(100 + xbegSh, 80);
		triangle[1] = Point(60 + xbegSh, 160);
		triangle[2] = Point(260 + xbegSh, 160);
		triangle[3] = Point(200 + xbegSh, 80);
		canvas->FillPolygon(br, triangle);
		array <System::Drawing::Point>^ triangle1 = gcnew array<Point>(3);
		if (rigth) {
			triangle1[0] = Point(95 + xbegSh, 80);
			triangle1[1] = Point(50 + xbegSh, 160);
			triangle1[2] = Point(48 + xbegSh, 30);
		}
		else {
			triangle1[0] = Point(205 + xbegSh, 80);
			triangle1[1] = Point(275 + xbegSh, 160);
			triangle1[2] = Point(260 + xbegSh, 30);
		}
		canvas->FillPolygon(br, triangle1);
		array <System::Drawing::Point>^ triangle2 = gcnew array<Point>(3);
		if (rigth) {
			triangle2[0] = Point(170 + xbegSh, 70);
			triangle2[1] = Point(110 + xbegSh, 70);
			triangle2[2] = Point(110 + xbegSh, 20);
		}
		else {
			triangle2[0] = Point(170 + xbegSh, 70);
			triangle2[1] = Point(110 + xbegSh, 70);
			triangle2[2] = Point(170 + xbegSh, 20);
		}
		canvas->FillPolygon(br, triangle2);

		array <System::Drawing::Point>^ triangle3 = gcnew array<Point>(3);

		if (rigth) {
			triangle3[0] = Point(170 + xbegSh, 170);
			triangle3[1] = Point(110 + xbegSh, 170);
			triangle3[2] = Point(110 + xbegSh, 230);
		}
		else {
			triangle3[0] = Point(170 + xbegSh, 170);
			triangle3[1] = Point(110 + xbegSh, 170);
			triangle3[2] = Point(170 + xbegSh, 230);
		}
		canvas->FillPolygon(br, triangle3);
		Rectangle op1(140 + xbegSh, 95, 30, 30);
		Rectangle op2(95 + xbegSh, 95, 30, 30);
		Rectangle op3(180 + xbegSh, 95, 30, 30);
		br = Brushes::WhiteSmoke;
		canvas->FillEllipse(br, op2);
		canvas->DrawEllipse(pen, op2);
		br = Brushes::WhiteSmoke;
		canvas->FillEllipse(br, op1);
		canvas->DrawEllipse(pen, op1);
		br = Brushes::WhiteSmoke;
		canvas->FillEllipse(br, op3);
		canvas->DrawEllipse(pen, op3);
	}

	void MyForm::drawBackground() {
		System::Drawing::Brush^ br = Brushes::SkyBlue;
		canvas->FillRectangle(br, 0, 0, 608, 546);
		br = Brushes::DarkGreen;
		canvas->FillEllipse(br, -100, 350, 608, 150);

	}

	void MyForm::task1() {
		drawPoezd();
		//drawBackground();

	}

	double fx(double x) {

		return log10(x);
	}


	void MyForm::drawAxes(int x, int y) {
		canvas->Clear(Color::FromArgb(255, 229, 247, 247));
		int sdvig_v_levo = 20;
		int sdvig_v_niz = 30;

		int shagX = 25;
		int countX = x / shagX - 1;

		int shagY = 25;
		int countY = y / shagY - 1;

		pen->Color = Color::FromArgb(150, 117, 117, 117);
		// сетка 
		// x
		for (int i = 0; i < countX; i++)
		{
			canvas->DrawLine(pen, x + i * shagX, 0, x + i * shagX, Height);
			canvas->DrawLine(pen, x - i * shagX, 0, x - i * shagX, Height);
		}
		// y
		for (int i = 0; i < countY; i++)
		{
			canvas->DrawLine(pen, 0, y + i * shagY, Width, y + i * shagY);
			canvas->DrawLine(pen, 0, y - i * shagY, Width, y - i * shagY);
		}
		pen->Color = Color::Black;

		//x
		canvas->DrawLine(pen, 0, y, Width - sdvig_v_levo, y);
		//y
		canvas->DrawLine(pen, x, 0 + sdvig_v_niz, x, Height);

		//стрелка x
		canvas->DrawLine(pen, Width - sdvig_v_levo, y, Width - sdvig_v_levo - 15, y - 7);
		canvas->DrawLine(pen, Width - sdvig_v_levo, y, Width - sdvig_v_levo - 15, y + 7);
		//стрелка у
		canvas->DrawLine(pen, x, 0 + sdvig_v_niz, x - 7, 15 + sdvig_v_niz);
		canvas->DrawLine(pen, x, 0 + sdvig_v_niz, x + 7, 15 + sdvig_v_niz);
	}

	void MyForm::task2() {

		const double max = 1.0;
		const int pointsCount = 200;
		const double step = 0.01;
		const int xScale = 120;
		const int yScale = 120;
		 int xBias = 800;
		 int yBias = 800;
		drawAxes(xBias, yBias);
		//drawAxes(xBias, yBias+40);
		/*array<Point>^ points1 = gcnew array<Point>(pointsCount);
		array<Point>^ points2 = gcnew array<Point>(pointsCount);
		int i = 0;
		for (double x = -1; x <= max; x += step, i++) {
			double y1 = fx(x);

			points1[i] = Point(static_cast<int>(x * xScale) + xBias, yBias - static_cast<int>(y1 * yScale));

		}

		Pen^ p1 = gcnew Pen{ Color::Red };

		canvas->DrawCurve(p1, points1);*/

	}

	void MyForm::task3() {
		DoubleBuffered = true;
		timer1->Enabled = moving;
		//drawBackground();
		drawSamolet();



	}
}
