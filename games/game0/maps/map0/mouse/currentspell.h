bbFlag CurrentSpell_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidgets* widgets = Widgets;
    bbWidget* SpellMenu = widgets->spellMenu;
    SpellMenu->tree.visible = true;
    SpellMenu->tree.childrenvisible = true;
    return Success;
}