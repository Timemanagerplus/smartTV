#define LV_USE_DEMO_WIDGETS
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <lv_demo.h>
#include <esp_http_client.h>

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
  // put your setup code here, to run once:
  Serial.begin(9600);
  TFT_Init();
  LV_Init();
}
char num[5]={'1','2','3','4','\0'};

void Num2Char(int num,char* str){
    int i;
    int tmp=num;
    for(i=3;i>=0;i--){
        *(str+i) = tmp%10+'0';
        tmp = tmp/10;
    }
    *(str+4) = '\0';
}

void loop() {
  // put your main code here, to run repeatedly:

    lv_obj_t *label_1 = lv_label_create( lv_scr_act() );
    lv_obj_set_align(label_1,LV_ALIGN_CENTER);
    lv_label_set_text(label_1, "you love me" );
    
    int i=0;
    while(1){
        Num2Char(i,num);
        Serial.printf("%s\n",num);
        //Serial.printf("%d",i);
        lv_label_set_text(label_1,num);
        lv_timer_handler(); /* let the GUI do its work */
        delay(50);
        lv_label_set_text(label_1,"you");
        i ++;
    }
}