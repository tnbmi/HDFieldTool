//*****************************************************************************
//
// オブジェクト列挙体 [mapObj.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// カテゴリ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------
// カテゴリの文字列
//----------------------------
const char* CATEGORY_OBJ[] =
{
	"ROAD",
	"STUMBLER",
	"TARGET",
};

//----------------------------
// カテゴリ数
//----------------------------
const int CATEGORY_OBJ_NUM = (sizeof(CATEGORY_OBJ) / sizeof(char*));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// タイプ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------
// タイプの文字列
//----------------------------
// 道
const char* TYPE_ROAD[] =
{
	"DIRT",
	"SAND",
	"ICE",
	"GRASSFIELD",
	"WATER",
};

// 障害物
const char* TYPE_SRUMBLER[] =
{
	"SIGNBOARD",
	"LION",
	"ROCK",
	"LOG_LEFT",
	"LOG_CENTER",
	"LOG_RIGHT",
	"BIRD",
	"DUSTBOX",
	"BARRICADE",
	"CUCTUS",
	"ICEBERG",
	"ICICLE",
	"NUTS",
	"NUTS_REVERSE",
	"SANDSTONE",
	"BEE",
	"HUNEYCOMB",
};

// ターゲット
const char* TYPE_TARGET[] =
{
	"GOAL",
};

//----------------------------
// タイプ数
//----------------------------
// 道
const int ROAD_NUM = (sizeof(TYPE_ROAD) / sizeof(char*));

// 障害物
const int SRUMBLER_NUM = (sizeof(TYPE_SRUMBLER) / sizeof(char*));

// ターゲット
const int TARGET_NUM = (sizeof(TYPE_TARGET) / sizeof(char*));
