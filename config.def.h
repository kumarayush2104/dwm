/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu:style=Bold:size=10" };
static const char norm_fg[]         = "#d2ecd8";
static const char norm_bg[]         = "#271e2c";
static const char norm_border[]     = "#93a597";

static const char sel_fg[]          = "#d2ecd8";
static const char sel_bg[]          = "#439ABF";
static const char sel_border[]      = "#d2ecd8";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg, norm_bg, norm_border },
	[SchemeSel]  = { sel_fg, sel_bg, sel_border  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *roficmd[] = { "rofi", "-show", "combi", NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *mediaPlayPausecmd[] = { "playerctl", "play-pause", NULL };
static const char *mediaNextcmd[] = { "playerctl", "next", NULL };
static const char *mediaPreviouscmd[] = { "playerctl", "previous", NULL };

static const char *volumeUpcmd[] = { "amixer", "set", "Master", "5%+", NULL };
static const char *volumeDowncmd[] = { "amixer", "set", "Master", "5%-", NULL };
static const char *muteToggle[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *scrotScreenshot[]  = { "scrot", "%Y-%m-%d-%s_$wx$h.jpg", "-e", "mv $f ~/Pictures/Screenshots/", NULL };
static const char *scrotSelectScreenshot[]  = { "scrot", "-s", "%Y-%m-%d-%s_$wx$h.jpg", "-e", "mv $f ~/Pictures/Screenshots/", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ ControlMask,             XK_space,  	      spawn,          {.v = roficmd } },
	{ MODKEY,             	   XK_Return, 	      spawn,          {.v = termcmd } },
	{ MODKEY,                  XK_b,      	      togglebar,      {0} },
	{ MODKEY,                  XK_j, 	      focusstack,     {.i = +1 } },
	{ MODKEY,                  XK_k,      	      focusstack,     {.i = -1 } },
	{ MODKEY,                  XK_i,      	      incnmaster,     {.i = +1 } },
	{ MODKEY,                  XK_d,      	      incnmaster,     {.i = -1 } },
	{ MODKEY,                  XK_h,              setmfact,       {.f = -0.05} },
	{ MODKEY,                  XK_l,      	      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,        XK_Return, 	      zoom,           {0} },
	{ MODKEY,                  XK_Tab,            view,           {0} },
	{ MODKEY|ShiftMask,        XK_c,              killclient,     {0} },
	{ MODKEY,                  XK_t,      	      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                  XK_f,              setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                  XK_m,              setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                  XK_space,  	      setlayout,      {0} },
	{ MODKEY|ShiftMask,        XK_space,  	      togglefloating, {0} },
	{ MODKEY,                  XK_0,      	      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,        XK_0,      	      tag,            {.ui = ~0 } },
	{ MODKEY,                  XK_comma,  	      focusmon,       {.i = -1 } },
	{ MODKEY,                  XK_period, 	      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,        XK_comma,  	      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,        XK_period, 	      tagmon,         {.i = +1 } },
	{ MODKEY,                  XK_minus,  	      setgaps,        {.i = -1 } },
	{ MODKEY,                  XK_equal,  	      setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,        XK_equal,  	      setgaps,        {.i = 0  } },
	TAGKEYS(                   XK_1,                      	      0)
	TAGKEYS(                   XK_2,                      	      1)
	TAGKEYS(                   XK_3,                      	      2)
	TAGKEYS(                   XK_4,                              3)
	TAGKEYS(                   XK_5,                              4)
	TAGKEYS(                   XK_6,                              5)
	TAGKEYS(                   XK_7,                              6)
	TAGKEYS(                   XK_8,                              7)
	TAGKEYS(                   XK_9,                              8)
	{ MODKEY|ShiftMask,        XK_q,      	      quit,           {0} },
	{ 0,			  XF86XK_AudioPlay,   spawn,          { .v = mediaPlayPausecmd } },	
	{ 0,			  XF86XK_AudioNext,   spawn,          { .v = mediaNextcmd } },
	{ 0,			  XF86XK_AudioPrev,   spawn,          { .v = mediaPreviouscmd } },
	{ 0, 			  XF86XK_AudioRaiseVolume,    spawn,  { .v = volumeUpcmd } },
	{ 0,			  XF86XK_AudioLowerVolume,    spawn,  { .v = volumeDowncmd } },
	{ 0, 			  XF86XK_AudioMute, 	      spawn,  { .v = muteToggle } },
	{ 0, 			  XK_Print,	      spawn,	      { .v = scrotScreenshot } },
	{ ShiftMask,		  XK_Print,	      spawn,	      { .v = scrotSelectScreenshot } }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

