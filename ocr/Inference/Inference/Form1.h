#include "cutting.h"
#include "Neural.h"
#include "receptors.h"

#pragma once

NeuralNetwork net[8];

Receptors receptors(300);
//Receptors receptors;

namespace DeltaRecogn {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Form1 的摘要
	///
	/// 警告: 如果您變更這個類別的名稱，就必須變更與這個類別所依據之所有 .resx 檔案關聯的
	///          Managed 資源編譯器工具的 'Resource File Name' 屬性。
	///          否則，這些設計工具
	///          將無法與這個表單關聯的當地語系化資源
	///          正確互動。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//


			//宣告類神經網路並初始化
			net[0].set_member("trainingData", "Net0");
			/*net[1].set_member("train1/trainingData", "Net1");
			net[2].set_member("train2/trainingData", "Net2");
			net[3].set_member("train3/trainingData", "Net3");
			net[4].set_member("train4/trainingData", "Net4");
			net[5].set_member("train5/trainingData", "Net5");
			net[6].set_member("train6/trainingData", "Net6");
			net[7].set_member("train7/trainingData", "Net7");*/
			
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::PictureBox^  pictureBox9;
	private: System::Windows::Forms::PictureBox^  pictureBox10;
	private: System::Windows::Forms::PictureBox^  pictureBox11;
	private: System::Windows::Forms::PictureBox^  pictureBox12;
	private: System::Windows::Forms::PictureBox^  pictureBox13;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		Bitmap^ MyImage;
		Bitmap^ MyImage2;
		Bitmap^ MyImage3;
		Bitmap^ MyImage4;
		Bitmap^ MyImage5;
		Bitmap^ MyImage6;
		Bitmap^ MyImage7;
		Bitmap^ MyImage8;
		Bitmap^ MyImage9;
		Bitmap^ MyImage10;
		Bitmap^ MyImage11;
		Bitmap^ MyImage12;
		Bitmap^ MyImage13;
		Bitmap^ MyImage14;
		Bitmap^ MyImage15;
		Bitmap^ MyImage16;
		Bitmap^ MyImage17;
		Bitmap^ MyImage18;
		Bitmap^ MyImage19;
		Bitmap^ MyImage20;
		Bitmap^ MyImage21;
		Bitmap^ MyImage22;
		Bitmap^ MyImage23;
		Bitmap^ MyImage24;
		Bitmap^ MyImage25;
		Bitmap^ MyImage26;
		Bitmap^ MyImage27;
		Bitmap^ MyImage28;
		Bitmap^ MyImage29;
		Bitmap^ MyImage30;
		Bitmap^ MyImage31;
		Bitmap^ MyImage32;
		Bitmap^ MyImage33;
		Bitmap^ MyImage34;
		Bitmap^ MyImage35;
		Bitmap^ MyImage36;
		Bitmap^ MyImage37;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::PictureBox^  pictureBox14;
	private: System::Windows::Forms::PictureBox^  pictureBox15;
	private: System::Windows::Forms::PictureBox^  pictureBox16;
	private: System::Windows::Forms::PictureBox^  pictureBox17;
	private: System::Windows::Forms::PictureBox^  pictureBox18;
	private: System::Windows::Forms::PictureBox^  pictureBox19;
	private: System::Windows::Forms::PictureBox^  pictureBox20;
	private: System::Windows::Forms::PictureBox^  pictureBox21;
	private: System::Windows::Forms::PictureBox^  pictureBox22;
	private: System::Windows::Forms::PictureBox^  pictureBox23;
	private: System::Windows::Forms::PictureBox^  pictureBox24;
	private: System::Windows::Forms::PictureBox^  pictureBox25;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::PictureBox^  pictureBox26;
	private: System::Windows::Forms::PictureBox^  pictureBox27;
	private: System::Windows::Forms::PictureBox^  pictureBox28;
	private: System::Windows::Forms::PictureBox^  pictureBox29;
	private: System::Windows::Forms::PictureBox^  pictureBox30;
	private: System::Windows::Forms::PictureBox^  pictureBox31;
	private: System::Windows::Forms::PictureBox^  pictureBox32;
	private: System::Windows::Forms::PictureBox^  pictureBox33;
	private: System::Windows::Forms::PictureBox^  pictureBox34;
	private: System::Windows::Forms::PictureBox^  pictureBox35;
	private: System::Windows::Forms::PictureBox^  pictureBox36;
	private: System::Windows::Forms::PictureBox^  pictureBox37;
	private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Label^  label5;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
private: Microsoft::VisualBasic::PowerPacks::LineShape^  lineShape3;
private: Microsoft::VisualBasic::PowerPacks::LineShape^  lineShape2;
private: Microsoft::VisualBasic::PowerPacks::LineShape^  lineShape1;
private: System::Windows::Forms::RadioButton^  radioButton1;
private: System::Windows::Forms::RadioButton^  radioButton2;
private: System::Windows::Forms::RadioButton^  radioButton3;
private: System::Windows::Forms::GroupBox^  groupBox1;


			 /// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改這個方法的內容。
		///
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->pictureBox14 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox21 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox22 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox23 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox24 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox25 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->pictureBox26 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox27 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox28 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox29 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox30 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox31 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox32 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox33 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox34 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox35 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox36 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox37 = (gcnew System::Windows::Forms::PictureBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->lineShape3 = (gcnew Microsoft::VisualBasic::PowerPacks::LineShape());
			this->lineShape2 = (gcnew Microsoft::VisualBasic::PowerPacks::LineShape());
			this->lineShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::LineShape());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox28))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox29))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox30))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox31))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox32))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox33))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox34))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox35))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox36))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox37))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(13, 13);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(100, 50);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button1->Location = System::Drawing::Point(848, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(155, 51);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Load Image";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button2->Location = System::Drawing::Point(848, 299);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(155, 51);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Recognize";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(12, 391);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(50, 50);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(103, 391);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(50, 50);
			this->pictureBox3->TabIndex = 5;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Location = System::Drawing::Point(190, 391);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(50, 50);
			this->pictureBox4->TabIndex = 6;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Location = System::Drawing::Point(278, 391);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(50, 50);
			this->pictureBox5->TabIndex = 7;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->Location = System::Drawing::Point(369, 391);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(50, 50);
			this->pictureBox6->TabIndex = 8;
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->Location = System::Drawing::Point(458, 391);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(50, 50);
			this->pictureBox7->TabIndex = 9;
			this->pictureBox7->TabStop = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->Location = System::Drawing::Point(552, 391);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(50, 50);
			this->pictureBox8->TabIndex = 10;
			this->pictureBox8->TabStop = false;
			// 
			// pictureBox9
			// 
			this->pictureBox9->Location = System::Drawing::Point(641, 391);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(50, 50);
			this->pictureBox9->TabIndex = 11;
			this->pictureBox9->TabStop = false;
			// 
			// pictureBox10
			// 
			this->pictureBox10->Location = System::Drawing::Point(728, 391);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(50, 50);
			this->pictureBox10->TabIndex = 12;
			this->pictureBox10->TabStop = false;
			// 
			// pictureBox11
			// 
			this->pictureBox11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox11->Location = System::Drawing::Point(12, 617);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(50, 50);
			this->pictureBox11->TabIndex = 13;
			this->pictureBox11->TabStop = false;
			// 
			// pictureBox12
			// 
			this->pictureBox12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox12->Location = System::Drawing::Point(103, 617);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(50, 50);
			this->pictureBox12->TabIndex = 14;
			this->pictureBox12->TabStop = false;
			// 
			// pictureBox13
			// 
			this->pictureBox13->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox13->Location = System::Drawing::Point(190, 617);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(50, 50);
			this->pictureBox13->TabIndex = 15;
			this->pictureBox13->TabStop = false;
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button3->Location = System::Drawing::Point(848, 613);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(155, 54);
			this->button3->TabIndex = 16;
			this->button3->Text = L"Exit";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// pictureBox14
			// 
			this->pictureBox14->Location = System::Drawing::Point(12, 278);
			this->pictureBox14->Name = L"pictureBox14";
			this->pictureBox14->Size = System::Drawing::Size(50, 50);
			this->pictureBox14->TabIndex = 17;
			this->pictureBox14->TabStop = false;
			// 
			// pictureBox15
			// 
			this->pictureBox15->Location = System::Drawing::Point(103, 278);
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->Size = System::Drawing::Size(50, 50);
			this->pictureBox15->TabIndex = 18;
			this->pictureBox15->TabStop = false;
			// 
			// pictureBox16
			// 
			this->pictureBox16->Location = System::Drawing::Point(190, 278);
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->Size = System::Drawing::Size(50, 50);
			this->pictureBox16->TabIndex = 19;
			this->pictureBox16->TabStop = false;
			// 
			// pictureBox17
			// 
			this->pictureBox17->Location = System::Drawing::Point(278, 278);
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->Size = System::Drawing::Size(50, 50);
			this->pictureBox17->TabIndex = 20;
			this->pictureBox17->TabStop = false;
			// 
			// pictureBox18
			// 
			this->pictureBox18->Location = System::Drawing::Point(369, 278);
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->Size = System::Drawing::Size(50, 50);
			this->pictureBox18->TabIndex = 21;
			this->pictureBox18->TabStop = false;
			// 
			// pictureBox19
			// 
			this->pictureBox19->Location = System::Drawing::Point(458, 278);
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->Size = System::Drawing::Size(50, 50);
			this->pictureBox19->TabIndex = 22;
			this->pictureBox19->TabStop = false;
			// 
			// pictureBox20
			// 
			this->pictureBox20->Location = System::Drawing::Point(552, 278);
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->Size = System::Drawing::Size(50, 50);
			this->pictureBox20->TabIndex = 23;
			this->pictureBox20->TabStop = false;
			// 
			// pictureBox21
			// 
			this->pictureBox21->Location = System::Drawing::Point(641, 278);
			this->pictureBox21->Name = L"pictureBox21";
			this->pictureBox21->Size = System::Drawing::Size(50, 50);
			this->pictureBox21->TabIndex = 24;
			this->pictureBox21->TabStop = false;
			// 
			// pictureBox22
			// 
			this->pictureBox22->Location = System::Drawing::Point(728, 278);
			this->pictureBox22->Name = L"pictureBox22";
			this->pictureBox22->Size = System::Drawing::Size(50, 50);
			this->pictureBox22->TabIndex = 25;
			this->pictureBox22->TabStop = false;
			// 
			// pictureBox23
			// 
			this->pictureBox23->Location = System::Drawing::Point(12, 505);
			this->pictureBox23->Name = L"pictureBox23";
			this->pictureBox23->Size = System::Drawing::Size(50, 50);
			this->pictureBox23->TabIndex = 26;
			this->pictureBox23->TabStop = false;
			// 
			// pictureBox24
			// 
			this->pictureBox24->Location = System::Drawing::Point(103, 505);
			this->pictureBox24->Name = L"pictureBox24";
			this->pictureBox24->Size = System::Drawing::Size(50, 50);
			this->pictureBox24->TabIndex = 27;
			this->pictureBox24->TabStop = false;
			// 
			// pictureBox25
			// 
			this->pictureBox25->Location = System::Drawing::Point(190, 505);
			this->pictureBox25->Name = L"pictureBox25";
			this->pictureBox25->Size = System::Drawing::Size(50, 50);
			this->pictureBox25->TabIndex = 28;
			this->pictureBox25->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(8, 247);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(86, 24);
			this->label1->TabIndex = 29;
			this->label1->Text = L"輸入影像";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(9, 357);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 24);
			this->label2->TabIndex = 30;
			this->label2->Text = L"辨識結果";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->textBox2->Location = System::Drawing::Point(869, 397);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(115, 33);
			this->textBox2->TabIndex = 31;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"新細明體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button4->Location = System::Drawing::Point(848, 546);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(155, 51);
			this->button4->TabIndex = 32;
			this->button4->Text = L"Clear";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// pictureBox26
			// 
			this->pictureBox26->Location = System::Drawing::Point(278, 505);
			this->pictureBox26->Name = L"pictureBox26";
			this->pictureBox26->Size = System::Drawing::Size(50, 50);
			this->pictureBox26->TabIndex = 33;
			this->pictureBox26->TabStop = false;
			// 
			// pictureBox27
			// 
			this->pictureBox27->Location = System::Drawing::Point(369, 505);
			this->pictureBox27->Name = L"pictureBox27";
			this->pictureBox27->Size = System::Drawing::Size(50, 50);
			this->pictureBox27->TabIndex = 34;
			this->pictureBox27->TabStop = false;
			// 
			// pictureBox28
			// 
			this->pictureBox28->Location = System::Drawing::Point(458, 505);
			this->pictureBox28->Name = L"pictureBox28";
			this->pictureBox28->Size = System::Drawing::Size(50, 50);
			this->pictureBox28->TabIndex = 35;
			this->pictureBox28->TabStop = false;
			// 
			// pictureBox29
			// 
			this->pictureBox29->Location = System::Drawing::Point(552, 505);
			this->pictureBox29->Name = L"pictureBox29";
			this->pictureBox29->Size = System::Drawing::Size(50, 50);
			this->pictureBox29->TabIndex = 36;
			this->pictureBox29->TabStop = false;
			// 
			// pictureBox30
			// 
			this->pictureBox30->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->pictureBox30->Location = System::Drawing::Point(641, 505);
			this->pictureBox30->Name = L"pictureBox30";
			this->pictureBox30->Size = System::Drawing::Size(50, 50);
			this->pictureBox30->TabIndex = 37;
			this->pictureBox30->TabStop = false;
			// 
			// pictureBox31
			// 
			this->pictureBox31->Location = System::Drawing::Point(728, 505);
			this->pictureBox31->Name = L"pictureBox31";
			this->pictureBox31->Size = System::Drawing::Size(50, 50);
			this->pictureBox31->TabIndex = 38;
			this->pictureBox31->TabStop = false;
			// 
			// pictureBox32
			// 
			this->pictureBox32->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox32->Location = System::Drawing::Point(278, 617);
			this->pictureBox32->Name = L"pictureBox32";
			this->pictureBox32->Size = System::Drawing::Size(50, 50);
			this->pictureBox32->TabIndex = 39;
			this->pictureBox32->TabStop = false;
			// 
			// pictureBox33
			// 
			this->pictureBox33->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox33->Location = System::Drawing::Point(369, 617);
			this->pictureBox33->Name = L"pictureBox33";
			this->pictureBox33->Size = System::Drawing::Size(50, 50);
			this->pictureBox33->TabIndex = 40;
			this->pictureBox33->TabStop = false;
			// 
			// pictureBox34
			// 
			this->pictureBox34->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox34->Location = System::Drawing::Point(458, 617);
			this->pictureBox34->Name = L"pictureBox34";
			this->pictureBox34->Size = System::Drawing::Size(50, 50);
			this->pictureBox34->TabIndex = 41;
			this->pictureBox34->TabStop = false;
			// 
			// pictureBox35
			// 
			this->pictureBox35->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox35->Location = System::Drawing::Point(552, 617);
			this->pictureBox35->Name = L"pictureBox35";
			this->pictureBox35->Size = System::Drawing::Size(50, 50);
			this->pictureBox35->TabIndex = 42;
			this->pictureBox35->TabStop = false;
			// 
			// pictureBox36
			// 
			this->pictureBox36->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox36->Location = System::Drawing::Point(641, 617);
			this->pictureBox36->Name = L"pictureBox36";
			this->pictureBox36->Size = System::Drawing::Size(50, 50);
			this->pictureBox36->TabIndex = 43;
			this->pictureBox36->TabStop = false;
			// 
			// pictureBox37
			// 
			this->pictureBox37->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox37->Location = System::Drawing::Point(728, 617);
			this->pictureBox37->Name = L"pictureBox37";
			this->pictureBox37->Size = System::Drawing::Size(50, 50);
			this->pictureBox37->TabIndex = 44;
			this->pictureBox37->TabStop = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(865, 370);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(119, 19);
			this->label3->TabIndex = 45;
			this->label3->Text = L"Execution time";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label4->Location = System::Drawing::Point(9, 472);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(86, 24);
			this->label4->TabIndex = 46;
			this->label4->Text = L"輸入影像";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->label5->Location = System::Drawing::Point(8, 583);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(86, 24);
			this->label5->TabIndex = 47;
			this->label5->Text = L"辨識結果";
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(0, 0);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(3) {this->lineShape3, 
				this->lineShape2, this->lineShape1});
			this->shapeContainer1->Size = System::Drawing::Size(1013, 702);
			this->shapeContainer1->TabIndex = 48;
			this->shapeContainer1->TabStop = false;
			// 
			// lineShape3
			// 
			this->lineShape3->Name = L"lineShape3";
			this->lineShape3->X1 = 13;
			this->lineShape3->X2 = 778;
			this->lineShape3->Y1 = 574;
			this->lineShape3->Y2 = 574;
			// 
			// lineShape2
			// 
			this->lineShape2->Name = L"lineShape2";
			this->lineShape2->X1 = 12;
			this->lineShape2->X2 = 777;
			this->lineShape2->Y1 = 461;
			this->lineShape2->Y2 = 461;
			// 
			// lineShape1
			// 
			this->lineShape1->Name = L"lineShape1";
			this->lineShape1->X1 = 12;
			this->lineShape1->X2 = 777;
			this->lineShape1->Y1 = 347;
			this->lineShape1->Y2 = 347;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->radioButton1->Location = System::Drawing::Point(869, 135);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(72, 31);
			this->radioButton1->TabIndex = 49;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"標準";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->radioButton2->Location = System::Drawing::Point(869, 176);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(114, 31);
			this->radioButton2->TabIndex = 50;
			this->radioButton2->Text = L"弧形排列";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->radioButton3->Location = System::Drawing::Point(869, 218);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(114, 31);
			this->radioButton3->TabIndex = 51;
			this->radioButton3->Text = L"噴墨點字";
			this->radioButton3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->groupBox1->ForeColor = System::Drawing::Color::RoyalBlue;
			this->groupBox1->Location = System::Drawing::Point(848, 89);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(155, 192);
			this->groupBox1->TabIndex = 52;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"辨識類型";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1013, 702);
			this->Controls->Add(this->radioButton3);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->pictureBox37);
			this->Controls->Add(this->pictureBox36);
			this->Controls->Add(this->pictureBox35);
			this->Controls->Add(this->pictureBox34);
			this->Controls->Add(this->pictureBox33);
			this->Controls->Add(this->pictureBox32);
			this->Controls->Add(this->pictureBox31);
			this->Controls->Add(this->pictureBox30);
			this->Controls->Add(this->pictureBox29);
			this->Controls->Add(this->pictureBox28);
			this->Controls->Add(this->pictureBox27);
			this->Controls->Add(this->pictureBox26);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox25);
			this->Controls->Add(this->pictureBox24);
			this->Controls->Add(this->pictureBox23);
			this->Controls->Add(this->pictureBox22);
			this->Controls->Add(this->pictureBox21);
			this->Controls->Add(this->pictureBox20);
			this->Controls->Add(this->pictureBox19);
			this->Controls->Add(this->pictureBox18);
			this->Controls->Add(this->pictureBox17);
			this->Controls->Add(this->pictureBox16);
			this->Controls->Add(this->pictureBox15);
			this->Controls->Add(this->pictureBox14);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->pictureBox13);
			this->Controls->Add(this->pictureBox12);
			this->Controls->Add(this->pictureBox11);
			this->Controls->Add(this->pictureBox10);
			this->Controls->Add(this->pictureBox9);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->shapeContainer1);
			this->Name = L"Form1";
			this->Text = L"Optical Character Recognition";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox28))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox29))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox30))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox31))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox32))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox33))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox34))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox35))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox36))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox37))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	OpenFileDialog^ OFD;

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 pictureBox1->Image = nullptr ;
				 pictureBox2->Image = nullptr ;
				 pictureBox3->Image = nullptr ;
				 pictureBox4->Image = nullptr ;
				 pictureBox5->Image = nullptr ;
				 pictureBox6->Image = nullptr ;
				 pictureBox7->Image = nullptr ;
				 pictureBox8->Image = nullptr ;
				 pictureBox9->Image = nullptr ;
				 pictureBox10->Image = nullptr ;
				 pictureBox11->Image = nullptr ;
				 pictureBox12->Image = nullptr ;
				 pictureBox13->Image = nullptr ;
				 pictureBox14->Image = nullptr ;
				 pictureBox15->Image = nullptr ;
				 pictureBox16->Image = nullptr ;
				 pictureBox17->Image = nullptr ;
				 pictureBox18->Image = nullptr ;
				 pictureBox19->Image = nullptr ;
				 pictureBox20->Image = nullptr ;
				 pictureBox21->Image = nullptr ;
				 pictureBox22->Image = nullptr ;
				 pictureBox23->Image = nullptr ;
				 pictureBox24->Image = nullptr ;
				 pictureBox25->Image = nullptr ;
				 pictureBox26->Image = nullptr ;
				 pictureBox27->Image = nullptr ;
				 pictureBox28->Image = nullptr ;
				 pictureBox29->Image = nullptr ;
				 pictureBox30->Image = nullptr ;
				 pictureBox31->Image = nullptr ;
				 pictureBox32->Image = nullptr ;
				 pictureBox33->Image = nullptr ;
				 pictureBox34->Image = nullptr ;
				 pictureBox35->Image = nullptr ;
				 pictureBox36->Image = nullptr ;
				 pictureBox37->Image = nullptr ;

				 delete(MyImage);
				 delete(MyImage2);
				 delete(MyImage3);
				 delete(MyImage4);
				 delete(MyImage5);
				 delete(MyImage6);
				 delete(MyImage7);
				 delete(MyImage8);
				 delete(MyImage9);
				 delete(MyImage10);
				 delete(MyImage11);
				 delete(MyImage12);
				 delete(MyImage13);
				 delete(MyImage14);
				 delete(MyImage15);
				 delete(MyImage16);
				 delete(MyImage17);
				 delete(MyImage18);
				 delete(MyImage19);
				 delete(MyImage20);
				 delete(MyImage21);
				 delete(MyImage22);
				 delete(MyImage23);
				 delete(MyImage24);
				 delete(MyImage25);
				 delete(MyImage26);
				 delete(MyImage27);
				 delete(MyImage28);
				 delete(MyImage29);
				 delete(MyImage30);
				 delete(MyImage31);
				 delete(MyImage32);
				 delete(MyImage33);
				 delete(MyImage34);
				 delete(MyImage35);
				 delete(MyImage36);
				 delete(MyImage37);
				 /*remove("temp/datanum");*/
				 remove("temp/data00.bmp");
				 remove("temp/data01.bmp");
				 remove("temp/data02.bmp");
				 remove("temp/data03.bmp");
				 remove("temp/data04.bmp");
				 remove("temp/data05.bmp");
				 remove("temp/data06.bmp");
				 remove("temp/data07.bmp");
				 remove("temp/data08.bmp");
				 remove("temp/data09.bmp");
				 remove("temp/data10.bmp");
				 remove("temp/data11.bmp");
				 remove("temp/data12.bmp");
				 remove("temp/data13.bmp");
				 remove("temp/data14.bmp");
				 remove("temp/data15.bmp");
				 remove("temp/data16.bmp");
				 remove("temp/data17.bmp");
				 remove("temp/data18.bmp");
				 remove("temp/data19.bmp");
				 remove("temp/data20.bmp");
				 remove("temp/data21.bmp");
				 remove("temp/data22.bmp");
				 remove("temp/data23.bmp");
				 remove("temp/data24.bmp");
				 remove("temp/data25.bmp");
				 remove("temp/data26.bmp");
				 remove("temp/data27.bmp");
				 remove("temp/data28.bmp");

				OFD = gcnew OpenFileDialog;
				
				OFD->InitialDirectory = "";
				OFD->Filter = "*.jpg;*.png;*.bmp|*.jpg;*.png;*.bmp";
				OFD->RestoreDirectory = true;
				
				if (OFD->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					//InitializeComponent();
					MyImage = gcnew Bitmap(OFD->FileName);
					char *filename = (char*)(void*)Marshal::StringToHGlobalAnsi(OFD->FileName);

					pictureBox1->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
					pictureBox1->Image = dynamic_cast<Image^>(MyImage);
				}	
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

			 double result;
			 stringstream time;
			 String^ str;

			 string numstr = "";
			 str = OFD->FileName;
			 char* str1 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
			 long long int start, end;
			
			 //start = clock();
			 
			 ImageAutoCut *d1 = new ImageAutoCut;

			 if(radioButton1->Checked)
					d1->recognitionType = COMMON;
			 else if ((radioButton2->Checked))
					d1->recognitionType = CURVE_ALIGNMENT;
			 else if ((radioButton3->Checked))
					d1->recognitionType = BRAILLE;
			 
			 d1->autocut(str1);
			 delete d1;
			 
		 
			 /******      辨識主體   start    ******/
			
			 string MatchedHigh;
			 double OutputValueHigh;
			 string MatchedLow;
			 double OutputValueLow;
			
			 vector<string> inputImages;
			 
			 double maxSimilarity = 0;
			 double NNSimilarity = 0;
			 double diffSimilarity = 0;
			 string mostMatchPath = "";

			 //存放切割後欲辨識圖片的資料夾路徑
			 char *toRecognizePath = "temp";
			 
			 int iRC = SearchDirectory ( inputImages, toRecognizePath, "bmp", true );

			 if (iRC)
			 {
			     cout << "NeuralDemo.cpp: LoadinputsAndRec() Error " << iRC << endl;
			 	 return;
			 }

		 	 fstream fout_result( "textW.txt", ios::out );
		 	 IplImage *imgSrc, *matchImage ;
		 	 imageProcess imageProcessing;
		     int saveFileNumber = 0;

			 for (unsigned int i=0;i<inputImages.size();i++)
			 {
				maxSimilarity = 0;
				
				imgSrc = cvLoadImage(inputImages[i].c_str(), CV_LOAD_IMAGE_GRAYSCALE);

				fout_result << endl << inputImages[i].substr( 0, inputImages[i].size() - 4 ) << endl;

				/*---scale normalization---*/
				IplImage *normalizedImg;
				
				normalizedImg =  imageProcessing.scaleNormalization( imgSrc,  normalizedWidth, normalizedHeight);
				
				imgSrc = normalizedImg;

				cvSmooth( imgSrc, imgSrc, CV_MEDIAN);
				cvThreshold(imgSrc,imgSrc,imageProcessing.cvSolveOtsuThreshold(imgSrc),1,CV_THRESH_BINARY_INV);

				imageProcessing.cvThin(imgSrc, imgSrc, 3);
				//cvDilate(imgSrc, imgSrc, NULL, 2);
		
				for(int j = 0 ; j < imgSrc->width ; j++) 
				{
					for(int k = 0 ; k < imgSrc->height ; k++)
					{
						if( ((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] == 0 )
							((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] = 255;
						else
							((uchar *)(imgSrc->imageData + k*imgSrc->widthStep))[j] = 0;
					}
				}

				char str[100];
				sprintf(str,"save/%d.bmp", saveFileNumber );
				saveFileNumber++;
				int count = 0;
				/****/
				/****/
				IplImage* resizeSaveImg = cvCreateImage(cvSize(normalizedWidth*10, normalizedHeight*10), 8, 1);
				cvResize(imgSrc, resizeSaveImg);
				cvThreshold(resizeSaveImg,resizeSaveImg,imageProcessing.cvSolveOtsuThreshold(resizeSaveImg),255,CV_THRESH_BINARY);
				/****/
				/****/
				cvSaveImage(str,resizeSaveImg);
				/*---end-------*/

				IplImage *matchNormalized ;
				
				double *input=new double[ 300 ];
				//double *input=new double[ normalizedHeight + normalizedWidth + 10 ];
				//double *input=new double[ normalizedHeight * normalizedWidth ];
				
				//input = ToMatrix(imgSrc, normalizedHeight, normalizedWidth);


/*
				double *ver_hist = new double[imgSrc->width];
				double *hor_hist = new double[imgSrc->height];
				int ver_hist_count, hor_hist_count;

				for(int k=0 ; k < imgSrc->width ; k++) 
				{
					ver_hist_count = 0;

					for(int j=0 ; j < imgSrc->height ; j++)
						if( ((uchar *)(imgSrc->imageData + j*imgSrc->widthStep))[k] == 0 )
							ver_hist_count++;
					
					ver_hist[k] = (float)ver_hist_count;
					input[k] = (double)ver_hist_count;
				}

				for(int j=0 ; j < imgSrc->height ; j++)
				{
					hor_hist_count = 0;

					for(int k=0 ; k < imgSrc->width ; k++)
						if( ((uchar *)(imgSrc->imageData + j*imgSrc->widthStep))[k] == 0 )
							hor_hist_count++;
					
					hor_hist[j] = (float)hor_hist_count;
					input[normalizedWidth + j] = (double)hor_hist_count;
				}
*/



				
				//加入 receptors 求得的 discriptor
				int *state = receptors.GetReceptorsState(imgSrc);  
				
				for(int j = 0 ; j < 300 ; j++)
					input[j] = state[j];
					//input[ normalizedHeight + normalizedWidth + j ] = state[j];

				delete [] state;
				

				/******* 依特徵分配各組辨識權重 start ********/
			/*	float weightOfGroup[8];

				for(int n = 0 ; n < 8 ; n++)
					weightOfGroup[n] = 1.0f;

				CvMemStorage *mem = cvCreateMemStorage(0);
				CvSeq *contours, *ptr;

				IplImage *imgTemp = cvCloneImage(normalizedImg);

				cvNot(imgTemp, imgTemp);

				cvFindContours(imgTemp, mem, &contours, sizeof(CvContour), CV_RETR_CCOMP,
									CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
				
				int compCount = 0;
				int holeCount = 0;

				for (ptr = contours; ptr != NULL; ptr = ptr->h_next)
				{
					contours = ptr;

					for (;ptr != NULL; ptr = ptr->v_next)
						holeCount++;

					compCount++;

					ptr = contours;
				}	
			
				if (compCount >= 2 || holeCount >= 2)
				{
					for(int n = 0 ; n < 8 ; n++)
					{
						if(n%2 == 1 && compCount >= 2 && holeCount >= 2)
							weightOfGroup[n] += 0.1f;
						else if (n%2 == 1)
							weightOfGroup[n] += 0.05f;
					}	
				}
				else
				{
					for(int n = 0 ; n < 8 ; n++)
					{
						if(n%2 == 0)
							weightOfGroup[n] += 0.05f;
					}	
				}
				
				cvClearSeq(contours);
				cvReleaseMemStorage(&mem);
				cvReleaseImage(&imgTemp);*/
				/******* 依特徵分配各組辨識權重 end ********/

start = clock();
				for( int netNum = 0 ; netNum < 1 ; netNum++ )
				{

					net[netNum].Recognize(input,MatchedHigh,OutputValueHigh,MatchedLow,OutputValueLow);
				}

				if(OutputValueHigh - OutputValueLow < 0.1)
				{
					OutputValueLow = OutputValueLow;
					i;
				}

				//輸出辨識結果到純文字檔
				fout_result << "Match" << endl;

				fout_result  << MatchedHigh << endl;

				fout_result  << "Weight: " << OutputValueHigh << endl;

				cvReleaseImage(&imgSrc);	
				delete [] input;

			}
			 
			 fout_result.close();

			 /******      辨識主體   end       ******/


			 end = clock();

			 ofstream fout("extime.txt", ios::binary | ios::out);
			 fout << ( double )( end - start ) / CLOCKS_PER_SEC;
			 fout.close();
			 
			 result = ( double )( end - start ) / CLOCKS_PER_SEC;
	
			 textBox2->Text = result.ToString();
			 String^ stringt;
			 int flag = 0;
			 string str3 = "Match";
			 int num = 0;
			 string str2;
			 char* file_name = "textW.txt";
			 ifstream fin(file_name, ios::binary | ios::in); 
			 str2.clear();

			 while(!fin.eof())
			 {
				fin >> str2;
				if (flag == 1)
				{
					num++;   					flag = 0;
					if (num == 1)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox2->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 2)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox3->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox3->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 3)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox4->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox4->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 4)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox5->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox5->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 5)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox6->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox6->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 6)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox7->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox7->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 7)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox8->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox8->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 8)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox9->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox9->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 9)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox10->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox10->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 10)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox11->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox11->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 11)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox12->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox12->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 12)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox13->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox13->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 13)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox32->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox32->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 14)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox33->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox33->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 15)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox34->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox34->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 16)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox35->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox35->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 17)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox36->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox36->Image = dynamic_cast<Image^>(MyImage);
					}
					else if (num == 18)
					{
						stringt = gcnew String(str2.c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox37->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox37->Image = dynamic_cast<Image^>(MyImage);
					}

				}
				if (str2 == str3)
				{
					flag = 1;					
				}
			 }


			 iRC = 0;
			 vector<string> vecBmpFilesP;
			 string bstring = "temp";
			 iRC = SearchDirectory(vecBmpFilesP, bstring, "bmp",false);

			 num = vecBmpFilesP.size();


			 for (int i = 0 ; i < num ; i++)
			 {
				 if (i == 0)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage = gcnew Bitmap(stringt);
						pictureBox14->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						pictureBox14->Image = dynamic_cast<Image^>(MyImage);
					}
				 else if (i == 1)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage2 = gcnew Bitmap(stringt);
						pictureBox15->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						pictureBox15->Image = dynamic_cast<Image^>(MyImage2);
					}
				 else if (i == 2)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage3 = gcnew Bitmap(stringt);
						pictureBox16->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						pictureBox16->Image = dynamic_cast<Image^>(MyImage3);
					}
				 else if (i == 3)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage4 = gcnew Bitmap(stringt);
						pictureBox17->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						pictureBox17->Image = dynamic_cast<Image^>(MyImage4);
					}
				 else if (i == 4)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage5 = gcnew Bitmap(stringt);
						pictureBox18->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						pictureBox18->Image = dynamic_cast<Image^>(MyImage5);
					}
				 else if (i == 5)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage6 = gcnew Bitmap(stringt);
						pictureBox19->Size = System::Drawing::Size(MyImage6->Width, MyImage6->Height);
						pictureBox19->Image = dynamic_cast<Image^>(MyImage6);
					}
				 else if (i == 6)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage7 = gcnew Bitmap(stringt);
						pictureBox20->Size = System::Drawing::Size(MyImage7->Width, MyImage7->Height);
						pictureBox20->Image = dynamic_cast<Image^>(MyImage7);
					}
				 else if (i == 7)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage8 = gcnew Bitmap(stringt);
						pictureBox21->Size = System::Drawing::Size(MyImage8->Width, MyImage8->Height);
						pictureBox21->Image = dynamic_cast<Image^>(MyImage8);
					}
				 else if (i == 8)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage9 = gcnew Bitmap(stringt);
						pictureBox22->Size = System::Drawing::Size(MyImage9->Width, MyImage9->Height);
						pictureBox22->Image = dynamic_cast<Image^>(MyImage9);
					}
				 else if (i ==9)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage10 = gcnew Bitmap(stringt);
						pictureBox23->Size = System::Drawing::Size(MyImage10->Width, MyImage10->Height);
						pictureBox23->Image = dynamic_cast<Image^>(MyImage10);
					}
				 else if (i == 10)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage11 = gcnew Bitmap(stringt);
						pictureBox24->Size = System::Drawing::Size(MyImage11->Width, MyImage11->Height);
						pictureBox24->Image = dynamic_cast<Image^>(MyImage11);
					}
				 else if (i == 11)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage12 = gcnew Bitmap(stringt);
						pictureBox25->Size = System::Drawing::Size(MyImage12->Width, MyImage12->Height);
						pictureBox25->Image = dynamic_cast<Image^>(MyImage12);
					}
				 else if (i == 12)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage13 = gcnew Bitmap(stringt);
						pictureBox26->Size = System::Drawing::Size(MyImage13->Width, MyImage13->Height);
						pictureBox26->Image = dynamic_cast<Image^>(MyImage13);
					}
				 else if (i == 13)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage14 = gcnew Bitmap(stringt);
						pictureBox27->Size = System::Drawing::Size(MyImage14->Width, MyImage14->Height);
						pictureBox27->Image = dynamic_cast<Image^>(MyImage14);
					}
				 else if (i == 14)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage15 = gcnew Bitmap(stringt);
						pictureBox28->Size = System::Drawing::Size(MyImage15->Width, MyImage15->Height);
						pictureBox28->Image = dynamic_cast<Image^>(MyImage15);
					}
				 else if (i == 15)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage16 = gcnew Bitmap(stringt);
						pictureBox29->Size = System::Drawing::Size(MyImage16->Width, MyImage16->Height);
						pictureBox29->Image = dynamic_cast<Image^>(MyImage16);
					}
				 else if (i == 16)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage17 = gcnew Bitmap(stringt);
						pictureBox30->Size = System::Drawing::Size(MyImage17->Width, MyImage17->Height);
						pictureBox30->Image = dynamic_cast<Image^>(MyImage17);
					}
				 else if (i == 17)
					{
						stringt = gcnew String(vecBmpFilesP[i].c_str());
						MyImage18 = gcnew Bitmap(stringt);
						pictureBox31->Size = System::Drawing::Size(MyImage18->Width, MyImage18->Height);
						pictureBox31->Image = dynamic_cast<Image^>(MyImage18);
					}
				 
			 }
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

			 delete(MyImage);
			 delete(MyImage2);
			 delete(MyImage3);
			 delete(MyImage4);
			 delete(MyImage5);
			 delete(MyImage6);
			 delete(MyImage7);
			 delete(MyImage8);
			 delete(MyImage9);
			 delete(MyImage10);
			 delete(MyImage11);
			 delete(MyImage12);
			 delete(MyImage13);
			 delete(MyImage14);
			 delete(MyImage15);
			 delete(MyImage16);
			 delete(MyImage17);
			 delete(MyImage18);

			 /*remove("temp/datanum");*/
			 remove("temp/data00.bmp");
			 remove("temp/data01.bmp");
			 remove("temp/data02.bmp");
			 remove("temp/data03.bmp");
			 remove("temp/data04.bmp");
			 remove("temp/data05.bmp");
			 remove("temp/data06.bmp");
			 remove("temp/data07.bmp");
			 remove("temp/data08.bmp");
			 remove("temp/data09.bmp");
			 remove("temp/data10.bmp");
			 remove("temp/data11.bmp");
			 remove("temp/data12.bmp");
			 remove("temp/data13.bmp");
			 remove("temp/data14.bmp");
			 remove("temp/data15.bmp");
			 remove("temp/data16.bmp");
			 remove("temp/data17.bmp");
			 remove("temp/data18.bmp");
			 remove("temp/data19.bmp");
			 remove("temp/data20.bmp");
			 remove("temp/data21.bmp");
			 remove("temp/data22.bmp");
			 remove("temp/data23.bmp");
			 remove("temp/data24.bmp");
			 remove("temp/data25.bmp");
			 remove("temp/data26.bmp");
			 remove("temp/data27.bmp");
			 remove("temp/data28.bmp");
			 exit(0);
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {

			 pictureBox1->Image = nullptr ;
			 pictureBox2->Image = nullptr ;
			 pictureBox3->Image = nullptr ;
			 pictureBox4->Image = nullptr ;
			 pictureBox5->Image = nullptr ;
			 pictureBox6->Image = nullptr ;
			 pictureBox7->Image = nullptr ;
			 pictureBox8->Image = nullptr ;
			 pictureBox9->Image = nullptr ;
			 pictureBox10->Image = nullptr ;
			 pictureBox11->Image = nullptr ;
			 pictureBox12->Image = nullptr ;
			 pictureBox13->Image = nullptr ;
			 pictureBox14->Image = nullptr ;
			 pictureBox15->Image = nullptr ;
			 pictureBox16->Image = nullptr ;
			 pictureBox17->Image = nullptr ;
			 pictureBox18->Image = nullptr ;
			 pictureBox19->Image = nullptr ;
			 pictureBox20->Image = nullptr ;
			 pictureBox21->Image = nullptr ;
			 pictureBox22->Image = nullptr ;
			 pictureBox23->Image = nullptr ;
			 pictureBox24->Image = nullptr ;
			 pictureBox25->Image = nullptr ;
			 pictureBox26->Image = nullptr ;
			 pictureBox27->Image = nullptr ;
			 pictureBox28->Image = nullptr ;
			 pictureBox29->Image = nullptr ;
			 pictureBox30->Image = nullptr ;
			 pictureBox31->Image = nullptr ;
			 pictureBox32->Image = nullptr ;
			 pictureBox33->Image = nullptr ;
			 pictureBox34->Image = nullptr ;
			 pictureBox35->Image = nullptr ;
			 pictureBox36->Image = nullptr ;
			 pictureBox37->Image = nullptr ;

			 delete(MyImage);
			 delete(MyImage2);
			 delete(MyImage3);
			 delete(MyImage4);
			 delete(MyImage5);
			 delete(MyImage6);
			 delete(MyImage7);
			 delete(MyImage8);
			 delete(MyImage9);
			 delete(MyImage10);
			 delete(MyImage11);
			 delete(MyImage12);
			 delete(MyImage13);
			 delete(MyImage14);
			 delete(MyImage15);
			 delete(MyImage16);
			 delete(MyImage17);
			 delete(MyImage18);

			remove("temp/data00.bmp");
			 remove("temp/data01.bmp");
			 remove("temp/data02.bmp");
			 remove("temp/data03.bmp");
			 remove("temp/data04.bmp");
			 remove("temp/data05.bmp");
			 remove("temp/data06.bmp");
			 remove("temp/data07.bmp");
			 remove("temp/data08.bmp");
			 remove("temp/data09.bmp");
			 remove("temp/data10.bmp");
			 remove("temp/data11.bmp");
			 remove("temp/data12.bmp");
			 remove("temp/data13.bmp");
			 remove("temp/data14.bmp");
			 remove("temp/data15.bmp");
			 remove("temp/data16.bmp");
			 remove("temp/data17.bmp");
			 remove("temp/data18.bmp");
			 remove("temp/data19.bmp");
			 remove("temp/data20.bmp");
			 remove("temp/data21.bmp");
			 remove("temp/data22.bmp");
			 remove("temp/data23.bmp");
			 remove("temp/data24.bmp");
			 remove("temp/data25.bmp");
			 remove("temp/data26.bmp");
			 remove("temp/data27.bmp");
			 remove("temp/data28.bmp");

		 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

