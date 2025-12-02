#pragma once

namespace Trabajofinalprueba {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de FormConsejo
	/// </summary>
	public ref class FormConsejo : public System::Windows::Forms::Form
	{
	public:

		FormConsejo(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

		void setMensaje(String^ texto) {
			lblTexto->Text = texto;
		}


	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FormConsejo()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblTexto;
	protected:

	private: System::Windows::Forms::Button^ btnContinuar;
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
			this->lblTexto = (gcnew System::Windows::Forms::Label());
			this->btnContinuar = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lblTexto
			// 
			this->lblTexto->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTexto->Location = System::Drawing::Point(29, 9);
			this->lblTexto->Name = L"lblTexto";
			this->lblTexto->Size = System::Drawing::Size(224, 177);
			this->lblTexto->TabIndex = 0;
			this->lblTexto->Text = L"label1";
			this->lblTexto->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnContinuar
			// 
			this->btnContinuar->Location = System::Drawing::Point(101, 204);
			this->btnContinuar->Name = L"btnContinuar";
			this->btnContinuar->Size = System::Drawing::Size(75, 37);
			this->btnContinuar->TabIndex = 1;
			this->btnContinuar->Text = L"Continuar";
			this->btnContinuar->UseVisualStyleBackColor = true;
			this->btnContinuar->Click += gcnew System::EventHandler(this, &FormConsejo::btnContinuar_Click);
			// 
			// FormConsejo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->btnContinuar);
			this->Controls->Add(this->lblTexto);
			this->Name = L"FormConsejo";
			this->Text = L"FormConsejo";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnContinuar_Click(System::Object^ sender, System::EventArgs^ e) {

		this->Close();

	}
	};
}
