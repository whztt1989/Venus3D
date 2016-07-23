////////////////////////////////////////////////////////////////////////////
//
//  The MIT License (MIT)
//  Copyright (c) 2016 Albert D Yang
// -------------------------------------------------------------------------
//  Module:      RenderTest
//  File name:   Main.cpp
//  Created:     2016/07/23 by Albert
//  Description:
// -------------------------------------------------------------------------
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
// -------------------------------------------------------------------------
//  The above copyright notice and this permission notice shall be included
//  in all copies or substantial portions of the Software.
// -------------------------------------------------------------------------
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////

#include "RenderTest.h"
#include <SDL.h>

int done;

/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void
quit(int rc)
{
	SDL_Quit();
	exit(rc);
}

static void
print_string(char **text, size_t *maxlen, const char *fmt, ...)
{
	int len;
	va_list ap;

	va_start(ap, fmt);
	len = SDL_vsnprintf(*text, *maxlen, fmt, ap);
	if (len > 0) {
		*text += len;
		if (((size_t)len) < *maxlen) {
			*maxlen -= (size_t)len;
		}
		else {
			*maxlen = 0;
		}
	}
	va_end(ap);
}

static void
print_modifiers(char **text, size_t *maxlen)
{
	int mod;
	print_string(text, maxlen, " modifiers:");
	mod = SDL_GetModState();
	if (!mod) {
		print_string(text, maxlen, " (none)");
		return;
	}
	if (mod & KMOD_LSHIFT)
		print_string(text, maxlen, " LSHIFT");
	if (mod & KMOD_RSHIFT)
		print_string(text, maxlen, " RSHIFT");
	if (mod & KMOD_LCTRL)
		print_string(text, maxlen, " LCTRL");
	if (mod & KMOD_RCTRL)
		print_string(text, maxlen, " RCTRL");
	if (mod & KMOD_LALT)
		print_string(text, maxlen, " LALT");
	if (mod & KMOD_RALT)
		print_string(text, maxlen, " RALT");
	if (mod & KMOD_LGUI)
		print_string(text, maxlen, " LGUI");
	if (mod & KMOD_RGUI)
		print_string(text, maxlen, " RGUI");
	if (mod & KMOD_NUM)
		print_string(text, maxlen, " NUM");
	if (mod & KMOD_CAPS)
		print_string(text, maxlen, " CAPS");
	if (mod & KMOD_MODE)
		print_string(text, maxlen, " MODE");
}

static void
PrintModifierState()
{
	char message[512];
	char *spot;
	size_t left;

	spot = message;
	left = sizeof(message);

	print_modifiers(&spot, &left);
	SDL_Log("Initial state:%s\n", message);
}

static void
PrintKey(SDL_Keysym * sym, SDL_bool pressed, SDL_bool repeat)
{
	char message[512];
	char *spot;
	size_t left;

	spot = message;
	left = sizeof(message);

	/* Print the keycode, name and state */
	if (sym->sym) {
		print_string(&spot, &left,
			"Key %s:  scancode %d = %s, keycode 0x%08X = %s ",
			pressed ? "pressed " : "released",
			sym->scancode,
			SDL_GetScancodeName(sym->scancode),
			sym->sym, SDL_GetKeyName(sym->sym));
	}
	else {
		print_string(&spot, &left,
			"Unknown Key (scancode %d = %s) %s ",
			sym->scancode,
			SDL_GetScancodeName(sym->scancode),
			pressed ? "pressed " : "released");
	}
	print_modifiers(&spot, &left);
	if (repeat) {
		print_string(&spot, &left, " (repeat)");
	}
	SDL_Log("%s\n", message);
}

static void
PrintText(const char *eventtype, const char *text)
{
	const char *spot;
	char expanded[1024];

	expanded[0] = '\0';
	for (spot = text; *spot; ++spot)
	{
		size_t length = SDL_strlen(expanded);
		SDL_snprintf(expanded + length, sizeof(expanded) - length, "\\x%.2x", (unsigned char)*spot);
	}
	SDL_Log("%s Text (%s): \"%s%s\"\n", eventtype, expanded, *text == '"' ? "\\" : "", text);
}

void
loop()
{
	SDL_Event event;
	/* Check for events */
	/*SDL_WaitEvent(&event); emscripten does not like waiting*/

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			PrintKey(&event.key.keysym, (event.key.state == SDL_PRESSED) ? SDL_TRUE : SDL_FALSE, (event.key.repeat) ? SDL_TRUE : SDL_FALSE);
			break;
		case SDL_TEXTEDITING:
			PrintText("EDIT", event.text.text);
			break;
		case SDL_TEXTINPUT:
			PrintText("INPUT", event.text.text);
			break;
		case SDL_MOUSEBUTTONDOWN:
			/* Any button press quits the app... */
		case SDL_QUIT:
			done = 1;
			break;
		default:
			break;
		}
	}
#ifdef __EMSCRIPTEN__
	if (done) {
		emscripten_cancel_main_loop();
	}
#endif
}

int32_t VeMain() noexcept
{
	SDL_Window *window;

	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	/* Set 640x480 video mode */
	window = SDL_CreateWindow("CheckKeys Test",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480, 0);
	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create 640x480 window: %s\n",
			SDL_GetError());
		quit(2);
	}

#if __IPHONEOS__
	/* Creating the context creates the view, which we need to show keyboard */
	SDL_GL_CreateContext(window);
#endif

	SDL_StartTextInput();

	/* Print initial modifier state */
	SDL_PumpEvents();
	PrintModifierState();

	/* Watch keystrokes */
	done = 0;

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(loop, 0, 1);
#else
	while (!done) {
		loop();
	}
#endif

	SDL_Quit();
	return 0;
}
