#pragma once
#include <iostream>
#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double a_1 = exp(-M_PI / 4.0) - exp(M_PI / 4.0);
double a_2 = (exp(-M_PI / 4.0) + exp(M_PI / 4.0)) * 4 * sqrt(2) / M_PI;

double b_1 = exp(-pow(M_PI, 2) / 8. / sqrt(2)) - exp(pow(M_PI, 2) / 8. / sqrt(2.) - M_PI / sqrt(2.));
double b_2 = -(exp(pow(M_PI, 2) / 8. / sqrt(2) - M_PI / sqrt(2)) + exp(-pow(M_PI, 2) / 8. / sqrt(2.)));

double p_1 = 8 * sqrt(2.) / pow(M_PI, 2) * (1 - exp(pow(M_PI, 2) / 8. / sqrt(2.) - M_PI / 2. / sqrt(2.))) - 1;
double p_2 = -8 * sqrt(2.) / pow(M_PI, 2) * exp(pow(M_PI, 2) / 8. / sqrt(2.) - M_PI / 2. / sqrt(2.));


double C_2 = (-p_2 - a_2 / a_1 * p_1) / (a_2 / a_1 * b_1 + b_2);
double c_1 = (C_2 * b_1 + p_1) / a_1;
double c_2 = -c_1;
double C_1 = -8 * sqrt(2) / pow(M_PI, 2) * exp(-M_PI / 2 / sqrt(2)) - C_2 * exp(-M_PI / sqrt(2));



// Истинное решение для тестовой задачи, найдено аналитическое решение
double test_true_trajectory(double x) {
	double c1 = c_1;
	double c2 = c_2;
	double C1 = C_1;
	double C2 = C_2;

	if (x < M_PI / 4)
		return c1 * exp(-x) + c2 * exp(x) + 1;
	else
		return C1 * exp(M_PI * x / (2 * sqrt(2))) + C2 * exp(-M_PI * x / (2 * sqrt(2))) + 8 * sqrt(2) / pow(M_PI, 2);
}


// Коэффициент разностной схемы для тестовой задачи
double a_i(double h, double breaking_point, double x_i_minus_05, double x_i_minus_1, double x_i) {
	if (x_i <= breaking_point)
		return 1.;
	if (x_i_minus_1 >= breaking_point)
		return 0.5;
	if(x_i >= breaking_point && x_i_minus_1 <= breaking_point)
		return pow(1./h*(breaking_point - x_i_minus_1) + 2. * (x_i - breaking_point) / h, -1);
}

// Коэффициент разностной схемы для основной задачи
double a_i_main(double h, double breaking_point, double x_i_minus_05, double x_i_minus_1, double x_i) {
	if (x_i <= breaking_point)
		return pow(((1 / sin(x_i_minus_1) + 1 / sin(x_i) + 4 / sin(x_i_minus_05))) / sqrt(2) / 6, -1);
	else if (x_i_minus_1 >= breaking_point)
		return pow((1 / pow(cos(x_i_minus_1), 2) + 1 / pow(cos(x_i), 2) + 4 / pow(cos(x_i_minus_05), 2)) / 6, -1);
	else
		return pow(((breaking_point - x_i_minus_1) / sqrt(2) / 6 * (1 / sin(x_i_minus_1) + 4 / sin(x_i_minus_1 / 2 + breaking_point / 2) + 1 / sin(breaking_point)))
			+ (x_i - breaking_point) / 6 * (1 / pow(cos(breaking_point), 2) + 1 / pow(cos(x_i), 2) + 4 / pow(cos(x_i/2+breaking_point/2), 2)), -1) * h;
}

// Коэффициент разностной схемы для тестовой задачи
double d_i(double h, double breaking_point, double x_i_minus_05, double x_i_plus_05, double x_i) {
	if (x_i_plus_05 <= breaking_point)
		return 1.;
	if (x_i_minus_05 >= breaking_point)
		return pow(M_PI, 2) / 16.;
	if (x_i_plus_05 >= breaking_point && x_i_minus_05 <= breaking_point)
		return 1. / h * (breaking_point - x_i_minus_05) + (pow(M_PI, 2) / 16. / h) * (x_i_plus_05 - breaking_point);
}

// Коэффициент разностной схемы для основной задачи
double d_i_main(double h, double breaking_point, double x_i_minus_05, double x_i_plus_05, double x_i) {
	if (x_i_plus_05 <= breaking_point)
		return 1.;
	else if (x_i_minus_05 >= breaking_point)
		return (pow(x_i_minus_05, 2) + 4 * pow(x_i, 2) + pow(x_i_plus_05, 2)) / 6;
	else
		return (breaking_point - x_i_minus_05) / h + (pow(breaking_point, 2) + 4 * pow(breaking_point / 2 + x_i_plus_05 / 2, 2) + pow(x_i_plus_05, 2)) / 6 / h;
}

// Коэффициент разностной схемы для тестовой задачи
double fi_i(double h, double breaking_point, double x_i_minus_05, double x_i_plus_05, double x_i) {
	if (x_i_plus_05 <= breaking_point)
		return 1.;
	if (x_i_minus_05 >= breaking_point)
		return 1./sqrt(2);
	if(x_i_plus_05 >= breaking_point && x_i_minus_05 <= breaking_point)
		return 1. / h * (breaking_point - x_i_minus_05) + 1. / sqrt(2) / h * (x_i_plus_05 - breaking_point);
}

// Коэффициент разностной схемы для основной задачи
double fi_i_main(double h, double breaking_point, double x_i_minus_05, double x_i_plus_05, double x_i) {
	if (x_i_plus_05 <= breaking_point)
		return (sin(2 * x_i_minus_05) + 4 * sin(2 * x_i) + sin(2 * x_i_plus_05)) / 6;
	else if (x_i_minus_05 >= breaking_point)
		return (cos(x_i_minus_05) + 4 * cos(x_i) + cos(x_i_plus_05)) / 6;
	else
		return (breaking_point - x_i_minus_05) / 6. / h * (sin(2 * x_i_minus_05) + 4 * sin(x_i_minus_05 + breaking_point) + sin(2 * breaking_point)) +
		(x_i_plus_05 - breaking_point) / 6. / h * (cos(x_i_plus_05) + 4 * cos(breaking_point / 2 + x_i_plus_05 / 2) + cos(breaking_point));
}

// Коэффициент из метода прогонки для тестовой задачи
double A_i(std::size_t i, double h, double breaking_point) {
	double ai = a_i(h, breaking_point, (i - 0.5) * h, (i - 1) * h, i * h);
	return ai / pow(h,2);
}
// Коэффициент из метода прогонки для основной задачи
double A_i_main(std::size_t i, double h, double breaking_point) {
	double ai = a_i_main(h, breaking_point, (i - 0.5) * h, (i - 1) * h, i * h);
	return ai / pow(h, 2);
}
// Коэффициент из метода прогонки для тестовой задачи
double B_i(std::size_t i, double h, double breaking_point) {
	std::size_t new_i = i + 1;
	double ai_plus_1 = a_i(h, breaking_point, (new_i - 0.5) * h, (new_i - 1) * h, new_i * h);
	return ai_plus_1 / pow(h, 2);
}
// Коэффициент из метода прогонки для основной задачи
double B_i_main(std::size_t i, double h, double breaking_point) {
	std::size_t new_i = i + 1;
	double ai_plus_1 = a_i_main(h, breaking_point, (new_i - 0.5) * h, (new_i - 1) * h, new_i * h);
	return ai_plus_1 / pow(h, 2);
}
// Коэффициент из метода прогонки для тестовой задачи
double C_i(std::size_t i, double h, double breaking_point) {
	double ai = a_i(h, breaking_point, (i - 0.5) * h, (i - 1) * h, i * h);
	double di = d_i(h, breaking_point, (i - 0.5) * h, (i + 0.5) * h, i * h);
	std::size_t new_i = i + 1;
	double ai_plus_1 = a_i(h, breaking_point, (new_i - 0.5) * h, (new_i - 1) * h, new_i * h);
	return (1 / pow(h, 2) * (ai + ai_plus_1) + di);
}
// Коэффициент из метода прогонки для основной задачи
double C_i_main(std::size_t i, double h, double breaking_point) {
	double ai = a_i_main(h, breaking_point, (i - 0.5) * h, (i - 1) * h, i * h);
	double di = d_i_main(h, breaking_point, (i - 0.5) * h, (i + 0.5) * h, i * h);
	std::size_t new_i = i + 1;
	double ai_plus_1 = a_i_main(h, breaking_point, (new_i - 0.5) * h, (new_i - 1) * h, new_i * h);
	return (1. / pow(h, 2) * (ai + ai_plus_1) + di);
}


// Метод прогонки для тестовой задачи
std::vector<double> running(std::size_t n, double mu1, double mu2, double breaking_point) {
	std::vector<double> result(n + 1);
	result[0] = mu1;	 //Граничное условие левое
	result[n] = mu2;	 //Граничное условие правое
	std::vector<double> alpha(n), beta(n);
	alpha[0] = 0;
	beta[0] = 1;
	double h = 1. / n;

	// Прямой ход прогонки 
	for (std::size_t i = 1; i < n; i++) {
		double Ai = A_i(i, h, breaking_point);
		double Bi = B_i(i, h, breaking_point);
		double Ci = C_i(i, h, breaking_point);
		double fii = fi_i(h, breaking_point, (i - 0.5) * h, (i + 0.5) * h, i * h);
		alpha[i] = Bi / (Ci - Ai * alpha[i - 1]);
		beta[i] = (fii + Ai * beta[i - 1]) / (Ci - Ai * alpha[i - 1]);
	}

	// Обратный ход прогонки
	for (std::size_t i = n - 1; i > 0; i--)
		result[i] = alpha[i] * result[i + 1] + beta[i];

	return result;
}

// Метод прогонки для основной задачи
std::vector<double> running_main(std::size_t n, double mu1, double mu2, double breaking_point) {
	std::vector<double> result(n + 1);
	result[0] = mu1;	//Граничное условие левое
	result[n] = mu2;	//Граничное условие правое
	std::vector<double> alpha(n), beta(n);
	alpha[0] = 0;
	beta[0] = 1;
	double h = 1. / n;

	// Прямой ход прогонки 
	for (std::size_t i = 1; i < n; i++) {
		double Ai = A_i_main(i, h, breaking_point);
		double Bi = B_i_main(i, h, breaking_point);
		double Ci = C_i_main(i, h, breaking_point);
		double fii = fi_i_main(h, breaking_point, (i - 0.5) * h, (i + 0.5) * h, i * h);
		alpha[i] = Bi / (Ci - Ai * alpha[i - 1]);
		beta[i] = (fii + Ai * beta[i - 1]) / (Ci - Ai * alpha[i - 1]);
	}

	// Обратный ход прогонки
	for (std::size_t i = n - 1; i > 0; i--)
		result[i] = alpha[i] * result[i + 1] + beta[i];

	return result;
}





namespace Graph {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ZedGraph;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: ZedGraph::ZedGraphControl^  zedGraphControl1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  I;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  x_i;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  u_i;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ v_i;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ u_i_v_i;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ узла;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label7;





	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->узла = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->x_i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->u_i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->v_i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->u_i_v_i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->zedGraphControl1->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->zedGraphControl1->Location = System::Drawing::Point(38, 30);
			this->zedGraphControl1->Name = L"zedGraphControl1";
			this->zedGraphControl1->ScrollGrace = 0;
			this->zedGraphControl1->ScrollMaxX = 0;
			this->zedGraphControl1->ScrollMaxY = 0;
			this->zedGraphControl1->ScrollMaxY2 = 0;
			this->zedGraphControl1->ScrollMinX = 0;
			this->zedGraphControl1->ScrollMinY = 0;
			this->zedGraphControl1->ScrollMinY2 = 0;
			this->zedGraphControl1->Size = System::Drawing::Size(501, 327);
			this->zedGraphControl1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(656, 379);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(142, 29);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Решение";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->узла, this->x_i,
					this->u_i, this->v_i, this->u_i_v_i
			});
			this->dataGridView1->Location = System::Drawing::Point(559, 30);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->Size = System::Drawing::Size(872, 327);
			this->dataGridView1->TabIndex = 2;
			// 
			// узла
			// 
			this->узла->HeaderText = L"№ узла";
			this->узла->Name = L"узла";
			this->узла->ReadOnly = true;
			this->узла->Width = 70;
			// 
			// x_i
			// 
			this->x_i->HeaderText = L"x_i";
			this->x_i->Name = L"x_i";
			this->x_i->ReadOnly = true;
			// 
			// u_i
			// 
			this->u_i->HeaderText = L"u_i";
			this->u_i->Name = L"u_i";
			this->u_i->ReadOnly = true;
			this->u_i->Width = 150;
			// 
			// v_i
			// 
			this->v_i->HeaderText = L"v_i";
			this->v_i->Name = L"v_i";
			this->v_i->ReadOnly = true;
			this->v_i->Width = 150;
			// 
			// u_i_v_i
			// 
			this->u_i_v_i->HeaderText = L"u_i - v_i";
			this->u_i_v_i->Name = L"u_i_v_i";
			this->u_i_v_i->ReadOnly = true;
			this->u_i_v_i->Width = 150;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(35, 434);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(202, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"задача решена с погрешностью ε_1 = \r\n";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(35, 454);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(428, 39);
			this->label2->TabIndex = 5;
			this->label2->Text = L"максимальное отклонение аналитического и численного решений наблюдается в \r\n\r\nточ"
				L"ке х  = \r\n";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(35, 408);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(359, 26);
			this->label3->TabIndex = 7;
			this->label3->Text = L"задача должна быть решена с погрешностью не более ε = 0.5 * 10^-6\r\n\r\n";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(502, 379);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(61, 20);
			this->textBox3->TabIndex = 8;
			this->textBox3->Text = L"10";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(880, 379);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(142, 29);
			this->button3->TabIndex = 14;
			this->button3->Text = L"Решение";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(880, 434);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(142, 29);
			this->button4->TabIndex = 15;
			this->button4->Text = L"График погрешности";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(243, 431);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(173, 20);
			this->textBox6->TabIndex = 16;
			this->textBox6->Text = L"10";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(656, 434);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(142, 29);
			this->button2->TabIndex = 17;
			this->button2->Text = L"График погрешности";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(688, 363);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(93, 13);
			this->label4->TabIndex = 18;
			this->label4->Text = L"Тестовая задача";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(902, 363);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(95, 13);
			this->label5->TabIndex = 19;
			this->label5->Text = L"Основная задача";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(35, 382);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(470, 26);
			this->label6->TabIndex = 20;
			this->label6->Text = L"Для решения тестовой задачи использована равномерная сетка с  числом разбиений n "
				L"= \r\n\r\n";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(101, 473);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(136, 20);
			this->textBox4->TabIndex = 21;
			this->textBox4->Text = L"1";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(35, 505);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(223, 13);
			this->label7->TabIndex = 22;
			this->label7->Text = L"Граничные значения сетки x_0 = 0, x_n = 1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1443, 694);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->zedGraphControl1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// График для отображения численного решения тестовой задачи и истинного решения
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		GraphPane^ panel = zedGraphControl1->GraphPane;
		panel->CurveList->Clear();
		PointPairList^ solve_list = gcnew ZedGraph::PointPairList();
		PointPairList^ true_list = gcnew ZedGraph::PointPairList();

		// Интервал, где есть данные
		double xmin = 0;
		double xmax = 1;

		double n = Convert::ToDouble(textBox3->Text);


		double xmin_limit = xmin - 0.1;
		double xmax_limit = xmax + 0.1;

		textBox6->Clear();
		textBox4->Clear();

		// Список точек
		int i = 0;
		double h = 1. / n;

		double m1 = 1;
		double m2 = 0;
		double max_olp = 0;
		double max_olp_x = 0;

		std::vector<double> temp = running(n, m1, m2, M_PI / 4);

		dataGridView1->Rows->Clear();
		for (double x = xmin; x <= xmax; x += h)
		{
			//Добавление на график
			solve_list->Add(x, temp[i]);
			true_list->Add(x, test_true_trajectory(x));
			//Печать в таблицу
			dataGridView1->Rows->Add();
			dataGridView1->Rows[i]->Cells[0]->Value = i;
			dataGridView1->Rows[i]->Cells[1]->Value = x;//floor(temp[i] * 1000) / 1000;
			dataGridView1->Rows[i]->Cells[2]->Value = test_true_trajectory(x);// abs(temp[i] - test_true_trajectory(x));
			dataGridView1->Rows[i]->Cells[3]->Value = temp[i];
			dataGridView1->Rows[i]->Cells[4]->Value = abs(temp[i] - test_true_trajectory(x));
			if (abs(temp[i] - test_true_trajectory(x)) > max_olp) {
				max_olp = abs(temp[i] - test_true_trajectory(x));
				max_olp_x = x;
			}
			i++;
		}
		LineItem^ Curve1 = panel->AddCurve("Истинное решение u_i", true_list, Color::Red, SymbolType::Plus);
		LineItem^ Curve2 = panel->AddCurve("Численное решение v_i", solve_list, Color::Blue, SymbolType::Plus);

		textBox6->AppendText(Convert::ToString(max_olp));
		textBox4->AppendText(Convert::ToString(max_olp_x));

		// Устанавливаем интересующий нас интервал по оси X
		panel->XAxis->Scale->Min = xmin_limit;
		panel->XAxis->Scale->Max = xmax_limit;
		/*
				// Устанавливаем интересующий нас интервал по оси Y
				panel->YAxis->Scale->Min = ymin_limit;
				panel->YAxis->Scale->Max = ymax_limit;
		*/
		// Вызываем метод AxisChange (), чтобы обновить данные об осях. 
		// В противном случае на рисунке будет показана только часть графика, 
		// которая умещается в интервалы по осям, установленные по умолчанию
		zedGraphControl1->AxisChange();
		// Обновляем график
		zedGraphControl1->Invalidate();
	}

// График погрешности для тестовой задачи
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	GraphPane^ panel = zedGraphControl1->GraphPane;
	panel->CurveList->Clear();
	PointPairList^ list = gcnew ZedGraph::PointPairList();

	textBox6->Clear();
	textBox4->Clear();

	// Интервал, где есть данные
	double xmin = 0;
	double xmax = 1;

	double n = Convert::ToDouble(textBox3->Text);


	double xmin_limit = xmin - 0.1;
	double xmax_limit = xmax + 0.1;

	// Список точек
	int i = 0;
	double h = 1. / n;

	double m1 = 1;
	double m2 = 0;
	double max_olp = 0;
	double max_olp_x = 0;

	std::vector<double> temp = running(n, m1, m2, M_PI / 4);

	dataGridView1->Rows->Clear();
	for (double x = xmin; x <= xmax; x += h)
	{
		//Добавление на график
		list->Add(x, abs(temp[i] - test_true_trajectory(x)));
		//Печать в таблицу
		dataGridView1->Rows->Add();
		dataGridView1->Rows[i]->Cells[0]->Value = i;
		dataGridView1->Rows[i]->Cells[1]->Value = x;//floor(temp[i] * 1000) / 1000;
		dataGridView1->Rows[i]->Cells[2]->Value = test_true_trajectory(x);// abs(temp[i] - test_true_trajectory(x));
		dataGridView1->Rows[i]->Cells[3]->Value = temp[i];
		dataGridView1->Rows[i]->Cells[4]->Value = abs(temp[i] - test_true_trajectory(x));
		if (abs(temp[i] - test_true_trajectory(x)) > max_olp) {
			max_olp = abs(temp[i] - test_true_trajectory(x));
			max_olp_x = x;
		}
		i++;
	}
	LineItem^ Curve1 = panel->AddCurve("График погрешности", list, Color::Blue, SymbolType::None);

	textBox6->AppendText(Convert::ToString(max_olp));
	textBox4->AppendText(Convert::ToString(max_olp_x));

	panel->XAxis->Scale->Min = xmin_limit;
	panel->XAxis->Scale->Max = xmax_limit;

	zedGraphControl1->AxisChange();
	zedGraphControl1->Invalidate();
}


// График для отображения численного решения основной задачи с сеткой n и 2n
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {

	GraphPane^ panel = zedGraphControl1->GraphPane;
	panel->CurveList->Clear();
	PointPairList^ f1_list = gcnew ZedGraph::PointPairList();
	PointPairList^ f2_list = gcnew ZedGraph::PointPairList();

	// Интервал, где есть данные
	double xmin = 0;
	double xmax = 1;

	double n = Convert::ToDouble(textBox3->Text);
	double xmin_limit = xmin - 0.1;
	double xmax_limit = xmax + 0.1;

	textBox6->Clear();
	textBox4->Clear();
	/*
			double ymin_limit = -1.0;
			double ymax_limit = 100.0;
	*/
	// Список точек
	double h = 1. / n;

	double m1 = 1;
	double m2 = 0;
	double max_olp = 0;
	double max_olp_x = 0;

	std::vector<double> temp_h = running_main(n, m1, m2, M_PI / 4);
	std::vector<double> temp_2h = running_main(2*n, m1, m2, M_PI / 4);
	
	dataGridView1->Rows->Clear();
	for (std::size_t i = 0; i <= 2*n; i++)
	{
		//Добавление на график

		if (i % 2 == 0) f1_list->Add(i*h/2, temp_h[i/2]);
		f2_list->Add(i * h /2, temp_2h[i]);
		//Печать в таблицу
		dataGridView1->Rows->Add();
		dataGridView1->Rows[i]->Cells[0]->Value = i;
		dataGridView1->Rows[i]->Cells[1]->Value = i*h/2;
		dataGridView1->Rows[i]->Cells[2]->Value = 0;
		dataGridView1->Rows[i]->Cells[3]->Value = 0;
		if (i % 2 == 0) {
			dataGridView1->Rows[i]->Cells[4]->Value = abs(temp_h[i / 2] - temp_2h[i]);
			if (abs(temp_h[i / 2] - temp_2h[i]) > max_olp) {
				max_olp = abs(temp_h[i / 2] - temp_2h[i]);
				max_olp_x = i * h/2;
			}
		}
		else
			dataGridView1->Rows[i]->Cells[4]->Value = "";
	}
	LineItem^ Curve1 = panel->AddCurve("h(x)", f1_list, Color::Red, SymbolType::Plus);
	LineItem^ Curve2 = panel->AddCurve("2h(x)", f2_list, Color::Blue, SymbolType::Plus);


	textBox6->AppendText(Convert::ToString(max_olp));
	textBox4->AppendText(Convert::ToString(max_olp_x));

	// Устанавливаем интересующий нас интервал по оси X
	panel->XAxis->Scale->Min = xmin_limit;
	panel->XAxis->Scale->Max = xmax_limit;
	/*
			// Устанавливаем интересующий нас интервал по оси Y
			panel->YAxis->Scale->Min = ymin_limit;
			panel->YAxis->Scale->Max = ymax_limit;
	*/
	// Вызываем метод AxisChange (), чтобы обновить данные об осях. 
	// В противном случае на рисунке будет показана только часть графика, 
	// которая умещается в интервалы по осям, установленные по умолчанию
	zedGraphControl1->AxisChange();
	// Обновляем график
	zedGraphControl1->Invalidate();
}

// График погрешности для основной задачи (пока не реализован)
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	/*

	GraphPane^ panel = zedGraphControl1->GraphPane;
	panel->CurveList->Clear();
	PointPairList^ f1_list = gcnew ZedGraph::PointPairList();
	PointPairList^ f2_list = gcnew ZedGraph::PointPairList();

	// Интервал, где есть данные
	double xmin = 0;
	double xmax = 1;

	std::size_t n = Convert::ToInt64(textBox3->Text);


	double xmin_limit = xmin - 0.1;
	double xmax_limit = xmax + 0.1;

	int i = 0;
	double h = 1. / n;

	double m1 = 1;
	double m2 = 0;


	std::vector<double> temp = running_main(n, m1, m2, M_PI / 4);

	dataGridView1->Rows->Clear();
	for (double x = xmin; x <= xmax; x += h)
	{
		//Добавление на график
		f1_list->Add(x, temp[i]);
		//Печать в таблицу
		dataGridView1->Rows->Add();
		dataGridView1->Rows[i]->Cells[0]->Value = x;
		dataGridView1->Rows[i]->Cells[1]->Value = floor(temp[i] * 1000) / 1000;
		dataGridView1->Rows[i]->Cells[2]->Value = 0;/*abs(temp[i] - test_true_trajectory(x));
		i++;
	}
	LineItem^ Curve1 = panel->AddCurve("test_true_trajectory(x)", f1_list, Color::Red, SymbolType::Plus);

	// Устанавливаем интересующий нас интервал по оси X
	panel->XAxis->Scale->Min = xmin_limit;
	panel->XAxis->Scale->Max = xmax_limit;

	// Вызываем метод AxisChange (), чтобы обновить данные об осях. 
	// В противном случае на рисунке будет показана только часть графика, 
	// которая умещается в интервалы по осям, установленные по умолчанию
	zedGraphControl1->AxisChange();
	// Обновляем график
	zedGraphControl1->Invalidate(); 

	*/
}
};
}
