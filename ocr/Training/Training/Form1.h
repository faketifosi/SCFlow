#include "cutting.h"
#include "receptors.h"
#include "Neural.h"
#include <time.h>
#pragma once


namespace DeltaProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

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

	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
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

	private: System::Windows::Forms::Button^  button5;


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
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::TextBox^  textBox2;


	private: System::Windows::Forms::TextBox^  textBox3;










	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::Button^  button19;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::Label^  label3;














			 /// </summary>
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改這個方法的內容。
			 ///
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->button2 = (gcnew System::Windows::Forms::Button());
				 this->button3 = (gcnew System::Windows::Forms::Button());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
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
				 this->button5 = (gcnew System::Windows::Forms::Button());
				 this->button7 = (gcnew System::Windows::Forms::Button());
				 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox3 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox4 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox5 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox6 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox7 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox8 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox9 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox10 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox11 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox12 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox13 = (gcnew System::Windows::Forms::TextBox());
				 this->button19 = (gcnew System::Windows::Forms::Button());
				 this->button13 = (gcnew System::Windows::Forms::Button());
				 this->button18 = (gcnew System::Windows::Forms::Button());
				 this->button12 = (gcnew System::Windows::Forms::Button());
				 this->button17 = (gcnew System::Windows::Forms::Button());
				 this->button11 = (gcnew System::Windows::Forms::Button());
				 this->button16 = (gcnew System::Windows::Forms::Button());
				 this->button10 = (gcnew System::Windows::Forms::Button());
				 this->button15 = (gcnew System::Windows::Forms::Button());
				 this->button9 = (gcnew System::Windows::Forms::Button());
				 this->button14 = (gcnew System::Windows::Forms::Button());
				 this->button8 = (gcnew System::Windows::Forms::Button());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->textBox14 = (gcnew System::Windows::Forms::TextBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
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
				 this->SuspendLayout();
				 // 
				 // textBox1
				 // 
				 this->textBox1->Location = System::Drawing::Point(706, 10);
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(96, 22);
				 this->textBox1->TabIndex = 0;
				 this->textBox1->Text = L"data1.bmp";
				 // 
				 // button1
				 // 
				 this->button1->Location = System::Drawing::Point(808, 10);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(75, 23);
				 this->button1->TabIndex = 1;
				 this->button1->Text = L"Load IMage";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
				 // 
				 // button2
				 // 
				 this->button2->Location = System::Drawing::Point(742, 415);
				 this->button2->Name = L"button2";
				 this->button2->Size = System::Drawing::Size(141, 67);
				 this->button2->TabIndex = 2;
				 this->button2->Text = L"Exit";
				 this->button2->UseVisualStyleBackColor = true;
				 this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
				 // 
				 // button3
				 // 
				 this->button3->Location = System::Drawing::Point(808, 56);
				 this->button3->Name = L"button3";
				 this->button3->Size = System::Drawing::Size(75, 23);
				 this->button3->TabIndex = 3;
				 this->button3->Text = L"Cutting";
				 this->button3->UseVisualStyleBackColor = true;
				 this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->Location = System::Drawing::Point(13, 29);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(100, 50);
				 this->pictureBox1->TabIndex = 4;
				 this->pictureBox1->TabStop = false;
				 this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
				 // 
				 // pictureBox2
				 // 
				 this->pictureBox2->Location = System::Drawing::Point(13, 223);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(100, 50);
				 this->pictureBox2->TabIndex = 5;
				 this->pictureBox2->TabStop = false;
				 // 
				 // pictureBox3
				 // 
				 this->pictureBox3->Location = System::Drawing::Point(171, 223);
				 this->pictureBox3->Name = L"pictureBox3";
				 this->pictureBox3->Size = System::Drawing::Size(100, 50);
				 this->pictureBox3->TabIndex = 6;
				 this->pictureBox3->TabStop = false;
				 // 
				 // pictureBox4
				 // 
				 this->pictureBox4->Location = System::Drawing::Point(325, 223);
				 this->pictureBox4->Name = L"pictureBox4";
				 this->pictureBox4->Size = System::Drawing::Size(100, 50);
				 this->pictureBox4->TabIndex = 7;
				 this->pictureBox4->TabStop = false;
				 this->pictureBox4->Click += gcnew System::EventHandler(this, &Form1::pictureBox4_Click);
				 // 
				 // pictureBox5
				 // 
				 this->pictureBox5->Location = System::Drawing::Point(474, 223);
				 this->pictureBox5->Name = L"pictureBox5";
				 this->pictureBox5->Size = System::Drawing::Size(100, 50);
				 this->pictureBox5->TabIndex = 8;
				 this->pictureBox5->TabStop = false;
				 // 
				 // pictureBox6
				 // 
				 this->pictureBox6->Location = System::Drawing::Point(640, 223);
				 this->pictureBox6->Name = L"pictureBox6";
				 this->pictureBox6->Size = System::Drawing::Size(100, 50);
				 this->pictureBox6->TabIndex = 9;
				 this->pictureBox6->TabStop = false;
				 // 
				 // pictureBox7
				 // 
				 this->pictureBox7->Location = System::Drawing::Point(783, 225);
				 this->pictureBox7->Name = L"pictureBox7";
				 this->pictureBox7->Size = System::Drawing::Size(100, 50);
				 this->pictureBox7->TabIndex = 10;
				 this->pictureBox7->TabStop = false;
				 // 
				 // pictureBox8
				 // 
				 this->pictureBox8->Location = System::Drawing::Point(13, 343);
				 this->pictureBox8->Name = L"pictureBox8";
				 this->pictureBox8->Size = System::Drawing::Size(100, 50);
				 this->pictureBox8->TabIndex = 11;
				 this->pictureBox8->TabStop = false;
				 // 
				 // pictureBox9
				 // 
				 this->pictureBox9->Location = System::Drawing::Point(171, 343);
				 this->pictureBox9->Name = L"pictureBox9";
				 this->pictureBox9->Size = System::Drawing::Size(100, 50);
				 this->pictureBox9->TabIndex = 12;
				 this->pictureBox9->TabStop = false;
				 // 
				 // pictureBox10
				 // 
				 this->pictureBox10->Location = System::Drawing::Point(325, 343);
				 this->pictureBox10->Name = L"pictureBox10";
				 this->pictureBox10->Size = System::Drawing::Size(100, 50);
				 this->pictureBox10->TabIndex = 13;
				 this->pictureBox10->TabStop = false;
				 // 
				 // pictureBox11
				 // 
				 this->pictureBox11->Location = System::Drawing::Point(474, 344);
				 this->pictureBox11->Name = L"pictureBox11";
				 this->pictureBox11->Size = System::Drawing::Size(100, 50);
				 this->pictureBox11->TabIndex = 14;
				 this->pictureBox11->TabStop = false;
				 // 
				 // pictureBox12
				 // 
				 this->pictureBox12->Location = System::Drawing::Point(641, 346);
				 this->pictureBox12->Name = L"pictureBox12";
				 this->pictureBox12->Size = System::Drawing::Size(100, 50);
				 this->pictureBox12->TabIndex = 15;
				 this->pictureBox12->TabStop = false;
				 // 
				 // pictureBox13
				 // 
				 this->pictureBox13->Location = System::Drawing::Point(783, 346);
				 this->pictureBox13->Name = L"pictureBox13";
				 this->pictureBox13->Size = System::Drawing::Size(100, 50);
				 this->pictureBox13->TabIndex = 16;
				 this->pictureBox13->TabStop = false;
				 // 
				 // button5
				 // 
				 this->button5->Location = System::Drawing::Point(12, 415);
				 this->button5->Name = L"button5";
				 this->button5->Size = System::Drawing::Size(160, 67);
				 this->button5->TabIndex = 18;
				 this->button5->Text = L"Training All Data";
				 this->button5->UseVisualStyleBackColor = true;
				 this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
				 // 
				 // button7
				 // 
				 this->button7->Location = System::Drawing::Point(580, 452);
				 this->button7->Name = L"button7";
				 this->button7->Size = System::Drawing::Size(108, 30);
				 this->button7->TabIndex = 20;
				 this->button7->Text = L"clear training data";
				 this->button7->UseVisualStyleBackColor = true;
				 this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
				 // 
				 // textBox2
				 // 
				 this->textBox2->Location = System::Drawing::Point(13, 192);
				 this->textBox2->Name = L"textBox2";
				 this->textBox2->Size = System::Drawing::Size(49, 22);
				 this->textBox2->TabIndex = 21;
				 // 
				 // textBox3
				 // 
				 this->textBox3->Location = System::Drawing::Point(171, 192);
				 this->textBox3->Name = L"textBox3";
				 this->textBox3->Size = System::Drawing::Size(49, 22);
				 this->textBox3->TabIndex = 24;
				 // 
				 // textBox4
				 // 
				 this->textBox4->Location = System::Drawing::Point(325, 191);
				 this->textBox4->Name = L"textBox4";
				 this->textBox4->Size = System::Drawing::Size(46, 22);
				 this->textBox4->TabIndex = 35;
				 // 
				 // textBox5
				 // 
				 this->textBox5->Location = System::Drawing::Point(474, 192);
				 this->textBox5->Name = L"textBox5";
				 this->textBox5->Size = System::Drawing::Size(43, 22);
				 this->textBox5->TabIndex = 36;
				 // 
				 // textBox6
				 // 
				 this->textBox6->Location = System::Drawing::Point(641, 194);
				 this->textBox6->Name = L"textBox6";
				 this->textBox6->Size = System::Drawing::Size(47, 22);
				 this->textBox6->TabIndex = 37;
				 // 
				 // textBox7
				 // 
				 this->textBox7->Location = System::Drawing::Point(783, 196);
				 this->textBox7->Name = L"textBox7";
				 this->textBox7->Size = System::Drawing::Size(48, 22);
				 this->textBox7->TabIndex = 38;
				 // 
				 // textBox8
				 // 
				 this->textBox8->Location = System::Drawing::Point(13, 314);
				 this->textBox8->Name = L"textBox8";
				 this->textBox8->Size = System::Drawing::Size(49, 22);
				 this->textBox8->TabIndex = 39;
				 // 
				 // textBox9
				 // 
				 this->textBox9->Location = System::Drawing::Point(171, 314);
				 this->textBox9->Name = L"textBox9";
				 this->textBox9->Size = System::Drawing::Size(49, 22);
				 this->textBox9->TabIndex = 40;
				 // 
				 // textBox10
				 // 
				 this->textBox10->Location = System::Drawing::Point(325, 315);
				 this->textBox10->Name = L"textBox10";
				 this->textBox10->Size = System::Drawing::Size(46, 22);
				 this->textBox10->TabIndex = 41;
				 // 
				 // textBox11
				 // 
				 this->textBox11->Location = System::Drawing::Point(474, 315);
				 this->textBox11->Name = L"textBox11";
				 this->textBox11->Size = System::Drawing::Size(43, 22);
				 this->textBox11->TabIndex = 42;
				 // 
				 // textBox12
				 // 
				 this->textBox12->Location = System::Drawing::Point(640, 317);
				 this->textBox12->Name = L"textBox12";
				 this->textBox12->Size = System::Drawing::Size(47, 22);
				 this->textBox12->TabIndex = 43;
				 // 
				 // textBox13
				 // 
				 this->textBox13->Location = System::Drawing::Point(783, 316);
				 this->textBox13->Name = L"textBox13";
				 this->textBox13->Size = System::Drawing::Size(48, 22);
				 this->textBox13->TabIndex = 44;
				 // 
				 // button19
				 // 
				 this->button19->Location = System::Drawing::Point(837, 317);
				 this->button19->Name = L"button19";
				 this->button19->Size = System::Drawing::Size(46, 23);
				 this->button19->TabIndex = 34;
				 this->button19->Text = L"save";
				 this->button19->UseVisualStyleBackColor = true;
				 this->button19->Click += gcnew System::EventHandler(this, &Form1::button19_Click);
				 // 
				 // button13
				 // 
				 this->button13->Location = System::Drawing::Point(837, 196);
				 this->button13->Name = L"button13";
				 this->button13->Size = System::Drawing::Size(46, 23);
				 this->button13->TabIndex = 28;
				 this->button13->Text = L"save";
				 this->button13->UseVisualStyleBackColor = true;
				 this->button13->Click += gcnew System::EventHandler(this, &Form1::button13_Click);
				 // 
				 // button18
				 // 
				 this->button18->Location = System::Drawing::Point(693, 317);
				 this->button18->Name = L"button18";
				 this->button18->Size = System::Drawing::Size(47, 23);
				 this->button18->TabIndex = 33;
				 this->button18->Text = L"save";
				 this->button18->UseVisualStyleBackColor = true;
				 this->button18->Click += gcnew System::EventHandler(this, &Form1::button18_Click);
				 // 
				 // button12
				 // 
				 this->button12->Location = System::Drawing::Point(693, 194);
				 this->button12->Name = L"button12";
				 this->button12->Size = System::Drawing::Size(47, 23);
				 this->button12->TabIndex = 27;
				 this->button12->Text = L"save";
				 this->button12->UseVisualStyleBackColor = true;
				 this->button12->Click += gcnew System::EventHandler(this, &Form1::button12_Click);
				 // 
				 // button17
				 // 
				 this->button17->Location = System::Drawing::Point(523, 315);
				 this->button17->Name = L"button17";
				 this->button17->Size = System::Drawing::Size(51, 23);
				 this->button17->TabIndex = 32;
				 this->button17->Text = L"save";
				 this->button17->UseVisualStyleBackColor = true;
				 this->button17->Click += gcnew System::EventHandler(this, &Form1::button17_Click);
				 // 
				 // button11
				 // 
				 this->button11->Location = System::Drawing::Point(523, 192);
				 this->button11->Name = L"button11";
				 this->button11->Size = System::Drawing::Size(51, 23);
				 this->button11->TabIndex = 26;
				 this->button11->Text = L"save";
				 this->button11->UseVisualStyleBackColor = true;
				 this->button11->Click += gcnew System::EventHandler(this, &Form1::button11_Click);
				 // 
				 // button16
				 // 
				 this->button16->Location = System::Drawing::Point(377, 312);
				 this->button16->Name = L"button16";
				 this->button16->Size = System::Drawing::Size(48, 23);
				 this->button16->TabIndex = 31;
				 this->button16->Text = L"save";
				 this->button16->UseVisualStyleBackColor = true;
				 this->button16->Click += gcnew System::EventHandler(this, &Form1::button16_Click);
				 // 
				 // button10
				 // 
				 this->button10->Location = System::Drawing::Point(377, 189);
				 this->button10->Name = L"button10";
				 this->button10->Size = System::Drawing::Size(48, 23);
				 this->button10->TabIndex = 25;
				 this->button10->Text = L"save";
				 this->button10->UseVisualStyleBackColor = true;
				 this->button10->Click += gcnew System::EventHandler(this, &Form1::button10_Click);
				 // 
				 // button15
				 // 
				 this->button15->Location = System::Drawing::Point(226, 314);
				 this->button15->Name = L"button15";
				 this->button15->Size = System::Drawing::Size(45, 23);
				 this->button15->TabIndex = 30;
				 this->button15->Text = L"save";
				 this->button15->UseVisualStyleBackColor = true;
				 this->button15->Click += gcnew System::EventHandler(this, &Form1::button15_Click);
				 // 
				 // button9
				 // 
				 this->button9->Location = System::Drawing::Point(226, 191);
				 this->button9->Name = L"button9";
				 this->button9->Size = System::Drawing::Size(45, 23);
				 this->button9->TabIndex = 23;
				 this->button9->Text = L"save";
				 this->button9->UseVisualStyleBackColor = true;
				 this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
				 // 
				 // button14
				 // 
				 this->button14->Location = System::Drawing::Point(67, 314);
				 this->button14->Name = L"button14";
				 this->button14->Size = System::Drawing::Size(44, 23);
				 this->button14->TabIndex = 29;
				 this->button14->Text = L"save";
				 this->button14->UseVisualStyleBackColor = true;
				 this->button14->Click += gcnew System::EventHandler(this, &Form1::button14_Click);
				 // 
				 // button8
				 // 
				 this->button8->Location = System::Drawing::Point(67, 192);
				 this->button8->Name = L"button8";
				 this->button8->Size = System::Drawing::Size(44, 23);
				 this->button8->TabIndex = 22;
				 this->button8->Text = L"save";
				 this->button8->UseVisualStyleBackColor = true;
				 this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(198, 461);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(0, 12);
				 this->label1->TabIndex = 45;
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(806, 100);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(0, 12);
				 this->label2->TabIndex = 46;
				 // 
				 // textBox14
				 // 
				 this->textBox14->Location = System::Drawing::Point(178, 415);
				 this->textBox14->Name = L"textBox14";
				 this->textBox14->Size = System::Drawing::Size(51, 22);
				 this->textBox14->TabIndex = 47;
				 this->textBox14->Text = L"295";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(338, 461);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(33, 12);
				 this->label3->TabIndex = 48;
				 this->label3->Text = L"label3";
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(893, 506);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->textBox14);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->textBox13);
				 this->Controls->Add(this->textBox12);
				 this->Controls->Add(this->textBox11);
				 this->Controls->Add(this->textBox10);
				 this->Controls->Add(this->textBox9);
				 this->Controls->Add(this->textBox8);
				 this->Controls->Add(this->textBox7);
				 this->Controls->Add(this->textBox6);
				 this->Controls->Add(this->textBox5);
				 this->Controls->Add(this->textBox4);
				 this->Controls->Add(this->button19);
				 this->Controls->Add(this->button18);
				 this->Controls->Add(this->button17);
				 this->Controls->Add(this->button16);
				 this->Controls->Add(this->button15);
				 this->Controls->Add(this->button14);
				 this->Controls->Add(this->button13);
				 this->Controls->Add(this->button12);
				 this->Controls->Add(this->button11);
				 this->Controls->Add(this->button10);
				 this->Controls->Add(this->textBox3);
				 this->Controls->Add(this->button9);
				 this->Controls->Add(this->button8);
				 this->Controls->Add(this->textBox2);
				 this->Controls->Add(this->button7);
				 this->Controls->Add(this->button5);
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
				 this->Controls->Add(this->pictureBox1);
				 this->Controls->Add(this->button3);
				 this->Controls->Add(this->button2);
				 this->Controls->Add(this->button1);
				 this->Controls->Add(this->textBox1);
				 this->Name = L"Form1";
				 this->Text = L"Form1";
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
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
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
				 remove("temp/datanum");
				 remove("temp/data0.bmp");
				 remove("temp/data1.bmp");
				 remove("temp/data2.bmp");
				 remove("temp/data3.bmp");
				 remove("temp/data4.bmp");
				 remove("temp/data5.bmp");
				 remove("temp/data6.bmp");
				 remove("temp/data7.bmp");
				 remove("temp/data8.bmp");
				 remove("temp/data9.bmp");
				 remove("temp/data10.bmp");
				 remove("temp/data11.bmp");
				 remove("temp/data12.bmp");
				 String^ str;
				 str = this->textBox1->Text;

				 MyImage = gcnew Bitmap(str);
				 pictureBox1->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
				 pictureBox1->Image = dynamic_cast<Image^>(MyImage);
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

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

				 remove("temp/datanum");
				 remove("temp/data0.bmp");
				 remove("temp/data1.bmp");
				 remove("temp/data2.bmp");
				 remove("temp/data3.bmp");
				 remove("temp/data4.bmp");
				 remove("temp/data5.bmp");
				 remove("temp/data6.bmp");
				 remove("temp/data7.bmp");
				 remove("temp/data8.bmp");
				 remove("temp/data9.bmp");
				 remove("temp/data10.bmp");
				 remove("temp/data11.bmp");
				 remove("temp/data12.bmp");
				 exit(0);
			 }
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

				 String^ str;
				 string numstr = "";
				 str = this->textBox1->Text;
				 char* str1;
				 str1 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
				 ImageAutoCut *d1 = new ImageAutoCut;
				 d1->autocut(str1);

				 int num = 0;
				 ifstream fin("temp/datanum", ios::binary | ios::in);
				 if (!fin)
				 {
					 num = 0; // 如果沒有檔案代表裡面無訓練資料
					 exit(0);
				 }
				 else
				 {
					 numstr.clear();
					 fin >> numstr ;
					 num  = atoi(numstr.c_str());
					 if (num == 1)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);
					 }
					 else if (num == 2)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);

						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);
					 }
					 else if (num == 3)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);
					 }
					 else if (num == 4)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);
					 }
					 else if (num == 5)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);


						 MyImage5 = gcnew Bitmap("temp/data4.bmp");
						 pictureBox6->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						 pictureBox6->Image = dynamic_cast<Image^>(MyImage5);

					 }
					 else if (num == 6)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);


						 MyImage5 = gcnew Bitmap("temp/data4.bmp");
						 pictureBox6->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						 pictureBox6->Image = dynamic_cast<Image^>(MyImage5);


						 MyImage6 = gcnew Bitmap("temp/data5.bmp");
						 pictureBox7->Size = System::Drawing::Size(MyImage6->Width, MyImage6->Height);
						 pictureBox7->Image = dynamic_cast<Image^>(MyImage6);
					 }
					 else if (num == 7)
					 {
						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);


						 MyImage5 = gcnew Bitmap("temp/data4.bmp");
						 pictureBox6->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						 pictureBox6->Image = dynamic_cast<Image^>(MyImage5);


						 MyImage6 = gcnew Bitmap("temp/data5.bmp");
						 pictureBox7->Size = System::Drawing::Size(MyImage6->Width, MyImage6->Height);
						 pictureBox7->Image = dynamic_cast<Image^>(MyImage6);


						 MyImage7 = gcnew Bitmap("temp/data6.bmp");
						 pictureBox8->Size = System::Drawing::Size(MyImage7->Width, MyImage7->Height);
						 pictureBox8->Image = dynamic_cast<Image^>(MyImage7);

						 //			 delete(MyImage7);



					 }
					 else if (num == 8)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);


						 MyImage5 = gcnew Bitmap("temp/data4.bmp");
						 pictureBox6->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						 pictureBox6->Image = dynamic_cast<Image^>(MyImage5);


						 MyImage6 = gcnew Bitmap("temp/data5.bmp");
						 pictureBox7->Size = System::Drawing::Size(MyImage6->Width, MyImage6->Height);
						 pictureBox7->Image = dynamic_cast<Image^>(MyImage6);


						 MyImage7 = gcnew Bitmap("temp/data6.bmp");
						 pictureBox8->Size = System::Drawing::Size(MyImage7->Width, MyImage7->Height);
						 pictureBox8->Image = dynamic_cast<Image^>(MyImage7);


						 MyImage8 = gcnew Bitmap("temp/data7.bmp");
						 pictureBox9->Size = System::Drawing::Size(MyImage8->Width, MyImage8->Height);
						 pictureBox9->Image = dynamic_cast<Image^>(MyImage8);
					 }
					 else if (num == 9)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);


						 MyImage5 = gcnew Bitmap("temp/data4.bmp");
						 pictureBox6->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						 pictureBox6->Image = dynamic_cast<Image^>(MyImage5);


						 MyImage6 = gcnew Bitmap("temp/data5.bmp");
						 pictureBox7->Size = System::Drawing::Size(MyImage6->Width, MyImage6->Height);
						 pictureBox7->Image = dynamic_cast<Image^>(MyImage6);


						 MyImage7 = gcnew Bitmap("temp/data6.bmp");
						 pictureBox8->Size = System::Drawing::Size(MyImage7->Width, MyImage7->Height);
						 pictureBox8->Image = dynamic_cast<Image^>(MyImage7);


						 MyImage8 = gcnew Bitmap("temp/data7.bmp");
						 pictureBox9->Size = System::Drawing::Size(MyImage8->Width, MyImage8->Height);
						 pictureBox9->Image = dynamic_cast<Image^>(MyImage8);


						 MyImage9 = gcnew Bitmap("temp/data8.bmp");
						 pictureBox10->Size = System::Drawing::Size(MyImage9->Width, MyImage9->Height);
						 pictureBox10->Image = dynamic_cast<Image^>(MyImage9);
					 }
					 else if (num == 10)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);


						 MyImage5 = gcnew Bitmap("temp/data4.bmp");
						 pictureBox6->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						 pictureBox6->Image = dynamic_cast<Image^>(MyImage5);


						 MyImage6 = gcnew Bitmap("temp/data5.bmp");
						 pictureBox7->Size = System::Drawing::Size(MyImage6->Width, MyImage6->Height);
						 pictureBox7->Image = dynamic_cast<Image^>(MyImage6);


						 MyImage7 = gcnew Bitmap("temp/data6.bmp");
						 pictureBox8->Size = System::Drawing::Size(MyImage7->Width, MyImage7->Height);
						 pictureBox8->Image = dynamic_cast<Image^>(MyImage7);


						 MyImage8 = gcnew Bitmap("temp/data7.bmp");
						 pictureBox9->Size = System::Drawing::Size(MyImage8->Width, MyImage8->Height);
						 pictureBox9->Image = dynamic_cast<Image^>(MyImage8);


						 MyImage9 = gcnew Bitmap("temp/data8.bmp");
						 pictureBox10->Size = System::Drawing::Size(MyImage9->Width, MyImage9->Height);
						 pictureBox10->Image = dynamic_cast<Image^>(MyImage9);


						 MyImage10 = gcnew Bitmap("temp/data9.bmp");
						 pictureBox11->Size = System::Drawing::Size(MyImage10->Width, MyImage10->Height);
						 pictureBox11->Image = dynamic_cast<Image^>(MyImage10);
					 }
					 else if (num == 11)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);


						 MyImage5 = gcnew Bitmap("temp/data4.bmp");
						 pictureBox6->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						 pictureBox6->Image = dynamic_cast<Image^>(MyImage5);


						 MyImage6 = gcnew Bitmap("temp/data5.bmp");
						 pictureBox7->Size = System::Drawing::Size(MyImage6->Width, MyImage6->Height);
						 pictureBox7->Image = dynamic_cast<Image^>(MyImage6);


						 MyImage7 = gcnew Bitmap("temp/data6.bmp");
						 pictureBox8->Size = System::Drawing::Size(MyImage7->Width, MyImage7->Height);
						 pictureBox8->Image = dynamic_cast<Image^>(MyImage7);


						 MyImage8 = gcnew Bitmap("temp/data7.bmp");
						 pictureBox9->Size = System::Drawing::Size(MyImage8->Width, MyImage8->Height);
						 pictureBox9->Image = dynamic_cast<Image^>(MyImage8);


						 MyImage9 = gcnew Bitmap("temp/data8.bmp");
						 pictureBox10->Size = System::Drawing::Size(MyImage9->Width, MyImage9->Height);
						 pictureBox10->Image = dynamic_cast<Image^>(MyImage9);


						 MyImage10 = gcnew Bitmap("temp/data9.bmp");
						 pictureBox11->Size = System::Drawing::Size(MyImage10->Width, MyImage10->Height);
						 pictureBox11->Image = dynamic_cast<Image^>(MyImage10);


						 MyImage11 = gcnew Bitmap("temp/data10.bmp");
						 pictureBox12->Size = System::Drawing::Size(MyImage11->Width, MyImage11->Height);
						 pictureBox12->Image = dynamic_cast<Image^>(MyImage11);
					 }
					 else if (num == 12)
					 {

						 MyImage = gcnew Bitmap("temp/data0.bmp");
						 pictureBox2->Size = System::Drawing::Size(MyImage->Width, MyImage->Height);
						 pictureBox2->Image = dynamic_cast<Image^>(MyImage);


						 MyImage2 = gcnew Bitmap("temp/data1.bmp");
						 pictureBox3->Size = System::Drawing::Size(MyImage2->Width, MyImage2->Height);
						 pictureBox3->Image = dynamic_cast<Image^>(MyImage2);


						 MyImage3 = gcnew Bitmap("temp/data2.bmp");
						 pictureBox4->Size = System::Drawing::Size(MyImage3->Width, MyImage3->Height);
						 pictureBox4->Image = dynamic_cast<Image^>(MyImage3);


						 MyImage4 = gcnew Bitmap("temp/data3.bmp");
						 pictureBox5->Size = System::Drawing::Size(MyImage4->Width, MyImage4->Height);
						 pictureBox5->Image = dynamic_cast<Image^>(MyImage4);


						 MyImage5 = gcnew Bitmap("temp/data4.bmp");
						 pictureBox6->Size = System::Drawing::Size(MyImage5->Width, MyImage5->Height);
						 pictureBox6->Image = dynamic_cast<Image^>(MyImage5);


						 MyImage6 = gcnew Bitmap("temp/data5.bmp");
						 pictureBox7->Size = System::Drawing::Size(MyImage6->Width, MyImage6->Height);
						 pictureBox7->Image = dynamic_cast<Image^>(MyImage6);


						 MyImage7 = gcnew Bitmap("temp/data6.bmp");
						 pictureBox8->Size = System::Drawing::Size(MyImage7->Width, MyImage7->Height);
						 pictureBox8->Image = dynamic_cast<Image^>(MyImage7);


						 MyImage8 = gcnew Bitmap("temp/data7.bmp");
						 pictureBox9->Size = System::Drawing::Size(MyImage8->Width, MyImage8->Height);
						 pictureBox9->Image = dynamic_cast<Image^>(MyImage8);


						 MyImage9 = gcnew Bitmap("temp/data8.bmp");
						 pictureBox10->Size = System::Drawing::Size(MyImage9->Width, MyImage9->Height);
						 pictureBox10->Image = dynamic_cast<Image^>(MyImage9);


						 MyImage10 = gcnew Bitmap("temp/data9.bmp");
						 pictureBox11->Size = System::Drawing::Size(MyImage10->Width, MyImage10->Height);
						 pictureBox11->Image = dynamic_cast<Image^>(MyImage10);


						 MyImage11 = gcnew Bitmap("temp/data10.bmp");
						 pictureBox12->Size = System::Drawing::Size(MyImage11->Width, MyImage11->Height);
						 pictureBox12->Image = dynamic_cast<Image^>(MyImage11);


						 MyImage12 = gcnew Bitmap("temp/data11.bmp");
						 pictureBox13->Size = System::Drawing::Size(MyImage12->Width, MyImage12->Height);
						 pictureBox13->Image = dynamic_cast<Image^>(MyImage12);
					 }
				 }




				 fin.close();



			 }
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {

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

				 string str = "";
				 int num = 0;
				 ifstream fin("trainingdata/datanum", ios::binary | ios::in);
				 if (!fin)
				 {
					 num = 0; // 如果沒有檔案代表裡面無訓練資料
				 }
				 else
				 {
					 str.clear();
					 fin >> str ;
					 num  = atoi(str.c_str());
				 }

				 fin.close();

				 int num2 = 0;
				 ifstream fin2("temp/datanum", ios::binary | ios::in);
				 if (!fin2)
				 {
					 num2 = 0; // 如果沒有檔案代表裡面無訓練資料
				 }
				 else
				 {
					 str.clear();
					 fin2 >> str ;
					 num2  = atoi(str.c_str());
				 }

				 fin2.close();

				 for (int i = 0 ; i < num2 ; i++)
				 {
					 stringstream savepath;
					 char newpath[100];
					 savepath << "trainingdata/" << "data" << num+i<< ".bmp";
					 savepath >> newpath;

					 stringstream savepath2;
					 char newpath2[100];
					 savepath2 << "temp/" << "data" << i<< ".bmp";
					 savepath2 >> newpath2;

					 IplImage *img1 = cvLoadImage(newpath2);
					 cvSaveImage(newpath,img1);
				 }

				 ofstream fout("trainingdata/datanum", ios::binary | ios::out);
				 fout << num+num2; // 記錄目前有多少筆data
				 fout.close();
			 }
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {

				 system("del trainingdata");
			 }

	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {

				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox2->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data0.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {

				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox3->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data1.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);

			 }
	private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox4->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data2.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox5->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data3.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox6->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data4.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox7->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data5.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox8->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data6.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox9->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data7.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox10->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data8.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button17_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox11->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data9.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox12->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data10.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button19_Click(System::Object^  sender, System::EventArgs^  e) {
				 stringstream savepath;
				 String^ str;
				 char newpath[100];
				 marshal_context^ context = gcnew marshal_context();
				 str = this->textBox13->Text;
				 string stl_s = context->marshal_as<std::string>(str);
				 savepath << "trainingdata/" << stl_s;
				 savepath >> newpath;
				 char *path2=  "temp/data11.bmp";
				 IplImage *img = cvLoadImage(path2,-1);
				 cvSaveImage(newpath,img);
			 }
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {

				 
				 int inputnum =  Convert::ToInt32(textBox14->Text);;
			
				 label1->Text ="Training , Please Wait";
				 clock_t start, end;
				 start = clock();
				 
				 NeuralNetwork *training = new NeuralNetwork();
				 //training->classify();
				 
				 //訓練8組類神經網路
				 for (int i = 0 ; i <= 0 ; i++)
				 {

					 label3->Text = i.ToString();
					 
					 char inpp[50];
					 char outpp[50];
					 char tspp[50];
					 stringstream inpath;
					 stringstream outpath;
					 stringstream tspath;

					 //inpath << "train" << i << "/trainingdata";
					 inpath << "trainingdata";
					 inpath >> inpp;
					 training->bstring = inpp;

					 training->InitializeSettings();		
					 training->GenerateTrainingSet();
					 training->CreateNeuralNetwork(100);

					 training->ToTrain();
					 outpath << "Net" << i;
					 outpath >> outpp;
					 training->saveNetwork(outpp);

					 tspath << "TS" << i;
					 tspath >> tspp;
					 training->RecognizeTS(tspp);
				 }

				 delete training;
				 
				 end = clock();

				 ofstream fout("Train time.txt", ios::binary | ios::out);
				 double traintime = ( double )( end - start ) / CLOCKS_PER_SEC;
				 fout << ( double )( end - start ) / CLOCKS_PER_SEC << endl;
				 fout.close();
				 
				 label2->Text = traintime.ToString();
				 label1->Text ="Training Done , Thank You";
			 }


private: System::Void pictureBox4_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

