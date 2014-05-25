#   File:       D2X.make
#   Purpose:    Compile d2x (descent 2 port to Unix) with MPW for Mac OS 9
#   Target:     D2X
#   Created:    Saturday, June 12, 2004 04:38:06 PM


MAKEFILE        = D2X.make
�MondoBuild�    = #{MAKEFILE}   Make blank to avoid rebuilds when makefile is modified

ObjDir          = ":obj:"
Includes        =  �
				  -i :include: �
				  -i :arch:include: �
				  -i "{CIncludes}SDL:" �
				  -i :arch:carbon: �
				  -i "{CIncludes}" �
				  -i :main:

Sym-PPC         = -sym on

PPCAOptions     = {Includes} {Sym-PPC}
# Comment out '-d OGL' to build for SDL Video
# More to do further down where the PPCLink call is...
PPCCOptions     = {Includes} -includes unix -prefix conf.h {Sym-PPC} -d HAVE_CONFIG_H -enum int -noMapCR -w 2,7,30,35 -d OGL -d USE_SDLMIXER -d NDEBUG -d RELEASE

### Source Files ###

SrcFiles        =  �
				  :2d:2dsline.c �
				  :2d:bitblt.c �
				  :2d:bitmap.c �
				  :2d:box.c �
				  :2d:canvas.c �
				  :2d:circle.c �
				  :2d:disc.c �
				  :2d:font.c �
				  :2d:gpixel.c �
				  :2d:line.c �
				  :2d:palette.c �
				  :2d:pcx.c �
				  :2d:pixel.c �
				  :2d:poly.c �
				  :2d:rect.c �
				  :2d:rle.c �
				  :2d:scalec.c �
				  :2d:tmerge.c �
				  :3d:clipper.c �
				  :3d:draw.c �
				  :3d:globvars.c �
				  :3d:instance.c �
				  :3d:interp.c �
				  :3d:matrix.c �
				  :3d:points.c �
				  :3d:rod.c �
				  :3d:setup.c �
				  :arch:carbon:SDL_main.c �
				  :arch:ogl:gr.c �
				  :arch:ogl:ogl.c �
				  :arch:sdl:digi.c �
				  :arch:sdl:digi_audio.c �
				  :arch:sdl:digi_mixer.c �
				  :arch:sdl:digi_mixer_music.c �
				  :arch:sdl:event.c �
				  :arch:sdl:gr.c �
				  :arch:sdl:init.c �
				  :arch:sdl:joy.c �
				  :arch:sdl:jukebox.c �
				  :arch:sdl:key.c �
				  :arch:sdl:mouse.c �
				  :arch:sdl:rbaudio.c �
				  :arch:sdl:timer.c �
				  :arch:sdl:window.c �
				  :iff:iff.c �
				  :libmve:decoder16.c �
				  :libmve:decoder8.c �
				  :libmve:mvelib.c �
				  :libmve:mveplay.c �
				  :libmve:mve_audio.c �
				  :main:ai.c �
				  :main:ai2.c �
				  :main:aipath.c �
				  :main:automap.c �
				  :main:bm.c �
				  :main:cntrlcen.c �
				  :main:collide.c �
				  :main:config.c �
				  :main:console.c �
				  :main:controls.c �
				  :main:credits.c �
				  :main:crypt.c �
				  :main:digiobj.c �
				  :main:effects.c �
				  :main:endlevel.c �
				  :main:escort.c �
				  :main:fireball.c �
				  :main:fuelcen.c �
				  :main:fvi.c �
				  :main:game.c �
				  :main:gamecntl.c �
				  :main:gamefont.c �
				  :main:gamemine.c �
				  :main:gamepal.c �
				  :main:gamerend.c �
				  :main:gamesave.c �
				  :main:gameseg.c �
				  :main:gameseq.c �
				  :main:gauges.c �
				  :main:hostage.c �
				  :main:hud.c �
				  :main:inferno.c �
				  :main:kconfig.c �
				  :main:kmatrix.c �
				  :main:laser.c �
				  :main:lighting.c �
				  :main:menu.c �
				  :main:mglobal.c �
				  :main:mission.c �
				  :main:morph.c �
				  :main:movie.c �
				  :main:multi.c �
				  :main:multibot.c �
				  :main:net_ipx.c �
				  :main:net_udp.c �
				  :main:newdemo.c �
				  :main:newmenu.c �
				  :main:object.c �
				  :main:paging.c �
				  :main:physics.c �
				  :main:piggy.c �
				  :main:player.c �
				  :main:playsave.c �
				  :main:polyobj.c �
				  :main:powerup.c �
				  :main:render.c �
				  :main:robot.c �
				  :main:scores.c �
				  :main:segment.c �
				  :main:slew.c �
				  :main:songs.c �
				  :main:state.c �
				  :main:switch.c �
				  :main:terrain.c �
				  :main:texmerge.c �
				  :main:text.c �
				  :main:titles.c �
				  :main:vclip.c �
				  :main:wall.c �
				  :main:weapon.c �
				  :maths:fixc.c �
				  :maths:rand.c �
				  :maths:tables.c �
				  :maths:vecmat.c �
				  :mem:mem.c �
				  :misc:args.c �
				  :misc:dl_list.c �
				  :misc:error.c �
				  :misc:hash.c �
				  :misc:hmp.c �
				  :misc:ignorecase.c �
				  :misc:physfsrwops.c �
				  :misc:physfsx.c �
				  :misc:strio.c �
				  :misc:strutil.c �
				  :texmap:ntmap.c �
				  :texmap:scanline.c �
				  :texmap:tmapflat.c �
				  :texmap:tmapppc.a


### Object Files ###

OpenGLObjects    =  �
				  "{ObjDir}gr.c.x" �
				  "{ObjDir}ogl.c.x"

SDLVideoObjects    =  �
				  "{ObjDir}SDL:gr.c.x"

GeneralObjects    =  �
				  {ObjDir}2dsline.c.x �
				  {ObjDir}bitblt.c.x �
				  {ObjDir}bitmap.c.x �
				  {ObjDir}box.c.x �
				  {ObjDir}canvas.c.x �
				  {ObjDir}circle.c.x �
				  {ObjDir}disc.c.x �
				  {ObjDir}font.c.x �
				  {ObjDir}gpixel.c.x �
				  {ObjDir}line.c.x �
				  {ObjDir}palette.c.x �
				  {ObjDir}pcx.c.x �
				  {ObjDir}pixel.c.x �
				  {ObjDir}poly.c.x �
				  {ObjDir}rect.c.x �
				  {ObjDir}rle.c.x �
				  {ObjDir}scalec.c.x �
				  {ObjDir}tmerge.c.x �
				  {ObjDir}clipper.c.x �
				  {ObjDir}draw.c.x �
				  {ObjDir}globvars.c.x �
				  {ObjDir}instance.c.x �
				  {ObjDir}interp.c.x �
				  {ObjDir}matrix.c.x �
				  {ObjDir}points.c.x �
				  {ObjDir}rod.c.x �
				  {ObjDir}setup.c.x �
				  {ObjDir}SDL_main.c.x �
				  {ObjDir}digi.c.x �
				  {ObjDir}digi_audio.c.x �
				  {ObjDir}digi_mixer.c.x �
				  {ObjDir}digi_mixer_music.c.x �
				  {ObjDir}event.c.x �
				  {ObjDir}init.c.x �
				  {ObjDir}joy.c.x �
				  {ObjDir}jukebox.c.x �
				  {ObjDir}key.c.x �
				  {ObjDir}mouse.c.x �
				  {ObjDir}rbaudio.c.x �
				  {ObjDir}timer.c.x �
				  {ObjDir}window.c.x �
				  {ObjDir}iff.c.x �
				  {ObjDir}decoder16.c.x �
				  {ObjDir}decoder8.c.x �
				  {ObjDir}mvelib.c.x �
				  {ObjDir}mveplay.c.x �
				  {ObjDir}mve_audio.c.x �
				  {ObjDir}ai.c.x �
				  {ObjDir}ai2.c.x �
				  {ObjDir}aipath.c.x �
				  {ObjDir}automap.c.x �
				  {ObjDir}bm.c.x �
				  {ObjDir}cntrlcen.c.x �
				  {ObjDir}collide.c.x �
				  {ObjDir}config.c.x �
				  {ObjDir}console.c.x �
				  {ObjDir}controls.c.x �
				  {ObjDir}credits.c.x �
				  {ObjDir}crypt.c.x �
				  {ObjDir}digiobj.c.x �
				  {ObjDir}effects.c.x �
				  {ObjDir}endlevel.c.x �
				  {ObjDir}escort.c.x �
				  {ObjDir}fireball.c.x �
				  {ObjDir}fuelcen.c.x �
				  {ObjDir}fvi.c.x �
				  {ObjDir}game.c.x �
				  {ObjDir}gamecntl.c.x �
				  {ObjDir}gamefont.c.x �
				  {ObjDir}gamemine.c.x �
				  {ObjDir}gamepal.c.x �
				  {ObjDir}gamerend.c.x �
				  {ObjDir}gamesave.c.x �
				  {ObjDir}gameseg.c.x �
				  {ObjDir}gameseq.c.x �
				  {ObjDir}gauges.c.x �
				  {ObjDir}hostage.c.x �
				  {ObjDir}hud.c.x �
				  {ObjDir}inferno.c.x �
				  {ObjDir}kconfig.c.x �
				  {ObjDir}kmatrix.c.x �
				  {ObjDir}laser.c.x �
				  {ObjDir}lighting.c.x �
				  {ObjDir}menu.c.x �
				  {ObjDir}mglobal.c.x �
				  {ObjDir}mission.c.x �
				  {ObjDir}morph.c.x �
				  {ObjDir}movie.c.x �
#				  {ObjDir}multi.c.x �
#				  {ObjDir}multibot.c.x �
#				  {ObjDir}net_ipx.c.x �
#				  {ObjDir}net_udp.c.x �
				  {ObjDir}newdemo.c.x �
				  {ObjDir}newmenu.c.x �
				  {ObjDir}object.c.x �
				  {ObjDir}paging.c.x �
				  {ObjDir}physics.c.x �
				  {ObjDir}piggy.c.x �
				  {ObjDir}player.c.x �
				  {ObjDir}playsave.c.x �
				  {ObjDir}polyobj.c.x �
				  {ObjDir}powerup.c.x �
				  {ObjDir}render.c.x �
				  {ObjDir}robot.c.x �
				  {ObjDir}scores.c.x �
				  {ObjDir}segment.c.x �
				  {ObjDir}slew.c.x �
				  {ObjDir}songs.c.x �
				  {ObjDir}state.c.x �
				  {ObjDir}switch.c.x �
				  {ObjDir}terrain.c.x �
				  {ObjDir}texmerge.c.x �
				  {ObjDir}text.c.x �
				  {ObjDir}titles.c.x �
				  {ObjDir}vclip.c.x �
				  {ObjDir}wall.c.x �
				  {ObjDir}weapon.c.x �
				  {ObjDir}fixc.c.x �
				  {ObjDir}rand.c.x �
				  {ObjDir}tables.c.x �
				  {ObjDir}vecmat.c.x �
				  {ObjDir}mem.c.x �
				  {ObjDir}args.c.x �
				  {ObjDir}dl_list.c.x �
				  {ObjDir}error.c.x �
				  {ObjDir}hash.c.x �
				  {ObjDir}hmp.c.x �
				  {ObjDir}ignorecase.c.x �
				  {ObjDir}physfsrwops.c.x �
				  {ObjDir}physfsx.c.x �
				  {ObjDir}strio.c.x �
				  {ObjDir}strutil.c.x �
				  {ObjDir}ntmap.c.x �
				  {ObjDir}scanline.c.x �
				  {ObjDir}tmapflat.c.x �
				  {ObjDir}tmapppc.a.x

### Libraries ###

GeneralLibFiles    =	�
					"{SharedLibraries}PhysicsFS" �
					"{SharedLibraries}SDL" �
					"{SharedLibraries}SDL_mixer" �
					"{SharedLibraries}StdCLib" �
#					"{SharedLibraries}CarbonLib" �
					"{SharedLibraries}DialogsLib" �
					"{SharedLibraries}InterfaceLib" �
					"{SharedLibraries}MathLib" �
					"{PPCLibraries}StdCRuntime.o" �
					"{PPCLibraries}PPCCRuntime.o" �
					"{PPCLibraries}PPCToolLibs.o"

OpenGLFiles    =	�
					"{SharedLibraries}OpenGLLibraryStub" �
					"{SharedLibraries}OpenGLUtilityStub"


### Default Rules ###

.a.x  �  .a  {�MondoBuild�}
	{PPCAsm} {depDir}{default}.a -o {targDir}{default}.a.x {PPCAOptions}

.c.x  �  .c  {�MondoBuild�}
	{PPCC} {depDir}{default}.c -o {targDir}{default}.c.x {PPCCOptions}


### Build Rules ###

# Comment out OpenGLObjects and OpenGLFiles for SDL Video build, commment out SDLVideoObjects for OpenGL build
# This should be done for the following line as well as the arguments to PPCLink
D2X  ��  directories {GeneralObjects} {GeneralLibFiles} {�MondoBuild�} {OpenGLObjects} {OpenGLFiles} #{SDLVideoObjects}
	PPCLink �
		-o {Targ} �
		{GeneralObjects} �
#		{SDLVideoObjects} �
		{OpenGLObjects} �
		{GeneralLibFiles} �
		{OpenGLFiles} �
		{Sym-PPC} �
		-mf -d �
		-m main �
		-t 'APPL' �
		-c 'DCT2'
	Rez -a -o {Targ} ":arch:carbon:descent.r"


# This is used to create the directories needed for build
directories �
	if !`Exists obj` ; NewFolder obj ; end
	if !`Exists :obj:SDL` ; NewFolder :obj:SDL ; end


### Required Dependencies ###

{ObjDir}2dsline.c.x	�	:2d:2dsline.c
{ObjDir}bitblt.c.x	�	:2d:bitblt.c
{ObjDir}bitmap.c.x	�	:2d:bitmap.c
{ObjDir}box.c.x	�	:2d:box.c
{ObjDir}canvas.c.x	�	:2d:canvas.c
{ObjDir}circle.c.x	�	:2d:circle.c
{ObjDir}disc.c.x	�	:2d:disc.c
{ObjDir}font.c.x	�	:2d:font.c
{ObjDir}gpixel.c.x	�	:2d:gpixel.c
{ObjDir}line.c.x	�	:2d:line.c
{ObjDir}palette.c.x	�	:2d:palette.c
{ObjDir}pcx.c.x	�	:2d:pcx.c
{ObjDir}pixel.c.x	�	:2d:pixel.c
{ObjDir}poly.c.x	�	:2d:poly.c
{ObjDir}rect.c.x	�	:2d:rect.c
{ObjDir}rle.c.x	�	:2d:rle.c
{ObjDir}scalec.c.x	�	:2d:scalec.c
{ObjDir}tmerge.c.x	�	:2d:tmerge.c
{ObjDir}clipper.c.x	�	:3d:clipper.c
{ObjDir}draw.c.x	�	:3d:draw.c
{ObjDir}globvars.c.x	�	:3d:globvars.c
{ObjDir}instance.c.x	�	:3d:instance.c
{ObjDir}interp.c.x	�	:3d:interp.c
{ObjDir}matrix.c.x	�	:3d:matrix.c
{ObjDir}points.c.x	�	:3d:points.c
{ObjDir}rod.c.x	�	:3d:rod.c
{ObjDir}setup.c.x	�	:3d:setup.c
{ObjDir}SDL_main.c.x	�	:arch:carbon:SDL_main.c
{ObjDir}gr.c.x	�	:arch:ogl:gr.c
{ObjDir}ogl.c.x	�	:arch:ogl:ogl.c
{ObjDir}digi.c.x	�	:arch:sdl:digi.c
{ObjDir}digi_audio.c.x	�	:arch:sdl:digi_audio.c
{ObjDir}digi_mixer.c.x	�	:arch:sdl:digi_mixer.c
{ObjDir}digi_mixer_music.c.x	�	:arch:sdl:digi_mixer_music.c
{ObjDir}event.c.x	�	:arch:sdl:event.c
{ObjDir}SDL:gr.c.x	�	:arch:sdl:gr.c
{ObjDir}init.c.x	�	:arch:sdl:init.c
{ObjDir}joy.c.x	�	:arch:sdl:joy.c
{ObjDir}jukebox.c.x	�	:arch:sdl:jukebox.c
{ObjDir}key.c.x	�	:arch:sdl:key.c
{ObjDir}mouse.c.x	�	:arch:sdl:mouse.c
{ObjDir}rbaudio.c.x	�	:arch:sdl:rbaudio.c
{ObjDir}timer.c.x	�	:arch:sdl:timer.c
{ObjDir}window.c.x	�	:arch:sdl:window.c
{ObjDir}iff.c.x	�	:iff:iff.c
{ObjDir}decoder16.c.x	�	:libmve:decoder16.c
{ObjDir}decoder8.c.x	�	:libmve:decoder8.c
{ObjDir}mvelib.c.x	�	:libmve:mvelib.c
{ObjDir}mveplay.c.x	�	:libmve:mveplay.c
{ObjDir}mve_audio.c.x	�	:libmve:mve_audio.c
{ObjDir}ai.c.x	�	:main:ai.c
{ObjDir}ai2.c.x	�	:main:ai2.c
{ObjDir}aipath.c.x	�	:main:aipath.c
{ObjDir}automap.c.x	�	:main:automap.c
{ObjDir}bm.c.x	�	:main:bm.c
{ObjDir}cntrlcen.c.x	�	:main:cntrlcen.c
{ObjDir}collide.c.x	�	:main:collide.c
{ObjDir}config.c.x	�	:main:config.c
{ObjDir}console.c.x	�	:main:console.c
{ObjDir}controls.c.x	�	:main:controls.c
{ObjDir}credits.c.x	�	:main:credits.c
{ObjDir}crypt.c.x	�	:main:crypt.c
{ObjDir}digiobj.c.x	�	:main:digiobj.c
{ObjDir}effects.c.x	�	:main:effects.c
{ObjDir}endlevel.c.x	�	:main:endlevel.c
{ObjDir}escort.c.x	�	:main:escort.c
{ObjDir}fireball.c.x	�	:main:fireball.c
{ObjDir}fuelcen.c.x	�	:main:fuelcen.c
{ObjDir}fvi.c.x	�	:main:fvi.c
{ObjDir}game.c.x	�	:main:game.c
{ObjDir}gamecntl.c.x	�	:main:gamecntl.c
{ObjDir}gamefont.c.x	�	:main:gamefont.c
{ObjDir}gamemine.c.x	�	:main:gamemine.c
{ObjDir}gamepal.c.x	�	:main:gamepal.c
{ObjDir}gamerend.c.x	�	:main:gamerend.c
{ObjDir}gamesave.c.x	�	:main:gamesave.c
{ObjDir}gameseg.c.x	�	:main:gameseg.c
{ObjDir}gameseq.c.x	�	:main:gameseq.c
{ObjDir}gauges.c.x	�	:main:gauges.c
{ObjDir}hostage.c.x	�	:main:hostage.c
{ObjDir}hud.c.x	�	:main:hud.c
{ObjDir}inferno.c.x	�	:main:inferno.c
{ObjDir}kconfig.c.x	�	:main:kconfig.c
{ObjDir}kmatrix.c.x	�	:main:kmatrix.c
{ObjDir}laser.c.x	�	:main:laser.c
{ObjDir}lighting.c.x	�	:main:lighting.c
{ObjDir}menu.c.x	�	:main:menu.c
{ObjDir}mglobal.c.x	�	:main:mglobal.c
{ObjDir}mission.c.x	�	:main:mission.c
{ObjDir}morph.c.x	�	:main:morph.c
{ObjDir}movie.c.x	�	:main:movie.c
{ObjDir}multi.c.x	�	:main:multi.c
{ObjDir}multibot.c.x	�	:main:multibot.c
{ObjDir}net_ipx.c.x	�	:main:net_ipx.c
{ObjDir}net_udp.c.x	�	:main:net_udp.c
{ObjDir}newdemo.c.x	�	:main:newdemo.c
{ObjDir}newmenu.c.x	�	:main:newmenu.c
{ObjDir}object.c.x	�	:main:object.c
{ObjDir}paging.c.x	�	:main:paging.c
{ObjDir}physics.c.x	�	:main:physics.c
{ObjDir}piggy.c.x	�	:main:piggy.c
{ObjDir}player.c.x	�	:main:player.c
{ObjDir}playsave.c.x	�	:main:playsave.c
{ObjDir}polyobj.c.x	�	:main:polyobj.c
{ObjDir}powerup.c.x	�	:main:powerup.c
{ObjDir}render.c.x	�	:main:render.c
{ObjDir}robot.c.x	�	:main:robot.c
{ObjDir}scores.c.x	�	:main:scores.c
{ObjDir}segment.c.x	�	:main:segment.c
{ObjDir}slew.c.x	�	:main:slew.c
{ObjDir}songs.c.x	�	:main:songs.c
{ObjDir}state.c.x	�	:main:state.c
{ObjDir}switch.c.x	�	:main:switch.c
{ObjDir}terrain.c.x	�	:main:terrain.c
{ObjDir}texmerge.c.x	�	:main:texmerge.c
{ObjDir}text.c.x	�	:main:text.c
{ObjDir}titles.c.x	�	:main:titles.c
{ObjDir}vclip.c.x	�	:main:vclip.c
{ObjDir}wall.c.x	�	:main:wall.c
{ObjDir}weapon.c.x	�	:main:weapon.c
{ObjDir}fixc.c.x	�	:maths:fixc.c
{ObjDir}rand.c.x	�	:maths:rand.c
{ObjDir}tables.c.x	�	:maths:tables.c
{ObjDir}vecmat.c.x	�	:maths:vecmat.c
{ObjDir}mem.c.x	�	:mem:mem.c
{ObjDir}args.c.x	�	:misc:args.c
{ObjDir}dl_list.c.x	�	:misc:dl_list.c
{ObjDir}error.c.x	�	:misc:error.c
{ObjDir}hash.c.x	�	:misc:hash.c
{ObjDir}hmp.c.x	�	:misc:hmp.c
{ObjDir}ignorecase.c.x	�	:misc:ignorecase.c
{ObjDir}physfsrwops.c.x	�	:misc:physfsrwops.c
{ObjDir}physfsx.c.x	�	:misc:physfsx.c
{ObjDir}strio.c.x	�	:misc:strio.c
{ObjDir}strutil.c.x	�	:misc:strutil.c
{ObjDir}ntmap.c.x	�	:texmap:ntmap.c
{ObjDir}scanline.c.x	�	:texmap:scanline.c
{ObjDir}tmapflat.c.x	�	:texmap:tmapflat.c
{ObjDir}tmapppc.a.x	�	:texmap:tmapppc.a

### Optional Dependencies ###
### Build this target to generate "include file" dependencies. ###

Dependencies  �  $OutOfDate
	MakeDepend �
		-append {MAKEFILE} �
		-ignore "{CIncludes}" �
		-objdir "{ObjDir}" �
		-objext .x �
		{Includes} �
		{SrcFiles}

