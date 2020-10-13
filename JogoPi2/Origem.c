#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


#define LARGURA 640
#define ALTURA 480


int menu(jogando, evento);

ALLEGRO_TIMER* timer = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_FONT* fonte = NULL;
// Variável representando a imagem
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_EVENT evento;
ALLEGRO_AUDIO_STREAM* musica = NULL;



void carregaArquivos() {

    // Carrega a imagem
    background = al_load_bitmap("menu.png");
    //carrega o stream
   

}

int inicializacao() {

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    fila_eventos = al_create_event_queue();

    //audio
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);

    return 1;
}

//disp = janela

int main()
{

    inicializacao();

    janela = al_create_display(LARGURA, ALTURA);

    //isso fica no main
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));



    carregaArquivos();

    // Desenha a imagem na tela
    al_draw_bitmap(background, 0, 0, 0);
    musica = al_load_audio_stream("musica.ogg", 4, 1024);
    //audio
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);

    // Atualiza a tela
    al_flip_display();

    bool redraw = true;


    int jogando = 1;



    while (jogando)
    {
        al_wait_for_event(fila_eventos, &evento);


        if ((evento.type == ALLEGRO_EVENT_KEY_DOWN) || (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if (al_is_event_queue_empty(fila_eventos))
        {
            jogando = menu(jogando, evento);

        }

        // Atualiza a tela
        al_flip_display();

    }

    al_destroy_font(fonte);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}



int menu(int jogando, ALLEGRO_EVENT evento) {

    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        if (evento.mouse.x >= 282 &&
            evento.mouse.x <= 353 && evento.mouse.y <= 383 &&
            evento.mouse.y >= 359) {

            return NULL;
        }
    }
}