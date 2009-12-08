//------------------------------------------------------------------------------
// Header generated by wxDesigner from file: Adapt_It.wdr
// Do not modify this file, all changes will be lost!
//------------------------------------------------------------------------------

#ifndef __WDR_Adapt_It_H__
#define __WDR_Adapt_It_H__

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
    #pragma interface "Adapt_It_wdr.h"
#endif

// Include wxWidgets' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/image.h>
#include <wx/statline.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/toolbar.h>
#include <wx/tglbtn.h>

// Declare window functions

const int ID_STATICBITMAP = -1;
const int ID_TEXT = 0;
const int ID_ABOUT_VERSION_LABEL = 1;
const int ID_ABOUT_VERSION_NUM = 2;
const int ID_ABOUT_VERSION_DATE = 3;
const int ID_STATIC_UNICODE_OR_ANSI = 4;
const int ID_STATIC_WX_VERSION_USED = 5;
const int ID_LINE = 6;
const int ID_STATIC_UI_LANGUAGE = 7;
const int ID_STATIC_HOST_OS = 8;
const int ID_STATIC_SYS_LANGUAGE = 9;
const int ID_STATIC_SYS_LOCALE_NAME = 10;
const int ID_STATIC_CANONICAL_LOCALE_NAME = 11;
const int ID_STATIC_SYS_ENCODING_NAME = 12;
const int ID_STATIC_SYSTEM_LAYOUT_DIR = 13;
wxSizer *AboutDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_RADIO_DRAFTING = 14;
const int IDC_RADIO_REVIEWING = 15;
const int IDC_CHECK_SINGLE_STEP = 16;
const int IDC_CHECK_KB_SAVE = 17;
const int IDC_CHECK_FORCE_ASK = 18;
const int IDC_BUTTON_NO_ADAPT = 19;
const int IDC_STATIC = 20;
const int IDC_EDIT_DELAY = 21;
const int IDC_CHECK_ISGLOSSING = 22;
wxSizer *ControlBarFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_COMPOSE = 23;
const int IDC_BUTTON_SHORTEN = 24;
const int IDC_BUTTON_PREV = 25;
const int IDC_BUTTON_LENGTHEN = 26;
const int IDC_BUTTON_NEXT = 27;
const int IDC_BUTTON_REMOVE = 28;
const int IDC_BUTTON_APPLY = 29;
const int IDC_STATIC_SECTION_DEF = 30;
const int IDC_RADIO_PUNCT_SECTION = 31;
const int IDC_RADIO_VERSE_SECTION = 32;
const int IDC_BUTTON_CLEAR = 33;
const int IDC_BUTTON_SELECT_ALL = 34;
wxSizer *ComposeBarFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_LISTBOX_ADAPTIONS = 35;
wxSizer *OpenExistingProjectDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_FILENAME = 36;
const int ID_TEXT_INVALID_CHARACTERS = 37;
wxSizer *GetOutputFilenameDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_SOURCE_LANGUAGE = 38;
const int IDC_TARGET_LANGUAGE = 39;
const int ID_TEXTCTRL_AS_STATIC_NL = 40;
const int IDC_CHECK_SFM_AFTER_NEWLINES = 41;
wxSizer *LanguagesPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_SOURCE_FONTNAME = 42;
const int IDC_CHECK_SRC_RTL = 43;
const int IDC_SOURCE_SIZE = 44;
const int IDC_SOURCE_LANG = 45;
const int IDC_BUTTON_SOURCE_COLOR = 46;
const int ID_BUTTON_CHANGE_SRC_ENCODING = 47;
const int IDC_TARGET_FONTNAME = 48;
const int IDC_CHECK_TGT_RTL = 49;
const int IDC_TARGET_SIZE = 50;
const int IDC_TARGET_LANG = 51;
const int IDC_BUTTON_TARGET_COLOR = 52;
const int ID_BUTTON_CHANGE_TGT_ENCODING = 53;
const int IDC_NAVTEXT_FONTNAME = 54;
const int IDC_CHECK_NAVTEXT_RTL = 55;
const int IDC_NAVTEXT_SIZE = 56;
const int IDC_CHANGE_NAV_TEXT = 57;
const int IDC_BUTTON_NAV_TEXT_COLOR = 58;
const int ID_BUTTON_CHANGE_NAV_ENCODING = 59;
const int ID_TEXTCTRL_AS_STATIC_FONTPAGE = 60;
const int IDC_BUTTON_SPECTEXTCOLOR = 61;
const int IDC_RETRANSLATION_BUTTON = 62;
wxSizer *FontsPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_PLEASE_WAIT = 63;
wxSizer *WaitDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_LIST_ACCEPTED = 64;
const int IDC_BUTTON_REJECT = 65;
const int IDC_BUTTON_ACCEPT = 66;
const int IDC_LIST_REJECTED = 67;
wxSizer *WhichFilesDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_TRANSFORM_TO_GLOSSES1 = 68;
const int ID_TEXTCTRL_TRANSFORM_TO_GLOSSES2 = 69;
const int ID_TEXTCTRL_TRANSFORM_TO_GLOSSES3 = 70;
wxSizer *TransformToGlossesDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_CHECK_SOURCE_USES_CAPS = 71;
const int ID_CHECK_USE_AUTO_CAPS = 72;
const int ID_TEXTCTRL_AS_CASE_PAGE_STATIC_TEXT = 73;
const int ID_TEXT_SL = 74;
const int ID_TEXT_TL = 75;
const int ID_TEXT_GL = 76;
const int IDC_EDIT_SRC_CASE_EQUIVALENCES = 77;
const int IDC_EDIT_TGT_CASE_EQUIVALENCES = 78;
const int IDC_EDIT_GLOSS_CASE_EQUIVALENCES = 79;
const int IDC_BUTTON_CLEAR_SRC_LIST = 80;
const int IDC_BUTTON_CLEAR_TGT_LIST = 81;
const int IDC_BUTTON_CLEAR_GLOSS_LIST = 82;
const int IDC_BUTTON_SRC_SET_ENGLISH = 83;
const int IDC_BUTTON_TGT_SET_ENGLISH = 84;
const int IDC_BUTTON_GLOSS_SET_ENGLISH = 85;
const int IDC_BUTTON_SRC_COPY_TO_NEXT = 86;
const int IDC_BUTTON_TGT_COPY_TO_NEXT = 87;
const int IDC_BUTTON_GLOSS_COPY_TO_NEXT = 88;
const int IDC_BUTTON_SRC_COPY_TO_GLOSS = 89;
wxSizer *CaseEquivDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_WELCOME_TO = 90;
const int IDC_EDIT_ADAPT_IT = 91;
const int ID_TEXTCTRL_AS_STATIC_WELCOME = 92;
const int IDC_CHECK_NOLONGER_SHOW = 93;
wxSizer *WelcomeDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_AS_STATIC_DOCPAGE = 94;
const int IDC_STATIC_WHICH_MODE = 95;
const int IDC_BUTTON_WHAT_IS_DOC = 96;
const int IDC_STATIC_WHICH_FOLDER = 97;
const int IDC_LIST_NEWDOC_AND_EXISTINGDOC = 98;
const int IDC_CHECK_CHANGE_FIXED_SPACES_TO_REGULAR_SPACES = 99;
const int IDC_CHANGE_FOLDER_BTN = 100;
const int IDC_CHECK_FORCE_UTF8 = 101;
wxSizer *DocPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_AS_STATIC_PROJECTPAGE = 102;
const int IDC_BUTTON_WHAT_IS_PROJECT = 103;
const int IDC_LIST_NEW_AND_EXISTING = 104;
wxSizer *ProjectPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_SRC = 105;
const int IDC_LIST_PUNCTS = 106;
const int ID_TEXTCTRL_AS_STATIC_PLACE_INT_PUNCT = 107;
const int IDC_EDIT_TGT = 108;
const int IDC_BUTTON_PLACE = 109;
wxSizer *PlaceInternalPunctDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_RADIO_INCHES = 110;
const int IDC_RADIO_CM = 111;
wxSizer *UnitsDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_MATCHED_SOURCE = 112;
const int IDC_MYLISTBOX_TRANSLATIONS = 113;
const int IDC_EDIT_REFERENCES = 114;
const int IDC_BUTTON_MOVE_UP = 115;
const int IDC_BUTTON_MOVE_DOWN = 116;
const int IDC_BUTTON_CANCEL_ASK = 117;
const int IDC_BUTTON_CANCEL_AND_SELECT = 118;
const int IDC_EDIT_NEW_TRANSLATION = 119;
wxSizer *ChooseTranslationDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_STATIC_SRC = 120;
const int IDC_EDIT_PRECONTEXT = 121;
const int IDC_EDIT_SOURCE_TEXT = 122;
const int IDC_EDIT_RETRANSLATION = 123;
const int IDC_COPY_RETRANSLATION_TO_CLIPBOARD = 124;
const int IDC_BUTTON_TOGGLE = 125;
const int IDC_STATIC_TGT = 126;
const int IDC_EDIT_FOLLCONTEXT = 127;
wxSizer *RetranslationDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_SRC_TEXT = 128;
const int IDC_EDIT_TGT_TEXT = 129;
const int IDC_SPIN_CHAPTER = 130;
const int IDC_SPIN_VERSE = 131;
const int IDC_GET_CHVERSE_TEXT = 132;
const int IDC_CLOSE_AND_JUMP = 133;
const int IDC_SHOW_MORE = 134;
const int IDC_SHOW_LESS = 135;
const int IDC_STATIC_BEGIN = 136;
const int IDC_STATIC_END = 137;
wxSizer *EarlierTransDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_CHECK_KB_BACKUP = 138;
const int IDC_CHECK_BAKUP_DOC = 139;
const int ID_TEXTCTRL_AS_STATIC_BACKUPS_AND_KB_PAGE = 140;
const int IDC_EDIT_SRC_NAME = 141;
const int IDC_EDIT_TGT_NAME = 142;
const int IDC_RADIO_ADAPT_BEFORE_GLOSS = 143;
const int IDC_RADIO_GLOSS_BEFORE_ADAPT = 144;
const int IDC_CHECK_LEGACY_SRC_TEXT_COPY = 145;
wxSizer *BackupsAndKBPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int STATIC_TEXT_V4 = 146;
const int IDC_EDIT_LEADING = 147;
const int STATIC_TEXT_V5 = 148;
const int IDC_EDIT_GAP_WIDTH = 149;
const int STATIC_TEXT_V6 = 150;
const int IDC_EDIT_LEFTMARGIN = 151;
const int STATIC_TEXT_V7 = 152;
const int IDC_EDIT_MULTIPLIER = 153;
const int IDC_EDIT_DIALOGFONTSIZE = 154;
const int IDC_CHECK_WELCOME_VISIBLE = 155;
const int IDC_CHECK_HIGHLIGHT_AUTO_INSERTED_TRANSLATIONS = 156;
const int IDC_BUTTON_CHOOSE_HIGHLIGHT_COLOR = 157;
const int IDC_CHECK_SHOW_ADMIN_MENU = 158;
wxSizer *ViewPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

wxSizer *UnitsPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_AS_STATIC_AUTOSAVE = 159;
const int IDC_CHECK_NO_AUTOSAVE = 160;
const int IDC_RADIO_BY_MINUTES = 161;
const int IDC_EDIT_MINUTES = 162;
const int IDC_SPIN_MINUTES = 163;
const int IDC_RADIO_BY_MOVES = 164;
const int IDC_EDIT_MOVES = 165;
const int IDC_SPIN_MOVES = 166;
const int IDC_EDIT_KB_MINUTES = 167;
const int IDC_SPIN_KB_MINUTES = 168;
wxSizer *AutoSavingPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_RADIO_DIV1 = 169;
const int IDC_RADIO_DIV2 = 170;
const int IDC_RADIO_DIV3 = 171;
const int IDC_RADIO_DIV4 = 172;
const int IDC_RADIO_DIV5 = 173;
const int IDC_COMBO_CHOOSE_BOOK = 174;
const int ID_TEXT_AS_STATIC = 175;
wxSizer *WhichBookDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_STATIC_MSG = 176;
const int IDC_EDIT_ERR_XML = 177;
const int IDC_STATIC_LBL = 178;
const int IDC_EDIT_OFFSET = 179;
wxSizer *XMLErrorDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_AS_STATIC_USFMPAGE = 180;
const int IDC_RADIO_USE_UBS_SET_ONLY = 181;
const int IDC_RADIO_USE_SILPNG_SET_ONLY = 182;
const int IDC_RADIO_USE_BOTH_SETS = 183;
const int IDC_RADIO_USE_UBS_SET_ONLY_PROJ = 184;
const int IDC_RADIO_USE_SILPNG_SET_ONLY_PROJ = 185;
const int IDC_RADIO_USE_BOTH_SETS_PROJ = 186;
const int IDC_RADIO_USE_UBS_SET_ONLY_FACTORY = 187;
const int IDC_RADIO_USE_SILPNG_SET_ONLY_FACTORY = 188;
const int IDC_RADIO_USE_BOTH_SETS_FACTORY = 189;
const int IDC_CHECK_CHANGE_FIXED_SPACES_TO_REGULAR_SPACES_USFM = 190;
wxSizer *USFMPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_AS_STATIC_FILTERPAGE = 191;
const int IDC_LIST_SFMS = 192;
const int IDC_LIST_SFMS_PROJ = 193;
const int IDC_LIST_SFMS_FACTORY = 194;
wxSizer *FilterPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_ED_SILCONVERTER_NAME = 195;
const int IDC_BTN_SELECT_SILCONVERTER = 196;
const int IDC_ED_SILCONVERTER_INFO = 197;
const int IDC_BTN_CLEAR_SILCONVERTER = 198;
wxSizer *SilConvertersDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_STATIC_FOLDER_DOCS = 199;
const int IDC_LIST_FOLDER_DOCS = 200;
const int IDC_BUTTON_NEXT_CHAPTER = 201;
const int IDC_BUTTON_SPLIT_NOW = 202;
const int IDC_STATIC_SPLITTING_WAIT = 203;
const int IDC_RADIO_PHRASEBOX_LOCATION = 204;
const int IDC_RADIO_CHAPTER_SFMARKER = 205;
const int IDC_RADIO_DIVIDE_INTO_CHAPTERS = 206;
const int IDC_STATIC_SPLIT_NAME = 207;
const int IDC_EDIT1 = 208;
const int IDC_STATIC_REMAIN_NAME = 209;
const int IDC_EDIT2 = 210;
wxSizer *SplitDialogFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_LIST_MARKERS = 211;
const int IDC_TEXTCTRL_AS_STATIC_PLACE_INT_MKRS = 212;
wxSizer *PlaceInternalMarkersDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_NOTE = 213;
const int IDC_EDIT_FIND_TEXT = 214;
const int IDC_FIND_NEXT_BTN = 215;
const int IDC_LAST_BTN = 216;
const int IDC_NEXT_BTN = 217;
const int IDC_PREV_BTN = 218;
const int IDC_FIRST_BTN = 219;
const int IDC_DELETE_BTN = 220;
wxSizer *NoteDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_AS_STATIC_COLLECT_BT = 221;
const int IDC_RADIO_COLLECT_ADAPTATIONS = 222;
const int IDC_RADIO_COLLECT_GLOSSES = 223;
wxSizer *CollectBackTranslationsDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_SPIN_DELAY_TICKS = 224;
wxSizer *SetDelayDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_RADIO_EXPORT_ALL = 225;
const int IDC_RADIO_EXPORT_SELECTED_MARKERS = 226;
const int ID_TEXTCTRL_AS_STATIC_EXPORT_OPTIONS = 227;
const int IDC_BUTTON_EXCLUDE_FROM_EXPORT = 228;
const int IDC_BUTTON_INCLUDE_IN_EXPORT = 229;
const int IDC_BUTTON_UNDO = 230;
const int IDC_STATIC_SPECIAL_NOTE = 231;
const int IDC_CHECK_PLACE_FREE_TRANS = 232;
const int IDC_CHECK_INTERLINEAR_PLACE_FREE_TRANS = 233;
const int IDC_CHECK_PLACE_BACK_TRANS = 234;
const int IDC_CHECK_INTERLINEAR_PLACE_BACK_TRANS = 235;
const int IDC_CHECK_PLACE_AI_NOTES = 236;
const int IDC_CHECK_INTERLINEAR_PLACE_AI_NOTES = 237;
wxSizer *ExportOptionsDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_STATIC_TITLE = 238;
const int IDC_RADIO_EXPORT_AS_SFM = 239;
const int ID_TEXTCTRL_AS_STATIC_EXPORT_SAVE_AS_1 = 240;
const int IDC_RADIO_EXPORT_AS_RTF = 241;
const int ID_TEXTCTRL_AS_STATIC_EXPORT_SAVE_AS_2 = 242;
const int ID_TEXTCTRL_AS_STATIC_EXPORT_SAVE_AS_3 = 243;
const int IDC_BUTTON_EXPORT_FILTER_OPTIONS = 244;
wxSizer *ExportSaveAsDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_CHECK_INCLUDE_NAV_TEXT = 245;
const int IDC_CHECK_INCLUDE_SOURCE_TEXT = 246;
const int IDC_CHECK_INCLUDE_TARGET_TEXT = 247;
const int IDC_CHECK_INCLUDE_GLS_TEXT = 248;
const int ID_TEXTCTRL_AS_STATIC_EXP_INTERLINEAR = 249;
const int IDC_RADIO_PORTRAIT = 250;
const int IDC_RADIO_LANDSCAPE = 251;
const int IDC_RADIO_OUTPUT_ALL = 252;
const int IDC_RADIO_OUTPUT_CHAPTER_VERSE_RANGE = 253;
const int IDC_EDIT_FROM_CHAPTER = 254;
const int IDC_EDIT_FROM_VERSE = 255;
const int IDC_EDIT_TO_CHAPTER = 256;
const int IDC_EDIT_TO_VERSE = 257;
const int IDC_RADIO_OUTPUT_PRELIM = 258;
const int IDC_RADIO_OUTPUT_FINAL = 259;
const int ID_CHECK_NEW_TABLES_FOR_NEWLINE_MARKERS = 260;
const int ID_CHECK_CENTER_TABLES_FOR_CENTERED_MARKERS = 261;
const int IDC_BUTTON_RTF_EXPORT_FILTER_OPTIONS = 262;
wxSizer *ExportInterlinearDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_LIST_MARKER = 263;
const int IDC_EDIT_MARKER_TEXT = 264;
const int IDC_REMOVE_BTN = 265;
const int IDC_BUTTON_SWITCH_ENCODING = 266;
const int IDC_LIST_MARKER_END = 267;
const int IDC_STATIC_MARKER_DESCRIPTION = 268;
const int IDC_STATIC_MARKER_STATUS = 269;
wxSizer *ViewFilteredMaterialDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_CHAPTER = 270;
const int IDC_EDIT_VERSE = 271;
wxSizer *GoToDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_KEY = 272;
const int IDC_EDIT_CH_VERSE = 273;
const int IDC_EDIT_ADAPTATION = 274;
const int IDC_LIST_TRANSLATIONS = 275;
const int IDC_RADIO_LIST_SELECT = 276;
const int IDC_RADIO_ACCEPT_CURRENT = 277;
const int IDC_RADIO_TYPE_NEW = 278;
const int IDC_EDIT_TYPE_NEW = 279;
const int IDC_NOTHING = 280;
const int IDC_BUTTON_IGNORE_IT = 281;
const int IDC_CHECK_DO_SAME = 282;
wxSizer *ConsistencyCheckDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_RADIO_CHECK_OPEN_DOC_ONLY = 283;
const int IDC_RADIO_CHECK_SELECTED_DOCS = 284;
const int ID_TEXTCTRL_AS_STATIC_CHOOSE_CONSISTENCY_CHECK_TYPE = 285;
wxSizer *ChooseConsistencyCheckTypeDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_EDIT_SOURCE_AS_STATIC0 = 286;
const int ID_TEXTCTRL = 287;
const int IDC_EDIT_OLD_SOURCE_TEXT = 288;
const int ID_TEXTCTRL_EDIT_SOURCE_AS_STATIC1 = 289;
const int ID_TEXTCTRL_EDIT_SOURCE_AS_STATIC2 = 290;
const int IDC_EDIT_NEW_SOURCE = 291;
const int ID_TEXTCTRL_EDIT_SOURCE_AS_STATIC4 = 292;
wxSizer *EditSourceTextDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_UNPACK_WARN = 293;
wxSizer *UnpackWarningDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_STATIC_COUNT = 294;
const int IDC_LIST_SRC_KEYS = 295;
const int IDC_LIST_EXISTING_TRANSLATIONS = 296;
const int IDC_EDIT_EDITORADD = 297;
const int IDC_BUTTON_UPDATE = 298;
const int IDC_BUTTON_ADD = 299;
const int IDC_ADD_NOTHING = 300;
const int IDC_EDIT_SHOW_FLAG = 301;
const int IDC_BUTTON_FLAG_TOGGLE = 302;
const int IDC_EDIT_SRC_KEY = 303;
const int IDC_EDIT_REF_COUNT = 304;
wxSizer *KBEditorPanelFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_STATIC_TEXT_SELECT_A_TAB = 305;
const int ID_KB_EDITOR_NOTEBOOK = 306;
wxSizer *KBEditorDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_STATIC_DOCS_IN_FOLDER = 307;
const int IDC_LIST_SOURCE_FOLDER_DOCS = 308;
const int IDC_RADIO_TO_BOOK_FOLDER = 309;
const int IDC_RADIO_FROM_BOOK_FOLDER = 310;
const int IDC_VIEW_OTHER = 311;
const int IDC_BUTTON_RENAME_DOC = 312;
const int IDC_MOVE_NOW = 313;
wxSizer *MoveDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_AS_STATIC_JOIN1 = 314;
const int IDC_BUTTON_MOVE_ALL_RIGHT = 315;
const int IDC_BUTTON_MOVE_ALL_LEFT = 316;
const int ID_TEXTCTRL_AS_STATIC_JOIN2 = 317;
const int ID_TEXTCTRL_AS_STATIC_JOIN3 = 318;
const int ID_JOIN_NOW = 319;
const int IDC_STATIC_JOINING_WAIT = 320;
const int ID_TEXTCTRL_AS_STATIC_JOIN4 = 321;
const int IDC_EDIT_NEW_FILENAME = 322;
wxSizer *JoinDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

wxSizer *ListDocInOtherFolderDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_STATIC_SET_FONT_TITLE = 323;
const int ID_STATIC_CURR_ENCODING_IS = 324;
const int ID_TEXT_CURR_ENCODING = 325;
const int ID_LISTBOX_POSSIBLE_FACENAMES = 326;
const int ID_LISTBOX_POSSIBLE_ENCODINGS = 327;
extern wxSizer *pTestBoxStaticTextBoxSizer;
const int ID_TEXT_TEST_ENCODING_BOX = 328;
const int ID_BUTTON_CHART_FONT_SIZE_DECREASE = 329;
const int ID_BUTTON_CHART_FONT_SIZE_INCREASE = 330;
const int ID_STATIC_CHART_FONT_SIZE = 331;
const int ID_SCROLLED_ENCODING_WINDOW = 332;
wxSizer *SetEncodingDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_CCT = 333;
wxSizer *CCTableEditDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_LIST_CCTABLES = 334;
const int IDC_EDIT_SELECTED_TABLE = 335;
const int IDC_BUTTON_BROWSE = 336;
const int IDC_BUTTON_CREATE_CCT = 337;
const int IDC_BUTTON_EDIT_CCT = 338;
const int IDC_BUTTON_SELECT_NONE = 339;
const int IDC_EDIT_FOLDER_PATH = 340;
wxSizer *CCTablePageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_RADIO_SRC_ONLY_FIND = 341;
const int IDC_RADIO_TGT_ONLY_FIND = 342;
const int IDC_RADIO_SRC_AND_TGT_FIND = 343;
const int IDC_CHECK_IGNORE_CASE_FIND = 344;
const int IDC_STATIC_SRC_FIND = 345;
const int IDC_EDIT_SRC_FIND = 346;
const int IDC_STATIC_TGT_FIND = 347;
const int IDC_EDIT_TGT_FIND = 348;
const int IDC_CHECK_INCLUDE_PUNCT_FIND = 349;
const int IDC_CHECK_SPAN_SRC_PHRASES_FIND = 350;
const int IDC_STATIC_SPECIAL = 351;
extern wxSizer *IDC_STATIC_SIZER_SPECIAL;
const int IDC_RADIO_RETRANSLATION = 352;
const int IDC_RADIO_NULL_SRC_PHRASE = 353;
const int IDC_RADIO_SFM = 354;
const int IDC_STATIC_SELECT_MKR = 355;
const int IDC_COMBO_SFM = 356;
const int IDC_BUTTON_SPECIAL = 357;
wxSizer *FindDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_RADIO_SRC_ONLY_REPLACE = 358;
const int IDC_RADIO_TGT_ONLY_REPLACE = 359;
const int IDC_RADIO_SRC_AND_TGT_REPLACE = 360;
const int IDC_CHECK_IGNORE_CASE_REPLACE = 361;
const int IDC_STATIC_SRC_REPLACE = 362;
const int IDC_EDIT_SRC_REPLACE = 363;
const int IDC_STATIC_TGT_REPLACE = 364;
const int IDC_EDIT_TGT_REPLACE = 365;
const int IDC_CHECK_INCLUDE_PUNCT_REPLACE = 366;
const int IDC_CHECK_SPAN_SRC_PHRASES_REPLACE = 367;
const int IDC_STATIC_REPLACE = 368;
const int IDC_EDIT_REPLACE = 369;
const int IDC_REPLACE = 370;
const int IDC_REPLACE_ALL_BUTTON = 371;
wxSizer *ReplaceDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_AS_STATIC = 372;
const int IDC_EDIT_TBLNAME = 373;
wxSizer *CCTableNameDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_EDIT_AS_STATIC = 374;
const int ID_RADIO_ALL = 375;
const int ID_RADIO_SELECTION = 376;
const int IDC_RADIO_PAGES = 377;
const int IDC_EDIT_PAGES_FROM = 378;
const int IDC_EDIT_PAGES_TO = 379;
const int IDC_RADIO_CHAPTER_VERSE_RANGE = 380;
const int IDC_EDIT3 = 381;
const int IDC_EDIT4 = 382;
const int IDC_CHECK_SUPPRESS_PREC_HEADING = 383;
const int IDC_CHECK_INCLUDE_FOLL_HEADING = 384;
const int IDC_CHECK_SUPPRESS_FOOTER = 385;
wxSizer *PrintOptionsDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_CC_TABBED_NOTEBOOK = 386;
wxSizer *CCTabbedNotebookFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_LIST_UI_LANGUAGES = 387;
const int ID_TEXT_AS_STATIC_SHORT_LANG_NAME = 388;
const int ID_TEXT_AS_STATIC_LONG_LANG_NAME = 389;
const int IDC_LOCALIZATION_PATH = 390;
const int IDC_BTN_BROWSE_PATH = 391;
wxSizer *ChooseLanguageDlgFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_COMBO_REMOVALS = 392;
const int ID_STATIC_TEXT_REMOVALS = 393;
const int IDC_BUTTON_UNDO_LAST_COPY = 394;
wxSizer *RemovalsBarFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_MSG_TEXT = 395;
const int IDC_BUTTON_PREV_STEP = 396;
const int IDC_BUTTON_NEXT_STEP = 397;
const int ID_BUTTON_END_NOW = 398;
const int ID_BUTTON_CANCEL_ALL_STEPS = 399;
wxSizer *VertEditBarFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT_TITLE = 400;
const int ID_TEXTCTRL_AS_STATIC_PUNCT_CORRESP_PAGE = 401;
const int IDC_TOGGLE_UNNNN_BTN = 402;
const int ID_NOTEBOOK = 403;
wxSizer *PunctCorrespPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_SRC0 = 404;
const int IDC_EDIT_TGT0 = 405;
const int IDC_EDIT_SRC9 = 406;
const int IDC_EDIT_TGT9 = 407;
const int IDC_EDIT_SRC18 = 408;
const int IDC_EDIT_TGT18 = 409;
const int IDC_EDIT_SRC1 = 410;
const int IDC_EDIT_TGT1 = 411;
const int IDC_EDIT_SRC10 = 412;
const int IDC_EDIT_TGT10 = 413;
const int IDC_EDIT_SRC19 = 414;
const int IDC_EDIT_TGT19 = 415;
const int IDC_EDIT_SRC2 = 416;
const int IDC_EDIT_TGT2 = 417;
const int IDC_EDIT_SRC11 = 418;
const int IDC_EDIT_TGT11 = 419;
const int IDC_EDIT_SRC20 = 420;
const int IDC_EDIT_TGT20 = 421;
const int IDC_EDIT_SRC3 = 422;
const int IDC_EDIT_TGT3 = 423;
const int IDC_EDIT_SRC12 = 424;
const int IDC_EDIT_TGT12 = 425;
const int IDC_EDIT_SRC21 = 426;
const int IDC_EDIT_TGT21 = 427;
const int IDC_EDIT_SRC4 = 428;
const int IDC_EDIT_TGT4 = 429;
const int IDC_EDIT_SRC13 = 430;
const int IDC_EDIT_TGT13 = 431;
const int IDC_EDIT_SRC22 = 432;
const int IDC_EDIT_TGT22 = 433;
const int IDC_EDIT_SRC5 = 434;
const int IDC_EDIT_TGT5 = 435;
const int IDC_EDIT_SRC14 = 436;
const int IDC_EDIT_TGT14 = 437;
const int IDC_EDIT_SRC23 = 438;
const int IDC_EDIT_TGT23 = 439;
const int IDC_EDIT_SRC6 = 440;
const int IDC_EDIT_TGT6 = 441;
const int IDC_EDIT_SRC15 = 442;
const int IDC_EDIT_TGT15 = 443;
const int IDC_EDIT_SRC24 = 444;
const int IDC_EDIT_TGT24 = 445;
const int IDC_EDIT_SRC7 = 446;
const int IDC_EDIT_TGT7 = 447;
const int IDC_EDIT_SRC16 = 448;
const int IDC_EDIT_TGT16 = 449;
const int IDC_EDIT_SRC25 = 450;
const int IDC_EDIT_TGT25 = 451;
const int IDC_EDIT_SRC8 = 452;
const int IDC_EDIT_TGT8 = 453;
const int IDC_EDIT_SRC17 = 454;
const int IDC_EDIT_TGT17 = 455;
wxSizer *SinglePunctTabPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int IDC_EDIT_2SRC0 = 456;
const int IDC_EDIT_2TGT0 = 457;
const int IDC_EDIT_2SRC5 = 458;
const int IDC_EDIT_2TGT5 = 459;
const int IDC_EDIT_2SRC1 = 460;
const int IDC_EDIT_2TGT1 = 461;
const int IDC_EDIT_2SRC6 = 462;
const int IDC_EDIT_2TGT6 = 463;
const int IDC_EDIT_2SRC2 = 464;
const int IDC_EDIT_2TGT2 = 465;
const int IDC_EDIT_2SRC7 = 466;
const int IDC_EDIT_2TGT7 = 467;
const int IDC_EDIT_2SRC3 = 468;
const int IDC_EDIT_2TGT3 = 469;
const int IDC_EDIT_2SRC8 = 470;
const int IDC_EDIT_2TGT8 = 471;
const int IDC_EDIT_2SRC4 = 472;
const int IDC_EDIT_2TGT4 = 473;
const int IDC_EDIT_2SRC9 = 474;
const int IDC_EDIT_2TGT9 = 475;
wxSizer *DoublePunctTabPageFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

wxSizer *ControlBar2LineFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXTCTRL_MSG = 476;
const int ID_BUTTON_LOCATE_SOURCE_FOLDER = 477;
const int ID_BITMAPBUTTON_SRC_OPEN_FOLDER_UP = 478;
const int ID_TEXT_SOURCE_FOLDER_PATH = 479;
const int ID_TEXTCTRL_SOURCE_PATH = 480;
const int ID_LISTCTRL_SOURCE_CONTENTS = 481;
const int ID_BUTTON_LOCATE_DESTINATION_FOLDER = 482;
const int ID_BITMAPBUTTON_DEST_OPEN_FOLDER_UP = 483;
const int ID_TEXTCTRL_DESTINATION_PATH = 484;
const int ID_LISTCTRL_DESTINATION_CONTENTS = 485;
const int ID_BUTTON_MOVE_FOLDER = 486;
const int ID_BUTTON_MOVE_FILES = 487;
const int ID_BUTTON_COPY_FOLDER = 488;
const int ID_BUTTON_COPY_FILES = 489;
const int ID_BUTTON_RENAME_DEST_FOLDER = 490;
const int ID_BUTTON_RENAME_DEST_FILES = 491;
const int ID_BUTTON_DELETE_DEST_FOLDER = 492;
const int ID_BUTTON_DELETE_DEST_FILES = 493;
wxSizer *MoveOrCopyFilesOrFoldersFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

const int ID_TEXT_MSG1 = 494;
const int ID_TEXTCTRL_SOURCE_FILE_DETAILS = 495;
const int ID_TEXTCTRL_DESTINATION_FILE_DETAILS = 496;
const int ID_RADIOBUTTON_REPLACE = 497;
const int ID_RADIOBUTTON_NO_COPY = 498;
const int ID_RADIOBUTTON_COPY_AND_RENAME = 499;
const int ID_TEXT_MODIFY_NAME = 500;
const int ID_CHECKBOX_HANDLE_SAME = 501;
wxSizer *FilenameConflictFunc( wxWindow *parent, bool call_fit = TRUE, bool set_sizer = TRUE );

// Declare menubar functions

const int ID_FILE_MENU = 502;
const int ID_FILE_PACK_DOC = 503;
const int ID_FILE_UNPACK_DOC = 504;
const int ID_MENU = 505;
const int ID_FILE_STARTUP_WIZARD = 506;
const int ID_FILE_CLOSEKB = 507;
const int ID_FILE_CHANGEFOLDER = 508;
const int ID_FILE_SAVEKB = 509;
const int ID_FILE_BACKUP_KB = 510;
const int ID_FILE_RESTORE_KB = 511;
const int ID_EDIT_MENU = 512;
const int ID_EDIT_CUT = 513;
const int ID_EDIT_COPY = 514;
const int ID_EDIT_PASTE = 515;
const int ID_GO_TO = 516;
const int ID_EDIT_SOURCE_TEXT = 517;
const int ID_EDIT_CONSISTENCY_CHECK = 518;
const int ID_EDIT_MOVE_NOTE_FORWARD = 519;
const int ID_EDIT_MOVE_NOTE_BACKWARD = 520;
const int ID_VIEW_MENU = 521;
const int ID_VIEW_TOOLBAR = 522;
const int ID_VIEW_STATUS_BAR = 523;
const int ID_VIEW_COMPOSE_BAR = 524;
const int ID_COPY_SOURCE = 525;
const int ID_MARKER_WRAPS_STRIP = 526;
const int ID_UNITS = 527;
const int ID_CHANGE_INTERFACE_LANGUAGE = 528;
const int ID_TOOLS_MENU = 529;
const int ID_TOOLS_DEFINE_CC = 530;
const int ID_UNLOAD_CC_TABLES = 531;
const int ID_USE_CC = 532;
const int ID_ACCEPT_CHANGES = 533;
const int ID_TOOLS_DEFINE_SILCONVERTER = 534;
const int ID_USE_SILCONVERTER = 535;
const int ID_TOOLS_KB_EDITOR = 536;
const int ID_TOOLS_AUTO_CAPITALIZATION = 537;
const int ID_RETRANS_REPORT = 538;
const int ID_TOOLS_SPLIT_DOC = 539;
const int ID_TOOLS_JOIN_DOCS = 540;
const int ID_TOOLS_MOVE_DOC = 541;
const int ID_EXPORT_IMPORT_MENU = 542;
const int ID_FILE_EXPORT_SOURCE = 543;
const int ID_FILE_EXPORT = 544;
const int ID_FILE_EXPORT_TO_RTF = 545;
const int ID_EXPORT_GLOSSES = 546;
const int ID_EXPORT_FREE_TRANS = 547;
const int ID_FILE_EXPORT_KB = 548;
const int ID_IMPORT_TO_KB = 549;
const int ID_ADVANCED_MENU = 550;
const int ID_ADVANCED_ENABLEGLOSSING = 551;
const int ID_ADVANCED_GLOSSING_USES_NAV_FONT = 552;
const int ID_ADVANCED_TRANSFORM_ADAPTATIONS_INTO_GLOSSES = 553;
const int ID_ADVANCED_DELAY = 554;
const int ID_ADVANCED_BOOKMODE = 555;
const int ID_ADVANCED_FREE_TRANSLATION_MODE = 556;
const int ID_ADVANCED_TARGET_TEXT_IS_DEFAULT = 557;
const int ID_ADVANCED_GLOSS_TEXT_IS_DEFAULT = 558;
const int ID_ADVANCED_REMOVE_FILTERED_FREE_TRANSLATIONS = 559;
const int ID_ADVANCED_COLLECT_BACKTRANSLATIONS = 560;
const int ID_ADVANCED_REMOVE_FILTERED_BACKTRANSLATIONS = 561;
const int ID_ADVANCED_USETRANSLITERATIONMODE = 562;
const int ID_ADVANCED_SENDSYNCHRONIZEDSCROLLINGMESSAGES = 563;
const int ID_ADVANCED_RECEIVESYNCHRONIZEDSCROLLINGMESSAGES = 564;
const int ID_LAYOUT_MENU = 565;
const int ID_ALIGNMENT = 566;
const int ID_HELP_MENU = 567;
const int ID_ONLINE_HELP = 568;
const int ID_USER_FORUM = 569;
const int ID_HELP_USE_TOOLTIPS = 570;
const int ID_ADMINISTRATOR_MENU = 571;
const int ID_CUSTOM_WORK_FOLDER_LOCATION = 572;
const int ID_LOCK_CUSTOM_LOCATION = 573;
const int ID_UNLOCK_CUSTOM_LOCATION = 574;
const int ID_LOCAL_WORK_FOLDER_MENU = 575;
const int ID_SET_PASSWORD_MENU = 576;
const int ID_MOVE_OR_COPY_FOLDERS_OR_FILES = 577;
wxMenuBar *AIMenuBarFunc();

// Declare toolbar functions

const int ID_BUTTON_CREATE_NOTE = 578;
const int ID_BUTTON_PREV_NOTE = 579;
const int ID_BUTTON_NEXT_NOTE = 580;
const int ID_BUTTON_DELETE_ALL_NOTES = 581;
const int ID_BUTTON_RESPECTING_BDRY = 582;
const int ID_BUTTON_SHOWING_PUNCT = 583;
const int ID_BUTTON_TO_END = 584;
const int ID_BUTTON_TO_START = 585;
const int ID_BUTTON_STEP_DOWN = 586;
const int ID_BUTTON_STEP_UP = 587;
const int ID_BUTTON_BACK = 588;
const int ID_BUTTON_MERGE = 589;
const int ID_BUTTON_RESTORE = 590;
const int ID_BUTTON_RETRANSLATION = 591;
const int ID_BUTTON_EDIT_RETRANSLATION = 592;
const int ID_REMOVE_RETRANSLATION = 593;
const int ID_BUTTON_NULL_SRC = 594;
const int ID_BUTTON_REMOVE_NULL_SRCPHRASE = 595;
const int ID_BUTTON_CHOOSE_TRANSLATION = 596;
const int ID_SHOWING_ALL = 597;
const int ID_BUTTON_EARLIER_TRANSLATION = 598;
const int ID_BUTTON_NO_PUNCT_COPY = 599;
void AIToolBarFunc( wxToolBar *parent );

void AIToolBar32x30Func( wxToolBar *parent );

// Declare bitmap functions

wxBitmap AIToolBarBitmapsUnToggledFunc( size_t index );

const int ID_BITMAP_FOLDERAI = 600;
const int ID_BITMAP_FILEAI = 601;
const int ID_BITMAP_EMPTY_FOLDER = 602;
wxBitmap AIMainFrameIcons( size_t index );

const int ID_BUTTON_IGNORING_BDRY = 603;
const int ID_BUTTON_HIDING_PUNCT = 604;
const int ID_SHOWING_TGT = 605;
const int ID_BUTTON_ENABLE_PUNCT_COPY = 606;
wxBitmap AIToolBarBitmapsToggledFunc( size_t index );

wxBitmap WhichFilesBitmapsFunc( size_t index );

wxBitmap AIToolBarBitmapsToggled32x30Func( size_t index );

wxBitmap AIToolBarBitmapsUnToggled32x30Func( size_t index );

#endif

// End of generated file
