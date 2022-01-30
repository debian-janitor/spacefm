/*
 *
 * License: See COPYING file
 *
 */

#ifndef _EXTERN_H_
#define _EXTERN_H_

static const char* terminal_programs[] = // for pref-dialog.c
    {"terminal",
     "xfce4-terminal",
     "aterm",
     "Eterm",
     "mlterm",
     "mrxvt",
     "rxvt",
     "sakura",
     "terminator",
     "urxvt",
     "xterm",
     "x-terminal-emulator",
     "qterminal"};

// clang-format off
static const char* su_commands[] = // order and contents must match prefdlg.ui
    {"/bin/su",
     "/usr/bin/sudo",
     "/usr/bin/doas"};
// clang-format on

#endif
