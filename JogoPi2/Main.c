#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define W 640
#define H 480
#define FPS 60

//Criação de uma struct que vai receber todos as imagens de sprite do Main Character
struct objeto
{
	ALLEGRO_BITMAP* imagem;
	int x;
	int y;
	int largura;
	int altura;
};

typedef struct objeto Objeto;
Objeto* personagem;

//Criação de ponteiros
ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_BITMAP* frame = NULL;

double tempoInicial = 0;

//Inicializa a biblioteca allegro com seus respectivos addons
bool inicializar() {

	al_init();

	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();

	janela = al_create_display(640, 480);
	fila_eventos = al_create_event_queue();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_window_title(janela, "Em busca do Hardware Perdido");

	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	return true;
}

//Destrói os ponteiros e libera a memória
void finalizar() {

	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);
	al_destroy_bitmap(personagem->imagem);
	al_destroy_bitmap(frame);
	free(personagem);

}

//Inicia um timer pegando a hora atual
void iniciarTimer() {
	tempoInicial = al_get_time();
}

//Faz o cálculo do tempo passado retornando o tempo atual menos o tempo inicial
double obterTempoTimer()
{
	return al_get_time() - tempoInicial;
}


int main(void) {


	if (!inicializar()) {
		return -1;
	}


	personagem = (Objeto*)malloc(sizeof(Objeto));
	personagem->imagem = al_load_bitmap("Sprites/MC_Sprite_walk.png");
	personagem->x = 0;
	personagem->largura = 978;
	personagem->altura = 102;
	personagem->y = (480 / 2) - (personagem->altura / 2);

	bool jogando = true;
	int pressionadox = 0;
	int ciclos = 0;
	int i = 0;
	int j = 0;
	int aux = 0;

	while (jogando)
	{
		iniciarTimer();

		while (!al_is_event_queue_empty(fila_eventos)) {

			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				jogando = 0;
			}

			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (evento.keyboard.keycode) {
				case ALLEGRO_KEY_LEFT:

					pressionadox = -8;
					j = 0;
					
					break;
				case ALLEGRO_KEY_RIGHT:

					pressionadox = 8;
					j = 1;

					break;
				}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
				pressionadox = 0;
			}
			if (pressionadox != 0) {

				if (!(personagem->x + pressionadox <= 0 || personagem->x + (personagem->largura / 10) + pressionadox >= 480)) {

					personagem->x += pressionadox;

					aux++;
					if (aux < 10) {
						i++;

					}
					if (aux > 9) {						
						i--;

					}
					if (i == 0) {
						aux = 0;
					}

					frame = al_create_sub_bitmap(personagem->imagem, (personagem->largura / 10) * i, 0, personagem->largura / 10, personagem->altura);

					al_clear_to_color(al_map_rgb(0, 0, 0));

					al_draw_bitmap(frame, personagem->x, personagem->y, j);

					al_flip_display();

					if (pressionadox && (obterTempoTimer() < 1.0 / FPS)) {
						al_rest((1.0 / FPS) - obterTempoTimer());
					}
				}

			}

			

		}
	}

	finalizar();

	return 0;
}