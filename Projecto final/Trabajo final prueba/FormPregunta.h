#pragma once

namespace Trabajofinalprueba {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de FormPregunta
	/// </summary>
	public ref class FormPregunta : public System::Windows::Forms::Form
	{
	public:

		bool respuestaCorrecta;
	    int correcta;

		FormPregunta(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

		void cargarPregunta(String^ texto, String^ op1, String^ op2, String^ op3, int correcta)
		{
			lblPregunta->Text = texto;
			btnOpcional1->Text = op1;
			btnOpcion2->Text = op2;
			btnOpcion3->Text = op3;

			correcta = correcta;
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FormPregunta()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblPregunta;
	private: System::Windows::Forms::Button^ btnOpcional1;
	private: System::Windows::Forms::Button^ btnOpcion2;


	private: System::Windows::Forms::Button^ btnOpcion3;

	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblPregunta = (gcnew System::Windows::Forms::Label());
			this->btnOpcional1 = (gcnew System::Windows::Forms::Button());
			this->btnOpcion2 = (gcnew System::Windows::Forms::Button());
			this->btnOpcion3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lblPregunta
			// 
			this->lblPregunta->AutoSize = true;
			this->lblPregunta->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPregunta->Location = System::Drawing::Point(56, 52);
			this->lblPregunta->Name = L"lblPregunta";
			this->lblPregunta->Size = System::Drawing::Size(58, 22);
			this->lblPregunta->TabIndex = 0;
			this->lblPregunta->Text = L"label1";
			// 
			// btnOpcional1
			// 
			this->btnOpcional1->Location = System::Drawing::Point(144, 212);
			this->btnOpcional1->Name = L"btnOpcional1";
			this->btnOpcional1->Size = System::Drawing::Size(235, 29);
			this->btnOpcional1->TabIndex = 1;
			this->btnOpcional1->Text = L"Opcion 1";
			this->btnOpcional1->UseVisualStyleBackColor = true;
			this->btnOpcional1->Click += gcnew System::EventHandler(this, &FormPregunta::btnOpcional1_Click);
			// 
			// btnOpcion2
			// 
			this->btnOpcion2->Location = System::Drawing::Point(144, 173);
			this->btnOpcion2->Name = L"btnOpcion2";
			this->btnOpcion2->Size = System::Drawing::Size(235, 33);
			this->btnOpcion2->TabIndex = 2;
			this->btnOpcion2->Text = L"Opcion 2";
			this->btnOpcion2->UseVisualStyleBackColor = true;
			this->btnOpcion2->Click += gcnew System::EventHandler(this, &FormPregunta::btnOpcion2_Click);
			// 
			// btnOpcion3
			// 
			this->btnOpcion3->Location = System::Drawing::Point(144, 134);
			this->btnOpcion3->Name = L"btnOpcion3";
			this->btnOpcion3->Size = System::Drawing::Size(235, 33);
			this->btnOpcion3->TabIndex = 3;
			this->btnOpcion3->Text = L"Opcion 3";
			this->btnOpcion3->UseVisualStyleBackColor = true;
			this->btnOpcion3->Click += gcnew System::EventHandler(this, &FormPregunta::btnOpcion3_Click);
			// 
			// FormPregunta
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(514, 253);
			this->Controls->Add(this->btnOpcion3);
			this->Controls->Add(this->btnOpcion2);
			this->Controls->Add(this->btnOpcional1);
			this->Controls->Add(this->lblPregunta);
			this->Name = L"FormPregunta";
			this->Text = L"FormPregunta";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnOpcional1_Click(System::Object^ sender, System::EventArgs^ e) {

		respuestaCorrecta = (0 == correcta);

		if (respuestaCorrecta)
			btnOpcional1->BackColor = Color::LimeGreen;
		else
			btnOpcional1->BackColor = Color::Red;

		btnOpcional1->Refresh();

		System::Threading::Thread::Sleep(400);

		this->Close();
	}

	
private: System::Void btnOpcion2_Click(System::Object^ sender, System::EventArgs^ e) {

	respuestaCorrecta = (1 == correcta);

	if (respuestaCorrecta)
		btnOpcion2->BackColor = Color::LimeGreen;
	else
		btnOpcion2->BackColor = Color::Red;

	btnOpcion2->Refresh();

	System::Threading::Thread::Sleep(400);

	this->Close();

}
private: System::Void btnOpcion3_Click(System::Object^ sender, System::EventArgs^ e) {

	respuestaCorrecta = (2 == correcta);

	if (respuestaCorrecta)
		btnOpcion3->BackColor = Color::LimeGreen;
	else
		btnOpcion3->BackColor = Color::Red;

	btnOpcion3->Refresh();

	System::Threading::Thread::Sleep(400);

	this->Close();

}
};
}
