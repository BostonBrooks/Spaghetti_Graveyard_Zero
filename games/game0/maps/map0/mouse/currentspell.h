bbFlag CurrentSpell_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidgets* widgets = Widgets;
    bbWidget* SpellMenu = widgets->spellMenu;

    bool visible = !SpellMenu->tree.visible;
    SpellMenu->tree.visible =  visible;
    SpellMenu->tree.childrenvisible =  visible;
    return Success;
}