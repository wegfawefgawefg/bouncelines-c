project('bouncelines', 'c',
    default_options: 'default_library=static')

install_headers('update.h')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

sdl2_dep = dependency('sdl2')
sdl2_ttf_dep = dependency('SDL2_ttf')
cglm_dep = dependency('cglm')


executable('bouncelines', 
    sources: [
        'main.c',
        'update.c',
    ],
    dependencies: [
        sdl2_dep, 
        sdl2_ttf_dep, 
        cglm_dep,
        m_dep,
    ]
)
