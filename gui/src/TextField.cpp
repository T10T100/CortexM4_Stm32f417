#include "TextField.h"

int TextFieldsDEfaultCickListener (TouchStruct arg)
{
    GTextField<ColorDepth> *textField = (GTextField<ColorDepth> *)arg.object;
    textField->setSelectionStart(arg.local.x);
    textField->setSelectionEnd(arg.local.x);
    return 0;
}

int TextFieldsDEfaultTouchListener (TouchStruct arg)
{
    GTextField<ColorDepth> *textField = (GTextField<ColorDepth> *)arg.object;
    textField->setSelectionEnd(arg.local.x);
    textField->setSelect();
    return 0;
}

int TextFieldsDEfaultReleaseListener (TouchStruct arg)
{
    GTextField<ColorDepth> *textField = (GTextField<ColorDepth> *)arg.object;
    textField->setSelectionStart(0);
    textField->setSelectionEnd(0);
    return 0;
}