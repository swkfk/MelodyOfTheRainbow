/* 此文件定义了一系列打开相应模块的宏，最终版本并非所有宏均需要打开 */

#ifndef __MODULE_START_H__
#define __MODULE_START_H__

/* 以下为正常模块、组件 */

#define _Led_group    /* Led 灯组 */
#define _Button_group /* 按钮组 */
#define _Piano        /* 钢琴触摸与钢琴的背光灯 */
#define _Tcs          /* 色彩识别模块 */
#define _Buzzer       /* 蜂鸣器模块 */

/* 以下为测试模块 */

// #define _Endless_flow_leds     /* 开机时的跑马灯将无限循环下去 */
#define _Show_keypressed       /* 将钢琴按下的键打印到串口中 */
#define _Show_buzzer_tone      /* 将蜂鸣器的理论输出值打印在串口中 */
#define _Show_color_recognized /* 将识别到的颜色打印在串口中 */
// #define _Show_button           /* 将读到的按钮输出到串口 */
// #define _Show_Mode             /* 将 loop() 中的模式打印出来 */

#endif
