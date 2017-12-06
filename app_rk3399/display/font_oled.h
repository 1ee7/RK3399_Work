#ifndef __FONT_H
#define __FONT_h

const unsigned char  asc16[]={

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",0*/
0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x18,0x18,0x00,0x00,/*"!",1*/
0x00,0x48,0x6C,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*""",2*/
0x00,0x00,0x00,0x24,0x24,0x24,0x7F,0x12,0x12,0x12,0x7F,0x12,0x12,0x12,0x00,0x00,/*"#",3*/
0x00,0x00,0x08,0x1C,0x2A,0x2A,0x0A,0x0C,0x18,0x28,0x28,0x2A,0x2A,0x1C,0x08,0x08,/*"$",4*/
0x00,0x00,0x00,0x22,0x25,0x15,0x15,0x15,0x2A,0x58,0x54,0x54,0x54,0x22,0x00,0x00,/*"%",5*/
0x00,0x00,0x00,0x0C,0x12,0x12,0x12,0x0A,0x76,0x25,0x29,0x11,0x91,0x6E,0x00,0x00,/*"&",6*/
0x00,0x06,0x06,0x04,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"'",7*/
0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00,/*"(",8*/
0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00,/*")",9*/
0x00,0x00,0x00,0x00,0x08,0x08,0x6B,0x1C,0x1C,0x6B,0x08,0x08,0x00,0x00,0x00,0x00,/*"*",10*/
0x00,0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x08,0x00,0x00,0x00,/*"+",11*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x04,0x03,/*",",12*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"-",13*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00,/*".",14*/
0x00,0x00,0x80,0x40,0x40,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x02,0x02,0x00,/*"/",15*/
0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,/*"0",16*/
0x00,0x00,0x00,0x08,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,/*"1",17*/
0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x20,0x20,0x10,0x08,0x04,0x42,0x7E,0x00,0x00,/*"2",18*/
0x00,0x00,0x00,0x3C,0x42,0x42,0x20,0x18,0x20,0x40,0x40,0x42,0x22,0x1C,0x00,0x00,/*"3",19*/
0x00,0x00,0x00,0x20,0x30,0x28,0x24,0x24,0x22,0x22,0x7E,0x20,0x20,0x78,0x00,0x00,/*"4",20*/
0x00,0x00,0x00,0x7E,0x02,0x02,0x02,0x1A,0x26,0x40,0x40,0x42,0x22,0x1C,0x00,0x00,/*"5",21*/
0x00,0x00,0x00,0x38,0x24,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x24,0x18,0x00,0x00,/*"6",22*/
0x00,0x00,0x00,0x7E,0x22,0x22,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,/*"7",23*/
0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00,/*"8",24*/
0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x64,0x58,0x40,0x40,0x24,0x1C,0x00,0x00,/*"9",25*/
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,/*":",26*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x04,/*";",27*/
0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00,/*"<",28*/
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,/*"=",29*/
0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00,/*">",30*/
0x00,0x00,0x00,0x3C,0x42,0x42,0x46,0x40,0x20,0x10,0x10,0x00,0x18,0x18,0x00,0x00,/*"?",31*/
0x00,0x00,0x00,0x1C,0x22,0x5A,0x55,0x55,0x55,0x55,0x2D,0x42,0x22,0x1C,0x00,0x00,/*"@",32*/
0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00,/*"A",33*/
0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x1E,0x22,0x42,0x42,0x42,0x22,0x1F,0x00,0x00,/*"B",34*/
0x00,0x00,0x00,0x7C,0x42,0x42,0x01,0x01,0x01,0x01,0x01,0x42,0x22,0x1C,0x00,0x00,/*"C",35*/
0x00,0x00,0x00,0x1F,0x22,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1F,0x00,0x00,/*"D",36*/
0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x42,0x42,0x3F,0x00,0x00,/*"E",37*/
0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x02,0x02,0x07,0x00,0x00,/*"F",38*/
0x00,0x00,0x00,0x3C,0x22,0x22,0x01,0x01,0x01,0x71,0x21,0x22,0x22,0x1C,0x00,0x00,/*"G",39*/
0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,/*"H",40*/
0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,/*"I",41*/
0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x0F,/*"J",42*/
0x00,0x00,0x00,0x77,0x22,0x12,0x0A,0x0E,0x0A,0x12,0x12,0x22,0x22,0x77,0x00,0x00,/*"K",43*/
0x00,0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x7F,0x00,0x00,/*"L",44*/
0x00,0x00,0x00,0x77,0x36,0x36,0x36,0x36,0x2A,0x2A,0x2A,0x2A,0x2A,0x6B,0x00,0x00,/*"M",45*/
0x00,0x00,0x00,0xE3,0x46,0x46,0x4A,0x4A,0x52,0x52,0x52,0x62,0x62,0x47,0x00,0x00,/*"N",46*/
0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00,/*"O",47*/
0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x42,0x3E,0x02,0x02,0x02,0x02,0x07,0x00,0x00,/*"P",48*/
0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x4D,0x53,0x32,0x1C,0x60,0x00,/*"Q",49*/
0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x3E,0x12,0x12,0x22,0x22,0x42,0xC7,0x00,0x00,/*"R",50*/
0x00,0x00,0x00,0x7C,0x42,0x42,0x02,0x04,0x18,0x20,0x40,0x42,0x42,0x3E,0x00,0x00,/*"S",51*/
0x00,0x00,0x00,0x7F,0x49,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00,/*"T",52*/
0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,/*"U",53*/
0x00,0x00,0x00,0xE7,0x42,0x42,0x22,0x24,0x24,0x14,0x14,0x18,0x08,0x08,0x00,0x00,/*"V",54*/
0x00,0x00,0x00,0x6B,0x49,0x49,0x49,0x49,0x55,0x55,0x36,0x22,0x22,0x22,0x00,0x00,/*"W",55*/
0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00,/*"X",56*/
0x00,0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00,/*"Y",57*/
0x00,0x00,0x00,0x7E,0x21,0x20,0x10,0x10,0x08,0x04,0x04,0x42,0x42,0x3F,0x00,0x00,/*"Z",58*/
0x00,0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00,/*"[",59*/
0x00,0x00,0x02,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x40,0x40,/*"\",60*/
0x00,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00,/*"]",61*/
0x00,0x38,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"^",62*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,/*"_",63*/
0x00,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"`",64*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x78,0x44,0x42,0x42,0xFC,0x00,0x00,/*"a",65*/
0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x26,0x1A,0x00,0x00,/*"b",66*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x02,0x02,0x02,0x44,0x38,0x00,0x00,/*"c",67*/
0x00,0x00,0x00,0x60,0x40,0x40,0x40,0x78,0x44,0x42,0x42,0x42,0x64,0xD8,0x00,0x00,/*"d",68*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x02,0x02,0x42,0x3C,0x00,0x00,/*"e",69*/
0x00,0x00,0x00,0xF0,0x88,0x08,0x08,0x7E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,/*"f",70*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x22,0x22,0x1C,0x02,0x3C,0x42,0x42,0x3C,/*"g",71*/
0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,/*"h",72*/
0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,/*"i",73*/
0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x22,0x1E,/*"j",74*/
0x00,0x00,0x00,0x03,0x02,0x02,0x02,0x72,0x12,0x0A,0x16,0x12,0x22,0x77,0x00,0x00,/*"k",75*/
0x00,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,/*"l",76*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x92,0x92,0x92,0x92,0x92,0xB7,0x00,0x00,/*"m",77*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3B,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,/*"n",78*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,/*"o",79*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x26,0x42,0x42,0x42,0x22,0x1E,0x02,0x07,/*"p",80*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0xE0,/*"q",81*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x4C,0x04,0x04,0x04,0x04,0x1F,0x00,0x00,/*"r",82*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x42,0x02,0x3C,0x40,0x42,0x3E,0x00,0x00,/*"s",83*/
0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3E,0x08,0x08,0x08,0x08,0x08,0x30,0x00,0x00,/*"t",84*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x42,0x42,0x42,0x42,0x62,0xDC,0x00,0x00,/*"u",85*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x14,0x08,0x08,0x00,0x00,/*"v",86*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEB,0x49,0x49,0x55,0x55,0x22,0x22,0x00,0x00,/*"w",87*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x24,0x18,0x18,0x18,0x24,0x6E,0x00,0x00,/*"x",88*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x14,0x18,0x08,0x08,0x07,/*"y",89*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x22,0x10,0x08,0x08,0x44,0x7E,0x00,0x00,/*"z",90*/
0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0x20,0xC0,0x00,/*"",91*/
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,/*"|",92*/
0x00,0x06,0x08,0x08,0x08,0x08,0x08,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x06,0x00,/*"}",93*/
0x0C,0x32,0xC2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"~",94*/

};

const unsigned int CodeTable[35] = {
  0xE6ADA6,0xE6B189,0XE8B0B7,0xE991AB,0xE7A791,0xE68A80,0xE69C89,0xE99990, /* 0-7 */
  0xE585AC,0xE58FB8,0xE7839F,0xE58FB0,0xE58C97,0xE696B9,0xE6989F,0xE7A9BA,   /* 8-15 */
  0xE88F9C,0xE58D95,0xe4b880,0xE4BA8C,0xE4B889,0xE59B9B,0xE4BA94,0xE585AD,/* 16-23 */
  0xE4B883,0xE585AB,0xE4B99D,0xE58D81,0xE99BB6,0xE6B58B,0xE8AF95,0xE4B88B,/*24-31*/
  0xE4B88A,0xE9A1B5,/*32-39*/
};

/*
武汉谷鑫科技有限
公司烟台北方星空
菜单一二三四五六
七八九十零测试下
上页
*/

const unsigned char Hz_16[35][32] =
{

0x00,0x00,0x04,0x1F,0x04,0x02,0x34,0x04,0x44,0x08,0x04,0x30,0xFF,0xC0,0x04,0x04,
0x24,0x44,0x24,0x44,0x25,0xFC,0x24,0x02,0x24,0x02,0x24,0x7E,0x04,0x03,0x04,0x02,//0武
0x00,0x00,0x00,0x01,0x00,0x01,0x78,0x02,0x47,0x04,0x40,0xC8,0x40,0x30,0x40,0xC8,
0x47,0x04,0x78,0x02,0x40,0x01,0x03,0x01,0x30,0xC0,0x40,0x3E,0x06,0x20,0x08,0x20,//1汉
0x00,0x00,0x00,0x80,0x10,0x80,0x21,0x00,0x41,0x7F,0x82,0x42,0x04,0x42,0x08,0x42,
0x30,0x42,0x08,0x42,0x04,0x42,0xC2,0x42,0x21,0x7F,0x11,0x00,0x08,0x80,0x00,0x80,//2谷
0x00,0x00,0x10,0x11,0x10,0x2B,0x11,0x69,0x25,0xBF,0x37,0x69,0x55,0x2B,0x55,0x11,
0x9F,0x00,0x55,0x11,0x55,0x2B,0x37,0x69,0x25,0xBF,0x11,0x69,0x10,0x2B,0x10,0x11,//3鑫
0x00,0x00,0x00,0x40,0x00,0x40,0x00,0x40,0xFF,0xFF,0x00,0x20,0x00,0x20,0x33,0x20,
0x44,0x20,0x00,0x20,0x44,0x80,0xC5,0x00,0x7F,0xFF,0x25,0x80,0x24,0x60,0x24,0x10,//4科
0x00,0x00,0x10,0x01,0x11,0x81,0x11,0x62,0x11,0x14,0xFF,0x08,0x11,0x34,0x11,0xC2,
0x11,0x02,0x10,0x01,0x09,0x01,0x08,0x80,0xFF,0xFE,0x08,0x41,0x08,0x22,0x08,0x20,//5技
0x00,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x27,0xFE,0x24,0x91,0x24,0x92,0x24,0x90,
0x24,0x90,0xE4,0x90,0x3C,0x90,0x27,0xFF,0x21,0x00,0x20,0x80,0x20,0x40,0x20,0x20,//6有
0x00,0x00,0x00,0x02,0x00,0x82,0x7F,0x44,0x49,0x28,0x49,0x30,0x49,0xC0,0x49,0x04,
0x49,0x02,0x7F,0xFF,0x00,0x00,0x61,0xE0,0x5A,0x10,0x44,0x20,0x7F,0xFF,0x00,0x00,//7限
0x00,0x00,0x00,0x80,0x00,0x80,0x01,0x00,0x02,0x06,0x04,0x1C,0x18,0x24,0xE0,0x04,
0x00,0x04,0x01,0x84,0x60,0x64,0x18,0x14,0x04,0x0E,0x02,0x04,0x01,0x00,0x00,0x80,//8公
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x40,0x01,0x48,0x02,0x48,0x00,0x49,0xFC,
0x49,0x08,0x49,0x08,0x49,0x08,0x49,0x08,0x49,0xFC,0x48,0x00,0x08,0x00,0x00,0x00,//9司

0x00,0x00,0x7F,0xFF,0x42,0x02,0x42,0x32,0x42,0x42,0x5F,0x82,0x42,0x62,0x42,0x12,
0x42,0x0A,0x7F,0xFF,0x10,0x08,0x08,0x10,0xFF,0xE0,0x00,0x18,0x0E,0x06,0x01,0x01,/*"烟",10*/
0x00,0x00,0x00,0x00,0x03,0x00,0x06,0x00,0x0A,0x7F,0x12,0x42,0x02,0x42,0x02,0x42,
0x02,0x42,0xC2,0x42,0x22,0x42,0x12,0x42,0x0A,0x7F,0x07,0x00,0x02,0x00,0x00,0x00,/*"台",11*/
0x00,0x00,0x00,0x1E,0x10,0x02,0x08,0x02,0x04,0x02,0x02,0x02,0xFF,0xFC,0x00,0x00,
0x00,0x00,0x00,0x00,0xFF,0xFF,0x04,0x08,0x04,0x08,0x04,0x04,0x04,0x06,0x00,0x04,/*"北",12*/
0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x11,0xFC,0x11,0x02,0x11,0x01,0x11,0x02,
0x71,0x00,0x91,0x00,0x1F,0xE0,0x10,0x18,0x10,0x04,0x10,0x02,0x10,0x01,0x10,0x00,/*"方",13*/
0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x82,0x7C,0x92,0x54,0x92,0x54,0x92,0x54,0x92,
0x57,0xFE,0x54,0x92,0x54,0x92,0x54,0x92,0x7D,0x92,0x00,0x42,0x00,0x22,0x00,0x00,/*"星",14*/
0x00,0x00,0x30,0x00,0x28,0x02,0x22,0x02,0x24,0x82,0x28,0x82,0x20,0x82,0x20,0x82,
0x60,0xFE,0xA0,0x82,0x20,0x82,0x28,0x82,0x24,0x82,0x22,0x02,0x30,0x02,0x08,0x00, /*"空",15*/

0x00,0x00,0x20,0x02,0x20,0x22,0x24,0x24,0x2D,0x24,0xF4,0xA8,0x24,0x30,0x24,0x20,
0x23,0x7F,0x22,0x20,0x22,0x30,0xF2,0xA8,0x23,0x24,0x22,0x24,0x20,0x22,0x20,0x02,/*"菜",16*/
0x00,0x00,0x00,0x08,0x00,0x08,0x1F,0xC8,0x92,0x48,0x52,0x48,0x32,0x48,0x12,0x48,
0x1F,0xFF,0x12,0x48,0x32,0x48,0x52,0x48,0x92,0x48,0x1F,0xC8,0x00,0x08,0x00,0x08,/*"单",17*/
0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,/*"一",18*/
0x00,0x00,0x00,0x08,0x00,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,
0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x00,0x08,0x00,0x08,/*"二",19*/
0x00,0x00,0x00,0x04,0x20,0x04,0x21,0x04,0x21,0x04,0x21,0x04,0x21,0x04,0x21,0x04,
0x21,0x04,0x21,0x04,0x21,0x04,0x21,0x04,0x21,0x04,0x21,0x04,0x20,0x04,0x00,0x04,/*"三",20*/
0x00,0x00,0x00,0x00,0x3F,0xFE,0x20,0x44,0x20,0x44,0x20,0x44,0x3F,0x84,0x20,0x04,
0x20,0x04,0x20,0x04,0x3F,0x04,0x20,0xC4,0x20,0x24,0x20,0x14,0x3F,0xFE,0x00,0x00,/*"四",21*/
0x00,0x00,0x00,0x02,0x40,0x02,0x40,0x02,0x43,0xFE,0x42,0x02,0x42,0x02,0x42,0x02,
0x42,0x02,0x7E,0x02,0x43,0xE2,0x42,0x1E,0x42,0x02,0x42,0x02,0x40,0x02,0x00,0x02,/*"五",22*/
0x00,0x00,0x04,0x00,0x04,0x06,0x04,0x18,0x04,0x20,0x04,0x40,0x04,0x80,0x34,0x00,
0x44,0x00,0x84,0x00,0x04,0xC0,0x04,0x30,0x04,0x08,0x04,0x04,0x04,0x02,0x04,0x00,/*"六",23*/
0x00,0x00,0x00,0x00,0x04,0x1E,0x04,0x02,0x04,0x02,0x04,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0xFF,0xFC,0x02,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,/*"七",24*/
0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x0C,0x00,0x30,0x01,0xC0,0x7E,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0xE0,0x00,0x18,0x00,0x06,0x00,0x01,0x00,0x00,/*"八",25*/
0x00,0x00,0x00,0x1E,0x00,0x02,0x00,0x02,0x00,0x02,0x0F,0xFC,0x08,0x00,0x08,0x00,
0x08,0x00,0x08,0x00,0xFF,0x00,0x08,0xE0,0x08,0x18,0x08,0x04,0x08,0x02,0x00,0x01,/*"九",26*/
0x00,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
0xFF,0xFF,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,/*"十",27*/
0x00,0x00,0x30,0x20,0x28,0x20,0xA0,0x40,0xAA,0x40,0xAA,0x98,0xAA,0x95,0xA1,0x12,
0xFE,0x32,0xA1,0x54,0xAA,0x94,0xAA,0x90,0xAA,0x50,0xA0,0x40,0x30,0x20,0x08,0x20,/*"零",28*/
0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x01,0x1F,0xE2,0x00,0x00,0x7F,0xE4,0x40,0x08,
0x4F,0xF0,0x40,0x0C,0x7F,0xE2,0x00,0x01,0x31,0x80,0x40,0x7E,0x06,0x20,0x08,0x20,/*"测",29*/
0x00,0x00,0x08,0x0F,0x68,0x02,0x88,0x0C,0x08,0x70,0xFF,0x80,0x09,0x08,0x09,0x08,
0x09,0xFC,0x09,0x06,0x09,0x14,0x00,0x08,0x33,0xFC,0x42,0x00,0x02,0x00,0x02,0x00,/*"试",30*/
0x00,0x00,0x40,0x00,0x40,0x00,0x40,0x60,0x40,0x80,0x41,0x00,0x42,0x00,0x40,0x00,
0x40,0x00,0x7F,0xFF,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,/*"下",31*/
0x00,0x00,0x00,0x02,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0xFF,0xFE,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x02,/*"上",32*/
0x00,0x00,0x00,0x00,0x40,0x00,0x40,0x01,0x4F,0xF2,0x48,0x04,0x48,0x08,0x48,0x10,
0x4B,0xE0,0x68,0x18,0x58,0x04,0x48,0x02,0x4F,0xF2,0x40,0x01,0x40,0x01,0x00,0x00 /*"页",33*/
};
 

#endif