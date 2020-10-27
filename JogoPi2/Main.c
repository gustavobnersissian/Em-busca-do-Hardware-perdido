#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define W 640
#define H 480
#define FPS 60.0
#define FrameFps 20.0

//Criação de uma struct que vai receber todos as imagens de sprite do Main Character
struct objeto
{
	ALLEGRO_BITMAP* imagem;
	float x;
	float y;
	int largura;
	int altura;
};

typedef struct objeto Objeto;

Objeto* personagem, * sprite_parado;

//Criação de ponteiros
ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_BITMAP* frame = NULL;
ALLEGRO_BITMAP* frame2 = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_TIMER* frametimer = NULL;

bool jogando = true;
int pressionadox = 0;
int i = 0;
int aux = 0;
int j = 0;

//Inicializa a biblioteca allegro com seus respectivos addons
bool inicializar() {

	al_init();

	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	timer = al_create_timer(1.0 / FPS);
	frametimer = al_create_timer(1.0 / FrameFps);

	janela = al_create_display(640, 480);
	fila_eventos = al_create_event_queue();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_window_title(janela, "Em busca do Hardware Perdido");

	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_register_event_source(fila_eventos, al_get_timer_event_source(frametimer));


	return true;
}

//Destrói os ponteiros e libera a memória
void finalizar() {

	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);
	al_destroy_bitmap(frame);
	al_destroy_bitmap(frame2);

	/*al_destroy_bitmap(personagem->imagem);
	al_destroy_bitmap(sprite_parado->imagem);
	al_destroy_bitmap(sprite_pulando->imagem);
	al_destroy_bitmap(frame2);
	al_destroy_bitmap(frame3);
	al_destroy_timer(timer);
	free(personagem);
	free(sprite_parado);
	free(sprite_pulando);*/
}


int main(void) {


	if (!inicializar()) {
		return -1;
	}

	ALLEGRO_KEYBOARD_STATE key_state;

	enum Direction { UP, DOWN, LEFT, RIGHT, IDLE };

	personagem = (Objeto*)malloc(sizeof(Objeto));
	personagem->imagem = al_load_bitmap("Sprites/MC_Sprite_walk.png");
	personagem->largura = 490;
	personagem->altura = 49;
	personagem->y = (480 / 2) - 49;
	personagem->x = 0;

	sprite_parado = (Objeto*)malloc(sizeof(Objeto));
	sprite_parado->imagem = al_load_bitmap("Sprites/MC_Sprite_idle.png");
	sprite_parado->x = personagem->x;
	sprite_parado->largura = 440;
	sprite_parado->altura = 49;
	sprite_parado->y = personagem->y;
	/*
	sprite_pulando = (Objeto*)malloc(sizeof(Objeto));
	sprite_pulando->imagem = al_load_bitmap("Sprites/MC_Sprite_jump.png");
	sprite_pulando->largura = 469;
	sprite_pulando->altura = 49;
	*/
	int dir = IDLE;
	bool draw = false, draw2 = true, ativo = false;
	int pressionando = 0;
	float velocidade_movimento = 2.5;
	float velx, vely;
	velx = vely = 0;

	bool pulando = false;
	float velocidade_pulo = 15;

	const float gravidade = 1;

	int sourceX = 0;


	/*for (i = 0; i < 10; i++) {
		frame[i] = al_create_sub_bitmap(personagem->imagem, (personagem->largura / 10) * i, 0, personagem->largura / 10, personagem->altura);
	}*/

	al_start_timer(timer);
	al_start_timer(frametimer);

	while (jogando)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		al_get_keyboard_state(&key_state);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			jogando = 0;
		}

		if (evento.type == ALLEGRO_EVENT_TIMER) {

			if (evento.timer.source == timer) {

				ativo = true;

				pressionando = 0;

				if (al_key_down(&key_state, ALLEGRO_KEY_UP) && pulando) {
					vely = -velocidade_pulo;
					pulando = false;
				}
				if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) {
					velx = velocidade_movimento;

					j = 1;

					pressionando = 1;
				}
				else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT)) {
					velx = -velocidade_movimento;
					
					j = 0; 

					pressionando = 1;
				}
				else {
					ativo = false;
					velx = 0;
				}	

				if(!pulando){
					vely += gravidade;
				}
				else {
					vely = 0;
				}
				personagem->x += velx;
				personagem->y += vely;
			
				pulando = (personagem->y + 49 >= 480);

				if (pulando) {
					personagem->y = 480 - 49;
				}

			}

			
			if (evento.timer.source == frametimer) {
				if (ativo) {
					sourceX += al_get_bitmap_width(personagem->imagem) / 10;
				}
				else {
					sourceX = 0;
				}
				if (sourceX >= al_get_bitmap_width(personagem->imagem)) {
					sourceX = 0;
				}

				if (pressionando == 1) {
					draw = true;
				}
				
				if (pressionando == 0) {

					i++;

					if (i > 10) {
						i = 0;
					}

					draw2 = true;
				}
			}

		}
		if (draw) {
			draw = false;

			//frame = al_create_sub_bitmap(personagem->imagem, (personagem->largura / 10) * i, 0, personagem->largura / 10 - 5, personagem->altura);

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap_region(personagem->imagem, sourceX, 0, personagem->largura/10, personagem->altura, personagem->x, personagem->y, j);
			al_flip_display();

		}
		else if (draw2) {
			draw2 = false;

			frame2 = al_create_sub_bitmap(sprite_parado->imagem, (sprite_parado->largura / 11) * i, 0, sprite_parado->largura / 11, sprite_parado->altura);
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(frame2, personagem->x, personagem->y, j);
			al_flip_display();
		}
	}
	finalizar();

	return 0;
}
