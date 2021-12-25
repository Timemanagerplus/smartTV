#define LV_USE_DEMO_WIDGETS
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <lv_demo.h>

/*
  TFT_SET
*/
TFT_eSPI tft = TFT_eSPI();
void TFT_Init(){
  tft.init();
  tft.setRotation(0);
}


static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];
static lv_disp_drv_t disp_drv;
/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();
    Serial.print("It is printing");

    lv_disp_flush_ready( disp );
}


void LV_Init(){
    lv_init();
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 10 );
    /*Initialize the display*/
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );
}

void setup() {
  TFT_Init();
  LV_Init();
  // put your setup code here, to run once:
  //Serial.begin(9600);
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    //lv_demo_widgets();            // OK
    lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text( label, LVGL_Arduino.c_str() );
    //lv_label_set_text( label, "i love you" )kk;
    lv_label_set_recolor(label, true);//先得使能文本重绘色功能
    lv_label_set_text( label, "#ff0000 red#,#00ff00 green#,#0000ff blue#" );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
    lv_obj_set_size(label,200,5);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  lv_obj_t *label_1 = lv_label_create( lv_scr_act() );
    //lv_label_set_text( label, LVGL_Arduino.c_str() );
    lv_label_set_text(label_1, "you love me" );
    lv_obj_align( label_1, LV_ALIGN_CENTER, 0, 10 );
    lv_timer_handler(); /* let the GUI do its work */
    while(1){
      Serial.print("init is ok\n");
      delay(5);
    }
}