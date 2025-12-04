#pragma once
#include "Jugador.h"
#include "Recurso.h"
#include "Enemigo.h"
#include "Aliado.h"
#include "FormConsejo.h"
#include "NPC.h"
#include "FormPregunta.h"
#include "FormFinJuego.h"

namespace Trabajofinalprueba {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class JuegoForm : public System::Windows::Forms::Form
	{
	private:
		// --- Variables Generales ---
		int nivelActual;
		int enemigosRestantes;

		// --- Feedback Visual ---
		bool mostrarAvisoNivel = false;
		String^ textoAvisoNivel = "";
		int tiempoAviso = 0;

		bool mostrarDaño = false; int dañoX = 0; int dañoY = 0; int tiempoDaño = 0;
		bool mostrarCura; int curaX, curaY; int tiempoCura;

		// --- NPC Dialogos ---
		bool consejoMostrado;
		bool mostrarFraseNPC;
		String^ textoFraseNPC;
		int xFrase, yFrase, tiempoFrase;

		// --- Variables NPC ---
		NPC* npcActual;
		int contadorSpawnNPC;
		int tiempoParaProximoNPC;
		//--- Variables fondo ---
		Bitmap^ fondo1;
		Bitmap^ fondo2;
		Bitmap^ fondo3;
		// --- Items y Personajes ---
		bool botiquinActivo = false; Recurso* botiquin; Bitmap^ bmpBotiquin;

		// Power Ups
		Recurso* itemVelocidad; Bitmap^ bmpVelocidad; bool itemVelocidadEnSuelo; bool poderVelocidadActivo; int tiempoVelocidad;
		Recurso* itemLentitud; Bitmap^ bmpLentitud; bool itemLentitudEnSuelo; bool poderLentitudActivo; int tiempoLentitud;

		// Aliados
		Aliado* aliado1; Aliado* aliado2; Aliado* aliado3;
		Bitmap^ bmpAliado1; Bitmap^ bmpAliado2; Bitmap^ bmpAliado3;

		// Enemigos
		Enemigo* oEnemigo; Enemigo* oEnemigo2; Enemigo* oEnemigo3; Bitmap^ bmpEnemigo;
		Enemigo* oSombra1; Enemigo* oSombra2; Enemigo* oSombra3; Bitmap^ bmpSombra;
		Enemigo* oRata1; Enemigo* oRata2; Enemigo* oRata3; Bitmap^ bmpRata;

		// Imagenes NPC
		Bitmap^ bmpFuturista1; Bitmap^ bmpFuturista2;
		Bitmap^ bmpVagabundo1; Bitmap^ bmpVagabundo2;
		Bitmap^ bmpCampesino1; Bitmap^ bmpCampesino2;

		// Jugador
		Jugador* oJugador;
		Bitmap^ bmpJugador;
		Bitmap^ bmpJugadorAtacar;

	private: System::Windows::Forms::ProgressBar^ barraVida;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ProgressBar^ barraConfianza;

	public:
		JuegoForm(void)
		{
			InitializeComponent();

			// Inicializar Recursos
			botiquin = new Recurso(0, 0, 24, 21);
			bmpBotiquin = gcnew Bitmap("img/corazon2.png");

			itemVelocidad = new Recurso(0, 0, 24, 24); bmpVelocidad = gcnew Bitmap("img/velocidad.png");
			itemLentitud = new Recurso(0, 0, 24, 24); bmpLentitud = gcnew Bitmap("img/lentitud.png");

			// Aliados
			bmpAliado1 = gcnew Bitmap("img/Aliado1.png");
			bmpAliado2 = gcnew Bitmap("img/Aliado2.png");
			bmpAliado3 = gcnew Bitmap("img/Aliado3.png");
			aliado1 = new Aliado(300, 300, 64, 64);
			aliado2 = new Aliado(300, 300, 64, 64);
			aliado3 = new Aliado(300, 300, 64, 64);

			// NPC Imagenes
			bmpFuturista1 = gcnew Bitmap("img/Futurista1.png"); bmpFuturista2 = gcnew Bitmap("img/Futurista2.png");
			bmpVagabundo1 = gcnew Bitmap("img/Vagabundo1.png"); bmpVagabundo2 = gcnew Bitmap("img/Vagabundo2.png");
			bmpCampesino1 = gcnew Bitmap("img/Campesino1.png"); bmpCampesino2 = gcnew Bitmap("img/Campesino2.png");

			npcActual = nullptr;
			contadorSpawnNPC = 0;
			tiempoParaProximoNPC = 60; // 3 seg aprox
			mostrarFraseNPC = false;

			// Jugador
			oJugador = new Jugador(50, 50);
			bmpJugador = gcnew Bitmap("img/Jugador.png");
			bmpJugadorAtacar = gcnew Bitmap("img/Jugador_Atacar.png");

			// Enemigos
			oEnemigo = new Enemigo(400, 300, 64, 64, 1);
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

			fondo1 = gcnew Bitmap("img/nivel1.png");
			fondo2 = gcnew Bitmap("img/nivel2.png");
			fondo3 = gcnew Bitmap("img/nivel3.png");

			this->BackgroundImage = fondo1;

			nivelActual = 1;
			enemigosRestantes = 2;
			mostrarMensajeNivel("Nivel 1");

			aliado1->setPos(350, 150);
			aliado1->activar();
			consejoMostrado = false;

			oEnemigo->vivo = false; oEnemigo2->vivo = false; oEnemigo3->vivo = false;
			oSombra1->vivo = false; oSombra2->vivo = false; oSombra3->vivo = false;
			oRata1->vivo = false;   oRata2->vivo = false;   oRata3->vivo = false;

			barraVida->Maximum = 5;
			barraVida->Value = oJugador->vida;

			this->barraConfianza->Visible = false;
			this->barraConfianza->Maximum = 4;
			this->barraConfianza->Value = 0;
		}

		void mostrarMensajeNivel(String^ texto)
		{
			mostrarAvisoNivel = true; textoAvisoNivel = texto; tiempoAviso = 50;
		}

		void mostrarConsejoNivel(int nivel)
		{
			consejoMostrado = true;
			timer1->Enabled = false;

			// Seguridad
			if (oEnemigo) oEnemigo->vivo = false; if (oEnemigo2) oEnemigo2->vivo = false; if (oEnemigo3) oEnemigo3->vivo = false;
			if (oSombra1) oSombra1->vivo = false; if (oSombra2) oSombra2->vivo = false; if (oSombra3) oSombra3->vivo = false;
			if (oRata1) oRata1->vivo = false; if (oRata2) oRata2->vivo = false; if (oRata3) oRata3->vivo = false;
			aliado1->desactivar(); aliado2->desactivar(); aliado3->desactivar();

			FormConsejo^ f = gcnew FormConsejo();
			Bitmap^ img = nullptr;

			if (nivel == 1) {
				f->setMensaje("Nivel 1 - Robots\n\nProtege a los civiles.\nLa IA esta invadiendo la ciudad.");
				if (bmpEnemigo != nullptr) img = bmpEnemigo->Clone(Rectangle(0, 0, 64, 64), bmpEnemigo->PixelFormat);
			}
			else if (nivel == 2) {
				f->setMensaje("Nivel 2 - Sombras\n\nLas sombras son rapidas.\nAyuda a los vagabundos supervivientes.");
				if (bmpSombra != nullptr) img = bmpSombra->Clone(Rectangle(0, 0, 64, 64), bmpSombra->PixelFormat);
			}
			else if (nivel == 3) {
				f->setMensaje("Nivel 3 - Ratas\n\nEstamos firmando la paz.\nLas ratas quieren sabotear el tratado.");
				if (bmpRata != nullptr) img = bmpRata->Clone(Rectangle(0, 0, 64, 64), bmpRata->PixelFormat);
			}
			if (img != nullptr) f->setImagenEnemigo(img);
			f->ShowDialog();

			timer1->Enabled = true;

			if (nivel == 1) { oEnemigo->resetVida(); oEnemigo->vivo = true; oEnemigo2->vivo = true; }
			if (nivel == 2) { oSombra1->resetVida(); oSombra2->resetVida(); oSombra3->resetVida(); oSombra1->vivo = true; oSombra2->vivo = true; oSombra3->vivo = true; }
			if (nivel == 3) { oRata1->resetVida(); oRata2->resetVida(); oRata3->resetVida(); oRata1->vivo = true; oRata2->vivo = true; oRata3->vivo = true; }
		}

		void verificarCondicionGanar()
		{
			if (enemigosRestantes <= 0 && barraConfianza->Value >= 4)
			{
				pasarNivel();
			}
		}



		void pasarNivel()
		{
			FormPregunta^ fp = gcnew FormPregunta();

			if (nivelActual == 1)
			{
				fp->cargarPregunta(
					"¿La eficiencia sin emociones puede llamarse vida?",
					"Sí, porque lo importante es ser funcional.",
					"Depende del propósito de la existencia.",
					"No, porque sentir es lo que da sentido a vivir.",
					2
				);
			}

			else if (nivelActual == 2)
			{
				fp->cargarPregunta(
					"¿Obedecer sin cuestionar es voluntad o programación?",
					"Es programación, no hay decisión propia.",
					"Es una señal de disciplina.",
					"Es una forma de survival.",
					0
				);
			}

			else if (nivelActual == 3)
			{
				fp->cargarPregunta(
					"¿Puede un ser perfecto aprender del error?",
					"Sí, si entiende que fallar también es información.",
					"No, la perfección no cambia.",
					"Solo cuando el sistema lo ordena.",
					0
				);
			}

			// Mostrar formulario
			timer1->Enabled = false;
			fp->ShowDialog();
			timer1->Enabled = true;

			// Evaluar resultado
			if (!fp->respuestaCorrecta)
			{
				oJugador->vida--;
				barraVida->Value = oJugador->vida;

				if (oJugador->vida <= 0)
				{
					timer1->Enabled = false;
					FormFinJuego^ f = gcnew FormFinJuego();
					f->MostrarResultado(false);
					f->ShowDialog();
					this->Close();
					return;
				}
			}

			nivelActual++;
			if (nivelActual == 1)
			{
				this->BackgroundImage = fondo1;
				this->BackgroundImageLayout = ImageLayout::Stretch;
			}
			else if (nivelActual == 2)
			{
				this->BackgroundImage = fondo2;
				this->BackgroundImageLayout = ImageLayout::Stretch;
			}
			else if (nivelActual == 3)
			{
				this->BackgroundImage = fondo3;
				this->BackgroundImageLayout = ImageLayout::Stretch;
			}
			poderVelocidadActivo = false; oJugador->setVelocidad(10);
			poderLentitudActivo = false;
			barraConfianza->Value = 0;
			if (npcActual) { delete npcActual; npcActual = nullptr; }

			if (nivelActual == 2) {
				mostrarMensajeNivel("Nivel 2");
				enemigosRestantes = 3;
				aliado2->setPos(350, 150); aliado2->activar(); consejoMostrado = false;
				oEnemigo->vivo = false; oEnemigo2->vivo = false; oEnemigo3->vivo = false;
			}
			else if (nivelActual == 3) {
				mostrarMensajeNivel("Nivel 3");
				enemigosRestantes = 3;
				aliado3->setPos(350, 150); aliado3->activar(); consejoMostrado = false;
				oSombra1->vivo = false; oSombra2->vivo = false; oSombra3->vivo = false;
			}
			else {
				timer1->Enabled = false;
				FormFinJuego^ f = gcnew FormFinJuego();
				f->MostrarResultado(true);
				f->ShowDialog();
				this->Close();
				return;
			}
		}

	protected:
		~JuegoForm()
		{
			if (components) delete components;
			delete itemVelocidad; delete itemLentitud; delete botiquin;
			delete aliado1; delete aliado2; delete aliado3;
			delete oEnemigo; delete oEnemigo2; delete oEnemigo3;
			delete oSombra1; delete oSombra2; delete oSombra3;
			delete oRata1; delete oRata2; delete oRata3;
			delete oJugador;
			if (npcActual != nullptr) delete npcActual;
		}

	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->barraVida = (gcnew System::Windows::Forms::ProgressBar());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->barraConfianza = (gcnew System::Windows::Forms::ProgressBar());
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
			   this->barraVida->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			   this->barraVida->Maximum = 5;
			   this->barraVida->Name = L"barraVida";
			   this->barraVida->Size = System::Drawing::Size(161, 31);
			   this->barraVida->TabIndex = 0;
			   this->barraVida->Value = 5;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label1->Location = System::Drawing::Point(9, 9);
			   this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(42, 16);
			   this->label1->TabIndex = 1;
			   this->label1->Text = L"VIDA";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label2->Location = System::Drawing::Point(197, 11);
			   this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(92, 16);
			   this->label2->TabIndex = 2;
			   this->label2->Text = L"CONFIANZA";
			   // 
			   // barraConfianza
			   // 
			   this->barraConfianza->Location = System::Drawing::Point(201, 36);
			   this->barraConfianza->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			   this->barraConfianza->Maximum = 4;
			   this->barraConfianza->Name = L"barraConfianza";
			   this->barraConfianza->Size = System::Drawing::Size(161, 31);
			   this->barraConfianza->TabIndex = 3;
			   // 
			   // JuegoForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->ClientSize = System::Drawing::Size(1529, 727);
			   this->Controls->Add(this->barraConfianza);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->barraVida);
			   this->ForeColor = System::Drawing::Color::Transparent;
			   this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			   this->Name = L"JuegoForm";
			   this->Text = L"La Rebelión Humana";
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

		Bitmap^ fondoActual = nullptr;

		if (nivelActual == 1) fondoActual = fondo1;
		else if (nivelActual == 2) fondoActual = fondo2;
		else if (nivelActual == 3) fondoActual = fondo3;

		buffer->Graphics->DrawImage(
			fondoActual,
			0, 0,
			this->ClientSize.Width,
			this->ClientSize.Height
		);
		

		if (oJugador->vivo) { oJugador->mover(buffer, bmpJugador, bmpJugadorAtacar); }
		Rectangle hitJugador = Rectangle(oJugador->getX(), oJugador->getY(), oJugador->getAncho(), oJugador->getAlto());

		// Dibujar Aliados
		if (nivelActual == 1 && aliado1->estaActivo()) aliado1->dibujar(buffer->Graphics, bmpAliado1);
		else if (nivelActual == 2 && aliado2->estaActivo()) aliado2->dibujar(buffer->Graphics, bmpAliado2);
		else if (nivelActual == 3 && aliado3->estaActivo()) aliado3->dibujar(buffer->Graphics, bmpAliado3);

		// LOGICA NPC (Civiles)
		if (consejoMostrado && enemigosRestantes >= 0) {
			if (npcActual == nullptr)
			{
				contadorSpawnNPC++;
				if (contadorSpawnNPC >= tiempoParaProximoNPC) {
					Random^ r = gcnew Random();
					npcActual = new NPC(r->Next(100, Width - 100), r->Next(100, Height - 150), 64, 64);
					npcActual->tipo = r->Next(1, 3);
					contadorSpawnNPC = 0;
					tiempoParaProximoNPC = r->Next(100, 161); // 5-8 Segs
				}
			}
			else
			{
				Bitmap^ spr;
				if (nivelActual == 1) spr = (npcActual->tipo == 1) ? bmpFuturista1 : bmpFuturista2;
				else if (nivelActual == 2) spr = (npcActual->tipo == 1) ? bmpVagabundo1 : bmpVagabundo2;
				else spr = (npcActual->tipo == 1) ? bmpCampesino1 : bmpCampesino2;

				if (spr != nullptr) npcActual->dibujar(buffer->Graphics, spr);

				// Colision NPC
				if (hitJugador.IntersectsWith(npcActual->getHitbox()))
				{
					mostrarFraseNPC = true; tiempoFrase = 60;
					xFrase = npcActual->getX(); yFrase = npcActual->getY() - 30;
					Random^ r = gcnew Random();
					int indiceFrase = r->Next(0, 3); // 0, 1 o 2 (3 FRASES ALEATORIAS)

					if (!oJugador->atacando)
					{
						// AMISTOSO: +1 Confianza
						if (barraConfianza->Value < 4) barraConfianza->Value += 1;

						if (nivelActual == 1) {
							if (indiceFrase == 0) textoFraseNPC = "¡Confio en ti!";
							else if (indiceFrase == 1) textoFraseNPC = "¡Acaba con los robots!";
							else textoFraseNPC = "¡Por la humanidad!";
						}
						else if (nivelActual == 2) {
							if (indiceFrase == 0) textoFraseNPC = "Gracias...";
							else if (indiceFrase == 1) textoFraseNPC = "Cuidado con las sombras.";
							else textoFraseNPC = "¿Tienes comida?";
						}
						else {
							if (indiceFrase == 0) textoFraseNPC = "Por la paz.";
							else if (indiceFrase == 1) textoFraseNPC = "Que vivan los humanos.";
							else textoFraseNPC = "No dejes que saboteen esto.";
						}
						delete npcActual; npcActual = nullptr;
						verificarCondicionGanar();
					}
					else
					{
						// ATAQUE: -1 Confianza
						if (barraConfianza->Value > 0) barraConfianza->Value -= 1;
						textoFraseNPC = "¡AYUDA! ¡AGRESION!";
						delete npcActual; npcActual = nullptr;
					}
				}
			}
		}

		if (mostrarFraseNPC) {
			buffer->Graphics->DrawString(textoFraseNPC, gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::White, xFrase, yFrase);
			tiempoFrase--; if (tiempoFrase <= 0) mostrarFraseNPC = false;
		}

		// Interacciones Inicio
		if (!consejoMostrado)
		{
			if (nivelActual == 1 && aliado1->estaActivo() && hitJugador.IntersectsWith(aliado1->getHitbox())) mostrarConsejoNivel(1);

			if (nivelActual == 2 && aliado2->estaActivo() && hitJugador.IntersectsWith(aliado2->getHitbox())) {
				mostrarConsejoNivel(2);
				if (!poderVelocidadActivo && !itemVelocidadEnSuelo) {
					itemVelocidadEnSuelo = true; Random^ r = gcnew Random();
					itemVelocidad->setX(r->Next(50, Width - 100)); itemVelocidad->setY(r->Next(50, Height - 150));
				}
			}
			if (nivelActual == 3 && aliado3->estaActivo() && hitJugador.IntersectsWith(aliado3->getHitbox())) {
				mostrarConsejoNivel(3);
				if (!poderLentitudActivo && !itemLentitudEnSuelo) {
					itemLentitudEnSuelo = true; Random^ r = gcnew Random();
					itemLentitud->setX(r->Next(50, Width - 100)); itemLentitud->setY(r->Next(50, Height - 150));
				}
			}
		}

		// Enemigos
		Enemigo* enemigosActivos[3];
		if (nivelActual == 1) { enemigosActivos[0] = oEnemigo; enemigosActivos[1] = oEnemigo2; enemigosActivos[2] = oEnemigo3; }
		else if (nivelActual == 2) { enemigosActivos[0] = oSombra1; enemigosActivos[1] = oSombra2; enemigosActivos[2] = oSombra3; }
		else if (nivelActual == 3) { enemigosActivos[0] = oRata1; enemigosActivos[1] = oRata2; enemigosActivos[2] = oRata3; }
		else { enemigosActivos[0] = nullptr; enemigosActivos[1] = nullptr; enemigosActivos[2] = nullptr; }

		// === AUMENTAR HITBOX ATAQUE JUGADOR ===
		// Obtener caja original y hacerla mas grande (30 pixeles mas)
		Rectangle areaAtaqueJugador = oJugador->getHitboxAtaque();
		areaAtaqueJugador.Inflate(30, 30); // <--- CAMBIO: AUMENTA RANGO ATAQUE

		for (int i = 0; i < 3; i++) {
			Enemigo* e = enemigosActivos[i];
			if (e == nullptr || !e->vivo) continue;

			e->moverHaciaJugador(oJugador);
			Bitmap^ spr = bmpEnemigo; if (nivelActual == 2) spr = bmpSombra; else if (nivelActual == 3) spr = bmpRata;
			e->mover(buffer, spr, spr);

			// Colisión Ataque Aumentada
			if (oJugador->atacando && (oJugador->indiceAtaque == 2 || oJugador->indiceAtaque == 3)) {
				// Usamos areaAtaqueJugador (la inflada) en vez de la original
				if (areaAtaqueJugador.IntersectsWith(Rectangle(e->getX(), e->getY(), e->getAncho(), e->getAlto()))) {
					if (!oJugador->yaGolpeoEnEsteAtaque) {
						e->vida--; oJugador->yaGolpeoEnEsteAtaque = true;
						mostrarDaño = true; dañoX = e->getX(); dañoY = e->getY(); tiempoDaño = 15;
						if (e->vida <= 0) {
							e->vivo = false; enemigosRestantes--;
							verificarCondicionGanar();

							Random^ rBot = gcnew Random();
							int prob = rBot->Next(0, 100); // 0 a 99

							if (prob < 50 && !botiquinActivo)  // 50% y solo si no hay uno activo
							{
								botiquinActivo = true;
								botiquin->setX(e->getX());
								botiquin->setY(e->getY());
							}
						}
					}
				}
			}
			if (oJugador->vivo && !oJugador->invulnerable &&
				hitJugador.IntersectsWith(Rectangle(e->getX(), e->getY(), e->getAncho(), e->getAlto()))) {

				oJugador->vida--;
				barraVida->Value = oJugador->vida;

				if (oJugador->vida <= 0) {
					oJugador->vivo = false;

					// NUEVO GAME OVER POR FORMULARIO
					timer1->Enabled = false;
					FormFinJuego^ f = gcnew FormFinJuego();
					f->MostrarResultado(false);  // false = perdió
					f->ShowDialog();
					this->Close();               // cerramos el juego
					return;
				}

				oJugador->invulnerable = true;
				oJugador->tiempoInvulnerable = 30;

				mostrarDaño = true;
				dañoX = oJugador->getX();
				dañoY = oJugador->getY();
				tiempoDaño = 15;
			}
		}
		if (oJugador->invulnerable) { oJugador->tiempoInvulnerable--; if (oJugador->tiempoInvulnerable <= 0) oJugador->invulnerable = false; }

		// --- LOGICA POWER UPS (INFINITOS) ---
		// Velocidad
		if (nivelActual == 2 && itemVelocidadEnSuelo) {
			itemVelocidad->dibujar(buffer, bmpVelocidad);
			if (hitJugador.IntersectsWith(Rectangle(itemVelocidad->getX(), itemVelocidad->getY(), 24, 24))) {
				itemVelocidadEnSuelo = false; poderVelocidadActivo = true;
				oJugador->setVelocidad(18); tiempoVelocidad = 150;
			}
		}
		if (poderVelocidadActivo) {
			tiempoVelocidad--;
			buffer->Graphics->DrawString("VELOCIDAD", gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold), Brushes::Cyan, 12, 60);
			if (tiempoVelocidad <= 0) {
				poderVelocidadActivo = false;
				oJugador->setVelocidad(10);

				// REAPARECER ITEM EN OTRO LADO (Uno tras otro)
				itemVelocidadEnSuelo = true;
				Random^ r = gcnew Random();
				itemVelocidad->setX(r->Next(50, Width - 100));
				itemVelocidad->setY(r->Next(50, Height - 150));
			}
		}

		// Lentitud
		if (nivelActual == 3 && itemLentitudEnSuelo) {
			itemLentitud->dibujar(buffer, bmpLentitud);
			if (hitJugador.IntersectsWith(Rectangle(itemLentitud->getX(), itemLentitud->getY(), 24, 24))) {
				itemLentitudEnSuelo = false; poderLentitudActivo = true;
				oRata1->setVelocidad(1); oRata2->setVelocidad(1); oRata3->setVelocidad(1);
				tiempoLentitud = 150;
			}
		}
		if (poderLentitudActivo) {
			tiempoLentitud--;
			buffer->Graphics->DrawString("CONGELAR", gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold), Brushes::Blue, 12, 60);
			if (tiempoLentitud <= 0) {
				poderLentitudActivo = false;
				oRata1->setVelocidad(3); oRata2->setVelocidad(3); oRata3->setVelocidad(3);

				// REAPARECER ITEM EN OTRO LADO
				itemLentitudEnSuelo = true;
				Random^ r = gcnew Random();
				itemLentitud->setX(r->Next(50, Width - 100));
				itemLentitud->setY(r->Next(50, Height - 150));
			}
		}

		if (botiquinActivo) {
			botiquin->dibujar(buffer, bmpBotiquin);
			if (hitJugador.IntersectsWith(Rectangle(botiquin->getX(), botiquin->getY(), 24, 21))) {
				botiquinActivo = false; oJugador->vida++;
				if (oJugador->vida > 5) oJugador->vida = 5; barraVida->Value = oJugador->vida;
				mostrarCura = true; curaX = oJugador->getX(); curaY = oJugador->getY(); tiempoCura = 15;
			}
		}

		if (mostrarAvisoNivel) {
			buffer->Graphics->DrawString(textoAvisoNivel, gcnew System::Drawing::Font("Arial", 28, FontStyle::Bold), Brushes::Yellow, Width / 2 - 150, 100);
			tiempoAviso--; if (tiempoAviso <= 0) mostrarAvisoNivel = false;
		}
		if (mostrarDaño) {
			dañoY -= 2; buffer->Graphics->DrawString("-1", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::Red, dañoX, dañoY);
			tiempoDaño--; if (tiempoDaño <= 0) mostrarDaño = false;
		}
		if (mostrarCura) {
			curaY -= 2; buffer->Graphics->DrawString("+1", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::LimeGreen, curaX, curaY);
			tiempoCura--; if (tiempoCura <= 0) mostrarCura = false;
		}

		// === GUI ===
		int guiX = Width - 200;
		buffer->Graphics->DrawString("MISIONES NIVEL " + nivelActual, gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold | FontStyle::Underline), Brushes::White, guiX, 10);
		int eRest = (enemigosRestantes < 0) ? 0 : enemigosRestantes;
		Brush^ cEn = (eRest == 0) ? Brushes::Lime : Brushes::Yellow;
		Brush^ cCo = (barraConfianza->Value >= 4) ? Brushes::Lime : Brushes::Yellow;
		buffer->Graphics->DrawString("- Eliminar: " + eRest + " rest.", gcnew System::Drawing::Font("Arial", 9, FontStyle::Bold), cEn, guiX, 35);
		buffer->Graphics->DrawString("- Confianza: " + barraConfianza->Value + " / 4", gcnew System::Drawing::Font("Arial", 9, FontStyle::Bold), cCo, guiX, 55);

		// Barra Azul Manual
		buffer->Graphics->FillRectangle(Brushes::Gray, 151, 29, 121, 25);
		if (barraConfianza->Maximum > 0) {
			float porcentaje = (float)barraConfianza->Value / 4.0f;
			int anchoRelleno = (int)(porcentaje * 121);
			if (anchoRelleno > 0) buffer->Graphics->FillRectangle(Brushes::Blue, 151, 29, anchoRelleno, 25);
		}
		buffer->Graphics->DrawRectangle(Pens::White, 151, 29, 121, 25);
		buffer->Graphics->DrawString(barraConfianza->Value + " / 4", gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold), Brushes::White, 190, 32);

		buffer->Render(g);
		delete buffer; delete espacio; delete g;
	}

	private: System::Void precionarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) { case Keys::Left: oJugador->direccion = Direcciones::Izquierda; break; case Keys::Right: oJugador->direccion = Direcciones::Derecha; break; case Keys::Up: oJugador->direccion = Direcciones::Arriba; break; case Keys::Down: oJugador->direccion = Direcciones::Abajo; break; }
											 if (e->KeyCode == Keys::A) { oJugador->atacando = true; oJugador->indiceAtaque = 0; oJugador->yaGolpeoEnEsteAtaque = false; }
	}
	private: System::Void soltarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) { oJugador->direccion = Direcciones::Ninguna; }
	private: System::Void FormCerrar(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) { Application::Exit(); }
	private: System::Void barraVida_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void progressBar1_Click(System::Object^ sender, System::EventArgs^ e) {}
	};
}