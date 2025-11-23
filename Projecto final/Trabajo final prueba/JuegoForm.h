#pragma once
#include "Jugador.h"
#include "Recurso.h"

namespace Trabajofinalprueba {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de JuegoForm
	/// </summary>
	public ref class JuegoForm : public System::Windows::Forms::Form
	{
	private:
		Recurso* oCorazon ;
		Bitmap^ bmpCorazon;


		Jugador* oJugador    ;
		   Bitmap^ bmpJugador;
	public:
		JuegoForm(void)
		{
			InitializeComponent();
			oCorazon = new Recurso(200, 150, 24, 21);
			bmpCorazon = gcnew Bitmap("corazon2.png");


			oJugador = new Jugador{ 50,50 };
			bmpJugador = gcnew Bitmap("walk.png");
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~JuegoForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &JuegoForm::timer1_Tick);
			// 
			// JuegoForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1146, 591);
			this->Name = L"JuegoForm";
			this->Text = L"JuegoForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &JuegoForm::FormCerrar);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &JuegoForm::precionarTecla);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &JuegoForm::soltarTecla);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);
		buffer->Graphics->Clear(Color::Black);

		oJugador->mover(buffer, bmpJugador);
		oCorazon->dibujarRecurso(buffer, bmpCorazon);

		buffer->Render(g);

		delete buffer;
		delete espacio;
		delete g;
	}
	private: System::Void precionarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::Left:
			oJugador->direccion = Direcciones::Izquierda;
			break;
		case Keys::Right:
			oJugador->direccion = Direcciones::Derecha;
			break;
		case Keys::Up:
			oJugador->direccion = Direcciones::Arriba;
			break;
		case Keys::Down:
			oJugador->direccion = Direcciones::Abajo;
			break;
		}

	}
	private: System::Void soltarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		oJugador->direccion = Direcciones::Ninguna;

	}
	private: System::Void FormCerrar(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		Application::Exit();
	}
};
}
