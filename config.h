/* mee LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int gappx 	= 0;
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono:size=12" };
static const char dmenufont[]       = "JetBrainsMono:monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ebdbb2";
static const char col_cyan[]        = "#458588";
static const char col_cyan2[]        = "#83a598";
static const char col_blue[]        = "#076678";
static const char col_purple[]      = "#b16286";
static const char col_red[]	    = "#ff0000";
static const char col_black[]	    = "#1c1c1c";
static const char col_black2[]	    = "#111111";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_black, col_black},
	[SchemeSel]  = { col_gray4, col_blue,  col_black  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating monitor */
        { "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_black, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char* browsercmd[] = { "firefox", NULL };
static const char *mutecmd[] = {"plwrap", "mute", NULL};
static const char *loudercmd[] = {"plwrap", "up", NULL};
static const char *lowercmd[] = {"plwrap", "down", NULL};
static const char* lockcmd[] = {"mylock", NULL};
static const char* reloadbarcmd[] = {"reloadbar", NULL};
static const char* mpcnext[]= {"mpc", "next", NULL};
static const char* mpctoggle[]= {"mpc", "toggle", NULL};
static const char* termtmuxcmd[] = {"kitty", "-e", "tmux", "-2", "new-session", "-A", "-s", "main", NULL};


#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termtmuxcmd } },
	//{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	//{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	//{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	//{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	//{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_a,      killclient,     {0} },
	{ MODKEY,                       XK_p,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        0x26,                       0)
	TAGKEYS(                        0xe9,                      1)
	TAGKEYS(                        0x22,                      2)
	TAGKEYS(                        0x27,                      3)
	TAGKEYS(                        0x28,                      4)
	TAGKEYS(                        0x2d,                      5)
	TAGKEYS(                        0xe8,                      6)
	TAGKEYS(                        0x5f,                      7)
	TAGKEYS(                        0xe7,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ ControlMask,					0xffbe /* f1 */,    spawn, 		   {.v = mutecmd } },
	{ ControlMask,					0xffbf /* f2 */,    spawn, 		   {.v = lowercmd } },
	{ ControlMask,					0xffc0 /* f3 */,    spawn, 		   {.v = loudercmd } },
	{ MODKEY|ControlMask,			XK_l,	   spawn, 		   {.v = lockcmd } },
    { MODKEY,                       0x77 /* w */,      spawn,          {.v = browsercmd } },
    { MODKEY,                       XK_r,              spawn,          {.v = reloadbarcmd } },
    { MODKEY,                       XK_n,              spawn,          {.v = mpcnext } },
    { MODKEY,                       XK_m,              spawn,          {.v = mpctoggle } },
    { MODKEY|ShiftMask,             XK_Return,         spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,              togglebar,      {0} },
    STACKKEYS(MODKEY,                          focus)
    STACKKEYS(MODKEY|ShiftMask,                push)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

