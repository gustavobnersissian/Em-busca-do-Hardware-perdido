#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



#define LARGURA 640
#define ALTURA 480
#define FPS 60.0
#define FrameFps 20.0
#define BlockSize 40
#define Chao 411


//Criação de uma struct que vai receber todos as imagens de sprite 
struct objeto
{
    ALLEGRO_BITMAP* imagem;
    float x;
    float y;
    int largura;
    int altura;
};

typedef struct objeto Objeto;

Objeto* personagem, * sprite_parado, * goblin;

ALLEGRO_KEYBOARD_STATE key_state;


ALLEGRO_BITMAP* frame = NULL;
ALLEGRO_BITMAP* frame2 = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_TIMER* frametimer = NULL;
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

//variaveis

int jogando = 1, menu = 1;

int pressionadox = 0;
int i = 0;
int aux = 0;
int j = 0;
int k = 0;

bool draw = false, draw2 = true, ativo = false;
int pressionando = 0;
float velocidade_movimento = 4.5;
float velx, vely;
velx = 0;
vely = 0;

bool pulando = false;
float velocidade_pulo = 15;

const float gravidade = 0.80;

int sourceX = 0, sourceX_inimigo = 0;

bool inimigo1 = true, inimigo2 = true;
int velocidade_inimigo = 1.5;


void movimentarSprite(ALLEGRO_KEYBOARD_STATE key_state) {

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

            if (!pulando) {
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

            if (personagem->x - goblin->x < 0) {
                goblin->x -= velocidade_inimigo;
                j = 0;
            }
            else if (personagem->x - goblin->x > 0) {
                goblin->x += velocidade_inimigo;
                j = 1;
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


            if (inimigo1) {
                sourceX_inimigo += al_get_bitmap_width(goblin->imagem) / 4;
            }
            else {
                sourceX_inimigo = 0;
            }
            if (sourceX_inimigo >= al_get_bitmap_width(goblin->imagem)) {
                sourceX_inimigo = 0;
            }
        }

    }

}



void desenharSprite() {
    if (draw) {
        draw = false;

        //frame = al_create_sub_bitmap(personagem->imagem, (personagem->largura / 10) * i, 0, personagem->largura / 10 - 5, personagem->altura);

        al_draw_bitmap_region(personagem->imagem, sourceX, 0, personagem->largura / 10, personagem->altura, personagem->x, personagem->y, j);
        al_flip_display();

    }
    else if (draw2) {
        draw2 = false;

        frame2 = al_create_sub_bitmap(sprite_parado->imagem, (sprite_parado->largura / 11) * i, 0, sprite_parado->largura / 11, sprite_parado->altura);
        al_draw_bitmap(frame2, personagem->x, personagem->y, j);
        al_flip_display();
    }
    if (inimigo1) {

        al_draw_bitmap(vermelho, 0, 0, 0);
        al_draw_bitmap_region(goblin->imagem, sourceX, 0, goblin->largura / 4, goblin->altura, goblin->x, goblin->y, k);
        al_flip_display();
    }
}

void colisaoGoblin() {
    if ((personagem->x + personagem->largura >= goblin->x &&
        personagem->x + personagem->largura <= goblin->x && personagem->y + personagem->altura <= goblin->y &&
        personagem->y + personagem->altura >= goblin->y)) {

        return 0;
    }
}

void carregaArquivos() {

    musica = al_load_audio_stream("musica.ogg", 4, 1024);
    // Carrega a imagem
    background = al_load_bitmap("menu1.jpg");
    //carrega o stream
    azul = al_load_bitmap("azul.png");
    vermelho = al_load_bitmap("vermelha.png");
    som = al_load_sample("som.ogg");
    infos = al_load_bitmap("infos.png");
    cred = al_load_bitmap("cred.png");

}

int introducao[3];

void intro() {
    
    int foto1 = al_load_bitmap("1.png");
    int foto2 = al_load_bitmap("2.png");
    int foto3 = al_load_bitmap("3.png");

    introducao[0] = foto1;
    introducao[1] = foto2;
    introducao[2] = foto3;

}

int inicializacao() {

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    timer = al_create_timer(1.0 / FPS);
    frametimer = al_create_timer(1.0 / FrameFps);

    janela = al_create_display(640, 480);
    fila_eventos = al_create_event_queue();
    al_set_window_title(janela, "Em busca do Hardware Perdido");

    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_timer_event_source(frametimer));

    //audio
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);

    return 1;
}

int info(ALLEGRO_BITMAP* infos) {


    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(infos, 0, 0, 0);
    al_flip_display();

    bool done = true;

    while (done) {


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


    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(cred, 0, 0, 0);
    al_flip_display();

    bool done = true;

    while (done) {


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


    bool jogando3 = true;

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(vermelho, 0, 0, 0);
    al_flip_display();

    while (jogando3) {



        //al_draw_bitmap(azul, 0, 0, 0);

        al_wait_for_event(fila_eventos, &evento);

        // Atualiza a tela
        al_flip_display();

        movimentarSprite(key_state);

        colisaoGoblin();

        desenharSprite();

            //se for na porta vermelha
            if ((personagem->x >= 58 &&
                personagem->x <= 127 && personagem->y <= 410 &&
                personagem->y >= 326)) {

                jogo(azul);
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

    
    bool jogando2 = true;
    

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(azul, 0, 0, 0);
    al_flip_display();

    while (jogando2) {


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

    personagem = (Objeto*)malloc(sizeof(Objeto));
    personagem->imagem = al_load_bitmap("Sprites/MC_Sprite_walk.png");
    personagem->largura = 490;
    personagem->altura = 49;
    personagem->y = Chao - personagem->altura;
    personagem->x = 0;

    sprite_parado = (Objeto*)malloc(sizeof(Objeto));
    sprite_parado->imagem = al_load_bitmap("Sprites/MC_Sprite_idle.png");
    sprite_parado->x = personagem->x;
    sprite_parado->largura = 440;
    sprite_parado->altura = 49;
    sprite_parado->y = personagem->y;

    goblin = (Objeto*)malloc(sizeof(Objeto));
    goblin->imagem = al_load_bitmap("Sprites/goblins.png");
    goblin->x = 250;
    goblin->y = Chao - goblin->altura;
    goblin->largura = 256;
    goblin->altura = 49;


    al_start_timer(timer);
    al_start_timer(frametimer);


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
            if ((evento.mouse.x >= 590 &&
                evento.mouse.x <= 630 && evento.mouse.y <= 42 &&
                evento.mouse.y >= 6)) {

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
    al_destroy_bitmap(frame);
    al_destroy_bitmap(frame2);
    al_destroy_timer(timer);
    free(personagem);
    free(sprite_parado);
    free(goblin);


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