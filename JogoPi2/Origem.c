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
ALLEGRO_SAMPLE* som = NULL;
ALLEGRO_BITMAP* infos = NULL;
ALLEGRO_BITMAP* cred = NULL;

jogo(azul);
jogo2(vermelho);


int menu = 1;

void carregaArquivos() {

    musica = al_load_audio_stream("musica.ogg", 4, 1024);
    // Carrega a imagem
    background = al_load_bitmap("menu1.png");
    //carrega o stream
    azul = al_load_bitmap("azul.png");
    vermelho = al_load_bitmap("vermelha.png");
    som = al_load_sample("som.ogg");
    infos = al_load_bitmap("infos.png");
    cred = al_load_bitmap("cred.png");
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

int info(ALLEGRO_BITMAP* infos) {

    inicializacao();
    carregaArquivos();

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(infos, 0, 0, 0);
    al_flip_display();

    bool done = true;

    while (done) {

        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos, al_get_mouse_event_source());
        al_register_event_source(fila_eventos, al_get_display_event_source(janela));

        //al_draw_bitmap(azul, 0, 0, 0);

        al_wait_for_event(fila_eventos, &evento);

        // Atualiza a tela
        al_flip_display();


        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            
            if ((evento.mouse.x >= 566 &&
                evento.mouse.x <= 619 && evento.mouse.y <= 57 &&
                evento.mouse.y >= 10)) {

                return 0;
            }
        }

    }

    return 0;
}


int creditos(ALLEGRO_BITMAP* cred) {

    inicializacao();
    carregaArquivos();

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(cred, 0, 0, 0);
    al_flip_display();

    bool done = true;

    while (done) {

        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos, al_get_mouse_event_source());
        al_register_event_source(fila_eventos, al_get_display_event_source(janela));

        //al_draw_bitmap(azul, 0, 0, 0);

        al_wait_for_event(fila_eventos, &evento);

        // Atualiza a tela
        al_flip_display();


        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {


            if ((evento.mouse.x >= 566 &&
                evento.mouse.x <= 619 && evento.mouse.y <= 57 &&
                evento.mouse.y >= 10)) {

                return 0;
            }
        }

    }

    return 0;
}


int jogo2(ALLEGRO_BITMAP* vermelho) {

    inicializacao();


    bool jogando3 = true;
    carregaArquivos();

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(vermelho, 0, 0, 0);
    al_flip_display();

    while (jogando3) {

        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos, al_get_mouse_event_source());
        al_register_event_source(fila_eventos, al_get_display_event_source(janela));

        //al_draw_bitmap(azul, 0, 0, 0);

        al_wait_for_event(fila_eventos, &evento);

        // Atualiza a tela
        al_flip_display();

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            //se for na porta vermelha
            if ((evento.mouse.x >= 58 &&
                evento.mouse.x <= 127 && evento.mouse.y <= 410 &&
                evento.mouse.y >= 326)) {

                jogo(azul);
            }
        }
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {


            if ((evento.mouse.x >= 0 &&
                evento.mouse.x <= 38 && evento.mouse.y <= 37 &&
                evento.mouse.y >= 1)) {

                return 0;
            }
        }


    }
    return 0;
}
//disp = janela

int jogo(ALLEGRO_BITMAP* azul) {

    inicializacao();
    bool jogando2 = true;
    carregaArquivos();

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(azul, 0, 0, 0);
    al_flip_display();

    while (jogando2) {

        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos, al_get_mouse_event_source());
        al_register_event_source(fila_eventos, al_get_display_event_source(janela));

        //al_draw_bitmap(azul, 0, 0, 0);

        al_wait_for_event(fila_eventos, &evento);

        // Atualiza a tela
        al_flip_display();

        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            //se for na porta azul
            if ((evento.mouse.x >= 507 &&
                evento.mouse.x <= 570 && evento.mouse.y <= 411 &&
                evento.mouse.y >= 315)) {

                jogo2(vermelho);
            }
            
        }
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {


            if ((evento.mouse.x >= 0 &&
                evento.mouse.x <= 38 && evento.mouse.y <= 37 &&
                evento.mouse.y >= 1)) {

                return 0;
            }
        }



    }
    return 0;
}




int main()
{

    inicializacao();

    janela = al_create_display(LARGURA, ALTURA);

    carregaArquivos();

    //audio
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playmode(musica, ALLEGRO_PLAYMODE_LOOP);

    // Atualiza a tela
    al_flip_display();

    int jogando = 1, menu = 1;

    while (jogando && menu == 1)
    {


        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos, al_get_mouse_event_source());
        al_register_event_source(fila_eventos, al_get_display_event_source(janela));

        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_bitmap(background, 0, 0, 0);

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


                info(infos);
            }
        }
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && menu == 1) {
            
            //se for jogar
            if ((evento.mouse.x >= 217 &&
                evento.mouse.x <= 400 && evento.mouse.y <= 204 &&
                evento.mouse.y >= 144)) {

                jogo(azul);
            }
        }
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            //se for creditos
            if ((evento.mouse.x >= 210 &&
                evento.mouse.x <= 405 && evento.mouse.y <= 390 &&
                evento.mouse.y >= 330)) {

                creditos(cred);
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
    al_destroy_bitmap(azul);
    al_destroy_bitmap(azul);
    al_destroy_bitmap(infos);
    al_destroy_bitmap(vermelho);
    al_destroy_bitmap(cred);

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