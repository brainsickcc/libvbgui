#include <windows.h>
#include <stdio.h>

extern void __stdcall pump(void);



struct IFormVtbl;
typedef struct IForm
{
  const struct IFormVtbl *lpVtbl;
} IForm;

typedef struct IFormVtbl
{
  HRESULT (__stdcall* Load)(IForm* self);
  HRESULT (__stdcall* Show)(IForm* self);
} IFormVtbl;

extern IForm* __stdcall new_form(void);

void __stdcall proc_main(void)
{
  printf("form-user: proc_main\n");
  IForm* form = new_form();
  printf("form-user: proc_main: have form\n");
  form->lpVtbl->Show(form);
  printf("form-user: proc_main: have shown\n");
  pump();
  printf("form-user: proc_main: have pumped\n");
}
