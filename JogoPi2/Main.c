#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define W 640
#define H 480
#define FPS 60

//testando um commit 


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
Objeto* personagem, *sprite_parado, *sprite_pulando;


//Criação de ponteiros
ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_BITMAP* frame = NULL;
ALLEGRO_BITMAP* frame2 = NULL;
ALLEGRO_BITMAP* frame3 = NULL;
ALLEGRO_TIMER* timer = NULL;

bool jogando = true;
int pressionadox = 0;
int ciclos = 0;
int i = 0;
int j = 0;
int aux = 0;
int vly = 0;
int grv = 10;
int caindo = 0;
int pulando = 0;
int vup = 5;
int pLimit = 0;
int chao = 240;

//Inicializa a biblioteca allegro com seus respectivos addons
bool inicializar() {

	al_init();

	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();

	timer = al_create_timer(1.0 / FPS);

	janela = al_create_display(640, 480);
	fila_eventos = al_create_event_queue();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_window_title(janela, "Em busca do Hardware Perdido");

	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));
	al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
	al_start_timer(timer);

	return true;
}

//Destrói os ponteiros e libera a memória
void finalizar() {

	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);
	al_destroy_bitmap(personagem->imagem);
	al_destroy_bitmap(sprite_parado->imagem);
	al_destroy_bitmap(sprite_pulando->imagem);
	al_destroy_bitmap(frame);
	al_destroy_bitmap(frame2);
	al_destroy_bitmap(frame3);
	al_destroy_timer(timer);
	free(personagem);
	free(sprite_parado);
	free(sprite_pulando);
}


int main(void) {


	if (!inicializar()) {
		return -1;
	}

	
	personagem = (Objeto*)malloc(sizeof(Objeto));
	personagem->imagem = al_load_bitmap("Sprites/MC_Sprite_walk.png");
	personagem->x = 0;
	personagem->largura = 501;
	personagem->altura = 49;
	personagem->y = chao;

	sprite_parado = (Objeto*)malloc(sizeof(Objeto));
	sprite_parado->imagem = al_load_bitmap("Sprites/MC_Sprite_idle.png");
	sprite_parado->x = personagem->x;
	sprite_parado->largura = 440;
	sprite_parado->altura = 49;
	sprite_parado->y = chao;

	sprite_pulando = (Objeto*)malloc(sizeof(Objeto));
	sprite_pulando->imagem = al_load_bitmap("Sprites/MC_Sprite_jump.png");
	sprite_pulando->largura = 469;
	sprite_pulando->altura = 49;


	while (jogando)
	{
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_eventos, &evento);

		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			jogando = 0;
		}

		else if (!pressionadox && al_is_event_queue_empty(fila_eventos)) {

			aux++;
			if (aux < 11) {
				i++;

			}
			if (aux > 10) {
				i--;

			}
			if (i == 0) {
				aux = 0;
			}

			frame2 = al_create_sub_bitmap(sprite_parado->imagem, (sprite_parado->largura / 11) * i, 0, sprite_parado->largura / 11, sprite_parado->altura);

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(frame2, personagem->x, personagem->y, j);

			al_flip_display();

			al_rest(0.090);

		}


		if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

			if (evento.keyboard.keycode == ALLEGRO_KEY_LEFT) {

				pressionadox = -8;
				j = 0;
			}

			if (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT) {

				pressionadox = 8;
				j = 1;

			}

			if (evento.keyboard.keycode == ALLEGRO_KEY_UP && !pulando && !vly) {
				pLimit = personagem->y;
				pulando = 1;
			}
		}
		if (evento.type == ALLEGRO_EVENT_KEY_UP) {
			pressionadox = 0;
		}

		
		if (pulando == 1 && personagem->y > pLimit - 90) {
			personagem->y += vly;
			vly = -vup;
			caindo = 1;
			/*for (i = 0; i < 5; i++) {
				frame3 = al_create_sub_bitmap(sprite_pulando->imagem, (sprite_pulando->largura / 10) * i, 0, sprite_pulando->largura / 10, sprite_pulando->altura);

				al_clear_to_color(al_map_rgb(0, 0, 0));

				al_draw_bitmap(frame3, personagem->x, personagem->y, j);

				al_flip_display();

			}*/
		}
		else if (caindo) {
			pulando = 0;
			vly += grv;
			personagem->y += vly;

			/*for (i = 5; i < 10; i++) {
				frame3 = al_create_sub_bitmap(sprite_pulando->imagem, (sprite_pulando->largura / 10) * i, 0, sprite_pulando->largura / 10, sprite_pulando->altura);

				al_clear_to_color(al_map_rgb(0, 0, 0));

				al_draw_bitmap(frame3, personagem->x, personagem->y, j);

				al_flip_display();

				al_rest(0.050);
			}*/
		}
		else {
			pulando = 0;
			vly = 0;
		}

		if (personagem->y >= chao) {
		
			caindo = 0;
		}


		if (pressionadox != 0 && al_is_event_queue_empty(fila_eventos)) {
			if (!(personagem->x + pressionadox <= 0 || personagem->x + (personagem->largura / 10) + pressionadox >= 640)) {

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

				al_rest(0.050);

			}
		}

	}
	

	finalizar();

	return 0;
}