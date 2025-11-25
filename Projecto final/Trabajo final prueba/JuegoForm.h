#pragma once
#include "Jugador.h"
#include "Recurso.h"
#include "Enemigo.h"
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

		bool mostrarDaño = false;
		int dañoX = 0;
		int dañoY = 0;
		int tiempoDaño = 0;

		Recurso* oCorazon;
		Bitmap^ bmpCorazon;

		Enemigo* oEnemigo;
		Bitmap^ bmpEnemigo;

		Jugador* oJugador;
		   Bitmap^ bmpJugador;
		   Bitmap^ bmpJugadorAtacar;

	public:
		JuegoForm(void)
		{
			InitializeComponent();
			oCorazon = new Recurso(200, 150, 24, 21);
			bmpCorazon = gcnew Bitmap("img/corazon2.png");

			oJugador = new Jugador{ 50,50 };
			bmpJugador = gcnew Bitmap("img/Jugador.png");
			bmpJugadorAtacar = gcnew Bitmap("img/Jugador_Atacar.png");

			oEnemigo = new Enemigo(400, 300, 64, 64,4);
			bmpEnemigo = gcnew Bitmap("img/enemigo.png");
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

		if (mostrarDaño)
		{
			dañoY -= 2; // sube el texto

			buffer->Graphics->DrawString(
				"-1",
				gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold),
				Brushes::Red,
				dañoX,
				dañoY
			);

			tiempoDaño--;

			if (tiempoDaño <= 0)
				mostrarDaño = false;
		}

		oJugador->mover(buffer, bmpJugador, bmpJugadorAtacar);

		if (oEnemigo->vivo)
		{
			// 2. Solo si el jugador está atacando
			if (oJugador->atacando)
			{
				// 3. El golpe solo existe en los frames 2 y 3
				if (oJugador->indiceAtaque == 2 || oJugador->indiceAtaque == 3)
				{
					// 4. Obtener hitbox del ataque
					Rectangle hitAtaque = oJugador->getHitboxAtaque();

					// 5. Obtener hitbox del enemigo
					Rectangle hitEnemigo(
						oEnemigo->getX(),
						oEnemigo->getY(),
						oEnemigo->getAncho(),
						oEnemigo->getAlto()
					);

					// 6. Detectar colisión
					if (hitAtaque.IntersectsWith(hitEnemigo))
					{
						// 7. Evitar golpes múltiples por ataque
						if (!oJugador->yaGolpeoEnEsteAtaque)
						{
							oEnemigo->vida--;                    // Quitar vida al enemigo
							oJugador->yaGolpeoEnEsteAtaque = true; // Marcar golpe

							mostrarDaño = true;
							dañoX = oEnemigo->getX();
							dañoY = oEnemigo->getY();
							tiempoDaño = 15; // dura 15 frames (0.25 segundos)

							// 8. Si vida llega a 0  enemigo muere
							if (oEnemigo->vida <= 0)
							{
								oEnemigo->vivo = false;
							}
						}
					}
				}
			}
		}

		if (oEnemigo->vivo) {
			oEnemigo->perseguir(oJugador);
			oEnemigo->mover(buffer, bmpEnemigo, bmpEnemigo);
		}

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

		if (e->KeyCode == Keys::A) {
			oJugador->atacando = true;
			oJugador->indiceAtaque = 0;
			oJugador->yaGolpeoEnEsteAtaque = false;
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
