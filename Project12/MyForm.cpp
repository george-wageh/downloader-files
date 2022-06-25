#include "MyForm.h"

#include <windows.h>
#include <iostream>

#include <cstdio>
#include <string>
#include <string.h>


using System::Runtime::InteropServices::Marshal;

using namespace System;
using namespace std;
using namespace System::Windows::Forms;

#pragma comment(lib, "Urlmon.lib")

String^ toSystemString(std::string a) {
	String^ str3 = gcnew String(a.data());
	return str3;
}
std::string toStandardString(System::String^ string)
{
	System::IntPtr pointer = Marshal::StringToHGlobalAnsi(string);
	char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
	std::string returnString(charPointer, string->Length);
	Marshal::FreeHGlobal(pointer);

	return returnString;
}

void project12::MyForm::start_do(int i) {
	checkBox2->Checked = false;
	if (i < dataGridView1->Rows->Count - 1) {
		string extension = "";
		string startnum = "";
		if (textBox2->Text->ToString() == "") {
			startnum = "1";
		}
		else {
			startnum = toStandardString(textBox2->Text->ToString());
		}
		int startnumint = stoi(startnum);
		if (dataGridView1->Rows[i]->Cells[0]->Value->ToString() == "") {
			MessageBox::Show("url is empty", "fail");
			this->checkBox2->Checked = true;
			return;
		}
		if (checkBox1->Checked) {
			if (textBox3->Text == "") {
				MessageBox::Show("extension is empty", "fail");
				this->checkBox2->Checked = true;
				return;
			}
			extension = toStandardString(textBox3->Text);
		}
		else {
			if (dataGridView1->Rows[i]->Cells[1]->Value->ToString() == "") {
				MessageBox::Show("extension is empty", "fail");
				this->checkBox2->Checked = true;
				return;
			}
			extension = toStandardString(dataGridView1->Rows[i]->Cells[1]->Value->ToString());
		}
		startnumint = startnumint + i;
		startnum = std::to_string(startnumint);
		string uurl = toStandardString(dataGridView1->Rows[i]->Cells[0]->Value->ToString());
		std::wstring widestr = std::wstring(uurl.begin(), uurl.end());
		const wchar_t* srcURL = widestr.c_str();
		string finename = startnum + "." + extension;
		std::wstring widestr2 = std::wstring(finename.begin(), finename.end());
		const wchar_t* destFile = widestr2.c_str();
		HRESULT hr = URLDownloadToFile(NULL, srcURL, destFile, 0, NULL);
		if (S_OK == hr) {
			dataGridView1->Rows[i]->Cells[2]->Style->BackColor = System::Drawing::Color::Lime;
			this->checkBox2->Checked = true;
		}
		else {
			dataGridView1->Rows[i]->Cells[2]->Style->BackColor = System::Drawing::Color::Red;
			this->checkBox2->Checked = true;
		}
	}
}

[STAThread]
void main() {

	Application::EnableVisualStyles();

	Application::SetCompatibleTextRenderingDefault(false);

	project12::MyForm form;

	Application::Run(% form);
}



