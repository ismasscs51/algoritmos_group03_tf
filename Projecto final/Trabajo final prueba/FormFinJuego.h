#pragma once

namespace Trabajofinalprueba {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de FormFinJuego
	/// </summary>
	public ref class FormFinJuego : public System::Windows::Forms::Form
	{
	public:
		FormFinJuego(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

		void MostrarResultado(bool gano)
		{
			if (gano)
				pictureBoxFin->Image = Image::FromFile("img/winner.png");
			else
				pictureBoxFin->Image = Image::FromFile("img/game_over.png");
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~FormFinJuego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBoxFin;
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
			this->pictureBoxFin = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxFin))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBoxFin
			// 
			this->pictureBoxFin->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBoxFin->Location = System::Drawing::Point(0, 0);
			this->pictureBoxFin->Name = L"pictureBoxFin";
			this->pictureBoxFin->Size = System::Drawing::Size(497, 431);
			this->pictureBoxFin->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBoxFin->TabIndex = 0;
			this->pictureBoxFin->TabStop = false;
			// 
			// FormFinJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(497, 431);
			this->Controls->Add(this->pictureBoxFin);
			this->Name = L"FormFinJuego";
			this->Text = L"FormFinJuego";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxFin))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
