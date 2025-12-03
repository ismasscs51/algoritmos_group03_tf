#pragma once
#include "Jugador.h"
#include "Recurso.h"
#include "Enemigo.h"
#include "Aliado.h"
#include "FormConsejo.h"
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

		int nivelActual;
		int enemigosRestantes;

		int jugadorInicialX = 50;
		int jugadorInicialY = 50;

		bool mostrarAvisoNivel = false;
		String^ textoAvisoNivel = "";
		int tiempoAviso = 0;

		bool mostrarDaño = false;
		int dañoX = 0;
		int dañoY = 0;
		int tiempoDaño = 0;

		bool botiquinActivo = false;
		bool consejoMostrado;

		bool mostrarCura;
		int curaX, curaY;
		int tiempoCura;

		Recurso* botiquin;
		Bitmap^ bmpBotiquin;
		Recurso* itemVelocidad;      // El objeto en el suelo (Nivel 2)
		Bitmap^ bmpVelocidad;        // La imagen velocidad.png
		bool itemVelocidadEnSuelo;   // Si aparece en el mapa
		bool poderVelocidadActivo;   // Si el jugador lo tiene activado
		int tiempoVelocidad;         // Contador de 10 segundos

		Recurso* itemLentitud;       // El objeto en el suelo (Nivel 3)
		Bitmap^ bmpLentitud;         // La imagen lentitud.png
		bool itemLentitudEnSuelo;    // Si aparece en el mapa
		bool poderLentitudActivo;    // Si el jugador lo tiene activado
		int tiempoLentitud;          // Contador de 10 segundos

		Aliado* aliado1;
		Aliado* aliado2;
		Aliado* aliado3;

		Bitmap^ bmpAliado1;
		Bitmap^ bmpAliado2;
		Bitmap^ bmpAliado3;

		Enemigo* oEnemigo;
		Enemigo* oEnemigo2;
		Enemigo* oEnemigo3;
		Bitmap^ bmpEnemigo;

		Enemigo* oSombra1;
		Enemigo* oSombra2;
		Enemigo* oSombra3;
		Bitmap^ bmpSombra;

		Enemigo* oRata1;
		Enemigo* oRata2;
		Enemigo* oRata3;
		Bitmap^ bmpRata;

		Jugador* oJugador;
		   Bitmap^ bmpJugador;
	private: System::Windows::Forms::ProgressBar^ barraVida;
	private: System::Windows::Forms::Label^ label1;

		   Bitmap^ bmpJugadorAtacar;

	public:
		JuegoForm(void)
		{
			InitializeComponent();
			botiquin = new Recurso(0, 0, 24, 21);
			bmpBotiquin = gcnew Bitmap("img/corazon2.png");

			botiquinActivo = false;


			itemVelocidad = new Recurso(0, 0, 24, 24);
			bmpVelocidad = gcnew Bitmap("img/velocidad.png");
			itemVelocidadEnSuelo = false;
			poderVelocidadActivo = false;
			tiempoVelocidad = 0;

			itemLentitud = new Recurso(0, 0, 24, 24);
			bmpLentitud = gcnew Bitmap("img/lentitud.png");
			itemLentitudEnSuelo = false;
			poderLentitudActivo = false;
			tiempoLentitud = 0;

			bmpAliado1 = gcnew Bitmap("img/Aliado1.png");
			bmpAliado2 = gcnew Bitmap("img/Aliado2.png");
			bmpAliado3 = gcnew Bitmap("img/Aliado3.png");

			aliado1 = new Aliado(300, 300, 64, 64);
			aliado2 = new Aliado(300, 300, 64, 64);
			aliado3 = new Aliado(300, 300, 64, 64);

			consejoMostrado = false;

			oJugador = new Jugador{ 50,50 };
			bmpJugador = gcnew Bitmap("img/Jugador.png");
			bmpJugadorAtacar = gcnew Bitmap("img/Jugador_Atacar.png");

			oEnemigo = new Enemigo(400, 300, 64, 64,1);
			oEnemigo2 = new Enemigo(200, 300, 64, 64, 1);
			oEnemigo3 = new Enemigo(600, 200, 64, 64, 1);
			bmpEnemigo = gcnew Bitmap("img/robot.png");

			oSombra1 = new Enemigo(400, 300, 64, 64, 2);
			oSombra2 = new Enemigo(200, 300, 64, 64, 2);
			oSombra3 = new Enemigo(600, 300, 64, 64, 2);
			bmpSombra = gcnew Bitmap("img/sombra.png");


			oRata1 = new Enemigo(300, 200, 64, 64, 3);
			oRata2 = new Enemigo(500, 300, 64, 64, 2);
			oRata3 = new Enemigo(150, 250, 64, 64, 2);
			bmpRata = gcnew Bitmap("img/Rata.png");
			

			nivelActual = 1;
			enemigosRestantes = 2;
			mostrarMensajeNivel("Nivel 1");

			aliado1->setPos(350, 150);
			aliado1->activar();
			consejoMostrado = false;

			oEnemigo->vivo = false;
			oEnemigo2->vivo = false;
			oEnemigo3->vivo = false;

			barraVida->Maximum = 5;
			barraVida->Value = oJugador->vida;
			
		}




		void mostrarMensajeNivel(String^ texto)
		{
			mostrarAvisoNivel = true;
			textoAvisoNivel = texto;
			tiempoAviso = 50;
		}

		void mostrarConsejoNivel(int nivel)
		{
			consejoMostrado = true;

			// Desactivar enemigos mientras vemos el consejo
			oEnemigo->vivo = false;
			oEnemigo2->vivo = false;
			oEnemigo3->vivo = false;

			oSombra1->vivo = false;
			oSombra2->vivo = false;
			oSombra3->vivo = false;

			oRata1->vivo = false;
			oRata2->vivo = false;
			oRata3->vivo = false;

			aliado1->desactivar();
			aliado2->desactivar();
			aliado3->desactivar();

			
			timer1->Enabled = false;

			FormConsejo^ f = gcnew FormConsejo();

			if (nivel == 1)
			{
				f->setMensaje(
					"Nivel 1 - Robots\n\n"
					"Vida: 3\nDaño: 1\nVelocidad: Lenta\n\n"
					"Los robots se acercan lentamente.\n"
					"Golpéalos manteniendo distancia."
				);
			}
			else if (nivel == 2)
			{
				f->setMensaje(
					"Nivel 2 - Sombras\n\n"
					"Vida: 3\nDaño: 1\nVelocidad: Media\n\n"
					"Evita quedarte en una esquina."
				);
			}
			else if (nivel == 3)
			{
				f->setMensaje(
					"Nivel 3 - Ratas\n\n"
					"Vida: 2\nDaño: 1\nVelocidad: Alta\n\n"
					"Muévete constantemente para evitar rodeos."
				);
			}

			f->ShowDialog();

			timer1->Enabled = true;

			// Reactivar enemigos cuando cerramos el consejo
			if (nivel == 1)
			{
				oEnemigo->resetVida();
				oEnemigo->vivo = true;
				oEnemigo2->vivo = true;
			}

			if (nivel == 2)
			{
				oSombra1->resetVida();
				oSombra2->resetVida();
				oSombra3->resetVida();

				oSombra1->vivo = true;
				oSombra2->vivo = true;
				oSombra3->vivo = true;
			}

			if (nivel == 3)
			{
				oRata1->resetVida();
				oRata2->resetVida();
				oRata3->resetVida();

				oRata1->vivo = true;
				oRata2->vivo = true;
				oRata3->vivo = true;
			}
		}

		void verificarCambioDeNivel()
		{
			if (enemigosRestantes <= 0)
			{
				nivelActual++;

				if (nivelActual == 1)
				{
					mostrarMensajeNivel("Nivel 1");
					enemigosRestantes = 1;

					aliado1->setPos(350, 150);
					aliado1->activar();
					consejoMostrado = false;

					oEnemigo->vivo = false;
					oEnemigo2->vivo = false;
					oEnemigo3->vivo = false;
				}

				else if (nivelActual == 2)
				{
					mostrarMensajeNivel("Nivel 2");
					enemigosRestantes = 3;

					aliado2->setPos(350, 150);
					aliado2->activar();
					consejoMostrado = false;

					oSombra1->vivo = false;
					oSombra2->vivo = false;
					oSombra3->vivo = false;
				}

				else if (nivelActual == 3)
				{
					mostrarMensajeNivel("Nivel 3");
					enemigosRestantes = 3;

					aliado3->setPos(350, 150);
					aliado3->activar();
					consejoMostrado = false;

					oRata1->vivo = false;
					oRata2->vivo = false;
					oRata3->vivo = false;
				}

				else if (nivelActual > 3)
				{
					mostrarMensajeNivel("¡GANASTE!");
				}
			}
		}


	protected:
		~JuegoForm()
		{
			if (components) delete components;

			// Items
			delete itemVelocidad;
			delete itemLentitud;
			delete botiquin;

			// Personajes
			delete aliado1; delete aliado2; delete aliado3;
			delete oEnemigo; delete oEnemigo2; delete oEnemigo3;
			delete oSombra1; delete oSombra2; delete oSombra3;
			delete oRata1; delete oRata2; delete oRata3;
			delete oJugador;
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
			this->barraVida = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &JuegoForm::timer1_Tick);
			// 
			// barraVida
			// 
			this->barraVida->Location = System::Drawing::Point(12, 36);
			this->barraVida->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->barraVida->Maximum = 5;
			this->barraVida->Name = L"barraVida";
			this->barraVida->Size = System::Drawing::Size(161, 31);
			this->barraVida->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->barraVida->TabIndex = 0;
			this->barraVida->Value = 5;
			this->barraVida->Click += gcnew System::EventHandler(this, &JuegoForm::barraVida_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(9, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"VIDA";
			// 
			// JuegoForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1147, 591);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->barraVida);
			this->ForeColor = System::Drawing::Color::Transparent;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"JuegoForm";
			this->Text = L"JuegoForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &JuegoForm::FormCerrar);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &JuegoForm::precionarTecla);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &JuegoForm::soltarTecla);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);

		if (this->BackgroundImage != nullptr)
		{
			buffer->Graphics->DrawImage(
				this->BackgroundImage,
				0, 0,
				this->ClientSize.Width,
				this->ClientSize.Height
			);
		}
		
		if (mostrarDaño)
		{
			dañoY -= 2;

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

		if (mostrarCura)
		{
			curaY -= 2;

			buffer->Graphics->DrawString(
				"+1",
				gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold),
				Brushes::LimeGreen,
				curaX,
				curaY
			);

			tiempoCura--;

			if (tiempoCura <= 0)
				mostrarCura = false;
		}

		

		if (oJugador->vivo)
		{
			oJugador->mover(buffer, bmpJugador, bmpJugadorAtacar);
		}

		Rectangle hitJugador = Rectangle(oJugador->getX(), oJugador->getY(), oJugador->getAncho(), oJugador->getAlto());

		if (nivelActual == 1 && aliado1->estaActivo())
		{
			aliado1->dibujar(buffer->Graphics, bmpAliado1);
		}
		else if (nivelActual == 2 && aliado2->estaActivo())
		{
			aliado2->dibujar(buffer->Graphics, bmpAliado2);
		}
		else if (nivelActual == 3 && aliado3->estaActivo())
		{
			aliado3->dibujar(buffer->Graphics, bmpAliado3);
		}

		if (!consejoMostrado)
		{
			// Aliado 1
			if (nivelActual == 1 && aliado1->estaActivo() && hitJugador.IntersectsWith(aliado1->getHitbox()))
			{
				mostrarConsejoNivel(1);
			}

			// Aliado 2 - Aparición Aleatoria de VELOCIDAD
			if (nivelActual == 2 && aliado2->estaActivo() && hitJugador.IntersectsWith(aliado2->getHitbox()))
			{
				mostrarConsejoNivel(2);

				if (!poderVelocidadActivo) {
					itemVelocidadEnSuelo = true;

					// --- CAMBIO: Logica Random ---
					Random^ r = gcnew Random();
					// Genera posicion X entre 50 y el ancho pantalla - 100
					int azarX = r->Next(50, this->ClientSize.Width - 100);
					int azarY = r->Next(50, this->ClientSize.Height - 100);

					itemVelocidad->setX(azarX);
					itemVelocidad->setY(azarY);
				}
			}

			// Aliado 3 - Aparición Aleatoria de LENTITUD
			if (nivelActual == 3 && aliado3->estaActivo() && hitJugador.IntersectsWith(aliado3->getHitbox()))
			{
				mostrarConsejoNivel(3);

				if (!poderLentitudActivo) {
					itemLentitudEnSuelo = true;

					// --- CAMBIO: Logica Random ---
					Random^ r = gcnew Random();
					int azarX = r->Next(50, this->ClientSize.Width - 100);
					int azarY = r->Next(50, this->ClientSize.Height - 100);

					itemLentitud->setX(azarX);
					itemLentitud->setY(azarY);
				}
			}
		}

		Enemigo* enemigosActivos[3];

		if (nivelActual == 1)
		{
			enemigosActivos[0] = oEnemigo;
			enemigosActivos[1] = oEnemigo2;
			enemigosActivos[2] = oEnemigo3;
		}
		else if (nivelActual == 2)
		{
			
			enemigosActivos[0] = oSombra1;
			enemigosActivos[1] = oSombra2;
			enemigosActivos[2] = oSombra3;
		}
		else if (nivelActual == 3)
		{
			
			enemigosActivos[0] = oRata1;
			enemigosActivos[1] = oRata2;
			enemigosActivos[2] = oRata3;
		}
		else
		{
			
			enemigosActivos[0] = nullptr;
			enemigosActivos[1] = nullptr;
			enemigosActivos[2] = nullptr;
		}

		for (int i = 0; i < 3; i++)
		{
			if (enemigosActivos[i] == nullptr) continue;

			Enemigo* e = enemigosActivos[i];

			if (e->vivo)
			{
				e->moverHaciaJugador(oJugador);

				Bitmap^ sprite;

				if (nivelActual == 1)
					sprite = bmpEnemigo;
				else if (nivelActual == 2)
					sprite = bmpSombra;
				else
					sprite = bmpRata;

				e->mover(buffer, sprite, sprite);
			}
		}

		for (int i = 0; i < 3; i++)
		{
			Enemigo* e = enemigosActivos[i];

			if (e == nullptr) continue;

			if (e->vivo && oJugador->atacando)
			{
				if (oJugador->indiceAtaque == 2 || oJugador->indiceAtaque == 3)
				{
					Rectangle hitAtaque = oJugador->getHitboxAtaque();
					Rectangle hitEnemigo(e->getX(), e->getY(), e->getAncho(), e->getAlto());

					if (hitAtaque.IntersectsWith(hitEnemigo))
					{
						if (!oJugador->yaGolpeoEnEsteAtaque)
						{
							e->vida--;
							oJugador->yaGolpeoEnEsteAtaque = true;

							mostrarDaño = true;
							dañoX = e->getX();
							dañoY = e->getY();
							tiempoDaño = 15;

							if (e->vida <= 0)
							{
								e->vivo = false;
								enemigosRestantes--;

								Random rnd;
								int chance = rnd.Next(0, 100);

								if (chance < 50)
								{
									botiquinActivo = true;

									botiquin->setX(e->getX());
									botiquin->setY(e->getY());
								}

								verificarCambioDeNivel();
							}
						}
					}
				}
			}
		}

		if (mostrarAvisoNivel)
		{
			System::Drawing::Font^ f = gcnew System::Drawing::Font("Arial", 32, FontStyle::Bold);
			buffer->Graphics->DrawString(textoAvisoNivel, f, Brushes::Yellow,
				this->Width / 2 - 100, 80);

			tiempoAviso--;

			if (tiempoAviso <= 0)
				mostrarAvisoNivel = false;
		}

		

		for (int i = 0; i < 3; i++)
		{
			Enemigo* e = enemigosActivos[i];
			if (e == nullptr) continue;

			if (e->vivo && oJugador->vivo && !oJugador->invulnerable)
			{
				Rectangle hitJugador = oJugador->getHitboxJugador();
				Rectangle hitEnemigo(e->getX(), e->getY(), e->getAncho(), e->getAlto());

				if (hitJugador.IntersectsWith(hitEnemigo))
				{
					oJugador->vida--;
					barraVida->Value = oJugador->vida;

					if (oJugador->vida <= 0)
					{
						oJugador->vivo = false;
						mostrarMensajeNivel("PERDISTE");
					}

					oJugador->invulnerable = true;
					oJugador->tiempoInvulnerable = 30;

					mostrarDaño = true;
					dañoX = oJugador->getX();
					dañoY = oJugador->getY();
					tiempoDaño = 15;
				}
			}
		}

		if (oJugador->invulnerable)
		{
			oJugador->tiempoInvulnerable--;

			if (oJugador->tiempoInvulnerable <= 0)
				oJugador->invulnerable = false;
		}

		
		// ================= LOGICA POWER UP VELOCIDAD (NIVEL 2) =================
		if (nivelActual == 2 && itemVelocidadEnSuelo)
		{
			itemVelocidad->dibujar(buffer, bmpVelocidad);

			Rectangle hitVelocidad(itemVelocidad->getX(), itemVelocidad->getY(), itemVelocidad->getAncho(), itemVelocidad->getAlto());

			if (hitJugador.IntersectsWith(hitVelocidad))
			{
				itemVelocidadEnSuelo = false; // Lo agarramos
				poderVelocidadActivo = true;

				// ACTIVAMOS SUPER VELOCIDAD (Normal es 10, ahora 18)
				oJugador->setVelocidad(18);

				// TIEMPO: Asumiendo Timer a 50ms -> 10 seg = 200 ticks
				tiempoVelocidad = 200;
			}
		}

		// Logica del contador y restaurar velocidad
		if (poderVelocidadActivo)
		{
			tiempoVelocidad--;

			// Dibujar TIMER DE VELOCIDAD debajo de la barra de vida
			buffer->Graphics->DrawString("VELOCIDAD: " + (tiempoVelocidad / 20).ToString() + "s",
				gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold),
				Brushes::Cyan, 12, 60);

			if (tiempoVelocidad <= 0)
			{
				poderVelocidadActivo = false;
				oJugador->setVelocidad(10); // Volver a velocidad normal
			}
		}


		// ================= LOGICA POWER UP LENTITUD (NIVEL 3) =================
		if (nivelActual == 3 && itemLentitudEnSuelo)
		{
			itemLentitud->dibujar(buffer, bmpLentitud);

			Rectangle hitLentitud(itemLentitud->getX(), itemLentitud->getY(), itemLentitud->getAncho(), itemLentitud->getAlto());

			if (hitJugador.IntersectsWith(hitLentitud))
			{
				itemLentitudEnSuelo = false;
				poderLentitudActivo = true;

				// ACTIVAMOS LENTITUD A ENEMIGOS (Ratas son velocidad 3 o 4)
				oRata1->setVelocidad(1); // Muy lentas
				oRata2->setVelocidad(1);
				oRata3->setVelocidad(1);

				tiempoLentitud = 200; // 10 segundos
			}
		}

		// Logica del contador y restaurar velocidad enemigos
		if (poderLentitudActivo)
		{
			tiempoLentitud--;

			// Dibujar TIMER DE LENTITUD debajo de la barra de vida
			buffer->Graphics->DrawString("CONGELAR: " + (tiempoLentitud / 20).ToString() + "s",
				gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold),
				Brushes::Blue, 12, 60);

			if (tiempoLentitud <= 0)
			{
				poderLentitudActivo = false;
				// Restaurar velocidad de Ratas (revisar constructor para valor original, creo era 3 o 4)
				oRata1->setVelocidad(3);
				oRata2->setVelocidad(3);
				oRata3->setVelocidad(3);
			}
		}
		if (botiquinActivo)
		{
			botiquin->dibujar(buffer, bmpBotiquin);
		}

		if (botiquinActivo)
		{
			Rectangle rectBotiquin(
				botiquin->getX(),
				botiquin->getY(),
				botiquin->getAncho(),
				botiquin->getAlto()
			);

			Rectangle rectJugador(
				oJugador->getX(),
				oJugador->getY(),
				oJugador->getAncho(),
				oJugador->getAlto()
			);

			if (rectJugador.IntersectsWith(rectBotiquin))
			{
				botiquinActivo = false;

				oJugador->vida++;
				if (oJugador->vida > barraVida->Maximum)
					oJugador->vida = barraVida->Maximum;

				barraVida->Value = oJugador->vida;

				mostrarCura = true;
				curaX = oJugador->getX();
				curaY = oJugador->getY();
				tiempoCura = 15;
			}
		}

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
private: System::Void barraVida_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
