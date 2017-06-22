#include <windows.h>
#include <stdio.h>

struct IButtonVtbl;
typedef struct IButton
{
  const struct IButtonVtbl *lpVtbl;
} IButton;

typedef struct IButtonVtbl
{
  HRESULT (__stdcall* SetCaption)(IButton* self, BSTR caption);
  HRESULT (__stdcall* SetTop)(IButton* self, double top);
  HRESULT (__stdcall* SetLeft)(IButton* self, double left);
  HRESULT (__stdcall* SetWidth)(IButton* self, double width); // TODO: check: single or double?
  HRESULT (__stdcall* SetHeight)(IButton* self, double height);
} IButtonVtbl;

typedef struct Button
{
  IButton IButton_iface;

  HWND hwnd;
} Button;

inline
static
Button*
impl_from_IButton(IButton *iface)
{
  printf("lib: impl_from_IButton\n");
  return CONTAINING_RECORD(iface, Button, IButton_iface);
}


struct ILabelVtbl;
typedef struct ILabel
{
  const struct ILabelVtbl *lpVtbl;
} ILabel;

typedef struct ILabelVtbl
{
  HRESULT (__stdcall* SetCaption)(ILabel* self, BSTR caption);
  HRESULT (__stdcall* SetTop)(ILabel* self, double top);
  HRESULT (__stdcall* SetLeft)(ILabel* self, double left);
  HRESULT (__stdcall* SetWidth)(ILabel* self, double width); // TODO: check: single or double?
  HRESULT (__stdcall* SetHeight)(ILabel* self, double height);
  HRESULT (__stdcall* SetForeColor)(ILabel* self, LONG x);
  HRESULT (__stdcall* SetBackColor)(ILabel* self, LONG x);
} ILabelVtbl;

typedef struct Label
{
  ILabel ILabel_iface;

  HWND hwnd;
  HBRUSH backBrush; // TODO: free on destroy
  LONG back; // is there a better type for this?  what does RGB macro return? CreateSolidBrush take?
  LONG foreground;
} Label;

inline
static
Label*
impl_from_ILabel(ILabel *iface)
{
  printf("lib: impl_from_ILabel\n");
  return CONTAINING_RECORD(iface, Label, ILabel_iface);
}






typedef struct
{
  int left, top, width, height;
} SizedRect;

SizedRect GetPos(HWND hwnd)
{
  RECT r1;
  GetClientRect(hwnd, &r1);
  int width = r1.right; // sic
  int height = r1.bottom; // sic
  POINT topleft;
  topleft.x = r1.top;
  topleft.y = r1.left;
  MapWindowPoints(hwnd, GetParent(hwnd), &topleft, 1);
  SizedRect r2;
  r2.left = topleft.x;
  r2.top = topleft.y;
  r2.width = width;
  r2.height = height;
  return r2;
}

HRESULT __stdcall Control_SetCaption(HWND hwnd, BSTR caption)
{
  /* VARIANT captionV = { VT_EMPTY }; */
  /* // FIXME: error handling, memory management, etc. */
  /* if (VariantChangeType(&captionV, value, 0, VT_BSTR) != S_OK) */
  /*   return E_OUTOFMEMORY; */
  /* LPWSTR caption = captionV.bstrVal; */
  SetWindowTextW(hwnd, caption);
  return S_OK;
}

HRESULT __stdcall Control_SetTop(HWND hwnd, double top)
{
  SizedRect r = GetPos(hwnd);
  SetWindowPos(hwnd, NULL, r.left, top / 15, r.width, r.height, 0);
  return S_OK;
}

HRESULT __stdcall Control_SetLeft(HWND hwnd, double left)
{
  SizedRect r = GetPos(hwnd);
  SetWindowPos(hwnd, NULL, left / 15, r.top, r.width, r.height, 0);
  return S_OK;
}

HRESULT __stdcall Control_SetWidth(HWND hwnd, double width)
{
  SizedRect r = GetPos(hwnd);
  SetWindowPos(hwnd, NULL, r.left, r.top, width / 15, r.height, 0);
  return S_OK;
}

HRESULT __stdcall Control_SetHeight(HWND hwnd, double height)
{
  SizedRect r = GetPos(hwnd);
  SetWindowPos(hwnd, NULL, r.left, r.top, r.width, height / 15, 0);
  return S_OK;
}




HRESULT __stdcall Button_SetCaption(IButton* iface, BSTR caption)
{
  HWND hwnd = impl_from_IButton(iface)->hwnd;
  return Control_SetCaption(hwnd, caption);
}

HRESULT __stdcall Button_SetTop(IButton* iface, double top)
{
  HWND hwnd = impl_from_IButton(iface)->hwnd;
  return Control_SetTop(hwnd, top);
}

HRESULT __stdcall Button_SetLeft(IButton* iface, double left)
{
  HWND hwnd = impl_from_IButton(iface)->hwnd;
  return Control_SetLeft(hwnd, left);
}

HRESULT __stdcall Button_SetWidth(IButton* iface, double width)
{
  HWND hwnd = impl_from_IButton(iface)->hwnd;
  return Control_SetWidth(hwnd, width);
}

HRESULT __stdcall Button_SetHeight(IButton* iface, double height)
{
  HWND hwnd = impl_from_IButton(iface)->hwnd;
  return Control_SetHeight(hwnd, height);
}

static const IButtonVtbl button_vtbl =
{
  Button_SetCaption,
  Button_SetTop,
  Button_SetLeft,
  Button_SetWidth,
  Button_SetHeight,
};



HRESULT __stdcall Label_SetCaption(ILabel* iface, BSTR caption)
{
  HWND hwnd = impl_from_ILabel(iface)->hwnd;
  return Control_SetCaption(hwnd, caption);
}

HRESULT __stdcall Label_SetTop(ILabel* iface, double top)
{
  HWND hwnd = impl_from_ILabel(iface)->hwnd;
  return Control_SetTop(hwnd, top);
}

HRESULT __stdcall Label_SetLeft(ILabel* iface, double left)
{
  HWND hwnd = impl_from_ILabel(iface)->hwnd;
  return Control_SetLeft(hwnd, left);
}

HRESULT __stdcall Label_SetWidth(ILabel* iface, double width)
{
  HWND hwnd = impl_from_ILabel(iface)->hwnd;
  return Control_SetWidth(hwnd, width);
}

HRESULT __stdcall Label_SetHeight(ILabel* iface, double height)
{
  HWND hwnd = impl_from_ILabel(iface)->hwnd;
  return Control_SetHeight(hwnd, height);
}

HRESULT __stdcall Label_SetForeColor(ILabel* iface, LONG x)
{
  Label* lbl = impl_from_ILabel(iface);
  lbl->foreground = x;
  return S_OK;
}

HRESULT __stdcall Label_SetBackColor(ILabel* iface, LONG x)
{
  Label* lbl = impl_from_ILabel(iface);
  lbl->back = x;
  lbl->backBrush = CreateSolidBrush(x);
  return S_OK;
}

static const ILabelVtbl label_vtbl =
{
  Label_SetCaption,
  Label_SetTop,
  Label_SetLeft,
  Label_SetWidth,
  Label_SetHeight,
  Label_SetForeColor,
  Label_SetBackColor,
};



static int FORMCOUNT = 0;

void __stdcall pump(void)
{
  printf("lib: pump\n");
  if (FORMCOUNT == 0)
    return;

  BOOL bRet;
  MSG msg;
  HWND hwnd = NULL;
  while ((bRet = GetMessage(&msg, hwnd, 0, 0)) != 0) {
    if (bRet == -1) {
      // handle the error and possibly exit
    } else {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

struct IFormVtbl;
typedef struct IForm
{
  const struct IFormVtbl *lpVtbl;
} IForm;

typedef struct IFormVtbl
{
  HRESULT (__stdcall* Load)(IForm* self);
  HRESULT (__stdcall* Show)(IForm* self);
  HRESULT (__stdcall* SetScaleWidth)(IForm* self, double scalewidth);
  HRESULT (__stdcall* SetScaleHeight)(IForm* self, double scaleheight);
  HRESULT (__stdcall* ControlsDotAdd)(IForm* self, BSTR progId, BSTR name, VARIANT container, VARIANT* ret);
} IFormVtbl;

typedef struct Form
{
  IForm IForm_iface;

  HWND hwnd;
  HFONT hUserFont;
  Label* lbl;
} Form;

inline
static
Form*
impl_from_IForm(IForm *iface)
{
  printf("lib: impl_from_IForm\n");
  return CONTAINING_RECORD(iface, Form, IForm_iface);
}

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HMODULE hInstance;
static void initHinstance()
{
  printf("lib: initHinstance\n");
  GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
		     GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		     (LPCSTR)&initHinstance, &hInstance);
}

Form* formsingleton; // FIXME
static Form* find_form(HWND hwnd)
{
  // FIXME.   Use thunking?  Window props?  A concurrent dict?
  return formsingleton;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

  Form* self = find_form(hwnd);

  PAINTSTRUCT ps;
  HDC         hdc;
  /* printf("lib: wndproc\n"); */
  switch ( iMsg ) {
  case WM_NCCREATE:
    FORMCOUNT++; // or during load?  load happens sooner.
    printf("NCCREATE: %i\n", FORMCOUNT);
    break;
  /* case WM_PAINT: */
  /*   hdc = BeginPaint(hwnd, &ps); */
  /*   TextOut(hdc, 50, 50, "Hellooooooo", 13); */
  /*   EndPaint(hwnd, &ps); */
  /*   break; */

    // FIXME: who's sending WM_DESTROY? i have the wrong count so I can't quit.
  case WM_DESTROY:
    {
      FORMCOUNT--;
      printf("DESTROY: %i\n", FORMCOUNT);
      if (FORMCOUNT == 0)
      	PostQuitMessage(0);
      return 0;
    }
  case WM_CTLCOLORSTATIC:
    {
      // re all three uses of self->lbl:
      // FIXME what if we haven't customized the colour?
      // FIXME: this only supports one label (not more, not less!!!)

      HDC hdcStatic = (HDC)wParam;
      SetTextColor(hdcStatic, self->lbl->foreground);
      // This sets the background of the text
      SetBkColor(hdcStatic, self->lbl->back);

      // This brush is needed for the background outwith the text.
      return (INT_PTR)self->lbl->backBrush;
    }
  }


  return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

HRESULT
__stdcall Form_Load(IForm* iface)
{
  printf("lib: Form_Load: %i\n", FORMCOUNT);
  initHinstance();

  Form* self = impl_from_IForm(iface);
  formsingleton = self;

  MSG         msg;
  WNDCLASSEX  wndclass;
  static const char classname[] = "Brainsick Form";

  wndclass.cbSize         = sizeof(wndclass);
  wndclass.style          = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc    = WndProc;
  wndclass.cbClsExtra     = 0;
  wndclass.cbWndExtra     = 0;
  wndclass.hInstance      = hInstance;
  wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground  = (HBRUSH) (COLOR_BTNFACE+1);
  wndclass.lpszClassName  = classname;
  wndclass.lpszMenuName   = NULL;


  RegisterClassEx(&wndclass);



  HWND hwnd = CreateWindow(classname, "Form1",
			   WS_OVERLAPPEDWINDOW,
			   200, 200, // was CW_USEDEFAULT
			   900, 900, // was CW_USEDEFAULT
			   NULL, NULL, hInstance, NULL);

/* MSDN says: It is not recommended that you employ [GetStockObject] to obtain the current font used by dialogs and windows. Instead, use the SystemParametersInfo function with the SPI_GETNONCLIENTMETRICS parameter to retrieve the current font. SystemParametersInfo will take into account the current theme and provides font information for captions, menus, and message dialogs.  */

// Should we ever clean up the font?
 NONCLIENTMETRICSW ncMetrics;
 HFONT hUserFont = NULL;
 ncMetrics.cbSize = sizeof(NONCLIENTMETRICSW);
 if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS,
			   sizeof(NONCLIENTMETRICSW), &ncMetrics, 0))

   self->hUserFont = CreateFontIndirectW( &ncMetrics.lfMessageFont );
 if (hUserFont)
   SendMessageW( hwnd, WM_SETFONT, (WPARAM)self->hUserFont, 0 );

  self->hwnd = hwnd;
  return S_OK;
}

static HWND formgethwndorload(Form* self)
{
  printf("lib: gethwnd\n");
  if (self->hwnd == NULL)
    self->IForm_iface.lpVtbl->Load(&self->IForm_iface);
  return self->hwnd;
}

HRESULT
__stdcall Form_Show(IForm* iface)
{
  printf("lib: form_show\n");
  Form* self = impl_from_IForm(iface);
  printf("lib: form_show: have impl\n");
  HWND hwnd = formgethwndorload(self);
  printf("lib: form_show: have hwnd\n");
  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);
  printf("lib: form_show: done\n");
  return S_OK;
}

HRESULT __stdcall Form_SetScaleWidth(IForm* iface, double scalewidth)
{
  Form* self = impl_from_IForm(iface);
  HWND hwnd = formgethwndorload(self);

  RECT clientdelta;
  clientdelta.left = 0;
  clientdelta.top = 0;
  clientdelta.right = 0;
  clientdelta.bottom = 0;
  AdjustWindowRect(&clientdelta, WS_OVERLAPPEDWINDOW, FALSE); // FALSE means no menu.

  RECT current;
  GetWindowRect(hwnd, &current);
  // i.e. unadjustwindowrect:
  current.left -= clientdelta.left;
  current.top -= clientdelta.top;
  current.right -= clientdelta.right;
  current.bottom -= clientdelta.bottom;

  RECT nu;
  nu.left = current.left;
  nu.top = current.top;
  nu.right = current.left + scalewidth / 15;
  nu.bottom = current.bottom;

  // or could do += clientdelta
  AdjustWindowRect(&nu, WS_OVERLAPPEDWINDOW, FALSE); // FALSE means no menu.
  
  SetWindowPos(hwnd, NULL, nu.left, nu.top, nu.right - nu.left, nu.bottom - nu.top, 0);
  return S_OK;
}

HRESULT __stdcall Form_SetScaleHeight(IForm* iface, double scaleheight)
{
  Form* self = impl_from_IForm(iface);
  HWND hwnd = formgethwndorload(self);

  RECT clientdelta;
  clientdelta.left = 0;
  clientdelta.top = 0;
  clientdelta.right = 0;
  clientdelta.bottom = 0;
  AdjustWindowRect(&clientdelta, WS_OVERLAPPEDWINDOW, FALSE); // FALSE means no menu.

  RECT current;
  GetWindowRect(hwnd, &current);
  // i.e. unadjustwindowrect:
  current.left -= clientdelta.left;
  current.top -= clientdelta.top;
  current.right -= clientdelta.right;
  current.bottom -= clientdelta.bottom;

  RECT nu;
  nu.left = current.left;
  nu.top = current.top;
  nu.right = current.right;
  nu.bottom = current.top + scaleheight / 15;

  // or could do += clientdelta
  AdjustWindowRect(&nu, WS_OVERLAPPEDWINDOW, FALSE); // FALSE means no menu.

  SetWindowPos(hwnd, NULL, nu.left, nu.top, nu.right - nu.left, nu.bottom - nu.top, 0);
  return S_OK;
}



/* IForm* __stdcall new_form(void) */
/* { */
/*   printf("lib: new_form\n"); */
/*   Form* f = (Form*)malloc(sizeof(Form)); */
/*   f->IForm_iface.lpVtbl = &form_vtbl; */
/*   f->hwnd = NULL; */
/*   return &(f->IForm_iface); */
/* } */

IButton* __stdcall AddButton(IForm* iform)
{
  printf("lib: addbutton\n");
  Form* form = impl_from_IForm(iform);
  printf("lib: addbutton: have impl\n");
  HWND formhwnd = formgethwndorload(form);
  printf("lib: addbutton: have hwnd\n");

  int x = 0;
  int y = 0;
  int width = 100;
  int height = 22;

  HWND hwnd = CreateWindow("BUTTON", "Command1",
			   WS_CHILD | WS_TABSTOP | WS_VISIBLE,
			   x, y,
			   100, 22,
			   formhwnd, NULL, hInstance, NULL);
   SendMessageW( hwnd, WM_SETFONT, (WPARAM)form->hUserFont, 0 );

  Button* b = (Button*)malloc(sizeof(Button));
  b->IButton_iface.lpVtbl = &button_vtbl;
  b->hwnd = hwnd;

  return &b->IButton_iface;
}

ILabel* __stdcall AddLabel(IForm* iform)
{
  printf("lib: addlabel\n");
  Form* form = impl_from_IForm(iform);
  printf("lib: addlabel: have impl\n");
  HWND formhwnd = formgethwndorload(form);
  printf("lib: addlabel: have hwnd\n");

  int x = 0;
  int y = 0;
  int width = 100;
  int height = 22;

  HWND hwnd = CreateWindow("STATIC", "Label1",
			   WS_CHILD | WS_VISIBLE,
			   x, y,
			   100, 22,
			   formhwnd, NULL, hInstance, NULL);
   SendMessageW( hwnd, WM_SETFONT, (WPARAM)form->hUserFont, 0 );

  Label* l = (Label*)malloc(sizeof(Label));
  l->ILabel_iface.lpVtbl = &label_vtbl;
  l->hwnd = hwnd;
  form->lbl = l;

  return &l->ILabel_iface;
}

HRESULT __stdcall Form_ControlsDotAdd(IForm* self, BSTR progId, BSTR name, VARIANT container, VARIANT* ret)
{
  Form* form = impl_from_IForm(self);

  // FIXME: need to look at progid (e.g. compare to VB.CommandButton)
  IButton* button = AddButton(self);

  ret->vt = VT_UNKNOWN;
  ret->punkVal = (IUnknown*)button;
  // FIXME: IButton_iface is not IUnknown!

  return S_OK;
}

static const IFormVtbl form_vtbl =
{
  Form_Load,
  Form_Show,
  Form_SetScaleWidth,
  Form_SetScaleHeight,
  Form_ControlsDotAdd,
};
