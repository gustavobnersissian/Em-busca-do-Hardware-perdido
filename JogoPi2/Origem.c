#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



#define LARGURA 640
#define ALTURA 480


//int menu(jogando, evento);

ALLEGRO_TIMER* timer = NULL;
ALLEGRO_EVENT_QUEUE* fila_eventos = NULL;
ALLEGRO_DISPLAY* janela = NULL;
ALLEGRO_FONT* fonte = NULL;
// Variável representando a imagem
ALLEGRO_BITMAP* background = NULL;
ALLEGRO_EVENT evento;
ALLEGRO_AUDIO_STREAM* musica = NULL;
//ALLEGRO_BITMAP* teste = NULL;
ALLEGRO_BITMAP* azul = NULL;
ALLEGRO_BITMAP* vermelho = NULL;



int menu = 1;

void carregaArquivos() {

    // Carrega a imagem
    background = al_load_bitmap("menu1.png");
    //carrega o stream
    azul = al_load_bitmap("azul.png");
    vermelho = al_load_bitmap("vermelho.png");
}


int mostra() {

    al_draw_bitmap(azul, 0, 0, 0);
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

    int tecla = 0;
    janela = al_create_display(LARGURA, ALTURA);

    
    



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
   

    int na_area_jogar = 0;//Diz se o mouse esta sobre a opção sair do jogo

    while (jogando)
    {


        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos, al_get_mouse_event_source());
        al_register_event_source(fila_eventos, al_get_display_event_source(janela));

        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_bitmap(background, 0, 0, NULL);

        al_wait_for_event(fila_eventos, &evento);

        // Se o evento for um clique do mouse
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && menu == 1) {

            //se o clique foi no botão sair
            if ((evento.mouse.x >= 566 &&
                evento.mouse.x <= 610 && evento.mouse.y <= 49 &&
                evento.mouse.y >= 9)) {

                //fecha o jogo
                return 0;
            }    
        }
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && menu == 1) {

            //se o clique for em infos
            if ((evento.mouse.x >= 213 &&
                evento.mouse.x <= 402 && evento.mouse.y <= 298 &&
                evento.mouse.y >= 239)) {

                
                
            }
        }
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && menu == 1) {
            
            //se for jogar
            if ((evento.mouse.x >= 217 &&
                evento.mouse.x <= 400 && evento.mouse.y <= 204 &&
                evento.mouse.y >= 144)) {

                
            }
        }

       


        /*
        if (al_is_event_queue_empty(fila_eventos))
        {




            //jogando = menu(jogando, evento);  
        }
        */
         
        // Atualiza a tela
        al_flip_display();

    }

    al_destroy_font(fonte);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}



/*
int menu(int jogando, ALLEGRO_EVENT evento) {

    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        if (evento.mouse.x >= 282 &&
            evento.mouse.x <= 353 && evento.mouse.y <= 383 &&
            evento.mouse.y >= 359) {

            return NULL;
        }
    }
}
*/