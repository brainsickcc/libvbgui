#include <windows.h>
#include <stdio.h>

const VARIANT vc = { VT_ERROR, 0, 0, 0, DISP_E_PARAMNOTFOUND };

void bstr1(void)
{
  BSTR str = SysAllocString(L"bstr1");
  VARIANT vbstr = { VT_BSTR, 0, 0, 0, (LONGLONG)str };
}

void bstr2(void)
{
  BSTR str = SysAllocString(L"bstr2");
  VARIANT vbstr;
  vbstr.vt = VT_BSTR,
  vbstr.bstrVal = str;
}


int main(void)
{
  VARIANT vs;
  vs.vt = VT_ERROR;
  vs.scode = DISP_E_PARAMNOTFOUND;
  // printf("VT s: %i\n", vs.vt);
  // printf("VT c: %i\n", vc.vt);

  // printf("SCODE s: %li\n", vs.scode);
  // printf("SCODE c: %li\n", vc.scode);

  return 0;
}