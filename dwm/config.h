/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const unsigned int gappih    = 9;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 9;       /* vert inner gap between windows */
static const unsigned int gappoh    = 9;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 9;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminus:size=14" };

/* Background and foreground color definitions */
static const char col_bg1[]       = "#002b36"; // Background color 1: Top bar background
static const char col_bg2[]       = "#002b36"; // Background color 2: Normal window borders
static const char col_bg3[]       = "#cccccc"; // Foreground for normal windows (unfocused)
static const char col_fg1[]       = "#ffffff"; // Foreground for selected windows (focused)
static const char col_acc[]       = "#ffffff"; // Accent color for selected window borders

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_bg3, col_bg1, col_bg2 },
	[SchemeSel]  = { col_fg1, col_fg1, col_acc },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };
static const char *alttags[] = { "1", "2", "3", "4" };

static const char *tagsel[][2] = {
	{ "#ffffff", col_bg1 },
	{ "#ffffff", col_bg1 },
	{ "#ffffff", col_bg1 },
	{ "#ffffff", col_bg1 },
	{ "#ffffff", col_bg1 },
	{ "#ffffff", col_bg1 },
};

/*
static const unsigned int ulinepad	= 5;	 horizontal padding between the underline and tag 
static const unsigned int ulinestroke	= 2;	 thickness / height of the underline 
static const unsigned int ulinevoffset	= 0;	 how far above the bottom of the bar the line should appear
static const int ulineall 		= 0;	 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       2,            0,           -1 },
  { "qutebrowser", NULL,    NULL,       2,            0,           -1 },
  { "pavucontrol", NULL,    NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "rofi -show run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL }; 
static const char *firefox[]  = { "firefox", NULL };
static const char *pcmanfm[]  = { "pcmanfm", NULL };


/* volume commands */
static const char *uvol[]   = { "pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *dvol[] = { "pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mvol[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };

/* brightness commands */
static const char *ubright[] = { "xbacklight", "-inc", "10",     NULL };
static const char *dbright[] = { "xbacklight", "-dec", "10",     NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	
  { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_f,      spawn,          {.v = firefox } },
  { MODKEY,                       XK_e,      spawn,          {.v = pcmanfm } },
 	{ MODKEY, 			                XK_d, 		 spawn,      		{.v = roficmd } },


  { MODKEY,                       XK_bracketright, spawn,    SHCMD("~/bin/settings")},
  { MODKEY,                       XK_bracketleft, spawn,     SHCMD("~/bin/menuz")},
	
  { MODKEY,                       XK_t, spawn,          {.v = termcmd } },
	
  { MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_j,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_Print,   spawn,         SHCMD("scrot -d 4 $HOME/Pictures/%d-%m-%H-%M-%S.png") },
  { 0,                            XK_Home,    spawn,         SHCMD("flameshot screen --path ~/Pictures/") },
	{ 0,                            0x1008FF02, spawn,         {.v = ubright } },
	{ 0,                            0x1008FF03, spawn,         {.v = dbright } },
	{ 0,                            0x1008FF13, spawn,         {.v = uvol } },
	{ 0,                            0x1008FF11, spawn,         {.v = dvol } },
	{ 0,                            0x1008FF12, spawn,         {.v = mvol } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

