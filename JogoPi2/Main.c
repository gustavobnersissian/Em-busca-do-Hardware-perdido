#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define Width 640
#define Height 480

int main(void) {

	struct objeto
	{
		ALLEGRO_BITMAP* imagem;
		int x;
		int y;
		int largura;
		int altura;
	};

	typedef struct objeto Objeto;

	ALLEGRO_DISPLAY* janela = NULL;
	ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
	Objeto* barra;

	al_init();

	al_init_image_addon();
	al_install_mouse();
	al_install_keyboard();

	janela = al_create_display(Width, Height);
	fila_eventos = al_create_event_queue();
	al_clear_to_color(al_map_rgb(0, 0, 0)); 
	al_set_window_title(janela, "Em busca do Hardware Perdido");

	al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_register_event_source(fila_eventos, al_get_mouse_event_source());
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	barra = (Objeto*)malloc(sizeof(Objeto));
	barra->imagem = al_load_bitmap("barra.png");
	barra->x = 8;
	barra->y = 480 / 2 - 150 / 2;
	barra->largura = 20;
	barra->altura = 150;

	bool jogando = true;
	int pressionado = 0;
	int pressionadox = 0;
	int ciclos = 0;

	while (jogando) {

		while (!al_is_event_queue_empty(fila_eventos)) {
			
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);

			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);

			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				jogando = 0;
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
				switch (evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					pressionado = -2;
					break;
				case ALLEGRO_KEY_DOWN:
					pressionado = 2;
					break;

				case ALLEGRO_KEY_LEFT:
					pressionadox = -2;
					break;
				case ALLEGRO_KEY_RIGHT:
					pressionadox = 2;
					break;
			}
			}
			else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
				pressionado = 0;
				pressionadox = 0;
			}
		}

		ciclos++;
		if (ciclos % 10 == 0) {

			if (pressionado != 0) {
				if (!(barra->y + pressionado <= 0 || barra->y + barra->altura + pressionado >= 480)) {
					barra->y += pressionado;
				}
			}
			if (pressionadox != 0) {
				if (!(barra->x + pressionado <= 0 || barra->x + barra->largura + pressionado >= 640)) {
					barra->x += pressionadox;
				}
			}

		}

		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(barra->imagem, barra->x, barra->y, 0);

		al_flip_display();
	}

	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);

	return 0;
}