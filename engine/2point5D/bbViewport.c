#include "engine/2point5D/bbViewport.h"

bbFlag bbRenderable_new(bbRenderable* renderable, I32 height, I32 width){

    renderable->renderTexture
    = sfRenderTexture_create(width, height, sfFalse);
    sfRenderTexture_clear(renderable->renderTexture, sfTransparent);

    renderable->texture = sfRenderTexture_getTexture(renderable->renderTexture);

    renderable->sprite = sfSprite_create();
    sfSprite_setTexture(renderable->sprite, renderable->texture, sfTrue);

    return Success;
}

bbFlag bbViewport_new(bbViewport** viewport, I32 height, I32 width){
    bbViewport* VP = malloc(sizeof *VP);

    bbRenderable_new(&VP->background, height, width);
    bbRenderable_new(&VP->ground, height, width);
    bbRenderable_new(&VP->main, height, width);
    bbRenderable_new(&VP->minimap, height, width);


    sfRenderTexture_clear(VP->background.renderTexture, sfBlue);

    char vertShader[] = "\
        uniform vec2 offset;\
        void main()\
        {\
         \
            vec4 offsetvertex = vec4(offset.x, offset.y, 0, 0);\
            gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex + offsetvertex);\
         \
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\
         \
           gl_FrontColor = gl_Color;\
        }\
    ";

    char fragShader[] = "\
        uniform sampler2D Background;\
        uniform sampler2D Ground;\
        uniform sampler2D Main;\
        uniform sampler2D MiniMap;\
        \
        void main()\
        {\
            vec4 background = texture2D(Background, gl_TexCoord[0].xy);\
            vec4 ground     = texture2D(Ground,     gl_TexCoord[0].xy);\
            vec4 main       = texture2D(Main,       gl_TexCoord[0].xy);\
            vec4 minimap    = texture2D(MiniMap,    gl_TexCoord[0].xy);\
        \
            vec4 mix1 = mix(background, ground,  ground.a);\
            vec4 mix2 = mix(mix1,       main,    main.a  );\
            vec4 mix3 = mix(mix2,       minimap, minimap.a   );\
\
            gl_FragColor =  mix3;\
            \
        }\
    ";

    VP->shader = sfShader_createFromMemory(vertShader, NULL, fragShader);

    VP->renderStates.shader = VP->shader;
    VP->renderStates.blendMode = sfBlendAlpha;
    VP->renderStates.transform = sfTransform_Identity;
    VP->renderStates.texture = VP->background.texture;

    sfShader_setTextureUniform(VP->shader,"Background", VP->background.texture);
    sfShader_setTextureUniform(VP->shader,"Ground", VP->ground.texture);
    sfShader_setTextureUniform(VP->shader,"Main", VP->main.texture);
    sfShader_setTextureUniform(VP->shader,"MiniMap", VP->minimap.texture);

    *viewport = VP;

    return Success;
}


bbFlag bbViewport_draw(sfRenderWindow* window, bbViewport* viewport){
    sfRenderTexture_display(viewport->background.renderTexture);
    sfRenderTexture_display(viewport->ground.renderTexture);
    sfRenderTexture_display(viewport->main.renderTexture);
    sfRenderTexture_display(viewport->minimap.renderTexture);

    sfRenderWindow_drawSprite(window, viewport->background.sprite,
                              &viewport->renderStates);

    return Success;
}
