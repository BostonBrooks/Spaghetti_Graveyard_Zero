#include "headers/bbDispatch.h"
#include "headers/bbSystemIncludes.h"
#include "headers/bbGame.h"
#include "headers/bbMouse.h"
#include "headers/bbWidget.h"
#include "headers/bbTree.h"
#include "headers/bbIntTypes.h"


I32 EventMouse(bbMouseEvent* mouse, I32 map){

    bbWidget* root = g_Game->m_Maps[map]->m_Widgets->m_Layout;
    bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;

    ascending_searchVisible(mouse, root, bbWidget_mouse, pool);

    return f_Success;
}
