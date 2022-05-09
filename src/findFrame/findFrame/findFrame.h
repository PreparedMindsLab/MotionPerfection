#pragma once
#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

#define WINDOW_TITLE_AND_VERSION L"Process Video 1.6.0"

namespace VideoProc {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	int imageH;
	int imageW;

	bool doAutorun = false;
	bool doingAutorun = false;
	bool doAutorunExtractOnly = false;
	bool isOpened = false;
	bool scanned = false;
	float fps = 1;
	int lastFrameNum = 0;
	float startTime = 0;
	float endTime = 0;
	int getFrameNum();
	std::string openVideo(char* filepathname, char* referencefilepathname);
	std::string extractVideo(char* videoBpathname, char* timesfilepathname, int *remaining);
	std::string extractVideo(char* videoBpathname, char* timesfilepathname, float definedTImeSec, int *remaining);
	std::string extractVideoRemaining(int *remaining);
	bool processNVideoFrame(int num);
	void showNVideoFrame(int num);
	bool showOneVideoFrame(bool showIt);
	void setVideoFrameAbs(int relativeFrame);
	void setVideoFrame(int relativeFrame);
	void setSubSampling(int NthFrame, bool halfSized);
	bool getMarkersChanged();
	int getMarkerCount();
	int getEndFrame();
	float getEndMS();
	int getStartFrame();
	float getStartMS();
	int getEndFrame(int idx);
	float getEndMS(int idx);
	int getStartFrame(int idx);
	float getStartMS(int idx);
	float getQual();
	float getQual(int idx);
	void setMarkerQty(int qty);
	float getFPS();
	int getEndFrameNum();
	bool inputOpened();
	bool haveAtLeastOneMarker();
	int previousMarkerCount = -1;

	std::string strVideoA_FName;
	std::string strRefImage_FName;
	std::string strTime_FName;
	std::string strVideoB_FName;

	/// <summary>
   /// Summary for MainForm
   /// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void autoRun(String^ time_FName, String^ videoB_FName, String^  markerTime) {
			doAutorun = true;
			this->txtTimesFilename->Text = time_FName;
			this->txtVideoBfilename->Text = videoB_FName;
			this->txtDefinedMarker->Text = markerTime;
			doAutorunExtractOnly = true;
		}
		void autoRun(String^ videoA_FName, String^ refImage_FName, String^ time_FName, String^ videoB_FName) {
			doAutorun = true;
			this->txtFilename->Text = videoA_FName;
			this->txtRefFilename->Text = refImage_FName;
			this->txtTimesFilename->Text = time_FName;
			this->txtVideoBfilename->Text = videoB_FName;
		}
		void autoRun(String^ videoA_FName, String^ refImage_FName, String^ time_FName, String^ videoB_FName, String^ startTime) {
			doAutorun = true;
			this->txtFilename->Text = videoA_FName;
			this->txtRefFilename->Text = refImage_FName;
			this->txtTimesFilename->Text = time_FName;
			this->txtVideoBfilename->Text = videoB_FName;
			this->txtStartTime->Text = startTime;
		}
		void autoRun(String^ videoA_FName, String^ refImage_FName, String^ time_FName, String^ videoB_FName, String^ startTime,  String^ triggerCount) {
			doAutorun = true;
			this->txtFilename->Text = videoA_FName;
			this->txtRefFilename->Text = refImage_FName;
			this->txtTimesFilename->Text = time_FName;
			this->txtVideoBfilename->Text = videoB_FName;
			this->txtStartTime->Text = startTime;
			this->txtMarkerQty->Text = triggerCount;
		}
		void autoRunStr(String^ videoA_FName, String^ refImage_FName, String^ time_FName, String^ videoB_FName, String^ markerTime, bool useMarkerTime, String^ startTime, String^ destFolder, String^ triggerCount, bool autorun) {
			doAutorun = true;
			this->txtFilename->Text = videoA_FName;
			this->txtRefFilename->Text = refImage_FName;
			this->txtTimesFilename->Text = time_FName;
			this->txtVideoBfilename->Text = videoB_FName;
			this->txtDefinedMarker->Text = markerTime;
			doAutorunExtractOnly = useMarkerTime;
			this->txtStartTime->Text = startTime;
			this->txtMarkerQty->Text = destFolder;
			this->txtMarkerQty->Text = triggerCount;
			doAutorun = autorun;

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::TextBox^  txtFilename;
	private: System::Windows::Forms::Button^  cmdOpen;









	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;

	private: System::Windows::Forms::TextBox^  txtFrame;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  cmdBrowse;
	private: System::Windows::Forms::Button^  Scan;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;

	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::CheckBox^  chkBack;

	private: System::Windows::Forms::CheckBox^  chkHalfSize;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownNthFrame;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  txtFPS;
	private: System::Windows::Forms::Label^  FPS;












	private: System::Windows::Forms::Button^  cmdGoto;
	private: System::Windows::Forms::TextBox^  txtTarget;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  cmdBroseRef;
	private: System::Windows::Forms::TextBox^  txtRefFilename;
	private: System::Windows::Forms::Button^  cmdBrowseTimes;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  txtTimesFilename;




	private: System::Windows::Forms::Label^  label5;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  txtVideoBfilename;
	private: System::Windows::Forms::Button^  cmdBrowseVideoB;
	private: System::Windows::Forms::Button^  cmdExtract;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  txtMarkerQty;
private: System::Windows::Forms::TextBox^  txtStartTime;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::TextBox^  txtErrors;
private: System::Windows::Forms::TextBox^  txtMarkers;
private: System::Windows::Forms::TextBox^  txtTargetSecs;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::CheckBox^  chkFromEnd;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::TextBox^  txtVidLen;
private: System::Windows::Forms::TextBox^  txtVidLenSecs;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::TextBox^  txtDefinedMarker;


















	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtFilename = (gcnew System::Windows::Forms::TextBox());
			this->cmdOpen = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->txtFrame = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->cmdBrowse = (gcnew System::Windows::Forms::Button());
			this->Scan = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->chkBack = (gcnew System::Windows::Forms::CheckBox());
			this->chkHalfSize = (gcnew System::Windows::Forms::CheckBox());
			this->numericUpDownNthFrame = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtFPS = (gcnew System::Windows::Forms::TextBox());
			this->FPS = (gcnew System::Windows::Forms::Label());
			this->cmdGoto = (gcnew System::Windows::Forms::Button());
			this->txtTarget = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->cmdBroseRef = (gcnew System::Windows::Forms::Button());
			this->txtRefFilename = (gcnew System::Windows::Forms::TextBox());
			this->cmdBrowseTimes = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txtTimesFilename = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->txtVideoBfilename = (gcnew System::Windows::Forms::TextBox());
			this->cmdBrowseVideoB = (gcnew System::Windows::Forms::Button());
			this->cmdExtract = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->txtMarkerQty = (gcnew System::Windows::Forms::TextBox());
			this->txtStartTime = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->txtErrors = (gcnew System::Windows::Forms::TextBox());
			this->txtMarkers = (gcnew System::Windows::Forms::TextBox());
			this->txtTargetSecs = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->chkFromEnd = (gcnew System::Windows::Forms::CheckBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->txtVidLen = (gcnew System::Windows::Forms::TextBox());
			this->txtVidLenSecs = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->txtDefinedMarker = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownNthFrame))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(88, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Trigger video File";
			// 
			// txtFilename
			// 
			this->txtFilename->Location = System::Drawing::Point(106, 17);
			this->txtFilename->Name = L"txtFilename";
			this->txtFilename->Size = System::Drawing::Size(476, 20);
			this->txtFilename->TabIndex = 1;
			// 
			// cmdOpen
			// 
			this->cmdOpen->Location = System::Drawing::Point(632, 44);
			this->cmdOpen->Name = L"cmdOpen";
			this->cmdOpen->Size = System::Drawing::Size(75, 23);
			this->cmdOpen->TabIndex = 2;
			this->cmdOpen->Text = L"Open";
			this->cmdOpen->UseVisualStyleBackColor = true;
			this->cmdOpen->Click += gcnew System::EventHandler(this, &MainForm::OnCmdOpen);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(188, 284);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(74, 33);
			this->button1->TabIndex = 12;
			this->button1->Text = L"Play 1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(268, 284);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(74, 33);
			this->button2->TabIndex = 13;
			this->button2->Text = L"Play 10";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(348, 284);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(74, 33);
			this->button3->TabIndex = 14;
			this->button3->Text = L"Play 100";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::button3_MouseDown);
			this->button3->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::button3_MouseUp);
			// 
			// txtFrame
			// 
			this->txtFrame->Location = System::Drawing::Point(12, 332);
			this->txtFrame->Name = L"txtFrame";
			this->txtFrame->ReadOnly = true;
			this->txtFrame->Size = System::Drawing::Size(100, 20);
			this->txtFrame->TabIndex = 16;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// cmdBrowse
			// 
			this->cmdBrowse->Location = System::Drawing::Point(589, 15);
			this->cmdBrowse->Name = L"cmdBrowse";
			this->cmdBrowse->Size = System::Drawing::Size(37, 23);
			this->cmdBrowse->TabIndex = 17;
			this->cmdBrowse->Text = L"...";
			this->cmdBrowse->UseVisualStyleBackColor = true;
			this->cmdBrowse->Click += gcnew System::EventHandler(this, &MainForm::cmdBrowse_Click);
			// 
			// Scan
			// 
			this->Scan->Location = System::Drawing::Point(428, 325);
			this->Scan->Name = L"Scan";
			this->Scan->Size = System::Drawing::Size(147, 33);
			this->Scan->TabIndex = 18;
			this->Scan->Text = L"Scan to end";
			this->Scan->UseVisualStyleBackColor = true;
			this->Scan->Click += gcnew System::EventHandler(this, &MainForm::Scan_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(188, 326);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(74, 32);
			this->button4->TabIndex = 19;
			this->button4->Text = L"Scan 1";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(269, 326);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(73, 32);
			this->button5->TabIndex = 20;
			this->button5->Text = L"Scan 10";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(349, 326);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(73, 32);
			this->button6->TabIndex = 21;
			this->button6->Text = L"Scan 100";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6_Click);
			// 
			// button7
			// 
			this->button7->Enabled = false;
			this->button7->Location = System::Drawing::Point(581, 325);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(70, 33);
			this->button7->TabIndex = 22;
			this->button7->Text = L"Stop";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MainForm::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(428, 284);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(73, 33);
			this->button8->TabIndex = 24;
			this->button8->Text = L"Play 1000";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MainForm::button8_Click);
			// 
			// chkBack
			// 
			this->chkBack->AutoSize = true;
			this->chkBack->Location = System::Drawing::Point(76, 290);
			this->chkBack->Name = L"chkBack";
			this->chkBack->Size = System::Drawing::Size(104, 17);
			this->chkBack->TabIndex = 25;
			this->chkBack->Text = L"Step Backwards";
			this->chkBack->UseVisualStyleBackColor = true;
			this->chkBack->Visible = false;
			// 
			// chkHalfSize
			// 
			this->chkHalfSize->AutoSize = true;
			this->chkHalfSize->Checked = true;
			this->chkHalfSize->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkHalfSize->Enabled = false;
			this->chkHalfSize->Location = System::Drawing::Point(632, 175);
			this->chkHalfSize->Name = L"chkHalfSize";
			this->chkHalfSize->Size = System::Drawing::Size(74, 17);
			this->chkHalfSize->TabIndex = 27;
			this->chkHalfSize->Text = L"Half Sized";
			this->chkHalfSize->UseVisualStyleBackColor = true;
			this->chkHalfSize->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkHalfSize_CheckedChanged);
			// 
			// numericUpDownNthFrame
			// 
			this->numericUpDownNthFrame->Enabled = false;
			this->numericUpDownNthFrame->Location = System::Drawing::Point(632, 197);
			this->numericUpDownNthFrame->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->numericUpDownNthFrame->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDownNthFrame->Name = L"numericUpDownNthFrame";
			this->numericUpDownNthFrame->Size = System::Drawing::Size(40, 20);
			this->numericUpDownNthFrame->TabIndex = 28;
			this->numericUpDownNthFrame->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDownNthFrame->ValueChanged += gcnew System::EventHandler(this, &MainForm::numericUpDownNthFrame_ValueChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Enabled = false;
			this->label2->Location = System::Drawing::Point(678, 199);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 29;
			this->label2->Text = L"Nth frame";
			// 
			// txtFPS
			// 
			this->txtFPS->Location = System::Drawing::Point(509, 173);
			this->txtFPS->Name = L"txtFPS";
			this->txtFPS->ReadOnly = true;
			this->txtFPS->Size = System::Drawing::Size(44, 20);
			this->txtFPS->TabIndex = 30;
			// 
			// FPS
			// 
			this->FPS->AutoSize = true;
			this->FPS->Location = System::Drawing::Point(476, 180);
			this->FPS->Name = L"FPS";
			this->FPS->Size = System::Drawing::Size(27, 13);
			this->FPS->TabIndex = 31;
			this->FPS->Text = L"FPS";
			// 
			// cmdGoto
			// 
			this->cmdGoto->Location = System::Drawing::Point(349, 246);
			this->cmdGoto->Name = L"cmdGoto";
			this->cmdGoto->Size = System::Drawing::Size(72, 33);
			this->cmdGoto->TabIndex = 42;
			this->cmdGoto->Text = L"Goto";
			this->cmdGoto->UseVisualStyleBackColor = true;
			this->cmdGoto->Click += gcnew System::EventHandler(this, &MainForm::cmdGoto_Click);
			// 
			// txtTarget
			// 
			this->txtTarget->Location = System::Drawing::Point(428, 257);
			this->txtTarget->Name = L"txtTarget";
			this->txtTarget->Size = System::Drawing::Size(61, 20);
			this->txtTarget->TabIndex = 43;
			this->txtTarget->TextChanged += gcnew System::EventHandler(this, &MainForm::txtTarget_TextChanged);
			this->txtTarget->Enter += gcnew System::EventHandler(this, &MainForm::txtTarget_Enter);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(15, 49);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(89, 13);
			this->label3->TabIndex = 44;
			this->label3->Text = L"Reference Image";
			// 
			// cmdBroseRef
			// 
			this->cmdBroseRef->Location = System::Drawing::Point(589, 44);
			this->cmdBroseRef->Name = L"cmdBroseRef";
			this->cmdBroseRef->Size = System::Drawing::Size(37, 23);
			this->cmdBroseRef->TabIndex = 45;
			this->cmdBroseRef->Text = L"...";
			this->cmdBroseRef->UseVisualStyleBackColor = true;
			this->cmdBroseRef->Click += gcnew System::EventHandler(this, &MainForm::cmdBroseRef_Click);
			// 
			// txtRefFilename
			// 
			this->txtRefFilename->Location = System::Drawing::Point(106, 46);
			this->txtRefFilename->Name = L"txtRefFilename";
			this->txtRefFilename->Size = System::Drawing::Size(477, 20);
			this->txtRefFilename->TabIndex = 46;
			// 
			// cmdBrowseTimes
			// 
			this->cmdBrowseTimes->Location = System::Drawing::Point(588, 73);
			this->cmdBrowseTimes->Name = L"cmdBrowseTimes";
			this->cmdBrowseTimes->Size = System::Drawing::Size(37, 23);
			this->cmdBrowseTimes->TabIndex = 47;
			this->cmdBrowseTimes->Text = L"...";
			this->cmdBrowseTimes->UseVisualStyleBackColor = true;
			this->cmdBrowseTimes->Click += gcnew System::EventHandler(this, &MainForm::cmdBrowseTimes_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 83);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 48;
			this->label4->Text = L"Times";
			// 
			// txtTimesFilename
			// 
			this->txtTimesFilename->Location = System::Drawing::Point(106, 76);
			this->txtTimesFilename->Name = L"txtTimesFilename";
			this->txtTimesFilename->Size = System::Drawing::Size(476, 20);
			this->txtTimesFilename->TabIndex = 49;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(9, 139);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(103, 13);
			this->label5->TabIndex = 54;
			this->label5->Text = L"frame/ms Start/Stop";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(15, 110);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(44, 13);
			this->label7->TabIndex = 56;
			this->label7->Text = L"Video B";
			// 
			// txtVideoBfilename
			// 
			this->txtVideoBfilename->Location = System::Drawing::Point(106, 105);
			this->txtVideoBfilename->Name = L"txtVideoBfilename";
			this->txtVideoBfilename->Size = System::Drawing::Size(477, 20);
			this->txtVideoBfilename->TabIndex = 57;
			// 
			// cmdBrowseVideoB
			// 
			this->cmdBrowseVideoB->Location = System::Drawing::Point(589, 103);
			this->cmdBrowseVideoB->Name = L"cmdBrowseVideoB";
			this->cmdBrowseVideoB->Size = System::Drawing::Size(37, 23);
			this->cmdBrowseVideoB->TabIndex = 58;
			this->cmdBrowseVideoB->Text = L"...";
			this->cmdBrowseVideoB->UseVisualStyleBackColor = true;
			this->cmdBrowseVideoB->Click += gcnew System::EventHandler(this, &MainForm::cmdBrowseVideoB_Click);
			// 
			// cmdExtract
			// 
			this->cmdExtract->Location = System::Drawing::Point(632, 103);
			this->cmdExtract->Name = L"cmdExtract";
			this->cmdExtract->Size = System::Drawing::Size(75, 23);
			this->cmdExtract->TabIndex = 59;
			this->cmdExtract->Text = L"Extract";
			this->cmdExtract->UseVisualStyleBackColor = true;
			this->cmdExtract->Click += gcnew System::EventHandler(this, &MainForm::cmdExtract_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(153, 139);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(109, 13);
			this->label8->TabIndex = 60;
			this->label8->Text = L"Expected marker Qty.";
			// 
			// txtMarkerQty
			// 
			this->txtMarkerQty->Location = System::Drawing::Point(269, 136);
			this->txtMarkerQty->Name = L"txtMarkerQty";
			this->txtMarkerQty->Size = System::Drawing::Size(27, 20);
			this->txtMarkerQty->TabIndex = 61;
			this->txtMarkerQty->Text = L"1";
			// 
			// txtStartTime
			// 
			this->txtStartTime->Location = System::Drawing::Point(509, 139);
			this->txtStartTime->Name = L"txtStartTime";
			this->txtStartTime->ReadOnly = true;
			this->txtStartTime->Size = System::Drawing::Size(73, 20);
			this->txtStartTime->TabIndex = 62;
			this->txtStartTime->Text = L"0";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(400, 142);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(101, 13);
			this->label9->TabIndex = 63;
			this->label9->Text = L"CLI start time (Secs)";
			// 
			// txtErrors
			// 
			this->txtErrors->Location = System::Drawing::Point(12, 364);
			this->txtErrors->Multiline = true;
			this->txtErrors->Name = L"txtErrors";
			this->txtErrors->Size = System::Drawing::Size(708, 75);
			this->txtErrors->TabIndex = 64;
			// 
			// txtMarkers
			// 
			this->txtMarkers->Location = System::Drawing::Point(12, 155);
			this->txtMarkers->Multiline = true;
			this->txtMarkers->Name = L"txtMarkers";
			this->txtMarkers->Size = System::Drawing::Size(244, 77);
			this->txtMarkers->TabIndex = 65;
			// 
			// txtTargetSecs
			// 
			this->txtTargetSecs->Location = System::Drawing::Point(495, 258);
			this->txtTargetSecs->Name = L"txtTargetSecs";
			this->txtTargetSecs->Size = System::Drawing::Size(66, 20);
			this->txtTargetSecs->TabIndex = 66;
			this->txtTargetSecs->TextChanged += gcnew System::EventHandler(this, &MainForm::txtTargetSecs_TextChanged);
			this->txtTargetSecs->Enter += gcnew System::EventHandler(this, &MainForm::txtTargetSecs_Enter);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(428, 240);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(36, 13);
			this->label6->TabIndex = 67;
			this->label6->Text = L"Frame";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(495, 239);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(49, 13);
			this->label10->TabIndex = 68;
			this->label10->Text = L"Seconds";
			// 
			// chkFromEnd
			// 
			this->chkFromEnd->AutoSize = true;
			this->chkFromEnd->Location = System::Drawing::Point(568, 260);
			this->chkFromEnd->Name = L"chkFromEnd";
			this->chkFromEnd->Size = System::Drawing::Size(75, 17);
			this->chkFromEnd->TabIndex = 69;
			this->chkFromEnd->Text = L"From END";
			this->chkFromEnd->UseVisualStyleBackColor = true;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(352, 215);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(70, 13);
			this->label11->TabIndex = 70;
			this->label11->Text = L"Video Length";
			// 
			// txtVidLen
			// 
			this->txtVidLen->Location = System::Drawing::Point(431, 212);
			this->txtVidLen->Name = L"txtVidLen";
			this->txtVidLen->ReadOnly = true;
			this->txtVidLen->Size = System::Drawing::Size(61, 20);
			this->txtVidLen->TabIndex = 71;
			// 
			// txtVidLenSecs
			// 
			this->txtVidLenSecs->Location = System::Drawing::Point(509, 212);
			this->txtVidLenSecs->Name = L"txtVidLenSecs";
			this->txtVidLenSecs->ReadOnly = true;
			this->txtVidLenSecs->Size = System::Drawing::Size(63, 20);
			this->txtVidLenSecs->TabIndex = 72;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(12, 316);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(70, 13);
			this->label12->TabIndex = 73;
			this->label12->Text = L"Current frame";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(12, 238);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(112, 13);
			this->label13->TabIndex = 74;
			this->label13->Text = L"Defined marker (Secs)";
			// 
			// txtDefinedMarker
			// 
			this->txtDefinedMarker->Location = System::Drawing::Point(156, 236);
			this->txtDefinedMarker->Name = L"txtDefinedMarker";
			this->txtDefinedMarker->Size = System::Drawing::Size(100, 20);
			this->txtDefinedMarker->TabIndex = 75;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(732, 441);
			this->Controls->Add(this->txtDefinedMarker);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->txtVidLenSecs);
			this->Controls->Add(this->txtVidLen);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->chkFromEnd);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->txtTargetSecs);
			this->Controls->Add(this->txtMarkers);
			this->Controls->Add(this->txtErrors);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->txtStartTime);
			this->Controls->Add(this->txtMarkerQty);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->cmdExtract);
			this->Controls->Add(this->cmdBrowseVideoB);
			this->Controls->Add(this->txtVideoBfilename);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->txtTimesFilename);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->cmdBrowseTimes);
			this->Controls->Add(this->txtRefFilename);
			this->Controls->Add(this->cmdBroseRef);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->txtTarget);
			this->Controls->Add(this->cmdGoto);
			this->Controls->Add(this->FPS);
			this->Controls->Add(this->txtFPS);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->numericUpDownNthFrame);
			this->Controls->Add(this->chkHalfSize);
			this->Controls->Add(this->chkBack);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->Scan);
			this->Controls->Add(this->cmdBrowse);
			this->Controls->Add(this->txtFrame);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->cmdOpen);
			this->Controls->Add(this->txtFilename);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"Process Video";
			this->Activated += gcnew System::EventHandler(this, &MainForm::MainForm_Activated);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownNthFrame))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void MarshalString(String ^ s, std::string& os) {
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}
		int MarshalStringToInt(String ^ s) {
			int lclInt = 0;
			std::string tmpStr;
			MarshalString(s, tmpStr);
			try {
				lclInt = std::stoi(tmpStr);
			}
			catch (...) {

			}
			return lclInt;
		}
		float MarshalStringToFloat(String ^ s) {
			float lclFloat = 0;
			std::string tmpStr;
			MarshalString(s, tmpStr);
			try {
				lclFloat = std::stof(tmpStr);
			}
			catch (...) {

			}
			return lclFloat;
		}

	private: void OnCmdOpen(System::Object^  sender, System::EventArgs^  e)
	{
		std::string openResult;
		char * a;
		char * b;
		a = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(txtFilename->Text);
		b = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(txtRefFilename->Text);
		openResult = openVideo(a,b);
		isOpened = inputOpened();

		txtErrors->Text = gcnew String(openResult.c_str());
		if (isOpened) {
			fps = getFPS();
			lastFrameNum = getEndFrameNum();
			txtFPS->Text = fps.ToString();
			txtVidLen->Text = lastFrameNum.ToString();
			txtVidLenSecs->Text = (lastFrameNum / fps).ToString();

			if (!mHaveSetFrameDivision) {
				if (fps > 75) {
					int division = fps / 75;
					numericUpDownNthFrame->Value = division;
				}
			}
			int nthFrame = (int)numericUpDownNthFrame->Value;
			setSubSampling(nthFrame, chkHalfSize->Checked);
			setMarkerQty(MarshalStringToInt(txtMarkerQty->Text));
			float startTime = MarshalStringToFloat(txtStartTime->Text);
			if (startTime != 0) {
				int frm = (int)(startTime * fps);
				if (frm < 0) {
					frm = lastFrameNum + frm;
					if (frm < 1)
						frm = 1;
				}
				if (frm > lastFrameNum) {
					frm = lastFrameNum;
					editingFrameNumber = true;
					txtTarget->Text = frm.ToString();
				}
				setVideoFrameAbs(frm);
			}
			showNVideoFrame(1);
		}
	}
			 int topLeft;
			 int topRight;
			 int bottomLeft;
			 int bottomRight;
			 int leftTop;
			 int leftBottom;
			 int rightTop;
			 int rightBottom;
			 bool mHaveSetFrameDivision = false;

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (chkBack->Checked) {
			setVideoFrame(-2);
			showNVideoFrame(1);
		}
		else {
			showNVideoFrame(1);
		}
		showStatus();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		showClick(10);
	}
			 bool stopScan;

	private: System::Void button3_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		txtFrame->Text = "---";
	}
	private: System::Void button3_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		showClick(100);
	}
	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
		showClick(1000);
	}
	private: System::Void showClick(int qty) {
		stopScan = false;
		button7->Enabled = true;
		if (chkBack->Checked) {
			setVideoFrame(-(qty + 1));
			showNVideoFrame(1);
		}
		else {
			for (int stp = 0; stp < qty; stp++) {
				showNVideoFrame(1);
				Application::DoEvents();
				showStatus();
				if (stopScan) break;
			}
		}
		showStatus();
		button7->Enabled = false;
	}
	private: System::Void cmdBrowse_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			txtFilename->Text = openFileDialog1->FileName;
		}
	}
	private: System::Void Scan_Click(System::Object^  sender, System::EventArgs^  e) {
		stopScan = false;
		button7->Enabled = true;
		while (processNVideoFrame(1)) {
			showStatus();
			Application::DoEvents();
			if (stopScan) break;
		}
		button7->Enabled = false;
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		processNVideoFrame(1);
		Application::DoEvents();
		showStatus();
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
		processClick(10);
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		processClick(100);
	}
	private: System::Void processClick(int qty) {
		stopScan = false;
		button7->Enabled = true;
		bool contLoop = true;
		for (int stp = 0; contLoop && stp < qty; stp++) {
			contLoop = processNVideoFrame(1);
			Application::DoEvents();
			showStatus();
			if (stopScan) break;
		}
		button7->Enabled = false;
	}
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
		stopScan = true;
	}
	private: System::Void numericUpDownNthFrame_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		int nthFrame = (int)numericUpDownNthFrame->Value;
		setSubSampling(nthFrame, chkHalfSize->Checked);
		mHaveSetFrameDivision = true;
	}
	private: System::Void chkHalfSize_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		int nthFrame = (int)numericUpDownNthFrame->Value;
		setSubSampling(nthFrame, chkHalfSize->Checked);
	}
	 System::Void showStatus() {
		txtFrame->Text = getFrameNum().ToString();
		if (getMarkersChanged()) {
			int lclMarkerCount = getMarkerCount();
			txtMarkers->Text = "";
			for (int idx = 0; idx < lclMarkerCount; idx++) {
				System::String ^tmpStr = getStartFrame(idx).ToString();
				tmpStr += ", ";
				tmpStr += ((int)getStartMS(idx) / 1000).ToString();
				tmpStr += ", ";
				tmpStr += getEndFrame(idx).ToString();
				tmpStr += ", ";
				tmpStr += ((int)getEndMS(idx) / 1000).ToString();
				tmpStr += ", ";
				tmpStr += getQual(idx).ToString("0.00");
				tmpStr += "\r\n";
				txtMarkers->Text += tmpStr;
			}

		}
	}
private: System::Void MainForm_Activated(System::Object^  sender, System::EventArgs^  e) {
	this->Text = WINDOW_TITLE_AND_VERSION;
	if (doAutorun && !doingAutorun) {
		doingAutorun = true;
		if (doAutorunExtractOnly) {
			cmdExtract_Click(sender, e);
			if (!stopScan)
				Close();
		}
		else {
			OnCmdOpen(sender, e);
			Scan_Click(sender, e);
			cmdExtract_Click(sender, e);
			if (!stopScan)
				Close();
		}

	}
}
private: System::Void cmdGoto_Click(System::Object^  sender, System::EventArgs^  e) {
	int frm = MarshalStringToInt(txtTarget->Text);
	if (chkFromEnd->Checked) {
		frm = lastFrameNum - frm;
		if (frm < 1)
			frm = 1;
	}
	else if (frm < 0) {
		frm = lastFrameNum + frm;
		if (frm < 1)
			frm = 1;

	}
	if (frm > lastFrameNum) {
		frm = lastFrameNum;
		editingFrameNumber = true;
		txtTarget->Text = frm.ToString();
	}
	setVideoFrameAbs(frm);
	showNVideoFrame(1);

}
private: System::Void cmdBrowseTimes_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		txtTimesFilename->Text = openFileDialog1->FileName;
	}
}
private: System::Void cmdBrowseVideoB_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		txtVideoBfilename->Text = openFileDialog1->FileName;
	}
}
private: System::Void cmdExtract_Click(System::Object^  sender, System::EventArgs^  e) {
	int remaining = -1;
	if (doAutorunExtractOnly) {
		char * a;
		char * b;
		a = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(txtVideoBfilename->Text);
		b = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(txtTimesFilename->Text);
		float markerTime = MarshalStringToFloat(txtDefinedMarker->Text);
		std::string extractResult = extractVideo(a, b, markerTime, &remaining);
		txtErrors->Text = gcnew String(extractResult.c_str());
		while (remaining > 0) {
			extractVideoRemaining(&remaining);
			txtErrors->Text = gcnew String(extractResult.c_str());
			Application::DoEvents();
		}
	}
	else {
		if (haveAtLeastOneMarker()) {
			char * a;
			char * b;
			a = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(txtVideoBfilename->Text);
			b = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(txtTimesFilename->Text);
			std::string extractResult = extractVideo(a, b, &remaining);
			txtErrors->Text = gcnew String(extractResult.c_str());
			while (remaining > 0) {
				extractResult = extractVideoRemaining(&remaining);
				txtErrors->Text = gcnew String(extractResult.c_str());
				Application::DoEvents();
			}

		}
		else {
			txtErrors->Text = "No markers detected yet";
		}
	}

}
private: System::Void cmdBroseRef_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		txtRefFilename->Text = openFileDialog1->FileName;
	}

}
		 bool editingFrameNumber = false;
private: System::Void txtTargetSecs_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	if (!editingFrameNumber && fps > 1) {
		int destSecs = MarshalStringToInt(txtTargetSecs->Text);
		int dest = (int)(destSecs * fps);
		if (dest > lastFrameNum) {
			dest = lastFrameNum;
			destSecs = lastFrameNum / fps;
			txtTargetSecs->Text = destSecs.ToString();
		}
		txtTarget->Text = dest.ToString();
	}
}
private: System::Void txtTarget_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	if (editingFrameNumber && fps > 1) {
		int dest = MarshalStringToInt(txtTarget->Text);
		if (dest > lastFrameNum) {
			dest = lastFrameNum;
			txtTarget->Text = dest.ToString();
		}
		txtTargetSecs->Text = (dest / fps).ToString();
	}

}
private: System::Void txtTarget_Enter(System::Object^  sender, System::EventArgs^  e) {
	editingFrameNumber = true;
}
private: System::Void txtTargetSecs_Enter(System::Object^  sender, System::EventArgs^  e) {
	editingFrameNumber = false;
}
};
}
