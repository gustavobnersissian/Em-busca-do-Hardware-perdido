#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>



int menu(jogando, evento);

int main()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
    ALLEGRO_FONT* font = al_create_builtin_font();
    // Variável representando a imagem
    ALLEGRO_BITMAP* background = NULL;
    ALLEGRO_EVENT evento;


    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Carrega a imagem
    background = al_load_bitmap("menu.jpg");

    // Desenha a imagem na tela
    al_draw_bitmap(background, 0, 0, 0);

    // Atualiza a tela
    al_flip_display();

    bool redraw = true;


    int jogando = 1;

    al_start_timer(timer);
    while (jogando)
    {
        al_wait_for_event(queue, &evento);


        if ((evento.type == ALLEGRO_EVENT_KEY_DOWN) || (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if (al_is_event_queue_empty(queue))
        {
            jogando = menu(jogando, evento);

        }

        // Atualiza a tela
        al_flip_display();

    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

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