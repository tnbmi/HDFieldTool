//*****************************************************************************
//
// �I�u�W�F�N�g�񋓑� [mapObj.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �J�e�S��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------
// �J�e�S���̕�����
//----------------------------
const char* CATEGORY_OBJ[] =
{
	"ROAD",
	"STUMBLER",
	"TARGET",
};

//----------------------------
// �J�e�S����
//----------------------------
const int CATEGORY_OBJ_NUM = (sizeof(CATEGORY_OBJ) / sizeof(char*));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �^�C�v
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------
// �^�C�v�̕�����
//----------------------------
// ��
const char* TYPE_ROAD[] =
{
	"DIRT",
	"SAND",
	"ICE",
	"GRASSFIELD",
	"WATER",
};

// ��Q��
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

// �^�[�Q�b�g
const char* TYPE_TARGET[] =
{
	"GOAL",
};

//----------------------------
// �^�C�v��
//----------------------------
// ��
const int ROAD_NUM = (sizeof(TYPE_ROAD) / sizeof(char*));

// ��Q��
const int SRUMBLER_NUM = (sizeof(TYPE_SRUMBLER) / sizeof(char*));

// �^�[�Q�b�g
const int TARGET_NUM = (sizeof(TYPE_TARGET) / sizeof(char*));
